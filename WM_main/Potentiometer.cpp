
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

#define NUMBER_OF_READINGS 1
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
    int RawPotentiometer_u8 = 0;
    RawPotentiometer_u8 = analogRead(InputPin_u8);

   
    int PotettiometerValue = 0;
    PotettiometerValue = map(RawPotentiometer_u8,0,4095,0,100);
    Serial.println(PotettiometerValue);

    // TBD: Map the program to the read value
    return WP_NONE;
}


void Potentiometer::TurnProgramLED_v(WashingProgram_te ProgramSelected_e)
{
    // TBD Map an led color to the selected wasching program
}

