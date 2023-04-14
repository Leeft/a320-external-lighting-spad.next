#ifndef MAIN_H
#define MAIN_H

#include <Arduino.h>

void force_switch_states();
void read_switch_states();
void update_switch_state(int *state, int newState, byte deviceIndex);

#endif