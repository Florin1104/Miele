/*******************************************************************************
@Module         Control Button
--------------------------------------------------------------------------------
@Filename       ControlButton.cpp
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
#include "ControlButton.h"

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
    s_interruptEnabledPinsCount_u8 = (uint8_t)(sizeof(interruptEnablePins_au8) / sizeof(interruptEnablePins_au8[0]));
}

/*******************************************************************************
Function description and additional notes,
are given at the function prototype in the header file
*******************************************************************************/
ButtonError_te ControlButton::Initialise_e(uint8_t pinNumber_u8)
{
    ButtonError_te error_e = BUTTON_ERROR_INVALID_PIN;
   
    if(m_InitFlag_b == false && pinNumber_u8 != NULL)
    {
        uint8_t i;
        for(i = 0; i < s_interruptEnabledPinsCount_u8; i++)
        {
            if(pinNumber_u8 == interruptEnablePins_au8[i])
            {
                error_e = BUTTON_ERROR_OK;
                break;
            }
        }
        if(error_e == BUTTON_ERROR_OK)
        {
            m_InputPinNumber_u8 = pinNumber_u8;
            pinMode(m_InputPinNumber_u8, INPUT_PULLUP);

            m_InitFlag_b = true;
        }
    }
    else
    {
        error_e = BUTTON_ERROR_INVALID_PIN;
    }
    return error_e;
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
        m_buttonState_u8 = 0x2; // 0x2 = any other value than 0x1 (HIGH) or 0x0 (LOW)
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