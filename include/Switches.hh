#ifndef SWITCHES_H
#define SWITCHES_H

#include <Arduino.h>
#include <stdint.h>

#define PIN_LANDINGLIGHTS_RETRACT_LEFT 2
#define PIN_LANDINGLIGHTS_LEFT 3
#define PIN_LANDINGLIGHTS_RETRACT_RIGHT 4
#define PIN_LANDINGLIGHTS_RIGHT 5
#define PIN_STROBE_ON 6
#define PIN_STROBE_OFF 7
#define PIN_NAV_OFF 8
#define PIN_NAV_2 9
#define PIN_RESERVED_1 14
#define PIN_RESERVED_2 16
#define PIN_NOSE_TAKEOFF A0
#define PIN_NOSE_OFF A1
#define PIN_RUNWAY_TURNOFF A2
#define PIN_BEACON A3
#define PIN_WING A4

void switch_pins_setup();
int read_switch_3_state(int i);
int read_switch_2_state(int i);

#endif