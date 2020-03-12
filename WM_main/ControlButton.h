/*******************************************************************************
@Module         Control Button

/*******************************************************************************
--------------------------------------------------------------------------------
@Filename       ControlButton.h

--------------------------------------------------------------------------------
@Description    Represents a single button from the washing machine control panel
// TODO add a bit more description. How can be used? Recomandation to use control panel instead etc. 
--------------------------------------------------------------------------------
@Author         Iulian G.
@Date           15.11.2018

-------------------------------------------------------------------------------
@Copyright      Miele & Cie Copyright 2018
*******************************************************************************/

#ifndef _CONTROLBUTTON_H_
#define _CONTROLBUTTON_H_

#include <stdint.h>

// TODO add comments
typedef enum ButtonError_e
{
    BUTTON_ERROR_OK = 0,
    BUTTON_ERROR_INVALID_PIN,
    BUTTON_ERROR_NO_INTERRUPT_ON_PIN,
    BUTTON_ERROR_DUPLICATE,
}ButtonError_te;

// TODO Double check this and move this conifg table into a GeneralConfig.h file
// wemos lolin32 (esp32) interrupt enabled pins
static uint8_t interruptEnablePins_au8[] = {15,2,0,4,5,18,23,19,21,22,13,12,14,27,26,25,35,34,33,32};

// TODO  maybe again this two values should be checked and maybe moved into a config file. 
// TODO double check about 14 DOOR PIN maybe needs to be removed
#define DEBOUNCE_DELAY_MS 50 // the debounce time, increase value if the output flickers
#define DOOR_PIN  14
#include <stdint.h>
#include "Arduino.h"

// TODO add comments
typedef enum ButtonsPanel_e
{
    BUTTON_POWER_ID = 0,
    BUTTON_START_STOP_ID,
    BUTTON_WASH_ID, 
    BUTTON_SPIN_ID,
    BUTTON_DOOR_SWITCH_ID,

    //this should be the last entry // TODO why this should be the last entry. because with this you can count how many buttons you have
    BUTTON_LAST_ENTRY_ID = 5
}ButtonsPanel_te;


// TODO  add description
class ControlButton
{

 private:

	 // TODO add more description. Can be any pin? For what is used the Debounce time is that in millis or in sec, the same for debounce time
     uint8_t m_InputPinNumber_u8;           // button pin location
     uint8_t m_buttonState_u8;              // current reading from the input pin
     uint8_t m_lastButtonState_u8;          // the previous reading from the input pin
     uint32_t m_lastDebounceTime_u32;       // the last time the output pin was toggled
     uint32_t m_debounceDelay_32;           // the debounce time
     bool m_InitFlag_b;                     // hold if init() has been called
	 // TODO add more description
     uint8_t s_interruptEnabledPinsCount_u8; // count interrupt enabled pins


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
     @Description   Initialize control button with pin location (only once); checks
                    for valid pin number
     --------------------------------------------------------------------------------
     @Returns       ButtonError_te - button error code
	 // TODO what errors can return and why?
     --------------------------------------------------------------------------------
     @Parameters    pinNumber_u8 - pin number // TODO what pins are valid?
     *******************************************************************************/
     ButtonError_te Initialise_e(uint8_t pinNumber_u8);



     /*******************************************************************************
     @Description   check if button is pressed taking into account the debounce

     --------------------------------------------------------------------------------
     @Returns       uint8_t - LOW(0x0) = pressed; HIGH(0x1) = not pressed

     --------------------------------------------------------------------------------
     @Parameters    None
     *******************************************************************************/
     uint8_t isPressed_b(); // TODO if it returns a uint_8 it should be _u8 otherwise it should return a bool

     /*******************************************************************************
     @Description   Check if door is open.

     --------------------------------------------------------------------------------
     @Returns       True if the door is open,
                    False otherwise.

					// TODO from what i see it retruns a uinit_8 a cast into the method is needed

     --------------------------------------------------------------------------------
     @Parameters    None
     *******************************************************************************/
	 // TODO  why this method is static. Is it really used somewhere?
     static bool isDoorOpen_b();
};

#endif