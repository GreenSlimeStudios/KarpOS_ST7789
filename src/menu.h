#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <constants.h>
#include <states.h>

#ifndef MENU_H
#define MENU_H

enum MenuActions{
    NOTHIN,
    MODIFY,
    ACCEPT,
};

struct Menu{
    StateManager *state_manager;
    Adafruit_ST7789 *display;
    int index = 0;
    Menu(StateManager *sm, Adafruit_ST7789 *d);
    MenuActions manage_input();
    void manage_state();
    void handle_menu();
    void draw_menu();
};


#endif
