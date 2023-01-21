#include "constants.h"

#ifndef STATES_H
#define STATES_H

enum State{
    SNAKE,
    SYSTEM_INFO,
    MENU,
};

struct StateManager{
    bool has_read = false;
    State state = State::SYSTEM_INFO;
    void check_for_state_change(); 
};

#endif
