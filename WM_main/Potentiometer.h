// Potentiometer.h

#ifndef _POTENTIOMETER_h
#define _POTENTIOMETER_h

#include "Arduino.h"

// Define the washing program to select
typedef enum WashingProgram {
    WP_NONE = 0,
    // ..
}WashingProgram_te;

class Potentiometer
{

 private:
     uint8_t InputPin_u8;
     void TurnProgramLED_v();
 


 public:
     Potentiometer(uint8_t InputPin_u8) { this->InputPin_u8 = InputPin_u8; }
     WashingProgram_te GetSelectedProgram();

     
};

#endif

