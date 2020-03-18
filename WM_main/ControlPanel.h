/*******************************************************************************
@Module         Control Panel

/*******************************************************************************
--------------------------------------------------------------------------------
@Filename       ControlPanel.h

--------------------------------------------------------------------------------
@Description    Represents the control panel from the wasing machine
This is a framework for all the buttons. It is recomended to use this instead off
ControlButton, because the function poolButtonsStateChanges_u8() in this module
constantly checks if a button was pressed, by listening to interrupts. 
It is easier to do it like this, than checking each button individualy by calling 
Button_ob.isPressed_u8();
--------------------------------------------------------------------------------
@Author         Iulian G. , Dragos B. , Marian S. , Stefan I. 
@Date           15.11.2018

-------------------------------------------------------------------------------
@Copyright      Miele & Cie Copyright 2018
*******************************************************************************/



/*******************************************************************************
@Example:
--------------------------------------------------------------------------------

#include "ControlPanel.h"
static uint8_t lastButtonPressed_8;

ControlPanel controlPanel_o;

void setup()
{
    // put your setup code here, to run once:

    Serial.begin(9600);                 // serial init for test messages
    delay(1000);                        // give time to Wemos Lolin32 to finish setup
    controlPanel_o.Initialise_e();      //be sure to initialise "s_pinLocation_au8[]" with propper pins
}

void loop()
{
    // put your main code here, to run repeatedly:
    lastButtonPressed_8 = controlPanel_o.poolButtonsStateChanges_u8(); // constantly check if a button was pressed
    switch(lastButtonPressed_8)
    {
    case BUTTON_POWER_ID:
        Serial.println("Power button pressed");
        // TBD
        break;
    case BUTTON_START_STOP_ID:
        Serial.println("Start/Stop button pressed");
        // TBD
        break;
    case BUTTON_WASH_ID:
        Serial.println("Wash button pressed");
        // TBD
        break;
    case BUTTON_SPIN_ID:
        Serial.println("Spin button pressed");
        // TBD
        break;
    case BUTTON_DOOR_SWITCH_ID:
        Serial.println("Door button pressed");
        // TBD
        break;
    default:
        break;
    }
}

*******************************************************************************/

#ifndef _CONTROLPANEL_H_
#define _CONTROLPANEL_H_

#include <stdint.h>
#include "Arduino.h"
#include "ControlButton.h"
#include "GeneralConfig.h"


// enter button pin locations
//                                      PowerPin,   StartPin,   WashPin,    SpinPin,    DoorPin
//static uint8_t s_pinLocation_au8[] =   {33,         18,         19,         13,         14       };
// TODO what is with above comment?

// The ControlPanel class controls all the buttons on the washing machine.
//It attaches an interrupt on each button and waits for it to occur when the button is pressed
//It holds the InitFlag variable, which tells us weather the class is initialized or not, and
//the m_btnList_ao array which holds the Button Objects
class ControlPanel
{
private:
    ControlButton m_btnList_ao[BUTTON_LAST_ENTRY_ID];       // panel button list
	
    bool m_InitFlag_b;                                      // hold if init() has been called
public:
    /*******************************************************************************
     @Description   Constructor used to initialise a button panel object

     --------------------------------------------------------------------------------
     @Returns       none

     --------------------------------------------------------------------------------
     @Parameters    none
     *******************************************************************************/
    ControlPanel();


    /*******************************************************************************
     @Description   Initialize control button panel with pins location (only once)
                    also searching for duplicates pin numbers
					PowerPin_u8 - pin number from s_pinLocation_au8[]
                    StartStopPin - pin number from s_pinLocation_au8[]
                    WashPin - pin number from s_pinLocation_au8[]
                    SpinPin - pin number from s_pinLocation_au8[]
                    DoorPin - pin number from s_pinLocation_au8[]
     --------------------------------------------------------------------------------
     @Returns       ButtonError_te - error

     --------------------------------------------------------------------------------
     @Parameters    
     *******************************************************************************/
     ButtonError_te Initialise_e();


    /*******************************************************************************
     @Description   constantly checks if a button was pressed // TODO are there any problems using delays in the code is this a good approach?>

     --------------------------------------------------------------------------------
     @Returns      uint8_t last button ID successful press 	//	BUTTON_POWER_ID = 0 // TODO Apparently it returns an enum it should be poolButtonsStateChanges_e
															//	BUTTON_START_STOP_ID = 1
															//	BUTTON_WASH_ID = 2
															//	BUTTON_SPIN_ID = 3
															//	BUTTON_DOOR_SWITCH_ID = 4
	// TODO here add more description e.g.:
		 @Returns ButtonsPanel_e an enum containing the last button that was pressed
		 BUTTON_POWER_ID (0) - In case the Power button was pressed.
		 BUTTON_START_STOP_ID (1) - In case ....
		 ......
		 .....
		 ....
		 BUTTON_LAST_ENTRY_ID - If no button was pressed....


     --------------------------------------------------------------------------------
     @Parameters    none
     *******************************************************************************/
     uint8_t poolButtonsStateChanges_u8(void);


    /*******************************************************************************
     @Description   get a button's state // TODO grammar and proper description "This function get a specific button state"
	 // TODO it seems that this method is not valid anymore.

     --------------------------------------------------------------------------------
     @Returns       true = pressed; false = not pressed or error if button is undefined
	 // TODO here you need to be consistent
	 TRUE if...
	 FALSE if...

     --------------------------------------------------------------------------------
     @Parameters    buttonID_e - button ID
     *******************************************************************************/
    bool getButtonState_b(ButtonsPanel_te buttonID_e);
};

#endif
