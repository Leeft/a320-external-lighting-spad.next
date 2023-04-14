#ifndef SPAD_H
#define SPAD_H

#include <CmdMessenger.h>

#define MESSAGING_DELAY 50
#define MESSAGING_START_DELAY 1000

const uint8_t DEFAULT_BRIGHTNESS = 50;

#define PIXEL_PIN 10
#define PIXEL_NUM 23

// CHANNELS
enum : byte
{
  kRequest = 0,    // Request from SPAD.neXt
  kCommand = 1,    // Command to SPAD.neXt
  kEvent = 2,      // Events from SPAD.neXt
  kDebug = 3,      // Debug strings to SPAD.neXt Logfile
  kSimCommand = 4, // Send Event to Simulation
  kData = 5,       // Send Data to Device
  kLED = 6,        // Update LEDs
  kDisplay = 7,    // Update Display
  kInput = 8,      // Update Input Value from Device
  kBrightness = 10,
};

// DEVICE INDEX
enum : byte
{
  virtualPower        = 0,
  switchBeacon        = 1,
  switchRunwayTurnoff = 2,
  switchWing          = 3,
  switchNavLogo       = 4,
  switchStrobe        = 5,
  switchLandingLeft   = 6,
  switchLandingRight  = 7,
  switchNose          = 8,
  ledBrightness       = 9,
};

void setPanelLighting(uint32_t color, uint8_t brightness);

void attachCommandCallbacks();

extern CmdMessenger messenger;

#endif
