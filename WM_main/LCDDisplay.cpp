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
LiquidCrystal_I2C* LCDDisplay::StartCommunication_b()
{
    static LiquidCrystal_I2C lcd(DeviceAdress_u8,NUMBER_OF_COLUMNS,NUMBER_OF_COLUMNS);
    if (!initflag_b)
    {
        lcd.begin();
        initflag_b = true;
    }
    return &lcd;
}

/*******************************************************************************
Function description and additional notes,
are given at the function prototype in the header file
*******************************************************************************/
bool LCDDisplay::ClearScreen_b()
{
    StartCommunication_b()->clear();
    WritingCursorColumn_u8 = WritingCursorLine_u8 = 0;
}

/*******************************************************************************
Function description and additional notes,
are given at the function prototype in the header file
*******************************************************************************/
bool LCDDisplay::DisplayString_b(char* StringToDisplay_pc)
{
    if (StringToDisplay_pc != NULL)
    {
        
        while (*StringToDisplay_pc != '\0')
        {
            SendCharacter_b(*StringToDisplay_pc);
            StringToDisplay_pc++;
        }
    }
    return false;
}

/*******************************************************************************
Function description and additional notes,
are given at the function prototype in the header file
*******************************************************************************/
bool LCDDisplay::SendCharacter_b(char CharacterToDisplay)
{
    
        if (WritingCursorColumn_u8 == NUMBER_OF_COLUMNS - 1)
        {
            if (WritingCursorLine_u8 < 1)
            {
                WritingCursorLine_u8++;
                WritingCursorColumn_u8 = 0;
            }
            else
                (void)ClearScreen_b();
        }
        LiquidCrystal_I2C *lcd = StartCommunication_b();
        lcd->setCursor(WritingCursorColumn_u8, WritingCursorLine_u8);
        lcd->print(CharacterToDisplay);
        WritingCursorColumn_u8++;
        return true;
   
}
