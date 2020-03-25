/*******************************************************************************
@Module         Control Panel

--------------------------------------------------------------------------------
@Filename       ControlPanel.h

--------------------------------------------------------------------------------
@Description    Represents the control panel from the washing machine
				This is a framework for all the buttons. It is recommended to use 
				this instead off ControlButton, because the function 
				poolButtonsStateChanges_e() in this module constantly checks if 
				a button was pressed, by listening to interrupts. 
				It is easier to do it like this, than checking each button 
				individually by calling Button_ob.isPressed_u8();.
--------------------------------------------------------------------------------
@Author         Iulian G. , Dragos B. , Marian S. , Stefan I. 
@Date           15.11.2018

-------------------------------------------------------------------------------
@Copyright      Miele & Cie Copyright 2020
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

    Serial.begin(9600);            // serial init for test messages
    delay(1000);                   // give time to Wemos Lolin32 to finish setup
    controlPanel_o.Initialise_e(); // be sure to initialize "s_pinLocation_au8[]" with proper pins
}

void loop()
{
    // put your main code here, to run repeatedly:
	 
	// constantly check if a button was pressed
    lastButtonPressed_8 = controlPanel_o.poolButtonsStateChanges_e(); 
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



// The ControlPanel class controls all the buttons on the washing machine.
// It attaches an interrupt on each button and waits for it to occur when the 
// button is pressed. It holds the InitFlag variable, which tells us weather 
// the class is initialized or not, and the m_btnList_ao array which holds 
// the Button Objects.
class ControlPanel
{
private:
    ControlButton m_btnList_ao[BUTTON_LAST_ENTRY_ID];   // panel button list
	
    bool m_InitFlag_b;                        // hold if init() has been called
public:
    /*******************************************************************************
     @Description   Constructor used to initialize a button panel object

     --------------------------------------------------------------------------------
     @Returns       none

     --------------------------------------------------------------------------------
     @Parameters    none
     *******************************************************************************/
    ControlPanel();


    /*******************************************************************************
     @Description   Initialize control button panel with the pins location (only once)
                    and also searching for duplicates pin numbers.
					PowerPin 		- pin number from s_pinLocation_au8[]
                    StartStopPin 	- pin number from s_pinLocation_au8[]
                    WashPin 		- pin number from s_pinLocation_au8[]
                    SpinPin 		- pin number from s_pinLocation_au8[]
                    DoorPin 		- pin number from s_pinLocation_au8[]
     --------------------------------------------------------------------------------
     @Returns       ButtonError_te - error

     --------------------------------------------------------------------------------
     @Parameters    
     *******************************************************************************/
     ButtonError_te Initialise_e();


    /*******************************************************************************
     @Description   Constantly checks if a button was pressed .
	 // TODO are there any problems using delays in the code is this a good approach?
    --------------------------------------------------------------------------------
     @Returns   ButtonsPanel_te an enum containing the last button ID successful press 	
				BUTTON_POWER_ID 	  (0) 	- Power button was pressed
				BUTTON_START_STOP_ID  (1) 	- Start/Stop button was pressed
				BUTTON_WASH_ID 		  (2) 	- Wash button was pressed
				BUTTON_SPIN_ID 		  (3) 	- Spin button was pressed
				BUTTON_DOOR_SWITCH_ID (4) 	- Door button was pressed
    --------------------------------------------------------------------------------
	 @Parameters    none
    *******************************************************************************/
     ButtonsPanel_te poolButtonsStateChanges_e(void);

};

#endif
