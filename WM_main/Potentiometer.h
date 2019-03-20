/*******************************************************************************
@Module          Potentiometer

/*******************************************************************************
--------------------------------------------------------------------------------
@Filename        Potentiometer.h

--------------------------------------------------------------------------------
@Description     Mainly used for interpreting different potetiometer positions 
                 as washing programmes

--------------------------------------------------------------------------------
@Author          Marian S., Baver D.
@Date            13.11.2018

-------------------------------------------------------------------------------
@Copyright       Miele & Cie Copyright 2019
*******************************************************************************/

/*******************************************************************************
// Example:
Potentiometer x(GPIO_NUM_25);

// This should be in the setup()

if (x.init_b() == true)
{
	Serial.println("We are now intialised.");
}

// This should be in the loop()

WashingProgram_te WashProgram_e = x.GetSelectedProgram();

if (WashProgram_e == WP_WASH)
{
	// Do something
}
else if (WashProgram_e == WP_NONE || WashProgram_e == WP_NOT_USED)
{
	// You need to select a program by turning the wheel
}
else
{
	// Other program used
}
*******************************************************************************/

#ifndef _POTENTIOMETER_H_
#define _POTENTIOMETER_H_

#include "Arduino.h"

// Define the washing program to select
typedef enum WashingProgram 
{
	// Position 0 - No program is selected
    WP_NONE = 0,
	//  Postion 1 - Used for selecting wash program
	WP_WASH = 1,
	//	Postion 2 - Used for only spinning the tub
	WP_SPIN = 2,
	//	Postion 3 - Used for selecting handwash program
	WP_HANDWASH = 3,
	//	Postion 4 - Used for selecting fast-wash program
	WP_FAST_WASH = 4,
	//	Postion 5 - Used for selecting intense wash program
	WP_INTENSE_WASH = 5,
	//	Postion 6 - Used for selecting to wash white clothes
	WP_WHITE_CLOTHES = 6,
	//	Postion 7 - Used for selecting to wash only the washing machine itself
	WP_CLEAN_WASHING_MACHINE = 7,
	//	Postion 8 - Used for selecting a wash program for shirts
	WP_SHIRTS   = 8,
	//	Postions 9 and above have no program attached
	WP_NOT_USED = 9,
	// Warning!! This should be the last in enum
    WP_ENUM_MAX
}	

WashingProgram_te;

class Potentiometer
{

 private:
	 // Used to verify if everything is initialized adn ready to go
     bool InitFlag_b;
     // Holds the number of the pin that the potentiometer is attached to
     uint8_t InputPin_u8;
     // When the user checks for a program, turn de according LED on
     void TurnProgramLED_v(WashingProgram_te SelectedProgram_e);
 


 public:

     /*******************************************************************************
     @Description   Constructor used to initialize a potentiometer object

     --------------------------------------------------------------------------------
     @Returns       none

     --------------------------------------------------------------------------------
     @Parameters    InputPin_u8 - pin number which the potetntiometer is attached
     *******************************************************************************/
	 Potentiometer(uint8_t InputPin_u8);
    
     /*******************************************************************************
     @Description   Used to get the selected program based on the potentiometer's 
                    position

     --------------------------------------------------------------------------------
     @Returns       WashingProgram_te - Wasching program selected
					    WP_NONE - Postion 0 - No program is selected
						WP_WASH - Postion 1 - Used for selecting wash program
						WP_SPIN - Postion 2 - Used for only spinning the tub
						WP_HANDWASH - Postion 3 - Used for selecting handwash program
						WP_FAST_WASH - Postion 4 - Used for selecting fast-wash program
						WP_INTENSE_WASH  - Postion 5 - Used for selecting intense wash program
						WP_WHITE_CLOTHES - Postion 6 - Used for selecting to wash white clothes
						WP_CLEAN_WASHING_MACHINE - Postion 7 - Used for selecting to wash only the washing machine itself
						WP_SHIRTS - Postion 8 - Used for selecting a wash program for shirts
						WP_NOT_USED - Postions 9 and above have no program attached

     --------------------------------------------------------------------------------
     @Parameters    None
     *******************************************************************************/
     WashingProgram_te GetSelectedProgram();

 
	 /*******************************************************************************
	 @Description   This method is used to initialise the module. It should be called
	 after the object creation.

	 --------------------------------------------------------------------------------
	 @Returns       none

	 --------------------------------------------------------------------------------
	 @Parameters    none
	 *******************************************************************************/
     bool Init_b();

};

#endif