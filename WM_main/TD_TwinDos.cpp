/*******************************************************************************
@Module         Twin Dos (TD)
--------------------------------------------------------------------------------
@Filename       TD_TwinDos.cpp
--------------------------------------------------------------------------------
@Description    check in header file for more details

--------------------------------------------------------------------------------
@Author         Iulian G.
@Date           14.11.2018

@Copyright      Miele  Cie Copyright 2018

*******************************************************************************/


/*******************************************************************************
@Project Includes
*******************************************************************************/
#include "TD_TwinDos.h"

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
TwinDos::TwinDos()
{
    m_InputPin1_u8 = 0;
    m_InputPin2_u8 = 0;
    m_InitFlag_b = false;
}

/*******************************************************************************
Function description and additional notes,
are given at the function prototype in the header file
*******************************************************************************/
bool TwinDos::Initialise_b(uint8_t pin1_u8, uint8_t pin2_u8)
{
    bool initialized_b = false;
    
    if(m_InitFlag_b == false)
    {
        m_InputPin1_u8 = pin1_u8;
        m_InputPin2_u8 = pin2_u8;
        pinMode(m_InputPin1_u8, INPUT_PULLUP);
        pinMode(m_InputPin2_u8, INPUT_PULLUP);

        m_InitFlag_b = true;
        initialized_b = true;
    }
    return initialized_b;
}

/*******************************************************************************
Function description and additional notes,
are given at the function prototype in the header file
*******************************************************************************/
bool TwinDos::isPresent_b()
{
    bool cartridgeIn_b = false;
    
    // "!" because when pressed they will connected to ground, their value will be "0", so: if(false && false)
    if(!digitalRead(m_InputPin1_u8) && !digitalRead(m_InputPin2_u8))
    {
        cartridgeIn_b = true;
    }
    
    return cartridgeIn_b;
}