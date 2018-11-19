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

#ifndef _CONTROLPANEL_H_
#define _CONTROLPANEL_H_

#include <stdint.h>
#include "Arduino.h"
#include "ControlButton.h"

// enter button pin locations
//                                      PowerPin,   StartPin,   WashPin,    SpinPin,    DoorPin
static uint8_t s_pinLocation_au8[] =   {33,         18,         22,         13,         14       };

class ControlPanel
{
private:
    ControlButton m_btnList_ao[BUTTON_LAST_ENTRY_ID];       // panel button list
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
     @Returns       none

     --------------------------------------------------------------------------------
     @Parameters    none
     *******************************************************************************/
    void poolButtonsStateChanges_v();


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