#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <iostream>
#include <string.h>
#include "states.h"

#ifndef KARP_OS_INFO
#define KARP_OS_INFO

struct SystemInfo{
    String os_name = "KarpOS";
    String version = "0.2.1";
    String release_date = "21.01.2023";

    void handle_show_info(Adafruit_ST7789 *display,StateManager *state_manager);
    void draw_system_text(Adafruit_ST7789 *display,int offset);
};

#endif
