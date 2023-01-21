#include "constants.h"
#include "states.h"
#include "Arduino.h"

void StateManager::check_for_state_change(){

    if (!digitalRead(pMENU)){
        if (!has_read){
            state = State::MENU;
            // if (state == State::SNAKE){state = State::SYSTEM_INFO;}
            // else if (state == State::SYSTEM_INFO){state = State::SNAKE;}
            has_read=true;
        }
    }
    else{has_read=false;}
}