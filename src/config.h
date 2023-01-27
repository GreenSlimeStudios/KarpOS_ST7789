#include "sd.h"
#include "SD.h"

#ifndef CONFIG_H
#define CONFIG_H

struct Config{
    MSD* sd;
    int brightnes = 255;
    int orientation = 2;

    Config(MSD* newsd);
    void loadFromSD();
    void saveToSD(fs::FS &fs);
};



#endif