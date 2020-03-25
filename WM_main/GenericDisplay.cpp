#include "GenericDisplay.h"


/*******************************************************************************
Since most of the times, the display will be an LCD 16x2, the default init_b 
will be implemented for this type of display
*******************************************************************************/
bool GenericDisplay::init_b() 
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
Since most of the times, the display will be an LCD 16x2, the default
DisplayString_b will be implemented for this type of display
*******************************************************************************/
bool GenericDisplay::DisplayString_b(char* StringToDisplay_pc)
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
	}
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
Since most of the times, the display will be an LCD 16x2, the default
ClearScreen_b will be implemented for this type of display
*******************************************************************************/
bool GenericDisplay::ClearScreen_b() 
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
Since most of the times, the display will be an LCD 16x2, the default
AutoScroll_b will be implemented for this type of display
*******************************************************************************/
bool GenericDisplay::AutoScroll_b() {}


/*******************************************************************************
Since most of the times, the display will be an LCD 16x2, the default 
ChangeFontSize_b will be implemented for this type of display
*******************************************************************************/
bool GenericDisplay::ChangeFontSize_b() {}

/*******************************************************************************
Since most of the times, the display will be an LCD 16x2, the default 
SendCharacter_b will be implemented for this type of display
*******************************************************************************/
bool GenericDisplay::SendCharacter_b(char CharacterToDisplay)
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