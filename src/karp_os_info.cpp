#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include "karp_os_info.h"
#include "constants.h"
#include "states.h"

void SystemInfo::handle_show_info(Adafruit_ST7789 *display, StateManager *state_manager)
{
  display->setTextColor(ST77XX_WHITE);
  display->fillScreen(ST77XX_BLACK);
  double x = -2.5 + 20 * 2.5 * 2 / SCREEN_WIDTH;
  display->drawCircle(240 / 4, 50 - 30, 10, ST77XX_WHITE);
  display->drawCircle(239 - 240 / 4, 50 - 30, 10, ST77XX_WHITE);
  for (int i = 20; i < SCREEN_WIDTH - 20; ++i)
  {
    x += 2.5 * 2 / SCREEN_WIDTH;
    double y = -(abs(x) * 2 - 3) * (abs(x) * 2 - 2) * (abs(x) * 2 - 4) * (sqrt(abs(x) * 2) * abs(x) / 12);
    double scaled_y = 105 - ((y * SCREEN_HEIGHT / 4) + SCREEN_HEIGHT / 4);
    display->drawPixel(i, int(scaled_y), ST77XX_WHITE);
    // display->display();
    state_manager->check_for_state_change();
    if ((*state_manager).state != State::SYSTEM_INFO)
      return;
  }
  // for (int offset=-16;offset<240;offset+=4){
  //   display->fillScreen(ST77XX_BLACK);
  //   x = -2.5;
  //   for (int i=0;i<SCREEN_WIDTH;++i){
  //     x += 2.5*2/SCREEN_WIDTH;
  //     double y = -(abs(x)*2-3)*(abs(x)*2-2)*(abs(x)*2-4)*(sqrt(abs(x)*2)*abs(x)/12);
  //     double scaled_y = 239-((y*SCREEN_HEIGHT/4)+SCREEN_HEIGHT/4);
  //     display->drawPixel(i,int(scaled_y)-offset,ST77XX_WHITE);
  //     // display->display();
  //   state_manager->check_for_state_change();
  //   if ((*state_manager).state != State::SYSTEM_INFO) return;
  //   }

  //   display->drawCircle(240/4,150-offset,10,ST77XX_WHITE);
  //   display->drawCircle(240-240/4,150-offset,10,ST77XX_WHITE);
  //   draw_system_text(display,offset);
  //   // display->display();
  //   delay(30);
  // }

  display->drawLine(0, 65, 239, 65, ST77XX_WHITE);
  draw_system_text(display, 240 - 75);
  for (;;)
  {
    state_manager->check_for_state_change();
    if ((*state_manager).state != State::SYSTEM_INFO)
      return;
  }
}

void addInfo(String name, String val, Adafruit_ST7789 *display)
{
  display->print(name);
  display->println(val);
  display->setCursor(0, display->getCursorY() + 2);
}

void SystemInfo::draw_system_text(Adafruit_ST7789 *display, int offset)
{
  display->setTextSize(1);
  display->setCursor(0, 240 - offset);
  addInfo("OS NAME: ", os_name, display);
  addInfo("VERSION: ", version, display);
  addInfo("REL. DATE: ", release_date, display);
}
