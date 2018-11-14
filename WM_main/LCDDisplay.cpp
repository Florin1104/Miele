/*******************************************************************************
@Module          LCD display

/*******************************************************************************
--------------------------------------------------------------------------------
@Filename        LCDDisplay.cpp

--------------------------------------------------------------------------------
@Description     Implementation of LCDDisplay class

--------------------------------------------------------------------------------
@Author          Marian S.
@Date            14.11.2018

-------------------------------------------------------------------------------
@Copyright       Miele & Cie Copyright 2018
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
    if (lcd_po != NULL && StringToDisplay_pc !=NULL)
    {
        while (*StringToDisplay_pc != '\0')
        {
            if (SendCharacter_b(*StringToDisplay_pc))
                StringToDisplay_pc++;
            return false;
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
                WritingCursorLine_u8++;
            else
                (void)ClearScreen_b();
        }
        lcd_po->setCursor(WritingCursorColumn_u8, WritingCursorLine_u8);
        lcd_po->print(CharacterToDisplay);
        WritingCursorColumn_u8++;
        return true;
    }
    return false;
}
