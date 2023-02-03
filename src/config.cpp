#include "config.h"
#include "sd.h"
#include "SD.h"

Config::Config(MSD *newsd)
{
   sd = newsd;
}

void Config::saveToSD(fs::FS &fs)
{
   std::string msg = "BRIGHTNES:";
   msg += std::to_string(brightnes);
   sd->writeFile(fs, "/config/config.txt", msg.c_str());

   msg = "\nORIENTATION:";
   msg += std::to_string(orientation);
   sd->appendFile(fs, "/config/config.txt", msg.c_str());
}
void Config::loadFromSD(fs::FS &fs)
{
   Serial.println("Reading config file: /config/config.txt");

   File file = fs.open("/config/config.txt");
   if (!file)
   {
      Serial.println("Failed to open file for reading");
      return;
   }
   Serial.println();
   // Serial.print("Read from file: ");
   while (file.available())
   {
      Serial.print(file.read());
   }
   file.close();
}