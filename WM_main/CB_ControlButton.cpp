/*******************************************************************************
@Module         Control Button (CB)
--------------------------------------------------------------------------------
@Filename       CB_ControlButton.cpp
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
#include "CB_ControlButton.h"

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

/*******************************************************************************
Function description and additional notes,
are given at the function prototype in the header file
*******************************************************************************/
ControlButton::ControlButton()
{
    m_InputPinNumber_u8 = 0;
    m_buttonState_u8 = HIGH;
    m_lastButtonState_u8 = HIGH;
    m_lastDebounceTime_u32 = 0;
    m_debounceDelay_32 = DEBOUNCE_DELAY_MS;
    m_InitFlag_b = false;
}

/*******************************************************************************
Function description and additional notes,
are given at the function prototype in the header file
*******************************************************************************/
bool ControlButton::Initialise_b(uint8_t pinNumber_u8)
{
    bool initialized_b = false;
    
    if(m_InitFlag_b == false)
    {
        m_InputPinNumber_u8 = pinNumber_u8;
        pinMode(m_InputPinNumber_u8, INPUT_PULLUP);

        m_InitFlag_b = true;
        initialized_b = true;
    }
    return initialized_b;
}

/*******************************************************************************
Function description and additional notes,
are given at the function prototype in the header file
*******************************************************************************/
uint8_t ControlButton::isPressed_b()
{
    uint8_t currentState_u8 = digitalRead(m_InputPinNumber_u8);
    if (currentState_u8 != m_lastButtonState_u8)
    {
        // reset the debouncing timer
        m_lastDebounceTime_u32 = millis();
    }

    if ((millis() - m_lastDebounceTime_u32) > m_debounceDelay_32)
    {
        // whatever the reading is at, it's been there for longer than the debounce
        // delay, so take it as the actual current state:

        // if a reliable button state change is detected:
        if (currentState_u8 != m_buttonState_u8)
        {
            m_buttonState_u8 = currentState_u8;
        }
    }

    // save the reading. Next time through the loop, it'll be the m_lastButtonState_u8
    m_lastButtonState_u8 = currentState_u8;
    return m_buttonState_u8;
}