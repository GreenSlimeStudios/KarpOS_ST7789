#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <iostream>
#include "snake.h"
#include "karp_os_info.h"
#include "constants.h"
#include "states.h"
#include "menu.h"
#include "sd.h"
#include "config.h"
#include "SD.h"
#include <Adafruit_ST7789.h>

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library.

Adafruit_ST7789 display = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);
SnakeGame snake_game = SnakeGame();
SystemInfo system_info = SystemInfo();
StateManager state_manager = StateManager();
Menu menu = Menu(&state_manager, &display);
MSD sd = MSD();
Config config = Config(&sd);

void setup()
{
  Serial.begin(921600);

  display.init(240, 240); // Init ST7789 240x240
  display.setRotation(2);
  display.fillScreen(ST77XX_BLACK);

  if (!sd.init(SD, SD_CS))
  {
    display.println("SD CARD ERROR");
    delay(3000);
    for (;;)
    {
    }
  }
  // sd.readFile(SD,"/test.txt");
  // config.saveToSD(SD);
  sd.readFile(SD, "/config/config.txt");

  pinMode(pUP, INPUT_PULLUP);
  pinMode(pDOWN, INPUT_PULLUP);
  pinMode(pLEFT, INPUT_PULLUP);
  pinMode(pRIGHT, INPUT_PULLUP);
  pinMode(pMENU, INPUT_PULLUP);
  pinMode(pINTER, INPUT_PULLUP);
}

void loop()
{
  // display.clearDisplay();
  state_manager.check_for_state_change();

  if (state_manager.state == State::MENU)
  {
    menu.handle_menu();
  }
  if (state_manager.state == State::SNAKE)
  {
    snake_game.handle_snake_game(&display);
  }
  if (state_manager.state == State::SYSTEM_INFO)
  {
    system_info.handle_show_info(&display, &state_manager);
    display.fillScreen(ST77XX_BLACK);
    // display.display();
  }
}