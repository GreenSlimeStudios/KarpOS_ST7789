#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <iostream>
#include <vector>

#ifndef SNAKE_H
#define SNAKE_H

enum Direction{
  UP,
  DOWN,
  LEFT,
  RIGHT,
};
struct Part{
  int x;
  int y;
};

// void render_part(int x, int y){
//   display.fillRoundRect(display.width()/2 + x*4, display.height()/2 + y*4, 4, 4, 2, SSD1306_WHITE);
// }
// void de_render_part(int x, int y){
//   display.fillRoundRect(display.width()/2 + x*4, display.height()/2 + y*4, 4, 4, 2, SSD1306_BLACK);
// }

struct Snake{
  Direction dir = Direction::RIGHT; 
  std::vector<Part> parts = {Part{x:0,y:0},Part{x:0,y:0},Part{x:0,y:0}};
  bool is_alive = true;

  void render_snake(Adafruit_ST7789 *display);
  void wrap_if_needed();
  void check_collision();
  void move(Adafruit_ST7789 *display);
  void check_input();
  void await_restart(Adafruit_ST7789 *display);
  void animate_death(Adafruit_ST7789 *display);
};

struct Berry{
  int x;
  int y;
  bool is_alive;
   Berry(int x, int y);
  void render(Adafruit_ST7789 *display);
};

// Snake snake = Snake();
// Berry berry = Berry(
//   random(-64/8,64/8),
//   random(-32/8,32/8)
// );

struct SnakeGame{
    Snake snake = Snake();
    Berry berry = Berry(
      random(-64/8,64/8),
      random(-32/8,32/8)
    );

    public: void handle_snake_game(Adafruit_ST7789 *display);
}; 

#endif
