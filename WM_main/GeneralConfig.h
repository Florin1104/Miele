#ifndef _GENERALCONFIG_H_
#define _GENERALCONFIG_H_

// TODO missing description of this file and what it is used for.

// TODO  used for? you should say it is used for and why is this value
#define DEBOUNCE_DELAY_MS 50 // the debounce time in milliseconds, increase value if the output flickers

// wemos lolin32 (esp32) all interrupt enabled pins // TODO write corectly  Wemos Lolin32 using . and ,.
//Keep in mind that PINs 13 14 18 19 33 are safely tested to use for the buttons interrupts
//if you want to use these pins for other purpose , then you will have to change the s_pinLocation_au8
//!WARNING! You can't use the same pin twice
//we use them for buttons
//											[       on BOOT side       ][        on EN side           ]
static uint8_t interruptEnablePins_au8[] = {15,2,0,4,5,18,23,19,21,22,23,13,12,14,27,26,25,35,34,33,32};

// TODO why is this static in headear file? is this a good practice?
//                                      PowerPin,   StartPin,   WashPin,    SpinPin,    DoorPin
static uint8_t s_pinLocation_au8[] =   {33,         18,         19,         13,         14       };

#endif