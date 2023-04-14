#ifndef STATE_H
#define STATE_H

struct SerialDeviceState
{
  //unsigned long last_touch = 0;
  bool power = false;
  //bool display_static = false;
  bool configured = false;
  bool debug = true;
};

#endif