// LCDDisplay.h

#ifndef _LCDDISPLAY_h
#define _LCDDISPLAY_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

class LCDDisplay
{

private:
    uint8_t SdaPinNumber_u8;
    uint8_t SclPinNumber_u8;
    uint8_t DeviceAdress_u8;

    bool SendCommand_b();


public:
   
    LCDDisplay(uint8_t SdaPinNumber_u8, uint8_t SclPinNumber_u8, uint8_t DeviceAdress_u8)
    {
        this->SclPinNumber_u8 = SclPinNumber_u8;
        this->SdaPinNumber_u8 = SdaPinNumber_u8;
        this->DeviceAdress_u8 = DeviceAdress_u8;
    }

    void init_v();
    bool SendCharacter_b(char CharacterToSend_c);
    bool SendString_b(char* StringToSend_pc);

};


#endif

