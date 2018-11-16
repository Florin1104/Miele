/*******************************************************************************
@Module         Control Button (CB)

/*******************************************************************************
--------------------------------------------------------------------------------
@Filename       CB_ControlButton.h

--------------------------------------------------------------------------------
@Description    Represents a single button from the wasing machine control panel

--------------------------------------------------------------------------------
@Author         Iulian G.
@Date           15.11.2018

-------------------------------------------------------------------------------
@Copyright      Miele & Cie Copyright 2018
*******************************************************************************/

#ifndef _CB_CONTROLBUTTON_H_
#define _CB_CONTROLBUTTON_H_

#define DEBOUNCE_DELAY_MS 50 // the debounce time, increase value if the output flickers

#include <stdint.h>
#include "Arduino.h"

typedef enum ButtonsPanel_e
{
    BTN_POWER_ID = 0,
    BTN_START_STOP_ID,
    BTN_WASH_ID, 
    BTN_SPIN_ID,
    BTN_DOOR_SWITCH_ID,

    //this should be the last entry
    BTN_LAST_ENTRY = 5
}ButtonsPanel_te;

class ControlButton
{

 private:

     uint8_t m_InputPinNumber_u8;       // button pin location
     uint8_t m_buttonState_u8;          // current reading from the input pin
     uint8_t m_lastButtonState_u8;      // the previous reading from the input pin
     uint32_t m_lastDebounceTime_u32;   // the last time the output pin was toggled
     uint32_t m_debounceDelay_32;       // the debounce time

     // hold if init() has been called
     bool m_InitFlag_b;


 public:
     /*******************************************************************************
     @Description   Constructor used to initialise a button object

     --------------------------------------------------------------------------------
     @Returns       none

     --------------------------------------------------------------------------------
     @Parameters    none
     *******************************************************************************/
     ControlButton();



     /*******************************************************************************
     @Description   Initialize control button with pin location (only once)

     --------------------------------------------------------------------------------
     @Returns       bool - whether or not button object was successfully initialized

     --------------------------------------------------------------------------------
     @Parameters    pinNumber_u8 - pin number
     *******************************************************************************/
     bool Initialise_b(uint8_t pinNumber_u8);



     /*******************************************************************************
     @Description   check if button is pressed taking into account the debounce

     --------------------------------------------------------------------------------
     @Returns       bool - true if pressed

     --------------------------------------------------------------------------------
     @Parameters    None
     *******************************************************************************/
     uint8_t isPressed_b();
};

#endif