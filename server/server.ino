#include <string>
#include <ArduinoJson.h>
// #include <ESP8266WiFi.h>
// #include <WiFiClient.h>
#include <ESP8266WebServer.h>
// #include <ESP8266mDNS.h>

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

int handleForm() {
  server.send(200, "text/plain", "success message");
 
  DynamicJsonDocument doc(1024);

  String input = server.arg("plain");
  deserializeJson(doc, input);

  const String name = doc["name"];
  const String expectancy = doc["expectancy"];
  return printMemento(name, expectancy);
}

int printMemento(String name, String expectancy) {
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

  return 0;
}

// void handleListFiles() {
//   Serial.println("list files");
//   server.sendHeader("Cache-Control", "no-cache");
//   server.send(200, "text/javascript; charset=utf-8", "result");
// }  // handleListFiles()

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

  // server.on("/$list", HTTP_GET, handleListFiles);
  server.on("/participants", HTTP_POST, handleForm);

  server.enableCORS(true);

  // server.on("/$participants", HTTP_POST, handleForm, handleForm);
  // server.on("/participants", []() {
  //   server.send(200, "text/plain", "success result");
  // });

  server.begin();
}

void loop()
{
  server.handleClient();
  //   while (!Serial) {
  //   // wait for serial port to connect. Needed for native USB
  // }
  // if (Serial.available() > 0)
  // {

  //   String info = Serial.readString();
  //   String strs[2];
  //   int StringCount = 0;

  //   int index = info.indexOf(' ');
  //   strs[0] = info.substring(0, index);
  //   strs[1] = info.substring(index + 1);

  //   String years = strs[1] + " years";
  //   if (strs[1] == "1")
  //   {
  //     years = strs[1] + " year";
  //   }

  //   String expiration = String("    You are due to expire in \n          " + years + ".");

  //   Serial.println("\n********************************");
  //   Serial.println(expiration);
  //   Serial.print(grimReaper);
  //   Serial.println("Enjoy it " + strs[0] + ".");
  //   Serial.println("I'll be waiting for you.");
  //   Serial.println("********************************");
  //   Serial.println("********************************");
  //}
}
