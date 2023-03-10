#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <constants.h>
#include <menu.h>
#include <states.h>

uint8_t up_state = 0;
uint8_t up_last_state = 0;
uint8_t down_state = 0;
uint8_t down_last_state = 0;

bool up = false;
bool down = false;

Menu::Menu(StateManager *sm, Adafruit_ST7789 *d)
{
    state_manager = sm;
    display = d;
}
bool is_up = false;
bool is_down = false;

// bool get_button(int pin){
//     if (!digitalRead(pin)){
//         while (!digitalRead(pin)){}
//         return true;
//     }
//     return false;
// }

MenuActions Menu::manage_input()
{
    if (!digitalRead(pINTER))
    {
        return MenuActions::ACCEPT;
    }
    up_state = digitalRead(pUP);
    if (up_state != up_last_state)
    {
        if (up_state == LOW)
        {
            up = true;
        }
        up_last_state = up_state;
    }
    down_state = digitalRead(pDOWN);
    if (down_state != down_last_state)
    {
        if (down_state == LOW)
        {
            down = true;
        }
        down_last_state = down_state;
    }
    delay(10);
    if (up)
    {
        up = false;
        down = false;
        if (index > 0)
        {
            index_prev = index;
            index--;
            return MenuActions::MODIFY;
        };
    };
    if (down)
    {
        up = false;
        down = false;
        if (index < 9)
        {
            index_prev = index;
            index++;
            return MenuActions::MODIFY;
        }
    };
    return MenuActions::NOTHIN;
}
void Menu::manage_state()
{
    switch (index)
    {
    case 0:
        (*state_manager).state = State::SNAKE;
        break;
    case 1:
        (*state_manager).state = State::SYSTEM_INFO;
        break;

    default:
        break;
    }
}
void Menu::handle_menu()
{
    display->fillScreen(ST77XX_BLACK);
    draw_menu();
    for (;;)
    {
        // if (manage_input() == MenuActions::MODIFY){
        //     Serial.print("MODIFICATION: "); Serial.println(index);
        // }
        MenuActions result = manage_input();
        if (result == MenuActions::ACCEPT)
        {
            manage_state();
            display->fillScreen(ST77XX_BLACK);
            // display->display();
            return;
        }
        if (result == MenuActions::MODIFY)
        {
            draw_menu();
        }
    }
}
void Menu::draw_menu()
{
    display->setCursor(10, 10);
    display->setTextSize(2);
    display->fillRect(0, 10 + index * 16 + index * 5, 20, 16, ST77XX_BLACK);
    display->fillRect(0, 0, 10, 240, ST77XX_BLACK);

    for (uint8_t i = 0; i < 10; i++)
    {
        if (index == i)
        {
            display->setTextColor(ST77XX_WHITE, ST77XX_MAGENTA);
            display->setCursor(20, display->getCursorY());
            display->fillCircle(10, display->getCursorY() + 8, 4, ST77XX_MAGENTA);
        }
        else
        {
            display->setTextColor(ST77XX_WHITE, ST77XX_BLACK);
        }
        String name;
        switch (i)
        {
        case 0:
            name = "snake";
            break;
        case 1:
            name = "system info";
            break;
        default:
            name = "null";
            break;
        };
        display->print(name);
        if (index != i)
        {
            display->println(" ");
        }
        else
        {
            display->println();
        }
        display->setCursor(10, display->getCursorY() + 5);
    }
    //    display->display();
}
