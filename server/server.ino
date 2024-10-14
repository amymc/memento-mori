#include <string>
#include <ArduinoJson.h>
#include <queue>
#include <ESP8266WebServer.h>
#include "secrets.h"  // add WLAN Credentials in here.

ESP8266WebServer server(80);

String grimReaper = "             ___\n"
                    "            /   \\\\\n"
                    "       /\\\\ | . . \\\\\n"
                    "     ////\\\\|     ||\n"
                    "   ////   \\\\ ___//_\n"
                    "  ///      \\\\      \\\n"
                    " ///       |\\\\      \\\n"
                    "//         | \\\\   \\  \\\n"
                    "/          |  \\\\   \\  \\\n"
                    "           |   \\\\  /  /\n"
                    "           |    \\ /  /\n"
                    "           |     \\\\ /\n"
                    "           |      \\\\|\n"
                    "           |       \\\\\n"
                    "           |________|\\\n";

class Participant {
  public:
    String name; 
    String expectancy;
};

Participant participant;
std::queue<Participant> participantQueue;

void handleForm() {
  DynamicJsonDocument doc(1024);

  String input = server.arg("plain");
  deserializeJson(doc, input);

  const String name = doc["name"];
  const String expectancy = doc["expectancy"];

  participantQueue.push({ name: name, expectancy: expectancy });

  server.send(200, "text/plain", "success");
}

void printMemento(String name, String expectancy) {
  String years = expectancy + " years";
  if (expectancy == "1"){
    years = expectancy + " year";
  }

  String expiration = String("    You are due to expire in \n          " + years + ".");

  Serial.println("\n********************************");
  Serial.println(expiration);
  Serial.print(grimReaper);
  Serial.println("Enjoy it " + name + ".");
  Serial.println("I'll be waiting for you.");
  Serial.println("********************************");
  Serial.println("********************************");
}

void setup()
{
  // Serial.begin(19200);
  Serial.begin(9600);

  delay(10000);
  Serial.printf("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/participants", HTTP_POST, handleForm);
  server.enableCORS(true);
  server.begin();
}

void loop()
{
  server.handleClient();

  while(!participantQueue.empty()) {
    participant = participantQueue.front();
    printMemento(participant.name, participant.expectancy);
    participantQueue.pop();
  }
}
