/*******************************************************************************
@Module          LCD display

/*******************************************************************************
--------------------------------------------------------------------------------
@Filename        Potentiometer.h

--------------------------------------------------------------------------------
@Description     Mainly used for interpreting different potetiometer positions 
                 as wasching programmes

--------------------------------------------------------------------------------
@Author          Marian S.
@Date            13.11.2018

-------------------------------------------------------------------------------
@Copyright       Miele & Cie Copyright 2018
*******************************************************************************/

#ifndef _POTENTIOMETER_h
#define _POTENTIOMETER_h

#include "Arduino.h"

// Define the washing program to select
typedef enum WashingProgram {
    WP_NONE = 0,
    // .. TBD
}WashingProgram_te;

class Potentiometer
{

 private:

     // Holds the number of the pin that the potentiometer is attached to
     uint8_t InputPin_u8;
     // When the user checks for a program, turn de according LED on
     void TurnProgramLED_v();
 


 public:

     /*******************************************************************************
     @Description   Constructor used to initialize a potentiometer object

     --------------------------------------------------------------------------------
     @Returns       none

     --------------------------------------------------------------------------------
     @Parameters    InputPin_u8 - pin number which the potetntiometer is attached
     *******************************************************************************/
     Potentiometer(uint8_t InputPin_u8) { this->InputPin_u8 = InputPin_u8; }
    
     /*******************************************************************************
     @Description   Used to get the selected program based on the potentiometer's 
                    position

     --------------------------------------------------------------------------------
     @Returns       WashingProgram_te - Wasching program selected

     --------------------------------------------------------------------------------
     @Parameters    None
     *******************************************************************************/
     WashingProgram_te GetSelectedProgram();

     
};

#endif

