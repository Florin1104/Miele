/*******************************************************************************
@Module          LCD display

--------------------------------------------------------------------------------
@Filename        LCDDisplay.cpp

--------------------------------------------------------------------------------
@Description     Implementation of LCDDisplay class

--------------------------------------------------------------------------------
@Author          Marian S., Fabian V.
@Date            14.11.2018

-------------------------------------------------------------------------------
@Copyright       Miele & Cie Copyright 2020
*******************************************************************************/

#include "LCDDisplay.h"

/*******************************************************************************
Function description and additional notes,
are given at the function prototype in the header file
*******************************************************************************/
bool LCDDisplay::init_b() 
{
    if (lcd_po == NULL)
    {
        lcd_po = new LiquidCrystal_I2C(DeviceAdress_u8, NUMBER_OF_COLUMNS, 
            NUMBER_OF_ROWS, LCD_2LINE);
        lcd_po->begin();
        lcd_po->backlight();
        return true;
    }
    return false;
}

/*******************************************************************************
Function description and additional notes,
are given at the function prototype in the header file
*******************************************************************************/
bool LCDDisplay::ClearScreen_b()
{
    if (lcd_po != NULL)
    {
        lcd_po->clear();
        WritingCursorColumn_u8 = WritingCursorLine_u8 = 0;
        return true;
    }

    return false;
}

/*******************************************************************************
Function description and additional notes,
are given at the function prototype in the header file
*******************************************************************************/
bool LCDDisplay::DisplayString_b(char* StringToDisplay_pc)
{
	// maximum for filling the connected LCD display
	if (strlen(StringToDisplay_pc) > NUMBER_OF_COLUMNS*NUMBER_OF_ROWS)
	{
		ClearScreen_b();
		DisplayString_b("FORBIDDEN!");
	}
	
	//WTF IS THIS FOR?
	if (strcmp(StringToDisplay_pc, "FORBIDDEN!") == 0)
	{
		return false;
	}//end of WTF
    if (lcd_po != NULL && StringToDisplay_pc !=NULL)
    {
        while (*StringToDisplay_pc != '\0')
        {
			if (SendCharacter_b(*StringToDisplay_pc) == true)
			{
				StringToDisplay_pc++;
			}
			else 
			{
				return false;
			}
				
        }
        return true;

    }
    return false;
}

/*******************************************************************************
Function description and additional notes,
are given at the function prototype in the header file
*******************************************************************************/
bool LCDDisplay::SendCharacter_b(char CharacterToDisplay)
{
    if (lcd_po != NULL)
    {
        if (WritingCursorColumn_u8 == NUMBER_OF_COLUMNS - 1)
        {
			if (WritingCursorLine_u8 < 1) 
			{
                WritingCursorLine_u8++;
				WritingCursorColumn_u8 = 0;
			}
			else
			{
                (void)ClearScreen_b();
			}
        }
        lcd_po->setCursor(WritingCursorColumn_u8, WritingCursorLine_u8);
        lcd_po->print(CharacterToDisplay);
        WritingCursorColumn_u8++;
        return true;
    }
    return false;
}
/*******************************************************************************
Function description and additional notes,
are given at the function prototype in the header file
*******************************************************************************/
bool LCDDisplay::m_isPinI2C_b(uint8_t Pin_u8)
{
	bool isI2CPinValid_b=false;

	// All the pins that are I2C capable for ESP32.
    const uint8_t ValidI2CPins_au8[] = VALID_PWM_I2C_PINS;
	
	// Is pin I2C capable?
	for (uint8_t i = 0; i< sizeof(ValidI2CPins_au8)/sizeof(ValidI2CPins_au8[0]); i++)
	{
		if(Pin_u8 == ValidI2CPins_au8[i])
		{
			isI2CPinValid_b=true;
			break;
		}
	}
	return isI2CPinValid_b;
}
