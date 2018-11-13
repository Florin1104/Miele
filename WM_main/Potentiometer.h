// Potentiometer.h

#ifndef _POTENTIOMETER_h
#define _POTENTIOMETER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class Potentiometer
{

 private:
     uint8_t InputPin_u8;
 protected:


 public:
     Potentiometer(uint8_t InputPin_u8) { this->InputPin_u8 = InputPin_u8; }
     
};



#endif

