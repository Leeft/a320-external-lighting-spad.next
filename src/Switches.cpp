#include <Arduino.h>

#include "SPAD.hh"
#include "Switches.hh"

const int switch_2_pins[3] = {
  PIN_BEACON,
  PIN_RUNWAY_TURNOFF,
  PIN_WING,
};

const int switch_3_pins[5][2] = {
  {PIN_NAV_OFF,PIN_NAV_2},
  {PIN_STROBE_OFF,PIN_STROBE_ON},
  {PIN_LANDINGLIGHTS_RETRACT_LEFT, PIN_LANDINGLIGHTS_LEFT},
  {PIN_LANDINGLIGHTS_RETRACT_RIGHT, PIN_LANDINGLIGHTS_RIGHT},
  {PIN_NOSE_OFF,PIN_NOSE_TAKEOFF},
};

void switch_pins_setup ()
{
  for (int i = 0; i < 3; i++) {
    pinMode(switch_2_pins[i], INPUT_PULLUP);
  }  

  for (int i = 0; i < 5; i++) {
    pinMode(switch_3_pins[i][0], INPUT_PULLUP);
    pinMode(switch_3_pins[i][1], INPUT_PULLUP);
  }  
}

int read_switch_2_state ( int i ) {
    return( !digitalRead(switch_2_pins[i]) );
}

int read_switch_3_state ( int i ) {
  int val1 = !digitalRead( switch_3_pins[i][0] );
  int val2 = !digitalRead( switch_3_pins[i][1] );
  int state = ( ( val1 * 2 ) + val2 );
  if ( state == 2 ) {
    state = 0;
  } else if ( state == 0 ) {
    state = 2;
  }
  return( state );
}

// EOF