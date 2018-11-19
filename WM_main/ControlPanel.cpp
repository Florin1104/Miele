/*******************************************************************************
@Module         Control Panel
--------------------------------------------------------------------------------
@Filename       ControlPanel.cpp
--------------------------------------------------------------------------------
@Description    check in header file for more details

--------------------------------------------------------------------------------
@Author         Iulian G.
@Date           15.11.2018

@Copyright      Miele  Cie Copyright 2018

*******************************************************************************/

/*******************************************************************************
@Project Includes
*******************************************************************************/
#include "ControlPanel.h"

/*******************************************************************************
@Constants (global)
*******************************************************************************/

/*******************************************************************************
@Macros (global)
*******************************************************************************/

/*******************************************************************************
@Type definitions  (global)
*******************************************************************************/

/*******************************************************************************
@Local Variables 
*******************************************************************************/

/*******************************************************************************
@External Prototypes
*******************************************************************************/

/*******************************************************************************
@Prototypes local Functions
*******************************************************************************/

// keep last button pressed
static uint8_t ButtonPushed_u8;

// button interrupt function
void BTN_PowerActive_v()
{
    ButtonPushed_u8 = BUTTON_POWER_ID;
}

// button interrupt function
void BTN_StartStopActive_v()
{
    ButtonPushed_u8 = BUTTON_START_STOP_ID;
}

// button interrupt function
void BTN_WashActive_v()
{
    ButtonPushed_u8 = BUTTON_WASH_ID;
}

// button interrupt function
void BTN_SpinActive_v()
{
    ButtonPushed_u8 = BUTTON_SPIN_ID;
}

// button interrupt function
void BTN_DoorActive_v()
{
    ButtonPushed_u8 = BUTTON_DOOR_SWITCH_ID;
}

ControlPanel::ControlPanel()
{
    
}

ButtonError_te ControlPanel::Initialise_e()
{
    ButtonError_te error = BUTTON_ERROR_INVALID_PIN;
    
    if(m_InitFlag_b == false)
    {
        uint8_t i,j;
        // search for duplicate pin number
        for(i = 0; i < BUTTON_LAST_ENTRY_ID-1; i++)
        {
            for(j = i+1; j < BUTTON_LAST_ENTRY_ID; j++)
            {
                if(s_pinLocation_au8[i] ==  s_pinLocation_au8[j])
                {
                    error = BUTTON_ERROR_DUPLICATE;
                    break;
                }
            }
        }
        if(error != BUTTON_ERROR_DUPLICATE)
        {
            // checks for valid pin number
            for(i = 0; i < BUTTON_LAST_ENTRY_ID; i++)
            {
                error = m_btnList_ao[i].Initialise_e(s_pinLocation_au8[i]);
                m_ButtonCurrentState_ab[i] = false;
                if(error != BUTTON_ERROR_OK)
                {
                    break;
                }
            }
        }
        if(BUTTON_ERROR_OK == error)
        {
            // register buttons interrupts
            attachInterrupt(digitalPinToInterrupt(s_pinLocation_au8[BUTTON_POWER_ID]), BTN_PowerActive_v, CHANGE);
            attachInterrupt(digitalPinToInterrupt(s_pinLocation_au8[BUTTON_START_STOP_ID]), BTN_StartStopActive_v, CHANGE);
            attachInterrupt(digitalPinToInterrupt(s_pinLocation_au8[BUTTON_WASH_ID]), BTN_WashActive_v, CHANGE);
            attachInterrupt(digitalPinToInterrupt(s_pinLocation_au8[BUTTON_SPIN_ID]), BTN_SpinActive_v, CHANGE);
            attachInterrupt(digitalPinToInterrupt(s_pinLocation_au8[BUTTON_DOOR_SWITCH_ID]), BTN_DoorActive_v, CHANGE);
            m_InitFlag_b = true;
        }
    }
    return error;
}

void ControlPanel::poolButtonsStateChanges_v()
{
    if(ButtonPushed_u8 != BUTTON_LAST_ENTRY_ID)
    {
        // ensure that is a LOW to HIGH transition
        if(m_btnList_ao[ButtonPushed_u8].isPressed_b() == LOW && m_ButtonCurrentState_ab[ButtonPushed_u8] == false)
        {
            switch(ButtonPushed_u8)
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
            m_ButtonCurrentState_ab[ButtonPushed_u8] = true;

            // ensure that a button "isPressed()" method is executed only once after a successful button press detection
            ButtonPushed_u8 = BUTTON_LAST_ENTRY_ID;
        }
    }
    // ensure that is a HIGH to LOW transition
    if(m_btnList_ao[ButtonPushed_u8].isPressed_b() == HIGH && m_ButtonCurrentState_ab[ButtonPushed_u8] == true)
    {
        m_ButtonCurrentState_ab[ButtonPushed_u8] = false;
        ButtonPushed_u8 = BUTTON_LAST_ENTRY_ID;
    }
}

bool ControlPanel::getButtonState_b(ButtonsPanel_te buttonID_e)
{
    bool buttonState_u8 = false;
    if(buttonID_e != NULL && buttonID_e >= 0 && buttonID_e < BUTTON_LAST_ENTRY_ID)
    {
        buttonState_u8 = m_ButtonCurrentState_ab[buttonID_e];
    }
    return buttonState_u8;
}