
/*******************************************************************************
@Module          Potentiometer

/*******************************************************************************
--------------------------------------------------------------------------------
@Filename        Potentiometer.cpp

--------------------------------------------------------------------------------
@Description     Implementation of potentiometer class

--------------------------------------------------------------------------------
@Author          Marian S.
@Date            14.11.2018

-------------------------------------------------------------------------------
@Copyright       Miele & Cie Copyright 2018
*******************************************************************************/
#include "Potentiometer.h"

/*******************************************************************************
Function description and additional notes,
are given at the function prototype in the header file
*******************************************************************************/
bool Potentiometer::init_b()
{
    if (!initflag_b)
    {
        pinMode(InputPin_u8, INPUT);
        return true;
    }
    return false;
}

/*******************************************************************************
Function description and additional notes,
are given at the function prototype in the header file
*******************************************************************************/
WashingProgram_te Potentiometer::GetSelectedProgram()
{
    uint8_t PotentiometerPosition_u8 = 0;
    PotentiometerPosition_u8 = analogRead(InputPin_u8);

    // TBD: Map the program to the read value
    return WP_NONE;
}

void Potentiometer::TurnProgramLED_v(WashingProgram_te ProgramSelected_e)
{
    // TBD Map an led color to the selected wasching program
}

