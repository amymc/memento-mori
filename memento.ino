#include <Bridge.h>
#include <HttpClient.h>
#include <ArduinoJson.h>
#include <string>
#include <vector>
#include <sstream>

String grimReaper =  "             ___\n"
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

void setup()
{
  Serial.begin(19200);
}

void loop()
{
  if (Serial.available() > 0) {
    String info = Serial.readString();
    String strs[2];
    int StringCount = 0;

    while (info.length() > 0) {
      int index = info.indexOf(' ');
      if(index == -1) {
        strs[StringCount++] = info;
        info = '\0';
      } else {
        strs[StringCount++] = info.substring(0, index);
        info = info.substring(index+1);
      }
    }

    String years = strs[1] + " years";
    if (strs[1] == "1"){
      years = strs[1] + " year";
    }

    String expiration = String("    You are due to expire in \n          "+ years + "." );

    Serial.println("\n********************************");
    Serial.println(expiration);
    Serial.print(grimReaper);
    Serial.println("Enjoy it " + strs[0] + ".");
    Serial.println("I'll be waiting for you.");
    Serial.println("********************************");
    Serial.println("********************************");

  }
}
