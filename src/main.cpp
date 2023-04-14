#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "main.hh"
#include "SPAD.hh"
#include "Switches.hh"
#include "SerialDeviceState.hh"

extern CmdMessenger messenger;
extern SerialDeviceState state;
extern Adafruit_NeoPixel pixels;

int switch_2_states[3] = {0, 0, 0};
int switch_3_states[5] = {0, 0, 0, 0, 0};

void force_switch_states ()
{
  for (int i = 0; i < 3; i++) {
    switch_2_states[i] = -1;
  }

  for (int i = 0; i < 5; i++) {
    switch_3_states[i] = -1;
  }
}

void read_switch_states ()
{
  update_switch_state( &switch_2_states[0], read_switch_2_state( 0 ), switchBeacon );
  update_switch_state( &switch_2_states[1], read_switch_2_state( 1 ), switchRunwayTurnoff );
  update_switch_state( &switch_2_states[2], read_switch_2_state( 2 ), switchWing );

  update_switch_state( &switch_3_states[0], read_switch_3_state( 0 ), switchNavLogo );
  update_switch_state( &switch_3_states[1], read_switch_3_state( 1 ), switchStrobe );
  update_switch_state( &switch_3_states[2], read_switch_3_state( 2 ), switchLandingLeft );
  update_switch_state( &switch_3_states[3], read_switch_3_state( 3 ), switchLandingRight );
  update_switch_state( &switch_3_states[4], read_switch_3_state( 4 ), switchNose );
}

void update_switch_state( int *state, int newState, byte deviceIndex )
{
  if ( newState != *state ) {
    *state = newState;
    messenger.sendCmdStart(kInput);
    messenger.sendCmdArg(deviceIndex);
    messenger.sendCmdArg(newState);
    messenger.sendCmdEnd();
  }
}

void setup()
{
  switch_pins_setup();

  Serial.begin(115200);

  pixels.begin();

  attachCommandCallbacks();

  setPanelLighting( 0x443000, 40 );
}

void loop()
{
  messenger.feedinSerialData();

  if (state.configured)
  {
    read_switch_states();

  }

  delay( 20 );
}

// EOF