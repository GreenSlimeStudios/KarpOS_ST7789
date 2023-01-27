#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <iostream>
#include <vector>
#include "snake.h"
#include "constants.h"

Berry::Berry(int x, int y)
{
  x = x;
  y = y;
  is_alive = true;
}
void Berry::render(Adafruit_ST7789 *display)
{
  display->fillRoundRect(display->width() / 2 + x * 6, display->height() / 2 + y * 6, 6, 6, 2, ST77XX_RED);
}

void render_part(int x, int y, Adafruit_ST7789 *display)
{
  display->fillRoundRect(display->width() / 2 + x * 6, display->height() / 2 + y * 6, 6, 6, 2, ST77XX_WHITE);
}
void de_render_part(int x, int y, Adafruit_ST7789 *display)
{
  display->fillRoundRect(display->width() / 2 + x * 6, display->height() / 2 + y * 6, 6, 6, 2, ST77XX_BLACK);
}

void Snake::render_snake(Adafruit_ST7789 *display)
{
  // display.clearDisplay();
  for (int i = 0; i < parts.size(); ++i)
  {
    render_part(parts[i].x, parts[i].y, display);
  }
  // display->display();
}
void Snake::wrap_if_needed()
{
  if (parts[0].x > 240 / 12 - 1)
    parts[0].x = -240 / 12;
  if (parts[0].x < -240 / 12)
    parts[0].x = 240 / 12;
  if (parts[0].y > 240 / 12 - 1)
    parts[0].y = -240 / 12;
  if (parts[0].y < -240 / 12)
    parts[0].y = 240 / 12;
}

void Snake::check_collision()
{
  for (int i = 1; i < parts.size(); ++i)
  {
    if (parts[0].x == parts[i].x && parts[0].y == parts[i].y)
    {
      is_alive = false;
    }
  }
}

void Snake::move(Adafruit_ST7789 *display)
{
  de_render_part(parts[parts.size() - 1].x, parts[parts.size() - 1].y, display);
  for (int i = parts.size() - 1; i >= 1; --i)
  {
    parts[i].x = parts[i - 1].x;
    parts[i].y = parts[i - 1].y;
  }
  if (dir == Direction::UP)
    parts[0].y--;
  if (dir == Direction::DOWN)
    parts[0].y++;
  if (dir == Direction::LEFT)
    parts[0].x--;
  if (dir == Direction::RIGHT)
    parts[0].x++;
  wrap_if_needed();
}

void Snake::check_input()
{
  if (!digitalRead(pUP) && dir != Direction::DOWN)
    dir = Direction::UP;
  if (!digitalRead(pDOWN) && dir != Direction::UP)
    dir = Direction::DOWN;
  if (!digitalRead(pLEFT) && dir != Direction::RIGHT)
    dir = Direction::LEFT;
  if (!digitalRead(pRIGHT) && dir != Direction::LEFT)
    dir = Direction::RIGHT;
}

void Snake::await_restart(Adafruit_ST7789 *display)
{
  if (!digitalRead(pUP) || !digitalRead(pDOWN) || !digitalRead(pLEFT) || !digitalRead(pRIGHT))
  {
    dir = Direction::RIGHT;
    parts = {Part{x : 0, y : 0}, Part{x : 0, y : 0}, Part{x : 0, y : 0}};
    is_alive = true;
    display->fillScreen(ST77XX_BLACK);
  }
}
void Snake::animate_death(Adafruit_ST7789 *display)
{
  for (int i = 0; i < 3; ++i)
  {
    for (int y = 0; y < parts.size(); ++y)
    {
      de_render_part(parts[y].x, parts[y].y, display);
    }
    // display->display();
    delay(100);
    for (int y = 0; y < parts.size(); ++y)
    {
      render_part(parts[y].x, parts[y].y, display);
    }
    // display->display();
    delay(100);
  }
  for (int i = parts.size() - 1; i >= 0; --i)
  {
    de_render_part(parts[i].x, parts[i].y, display);
    // display->display();
    delay(20);
  }
}
int random(int min, int max) // range : [min, max]
{
  static bool first = true;
  if (first)
  {
    srand(time(NULL)); // seeding for the first time only!
    first = false;
  }
  return min + rand() % (max + 1 - min);
}

void end_game(Adafruit_ST7789 *display, Snake *snake)
{
  (*snake).animate_death(display);
  display->fillScreen(ST77XX_BLACK);
  display->setTextSize(1);
  display->setTextColor(ST77XX_WHITE);
  display->setCursor(0, 10);
  display->println(F("DEATH"));
  display->setTextSize(2);
  display->setTextColor(ST77XX_BLACK, ST77XX_WHITE);
  display->print(F("score "));
  display->println((*snake).parts.size());
  display->setTextSize(1);
  display->setTextColor(ST77XX_WHITE);
  display->print(F("press any button to restart"));
  // display->display();
  delay(500);
}

void handle_berry(Adafruit_ST7789 *display, Berry *berry, Snake *snake)
{
  for (int i = 0; i < (*snake).parts.size(); ++i)
  {
    if ((*snake).parts[i].x == (*berry).x && (*snake).parts[i].y == (*berry).y)
    {
      (*berry).is_alive = false;
      Serial.println("BERRY EATEN");
    }
  }
  if ((*berry).is_alive == false)
  {
    // de_render_part((*berry).x,(*berry).y,display);
    for (int i = 0; i < 2; ++i)
    {
      (*snake).parts.push_back((*snake).parts[(*snake).parts.size() - 1]);
    }
    (*berry).x = random(-120 / 8, 120 / 8);
    (*berry).y = random(-120 / 8, 120 / 8);
    (*berry).is_alive = true;
    (*berry).render(display);
  }
}

void SnakeGame::handle_snake_game(Adafruit_ST7789 *display)
{
  if (snake.is_alive)
  {
    berry.render(display);
    // Serial.print(berry.x); Serial.print(" "); Serial.println(berry.y);
    snake.check_input();
    snake.move(display);
    snake.render_snake(display);
    snake.check_collision();
    if (snake.is_alive == false)
      end_game(display, &snake);
    handle_berry(display, &berry, &snake);
    delay(100);
  }
  else
  {
    snake.await_restart(display);
  }
}
