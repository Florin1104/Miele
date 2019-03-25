/*******************************************************************************
@Module         Control Panel

/*******************************************************************************
--------------------------------------------------------------------------------
@Filename       ControlPanel.h

--------------------------------------------------------------------------------
@Description    Represents the control panel from the wasing machine

--------------------------------------------------------------------------------
@Author         Iulian G.
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
    lastButtonPressed_8 = controlPanel_o.poolButtonsStateChanges_v(); // constantly check if a button was pressed
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

// enter button pin locations
//                                      PowerPin,   StartPin,   WashPin,    SpinPin,    DoorPin
static uint8_t s_pinLocation_au8[] =   {33,         18,         19,         13,         14       };

class ControlPanel
{
private:
    ControlButton m_btnList_ao[BUTTON_LAST_ENTRY_ID];       // panel button list
    uint8_t m_lastSuccessfulButtonPush_u8;                  // remember last button successful press
    bool m_ButtonCurrentState_ab[BUTTON_LAST_ENTRY_ID];     // remember button state to answer when asked
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
     --------------------------------------------------------------------------------
     @Returns       bool - whether or not panel object was successfully initialized

     --------------------------------------------------------------------------------
     @Parameters    PowerPin_u8 - pin number
                    StartStopPin - pin number
                    WashPin - pin number
                    SpinPin - pin number
                    DoorPin - pin number
     *******************************************************************************/
     ButtonError_te Initialise_e();


    /*******************************************************************************
     @Description   constantly checks if a button was pressed

     --------------------------------------------------------------------------------
     @Returns       last button ID successful press

     --------------------------------------------------------------------------------
     @Parameters    none
     *******************************************************************************/
     uint8_t poolButtonsStateChanges_v();


    /*******************************************************************************
     @Description   get a button's state

     --------------------------------------------------------------------------------
     @Returns       true = pressed; false = not pressed

     --------------------------------------------------------------------------------
     @Parameters    buttonID_e - button ID
     *******************************************************************************/
    bool getButtonState_b(ButtonsPanel_te buttonID_e);
};

#endif
