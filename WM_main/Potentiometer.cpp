
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
@Copyright       Miele & Cie Copyright 2019
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



    int PotentiometerValue = 0;
    //PotentiometerValue = map(RawPotentiometer_u8,0,4095,0,100); // TODO  do we still need this?
	//Serial.println(PotentiometerValue);
	//Serial.println(RawPotentiometer_u8);


	if ((RawPotentiometer_u8 > 1) && (RawPotentiometer_u8 < 200)) //200
	{
		WashProgram_e = WP_WASH;
		//SERIAL_PRINT("Program selected is simple wash");

	}
	else if ((RawPotentiometer_u8 > 200) && (RawPotentiometer_u8 < 600))//200 600
	{
		WashProgram_e = WP_SPIN;
		//SERIAL_PRINT("Now we are spining"); // TODO spinning (Do we need this serial prins here?

	}
	else if ((RawPotentiometer_u8 > 600) && (RawPotentiometer_u8 < 1000))//600 1000
	{
		WashProgram_e = WP_HANDWASH;
		//SERIAL_PRINT("Program selected is handwash");
	}
	else if ((RawPotentiometer_u8 > 1000) && (RawPotentiometer_u8 < 1500)) //1000 1500
	{
		WashProgram_e = WP_FAST_WASH;
		//SERIAL_PRINT("Program selected is fast wash");
	}
	else if ((RawPotentiometer_u8 > 1500) && (RawPotentiometer_u8 < 2000)) //1500 2000
	{
		WashProgram_e = WP_INTENSE_WASH;
		//SERIAL_PRINT("Program selected is intense wash");
	}
	else if ((RawPotentiometer_u8 > 2000) && (RawPotentiometer_u8 < 2400)) //200 2400
	{
		WashProgram_e = WP_WHITE_CLOTHES;
		//SERIAL_PRINT("We are now washing white clothes");
	}
	else if ((RawPotentiometer_u8 > 2400) && (RawPotentiometer_u8 < 2800)) //2400 2800
	{
		WashProgram_e = WP_CLEAN_WASHING_MACHINE;
		//SERIAL_PRINT("We are now cleaning the washing machine");
	}
	else if ((RawPotentiometer_u8 > 2800) && (RawPotentiometer_u8 < 3250)) //2800 3250
	{
		WashProgram_e = WP_SHIRTS;
		//SERIAL_PRINT("We are now washing shirts");
	}
	else if ((RawPotentiometer_u8  > 3250))  //3250
	{
		WashProgram_e = WP_NOT_USED;
		//SERIAL_PRINT("We are over limit");
	}
	else 
	{
		WashProgram_e = WP_NONE;
		//SERIAL_PRINT("We are doing nothing");
	}

    // TBD: Map the program to the read value
	
    return WashProgram_e;
}


Potentiometer::Potentiometer(uint8_t InputPin_u8)
{
	this->InputPin_u8 = InputPin_u8;
	this->InitFlag_b  = false;
}

void Potentiometer::TurnProgramLED_v(WashingProgram_te ProgramSelected_e)
{
    // TBD Map an led color to the selected wasching program
	// TODO are wee still keeping this?
}
