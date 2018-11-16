/*******************************************************************************
@Module         Control Panel (CP)
--------------------------------------------------------------------------------
@Filename       CP_ControlPanel.cpp
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
#include "CP_ControlPanel.h"

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

uint8_t ButtonPushed_u8;

// enter button pin locations
//                                      PowerPin,   StartPin,   WashPin,    SpinPin,    DoorPin
static uint8_t s_pinLocation_au8[] =   {0,          2,          3,          0,          0       };

// button interrupt function
void BTN_PowerActive_v()
{
    ButtonPushed_u8 = BTN_POWER_ID;
}

// button interrupt function
void BTN_StartStopActive_v()
{
    ButtonPushed_u8 = BTN_START_STOP_ID;
}

// button interrupt function
void BTN_WashActive_v()
{
    ButtonPushed_u8 = BTN_WASH_ID;
}

// button interrupt function
void BTN_SpinActive_v()
{
    ButtonPushed_u8 = BTN_SPIN_ID;
}

// button interrupt function
void BTN_DoorActive_v()
{
    ButtonPushed_u8 = BTN_DOOR_SWITCH_ID;
}

ControlPanel::ControlPanel()
{
    uint8_t i;
    for(i = 0; i < BTN_LAST_ENTRY; i++)
    {
        m_btnList_ao[i].Initialise_b(s_pinLocation_au8[i]);
        m_ButtonCurrentState_ab[i] = false;
    }

    // register buttons interrupts
    attachInterrupt(digitalPinToInterrupt(s_pinLocation_au8[BTN_POWER_ID]), BTN_PowerActive_v, CHANGE);
    attachInterrupt(digitalPinToInterrupt(s_pinLocation_au8[BTN_START_STOP_ID]), BTN_StartStopActive_v, CHANGE);
    attachInterrupt(digitalPinToInterrupt(s_pinLocation_au8[BTN_WASH_ID]), BTN_WashActive_v, CHANGE);
    attachInterrupt(digitalPinToInterrupt(s_pinLocation_au8[BTN_SPIN_ID]), BTN_SpinActive_v, CHANGE);
    attachInterrupt(digitalPinToInterrupt(s_pinLocation_au8[BTN_DOOR_SWITCH_ID]), BTN_DoorActive_v, CHANGE);
}

void ControlPanel::checkButtonPress_v()
{
    if(ButtonPushed_u8 != BTN_LAST_ENTRY)
    {
        // if(button_is_pressed && was_not_pressed)
        if(m_btnList_ao[ButtonPushed_u8].isPressed_b() == LOW && m_ButtonCurrentState_ab[ButtonPushed_u8] == false)
        {
            Serial.println("Start Button pressed");
            /*switch(ButtonPushed_u8)
            {
            case BTN_POWER_ID:
                Serial.println("Power BTN pushed");
                break;
            case BTN_START_STOP_ID:
                Serial.println("Start BTN pushed");
                break;
            case BTN_WASH_ID:
                Serial.println("Wash BTN pushed");
                break;
            case BTN_SPIN_ID:
                Serial.println("Spin BTN pushed");
                break;
            case BTN_DOOR_SWITCH_ID:
                Serial.println("Door BTN pushed");
                break;
            default:
                break;
            }*/
            m_ButtonCurrentState_ab[ButtonPushed_u8] = true;

            // ensure that a button "isPressed()" method is executed only once after a successful button press detection
            ButtonPushed_u8 = BTN_LAST_ENTRY;
        }
    }
    if(m_btnList_ao[ButtonPushed_u8].isPressed_b() == HIGH)
    {
        m_ButtonCurrentState_ab[ButtonPushed_u8] = false;
    }
}

bool ControlPanel::getButtonState_b(ButtonsPanel_te buttonID_e)
{
    bool buttonState_u8 = false;
    if(buttonID_e != NULL && buttonID_e >= 0 && buttonID_e < BTN_LAST_ENTRY)
    {
        buttonState_u8 = m_ButtonCurrentState_ab[buttonID_e];
    }
    return buttonState_u8;
}