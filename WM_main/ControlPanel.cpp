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

// keep last button interrupt
static volatile uint8_t LastButtonInterrupt_u8;

// button interrupt function
void BTN_PowerActive_v()
{
    LastButtonInterrupt_u8 = BUTTON_POWER_ID;
}

// button interrupt function
void BTN_StartStopActive_v()
{
    LastButtonInterrupt_u8 = BUTTON_START_STOP_ID;
}

// button interrupt function
void BTN_WashActive_v()
{
    LastButtonInterrupt_u8 = BUTTON_WASH_ID;
}

// button interrupt function
void BTN_SpinActive_v()
{
    LastButtonInterrupt_u8 = BUTTON_SPIN_ID;
}

// button interrupt function
void BTN_DoorActive_v()
{
    LastButtonInterrupt_u8 = BUTTON_DOOR_SWITCH_ID;
}

ControlPanel::ControlPanel()
{
    
}

ButtonError_te ControlPanel::Initialise_e()
{
    LastButtonInterrupt_u8 = BUTTON_LAST_ENTRY_ID;
    ButtonError_te error = BUTTON_ERROR_INVALID_PIN;
    m_lastSuccessfulButtonPush_u8 = BUTTON_LAST_ENTRY_ID;
    
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
            attachInterrupt(digitalPinToInterrupt(s_pinLocation_au8[BUTTON_POWER_ID]), BTN_PowerActive_v, RISING);
            attachInterrupt(digitalPinToInterrupt(s_pinLocation_au8[BUTTON_START_STOP_ID]), BTN_StartStopActive_v, RISING);
            attachInterrupt(digitalPinToInterrupt(s_pinLocation_au8[BUTTON_WASH_ID]), BTN_WashActive_v, RISING);
            attachInterrupt(digitalPinToInterrupt(s_pinLocation_au8[BUTTON_SPIN_ID]), BTN_SpinActive_v, RISING);
            attachInterrupt(digitalPinToInterrupt(s_pinLocation_au8[BUTTON_DOOR_SWITCH_ID]), BTN_DoorActive_v, RISING);
            m_InitFlag_b = true;
        }
    }
    return error;
}

uint8_t ControlPanel::poolButtonsStateChanges_u8()
{

    uint8_t RetrunedLastButton = LastButtonInterrupt_u8;

    LastButtonInterrupt_u8 = BUTTON_LAST_ENTRY_ID;
 
  
    return RetrunedLastButton;
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