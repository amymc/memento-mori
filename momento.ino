#include <Bridge.h>
#include <HttpClient.h>
#include <ArduinoJson.h>

int age = 35;
char sex[ ] ="f";
String name = "amy";

String partOne ="               ___                \n"
"              /   \\\\              \n";  
String partTwo = String("         /\\\\ | . . \\\\      Enjoy it " + name + "\n");   
String partThree ="       ////\\\\|     ||      I'll be waiting for you.\n"
"     ////   \\\\ ___//\\             \n"
"    ///      \\\\      \\      \n"
"   ///       |\\\\      |     \n"
"  //         | \\\\  \\   \\    \n"
"  /          |  \\\\  \\   \\   \n"
"             |   \\\\ /   /   \n"
"             |     \/   /    \n"
"             |     \\\\/|     \n"
"             |      \\\\|     \n"
"             |       \\\\     \n"
"             |_________\\ ";

void setup() {
  Serial.begin(115200);
  StaticJsonBuffer<200> jsonBuffer;
  HttpClient client;
  client.get("http://api.population.io:80/1.0/life-expectancy/remaining/female/Ireland/2018-12-09/35y6m/");

//while (client.available()) {
//  char received = Serial.read();  
//}

// char json[] = "{\"sensor\":\"gps\",\"time\":1351824120,\"data\":[48.756080,2.302038]}";
JsonObject& root = jsonBuffer.parseObject(client);

//Serial.println(root["sensor"].as<char*>());
const char* sensor = root["country"];
Serial.println(sensor);

Serial.print(partOne); 
Serial.print(partTwo); 
Serial.print(partThree);

}

void loop() {

}
