/*******************************************************************************
@Module          Potentiometer

/*******************************************************************************
--------------------------------------------------------------------------------
@Filename        Potentiometer.cpp

--------------------------------------------------------------------------------
@Description     Implementation of potentiometer class

--------------------------------------------------------------------------------
@Author          Marian S., Baver D., Bratu D.
@Date            14.11.2018

-------------------------------------------------------------------------------
@Copyright       Miele & Cie Copyright 2020
*******************************************************************************/
#include "Potentiometer.h"

#define NUMBER_OF_READINGS 1
#define SERIAL_PRINT_ON (0)

#if SERIAL_PRINT_ON == 1
#define SERIAL_PRINT(Data) Serial.println(Data)
#else
#define SERIAL_PRINT(Data)
#endif //  SERIAL_PRINT_ON == 1

/*******************************************************************************
Function description and additional notes,
are given at the function prototype in the header file
*******************************************************************************/
bool Potentiometer::Init_b()
{
    if (InitFlag_b == false)
    {
        pinMode(InputPin_u8, INPUT);

		    InitFlag_b = true;

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
    //Serial.println(RawPotentiometer_u8);
	  WashingProgram_te WashProgram_e;


	if ((RawPotentiometer_u8 < 3000) && (RawPotentiometer_u8 > 2500)) //200
	{
		WashProgram_e = WP_WASH;

	}
	else if ((RawPotentiometer_u8 < 2500) && (RawPotentiometer_u8 > 1600))
	{
		WashProgram_e = WP_SPIN;

	}
	else if ((RawPotentiometer_u8 < 1600) && (RawPotentiometer_u8 > 1200))
	{
		WashProgram_e = WP_HANDWASH;
	}
	else if ((RawPotentiometer_u8 < 1200) && (RawPotentiometer_u8 > 1000)) 
	{
		WashProgram_e = WP_FAST_WASH;
	}
	else if ((RawPotentiometer_u8 < 1000) && (RawPotentiometer_u8 > 750)) 
	{
		WashProgram_e = WP_INTENSE_WASH;
	}
	else if ((RawPotentiometer_u8 < 750) && (RawPotentiometer_u8 > 600)) 
	{
		WashProgram_e = WP_WHITE_CLOTHES;
	}
	else if ((RawPotentiometer_u8 < 600) && (RawPotentiometer_u8 > 570)) 
	{
		WashProgram_e = WP_CLEAN_WASHING_MACHINE;
	}
	else if ((RawPotentiometer_u8 < 570) && (RawPotentiometer_u8 > 450)) 
	{
		WashProgram_e = WP_SHIRTS;
	}
	else if ((RawPotentiometer_u8  < 450))  
	{
		WashProgram_e = WP_NOT_USED;
		//SERIAL_PRINT("We are over limit");
	}
	else 
	{
		WashProgram_e = WP_NONE;
		
	}

    
	
    return WashProgram_e;
}


Potentiometer::Potentiometer(uint8_t InputPin_u8)
{
	this->InputPin_u8 = InputPin_u8;
	this->InitFlag_b  = false;
}

void Potentiometer::TurnProgramLED_v(WashingProgram_te ProgramSelected_e)
{
    // TBD Map an led color to the selected washing program
	// TODO are wee still keeping this?
	// Nu STIU??
}
