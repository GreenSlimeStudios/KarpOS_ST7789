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
#include <Adafruit_ST7789.h>

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library. 

Adafruit_ST7789 display = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

SnakeGame snake_game = SnakeGame();
SystemInfo system_info = SystemInfo();
StateManager state_manager = StateManager();
Menu menu = Menu(&state_manager, &display);

void setup() {
  Serial.begin(921600);


  display.init(240, 240);           // Init ST7789 240x240
  display.setRotation(2);
  display.fillScreen(ST77XX_BLACK);

  // display.drawPixel(140,140,ST77XX_RED);
  // display.drawPixel(140,141,ST77XX_BLUE);
  // for(;;){}

  pinMode(pUP,INPUT_PULLUP);
  pinMode(pDOWN,INPUT_PULLUP);
  pinMode(pLEFT,INPUT_PULLUP);
  pinMode(pRIGHT,INPUT_PULLUP);
  pinMode(pMENU,INPUT_PULLUP);
  pinMode(pINTER,INPUT_PULLUP);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  // if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
  //   Serial.println(F("SSD1306 allocation failed"));
  //   for(;;); // Don't proceed, loop forever
  // }
  // display.clearDisplay();
}

void loop(){
  // display.clearDisplay();
  state_manager.check_for_state_change();
  Serial.println(state_manager.state);
  if (state_manager.state == State::MENU){
    menu.handle_menu();
  }
  if (state_manager.state == State::SNAKE){
    snake_game.handle_snake_game(&display);
  }
  if (state_manager.state == State::SYSTEM_INFO){
    system_info.handle_show_info(&display,&state_manager);
    display.fillScreen(ST77XX_BLACK);
    // display.display();
  }
  // delay(2000);
}