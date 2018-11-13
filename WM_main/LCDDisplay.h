// LCDDisplay.h

#ifndef _LCDDISPLAY_h
#define _LCDDISPLAY_h

#define CURSOR_INITIAL_INDEX 0

#include "Arduino.h"
#include "LiquidCrystal_I2C.h"
class LCDDisplay
{

private:
    uint8_t SdaPinNumber_u8;
    uint8_t SclPinNumber_u8;
    uint8_t DeviceAdress_u8;
    uint8_t WritingCursorLine_u8;
    uint8_t WritingCursorColumn_u8;
    bool SendCommand_b();
    bool SendCharacter_b(char CharacterToSend_c);


public:
   
    LCDDisplay(uint8_t SdaPinNumber_u8, uint8_t SclPinNumber_u8, uint8_t DeviceAdress_u8)
    {
        this->SclPinNumber_u8 = SclPinNumber_u8;
        this->SdaPinNumber_u8 = SdaPinNumber_u8;
        this->DeviceAdress_u8 = DeviceAdress_u8;
        WritingCursorColumn_u8 = CURSOR_INITIAL_INDEX;
        WritingCursorLine_u8 = CURSOR_INITIAL_INDEX;
    }

    void init_v();
    bool DisplayString_b(char* StringToSend_pc);
    bool ClearScreen_b();

};

#endif

