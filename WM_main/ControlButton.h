/*******************************************************************************
@Module         Control Button

/*******************************************************************************
--------------------------------------------------------------------------------
@Filename       ControlButton.h

--------------------------------------------------------------------------------
@Description	It contains a class that defines the behavior of a button
				Its instances represent a single button from the washing 
				machine control panel. It is recommended to  use ControlPanel 
				class from ControlPanel.h instead, because it is easier to 
				check only when a button is  pressed than to check each one
                individually.
--------------------------------------------------------------------------------
@Author         Iulian G. , Dragos B. , Marian S. , Stefan I. 
@Date           15.11.2018

-------------------------------------------------------------------------------
@Copyright      Miele & Cie Copyright 2020
*******************************************************************************/

/*******************************************************************************
@Example:
--------------------------------------------------------------------------------

#include "ControlButton.h"
#define SPIN_BUTTON 13
#define WASH_BUTTON 19
ControlButton button_o;
ControlButton button_o1;
void setup()
{
    // put your setup code here, to run once:

    Serial.begin(9600);                 		// serial init for test messages
    delay(1000);                        		// give time to Wemos Lolin32 to finish setup
    button_o.Initialise_e(SPIN_BUTTON);      	//be sure to initialise "s_pinLocation_au8[]" with propper pins
	button_o1.Initialise_e(WASH_BUTTON);
}

void loop()
{
    // put your main code here, to run repeatedly:
    if(button_o.IsButtonPressed_u8()==0)
	{
		Serial.println("BUTTON IS PRESSED");
	}
	else
	{
		Serial.println("BUTTON IS NOT PRESSED");
	}
	
	if(button_o1.IsButtonPressed_u8()==0)
	{
		Serial.println("BUTTON IS PRESSED");
	}
	else
	{
		Serial.println("BUTTON IS NOT PRESSED");
	}
}

*******************************************************************************/
#ifndef _CONTROLBUTTON_H_
#define _CONTROLBUTTON_H_

#include <stdint.h>
#include "GeneralConfig.h"

/*
Enum is a user defined data type where we specify a set of values for a variable
and the variable can only take one out of a small set of possible values. 
We use enum keyword to define a Enumeration.
By default, BUTTON_ERROR_OK is 0, BUTTON_ERROR_INVALID_PIN is 1 and so on. 
You can change the default value of an enum element during declaration (if necessary).
*/

// This enum holds all the possible errors for this module. 
// Possible values can be:
// - BUTTON_ERROR_OK: When no error is encountered
// - BUTTON_ERROR_INVALID_PIN: When an invalid pin was selected for use
// - BUTTON_ERROR_NO_INTERRUPT_ON_PIN: When the pin in use does not support interrupts
// - BUTTON_ERROR_DUPLICATE: When the pin in use is reused somewhere else

typedef enum ButtonError_e
{
    BUTTON_ERROR_OK = 0,					//	BUTTON_ERROR_OK = 0
    BUTTON_ERROR_INVALID_PIN,				//	BUTTON_ERROR_INVALID_PIN = 1
    BUTTON_ERROR_NO_INTERRUPT_ON_PIN,		//	BUTTON_ERROR_NO_INTERRUPT_ON_PIN = 2
    BUTTON_ERROR_DUPLICATE,					//	BUTTON_ERROR_DUPLICATE = 3
}ButtonError_te;


#include <stdint.h>
#include "Arduino.h"

// This enum holds the ID's of the buttons contained in the Control Panel. We assigned
// an ID to each button in order to be easier to access and to keep track of
// Possible values can be:
// - BUTTON_POWER_ID: 		Value 0 is assigned as ID to the POWER BUTTON
// - BUTTON_START_STOP_ID: 	Value 1 is assigned as ID to the START_STOP BUTTON
// - BUTTON_WASH_ID: 		Value 2 is assigned as ID to the WASH BUTTON
// - BUTTON_SPIN_ID: 		Value 3 is assigned as ID to the SPIN BUTTON
// - BUTTON_DOOR_SWITCH_ID: Value 4 is assigned as ID to the DOOR BUTTON
// - BUTTON_LAST_ENTRY_ID:	Value 5 is assigned as ID to the LAST ENTRY
//							in order to keep track of the number of buttons


typedef enum ButtonsPanel_e
{
    BUTTON_POWER_ID = 0,		//	BUTTON_POWER_ID = 0
    BUTTON_START_STOP_ID,		//	BUTTON_START_STOP_ID = 1
    BUTTON_WASH_ID, 			//	BUTTON_WASH_ID = 2
    BUTTON_SPIN_ID,				//	BUTTON_SPIN_ID = 3
    BUTTON_DOOR_SWITCH_ID,		//	BUTTON_DOOR_SWITCH_ID = 4

    //this should be the last entry  because with this you can keep track of how many buttons you have
	//Check the BUTTON_LAST_ENTRY_ID value to find the number of buttons
    BUTTON_LAST_ENTRY_ID = 5
}ButtonsPanel_te;


/*******************************************************************************
@Description	This class controls all the buttons as an universal framework
				
*******************************************************************************/
class ControlButton
{

 private:

	 // TODO add more description. Can be any pin? For what is used the Debounce time
	 
     uint8_t m_InputPinNumber_u8;           // button pin location. Use proper pins from interruptEnablePins_au8[] = {15,2,0,4,5,18,23,19,21,22,13,12,14,27,26,25,35,34,33,32};
											// Represents a pin which is Interrupt enabled
	 uint8_t m_buttonState_u8;              // current reading from the input pin
     uint8_t m_lastButtonState_u8;          // the previous reading from the input pin
	 
     uint32_t m_lastDebounceTime_u32;       // the last time the output pin was toggled in milliseconds
											// it holds the moment the Button was last pressed
											// in order to perform the debouncing mechanism
											// check ControlButton.cpp to see details
											
     uint32_t m_debounceDelay_32;           // the debounce time threshold in milliseconds
     bool m_InitFlag_b;                     // hold if init() has been called
	 
	 // This variable is used to keep track of how many interrupt pins were in fact used
     uint8_t s_interruptEnabledPinsCount_u8; // count interrupt enabled pins


 public:
     /*******************************************************************************
     @Description   Constructor used to initialize a button object

     --------------------------------------------------------------------------------
     @Returns       none

     --------------------------------------------------------------------------------
     @Parameters    none
     *******************************************************************************/
     ControlButton();



     /*******************************************************************************
     @Description   Initialize control button with pin location (only once); 
					checks for valid pin number.
     --------------------------------------------------------------------------------
     @Returns       ButtonError_te - button error code
					Possible return values:
					
					-BUTTON_ERROR_INVALID_PIN if pinNumber_u8 is not contained in the 
															interruptEnablePins_au8[]
					
					-BUTTON_ERROR_OK if no error has occurred
     --------------------------------------------------------------------------------
     @Parameters    pinNumber_u8 - pin number of {15,2,0,4,5,18,23,19,21,22,13,12,14,
												  27,26,25,35,34,33,32}
     *******************************************************************************/
     ButtonError_te Initialise_e(uint8_t pinNumber_u8);



     /*******************************************************************************
     @Description   check if button is pressed taking into account the debounce

     --------------------------------------------------------------------------------
     @Returns       uint8_t - LOW(0x0) = pressed; HIGH(0x1) = not pressed

     --------------------------------------------------------------------------------
     @Parameters    None
     *******************************************************************************/
     uint8_t IsButtonPressed_u8(void); 

};

#endif
