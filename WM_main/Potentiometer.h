/*******************************************************************************
@Module          Potentiometer
--------------------------------------------------------------------------------
@Filename        Potentiometer.h

--------------------------------------------------------------------------------
@Description     Mainly used for interpreting different potentiometer positions 
                 as washing programs 
--------------------------------------------------------------------------------
@Author          Marian S., Baver D., Stefan I.
@Date            13.11.2018

-------------------------------------------------------------------------------
@Copyright       Miele & Cie Copyright 2020
*******************************************************************************/

/*******************************************************************************
// Example:
Potentiometer x(GPIO_NUM_27);

// This should be in the setup()

if (x.Init_b() == true)
{
	Serial.println("We are now initialized.");
}

// This should be in the loop()

WashingProgram_te WashProgram_e = x.GetSelectedProgram();

if (WashProgram_e == WP_WASH)
{
	// Do something
}
else if (WashProgram_e == WP_SPIN)
{
	// You need to select a program by turning the wheel
}
else if (WashProgram_e == WP_WHITE_CLOTHES)
{
	// You need to select a program by turning the wheel
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
	//  Position 1 - Used for selecting wash program 
	WP_WASH = 1,
	//	Position 2 - Used for only spinning the tub 
	WP_SPIN = 2,
	//	Position 3 - Used for selecting hand wash program 
	WP_HANDWASH = 3,
	//	Position 4 - Used for selecting fast-wash program 
	WP_FAST_WASH = 4,
	//	Position 5 - Used for selecting intense wash program 
	WP_INTENSE_WASH = 5,
	//	Position 6 - Used for selecting to wash white clothes 
	WP_WHITE_CLOTHES = 6,
	//	Position 7 - Used for selecting to wash only the washing machine itself 
	WP_CLEAN_WASHING_MACHINE = 7, 
	//	Position 8 - Used for selecting a wash program for shirts
	WP_SHIRTS   = 8,
	//	Position 9 and above have no program attached 
	WP_NOT_USED = 9,
	// Warning!! This should be the last in enum
    WP_ENUM_MAX
}WashingProgram_te;

class Potentiometer
{

 private:
	 // Used to verify if everything is initialized and ready to go
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
     @Parameters    InputPin_u8 - pin number which the potentiometer is attached
     *******************************************************************************/
	 Potentiometer(uint8_t InputPin_u8);
    
	
     /*******************************************************************************
     @Description   Used to get the selected program based on the potentiometer's 
                    position

     --------------------------------------------------------------------------------
     @Returns   WashingProgram_te - Washing program selected
	  WP_NONE - Position 0 - No program is selected
	  WP_WASH - Position 1 - Used for selecting wash program
	  WP_SPIN - Position 2 - Used for only spinning the tub
	  WP_HANDWASH - Position 3 - Used for selecting hand wash program
	  WP_FAST_WASH - Position 4 - Used for selecting fast-wash program 
	  WP_INTENSE_WASH  - Position 5 - Used for selecting intense wash program
	  WP_WHITE_CLOTHES - Position 6 - Used for selecting to wash white clothes 
	  WP_CLEAN_WASHING_MACHINE - Position 7 - Used for selecting to wash 
                                            only the washing machine itself 
	  WP_SHIRTS - Position 8 - Used for selecting a wash program for shirts 
	  WP_NOT_USED - Position 9 and above have no program attached 

     --------------------------------------------------------------------------------
     @Parameters    None
     *******************************************************************************/
     WashingProgram_te GetSelectedProgram();

 
	 /*******************************************************************************
	 @Description   This method is used to initialize the module. It should be called
	 after the object creation.

	 --------------------------------------------------------------------------------
	 @Returns       TRUE  - the device has initialized
					FALSE - the device failed to initialized

	 --------------------------------------------------------------------------------
	 @Parameters    none
	 *******************************************************************************/
     bool Init_b();

};

#endif