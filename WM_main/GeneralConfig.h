/*******************************************************************************
@Module          General Config
--------------------------------------------------------------------------------
@Filename        GeneralConfig.h

--------------------------------------------------------------------------------
@Description     Used for storing important variables, buffers and 
				 type definitions for the ControlButton and ControlPanel
				 modules.
--------------------------------------------------------------------------------
@Author          Stefan I.
@Date            20.03.2020
-------------------------------------------------------------------------------
@Copyright       Miele & Cie Copyright 2020
*******************************************************************************/


#ifndef _GENERALCONFIG_H_
#define _GENERALCONFIG_H_

/*******************************************************************************
@Macros (global)
*******************************************************************************/
// Only when the switch has stayed on the same value for a period of time,
// do we send the signal to the computer. This period is called the debounce delay 
// It’s the time that you’re filtering out all those signals that you don’t want to send 
// to the computer.

// TODO  why is this value? 
// the debounce time in milliseconds, increase value if the output flickers.
#define DEBOUNCE_DELAY_MS 50 
// This array contains all the pins on the Wemos Lolin32 (esp32) board that are
// PWM and I2C capable.
#define VALID_PWM_I2C_PINS  { 15,2,0,4,16,17,5,18,23,19,21,22,13,12,14,27,26,25,35,34,33,32,39,36}

// Wemos Lolin32 (esp32) all interrupt enabled pins.
// Keep in mind that PINs 13 14 18 19 33 are safely tested to use for the buttons interrupts.
// If you want to use these pins for other purpose , then you will have to change the s_pinLocation_au8
// !WARNING! You can't use the same pin twice
// we use them for buttons
//											[       on BOOT side       ][        on EN side           ]
static uint8_t interruptEnablePins_au8[] = {15,2,0,4,5,18,23,19,21,22,23,13,12,14,27,26,25,35,34,33,32};

// TODO why is this static in header file? is this a good practice?
//                                      PowerPin,   StartPin,   WashPin,    SpinPin,    DoorPin
static uint8_t s_pinLocation_au8[] =   {33,         18,         19,         13,         14       };


//const uint8_t ValidI2CPins_au8[] = { 15,2,0,4,16,17,5,18,23,19,21,22,13,12,14,27,26,25,35,34,33,32,39,36};

#endif