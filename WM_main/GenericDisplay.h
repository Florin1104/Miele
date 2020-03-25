/*******************************************************************************
@Module          Generic display
--------------------------------------------------------------------------------
@Filename        GenericDisplay.h
--------------------------------------------------------------------------------
@Description     Used for creating a control interface for all used displays
--------------------------------------------------------------------------------
@Author          Stefan I.
@Date            20.03.2020
-------------------------------------------------------------------------------
@Copyright       Miele & Cie Copyright 2020
*******************************************************************************/
#ifndef _GENERICDISPLAY_h
	#define _GENERICDISPLAY_h
	
#include "LiquidCrystal_I2C.h"



// Since most of the times a display will be LCD 16x2, then this will be the standard definitions.

// Initial starting point of the LCD cursor (0,0)	
#define CURSOR_INITIAL_INDEX 0
#define NUMBER_OF_COLUMNS    16
#define NUMBER_OF_ROWS       2

class GenericDisplay
{
	public:
		virtual bool init_b();
		virtual bool DisplayString_b(char* StringToDisplay_pc);
		virtual bool ClearScreen_b();
        virtual bool SendCharacter_b(char CharacterToDisplay);
		//todo not implemented
		virtual bool AutoScroll_b();
		virtual bool ChangeFontSize_b();
		
		
	// Since most of the times a display will be LCD 16x2, then this will be the standard settings.
	protected:
	LiquidCrystal_I2C * lcd_po;
	// Writing coordinates of the LCD 16x2 cursor.
    uint8_t WritingCursorLine_u8;
    uint8_t WritingCursorColumn_u8;
	
	// These are the pins that we use for the I2C protocol.
	// SdaPinNumber_u8 - is used to control the Serial Data Line
	// SclPinNumber_u8 - is used to control the Serial Clock Line 
	// DeviceAdress_u8 - holds the display device address
    uint8_t SdaPinNumber_u8;
    uint8_t SclPinNumber_u8;
    uint8_t DeviceAdress_u8;
};


#endif