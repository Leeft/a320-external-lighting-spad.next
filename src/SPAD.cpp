#include <CmdMessenger.h>
#include <Arduino.h>
#include <float.h>
#include <Adafruit_NeoPixel.h>

#include "main.hh"
#include "SPAD.hh"
#include "SerialDeviceState.hh"

uint8_t globalBrightness = DEFAULT_BRIGHTNESS;
uint32_t globalColor = 0;
Adafruit_NeoPixel pixels( PIXEL_NUM, PIXEL_PIN, NEO_RGB + NEO_KHZ800 );

CmdMessenger messenger(Serial);

extern struct SerialDeviceState state;

void setPanelLighting( uint32_t color, uint8_t brightness )
{
  for ( int i = 0; i < PIXEL_NUM; i++ ) {
    pixels.setPixelColor(i, color);
  }

  pixels.setBrightness( brightness );
  pixels.show();
}

template <class T>
void sendCmdDebugMsg(uint8_t command, uint8_t idx, T arg)
{
}

// ------------------  C A L L B A C K S -----------------------

void onUnknownCommand()
{
    //uint8_t cmd = messenger.commandID();
    char *szRequest = messenger.readStringArg();

    // if (state.debug) {
    //     disp.printDebug(msg + cmd);
    // }

    String msg = F("UNKNOWN COMMAND: ");
    messenger.sendCmd(kDebug, msg + szRequest );
}

