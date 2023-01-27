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