void onIdentifyRequest()
{
  char *szRequest = messenger.readStringArg();

  if (strcmp(szRequest, "INIT") == 0)
  {
    state.power = false;
    state.configured = false;

    messenger.sendCmdStart(kRequest);
    messenger.sendCmdArg(F("SPAD"));
    messenger.sendCmdArg(F("{D5B645DC-020A-4BA2-9C12-5A485DA3F039}"));
    messenger.sendCmdArg(F("Airbus External Lighting"));
    messenger.sendCmdArg(2); // SerialVersion
    messenger.sendCmdArg(F("0.1")); // DeviceVersion
    messenger.sendCmdArg(F("ALLOWLOCAL=1"));
    messenger.sendCmdArg(F("PROFILE_RO=0"));
    messenger.sendCmdEnd();
    return;
  }

  if (strcmp(szRequest, "PING") == 0)
  {
    messenger.sendCmdStart(kRequest);
    messenger.sendCmdArg(F("PONG"));
    messenger.sendCmdArg(messenger.readInt32Arg());
    messenger.sendCmdEnd();
    return;
  }

  if (strcmp(szRequest, "CONFIG") == 0) {
    messenger.sendCmdStart(kRequest);
    messenger.sendCmdArg("OPTION");
    messenger.sendCmdArg("ISGENERIC=1");
    messenger.sendCmdArg("PAGESUPPORT=1");
    messenger.sendCmdArg("VPSUPPORT=1");
    messenger.sendCmdArg("NO_DISPLAY_CLEAR=1");
    messenger.sendCmdArg("NO_LED_CLEAR=1");
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kRequest);
    messenger.sendCmdArg(F("COLORSET"));
    messenger.sendCmdArg(F("PanelTint"));
    messenger.sendCmdArg(F("White=#FFFFFF"));
    messenger.sendCmdArg(F("Yellow=#FFFF70"));
    messenger.sendCmdArg(F("Orange=#FFA030"));
    messenger.sendCmdArg(F("Blue=#6060FF"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kRequest);
    messenger.sendCmdArg(F("INPUT"));
    messenger.sendCmdArg(virtualPower);
    messenger.sendCmdArg(F("CONFIGURE_PANEL_STATUS"));
    messenger.sendCmdArg(F("SYSTEM"));
    messenger.sendCmdArg(F("SPAD_VIRTUAL_POWER"));
    messenger.sendCmdArg(F("UI_TYPE=3"));
    messenger.sendCmdArg(F("CUSTOM_TYPE=POWER"));
    messenger.sendCmdArg(F("PANEL=Switches"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kRequest);
    messenger.sendCmdArg(F("INPUT"));
    messenger.sendCmdArg(switchStrobe);
    messenger.sendCmdArg(F("STROBE"));
    messenger.sendCmdArg(F("SWITCH3"));
    messenger.sendCmdArg(F(""));
    messenger.sendCmdArg(F("POS_NAMES=OFF#ON#AUTO"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kRequest);
    messenger.sendCmdArg(F("INPUT"));
    messenger.sendCmdArg(switchBeacon);
    messenger.sendCmdArg(F("BEACON"));
    messenger.sendCmdArg(F("SWITCH"));
    messenger.sendCmdArg(F(""));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kRequest);
    messenger.sendCmdArg(F("INPUT"));
    messenger.sendCmdArg(switchWing);
    messenger.sendCmdArg(F("WING"));
    messenger.sendCmdArg(F("SWITCH"));
    messenger.sendCmdArg(F(""));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kRequest);
    messenger.sendCmdArg(F("INPUT"));
    messenger.sendCmdArg(switchNavLogo);
    messenger.sendCmdArg(F("NAV_LOGO"));
    messenger.sendCmdArg(F("SWITCH3"));
    messenger.sendCmdArg(F(""));
    messenger.sendCmdArg(F("POS_NAMES=OFF#2#1"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kRequest);
    messenger.sendCmdArg(F("INPUT"));
    messenger.sendCmdArg(switchRunwayTurnoff);
    messenger.sendCmdArg(F("RWY_TURN_OFF"));
    messenger.sendCmdArg(F("SWITCH"));
    messenger.sendCmdArg(F(""));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kRequest);
    messenger.sendCmdArg(F("INPUT"));
    messenger.sendCmdArg(switchLandingLeft);
    messenger.sendCmdArg(F("LANDING_LEFT"));
    messenger.sendCmdArg(F("SWITCH3"));
    messenger.sendCmdArg(F(""));
    messenger.sendCmdArg(F("POS_NAMES=RETRACT#ON#OFF"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kRequest);
    messenger.sendCmdArg(F("INPUT"));
    messenger.sendCmdArg(switchLandingRight);
    messenger.sendCmdArg(F("LANDING_RIGHT"));
    messenger.sendCmdArg(F("SWITCH3"));
    messenger.sendCmdArg(F(""));
    messenger.sendCmdArg(F("POS_NAMES=RETRACT#ON#OFF"));
    messenger.sendCmdEnd();

    messenger.sendCmdStart(kRequest);
    messenger.sendCmdArg(F("INPUT"));
    messenger.sendCmdArg(switchNose);
    messenger.sendCmdArg(F("NOSE"));
    messenger.sendCmdArg(F("SWITCH3"));
    messenger.sendCmdArg(F(""));
    messenger.sendCmdArg(F("POS_NAMES=OFF#TO#TAXI"));
    messenger.sendCmdEnd();

    // // Expose led colour tint
    // // 0,OUTPUT,<DeviceIndex>,<Tag>,<Type>,<Inherits>[,<Option>=<Value>,...];
    messenger.sendCmdStart(kRequest);
    messenger.sendCmdArg(F("OUTPUT"));
    messenger.sendCmdArg(ledBrightness);
    messenger.sendCmdArg(F("L_PANEL_TINT"));  // Tag will become "SERIAL:<guid>/L_BRIGHTNESS"
    messenger.sendCmdArg(F("LED")); // Type
    messenger.sendCmdArg(F("SPAD_LED_C")); // Custom defined colours (COLORSET=)
    messenger.sendCmdArg(F("UI_FACE=0"));
    messenger.sendCmdArg(F("NOIMG=1"));
    messenger.sendCmdArg(F("COLORSET=PanelTint"));
    messenger.sendCmdEnd();

    // // Expose brightness setting
    // // 1,ADD,<CHANNELID>,<path>,<valuetype>,<access>,<name>[[,description][,options]];
    // messenger.sendCmdStart(kCommand);
    // messenger.sendCmdArg(F("ADD"));
    // messenger.sendCmdArg(kBrightness);
    // messenger.sendCmdArg(F("PanelBrightness"));  // Tag will become "SERIAL:<guid>/PanelBrightness"
    // messenger.sendCmdArg(F("U8")); // valuetype
    // messenger.sendCmdArg(F("RW"));
    // messenger.sendCmdArg(F("Panel backlight brightness"));
    // messenger.sendCmdEnd();

    // tell SPAD.neXT we are done with config
    messenger.sendCmd(kRequest, F("CONFIG"));

    return;
  }

  if ( (strcmp(szRequest, "SCANSTATE") == 0) || (strcmp(szRequest, "STATESCAN") == 0) ) {
    messenger.sendCmdStart(kRequest);
    messenger.sendCmdArg(F("STATESCAN"));
    messenger.sendCmdArg(F("1"));
    messenger.sendCmdEnd();

    force_switch_states();
    read_switch_states();

    messenger.sendCmdStart(kRequest);
    messenger.sendCmdArg(F("STATESCAN"));
    messenger.sendCmdArg(F("2"));
    messenger.sendCmdEnd();

    state.configured = true;

    return;
  }

  String msg = F("Unknown command: ");
  messenger.sendCmd(kDebug, msg + szRequest ); // if a command comes in that is not recognized from sketch write to the spad log

}

void onEvent()
{
    char *szRequest = messenger.readStringArg();

    if (strcmp(szRequest, "VIRTUALPOWER") == 0)
    {
        bool flag = messenger.readBoolArg();
        uint8_t brightness = globalBrightness;

        if (flag != state.power) {
            state.power = flag;
            if (!state.power) {
                brightness = 0;
            }
        }

        setPanelLighting( globalColor, brightness );
    }
    else if (strcmp(szRequest, "PROFILECHANGED") == 0)
    {
        //char *str = messenger.readStringArg();
        return;
    }
    else if (strcmp(szRequest, "PAGE") == 0)
    {
        //char *uid = messenger.readStringArg();
        //uint8_t pagenum = messenger.readInt16Arg();
        //char *pagename = messenger.readStringArg();
        return;
    }
    else if (strcmp(szRequest, "START") == 0)
    {
        if (!state.power) {
            //disp.printSplash(F("-"));
        }

        setPanelLighting( globalColor, globalBrightness * state.power );
    }
}

void onLED()
{
  // Example input: 6,9,1,L_PANEL_TINT,#FFC0C0;

  // 6,<LEDINDEX>,<ONOFF>,<TAG>[,<COLORNAME>,<COLORVALUE>];
  // <LEDINDEX> is the index the device defined in configuration phase
  // <ONOFF> will be 0 or 1 to turn the led off or on
  // <TAG> is the tag the device defined in configuration phase
  // <COLORNAME> and <COLORVALUE> are only present for colored led's (3-State or ColorSets)

  messenger.readInt16Arg();
  bool onOff = messenger.readBoolArg();
  messenger.readStringArg();
  char *colorValue = messenger.readStringArg();
  uint32_t rgb = 0;
  if ( onOff && colorValue[0] == '#' ) {
    colorValue += 1;
    rgb = strtol( colorValue, NULL, 16 );
    globalColor = rgb;
    setPanelLighting( rgb, globalBrightness );
  }
}

void onData()
{
    uint8_t dataIdx = messenger.readInt16Arg();

    if (dataIdx == kBrightness)
    {
        uint8_t brightness = messenger.readInt16Arg();
        globalBrightness = brightness;
        setPanelLighting( globalColor, brightness );
    }
    else
    {
        messenger.sendCmd(kDebug, "Unknown DATA index " + String(dataIdx) + "."); // Writing the Spad Log that we turned the FD Annunciator ON...
    }
}

// Define callbacks for the different SPAD command sets
void attachCommandCallbacks()
{
    messenger.attach(onUnknownCommand);
    messenger.attach(kRequest, onIdentifyRequest);
    messenger.attach(kEvent, onEvent);
    messenger.attach(kData, onData);
    messenger.attach(kLED, onLED);
}

// EOF
