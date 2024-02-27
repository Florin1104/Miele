/*******************************************************************************
@Module          Touch display
--------------------------------------------------------------------------------
@Filename        TouchDisplay.cpp
--------------------------------------------------------------------------------
@Description     Implementation of TouchDisplay class
--------------------------------------------------------------------------------
@Author          Stefan I.
@Date            18.03.2020
-------------------------------------------------------------------------------
@Copyright       Miele & Cie Copyright 2020
*******************************************************************************/

#include "TouchDisplay.h"


/*******************************************************************************
Function description and additional notes,
are given at the function prototype in the header file
*******************************************************************************/
bool TouchDisplay::init_b()
{
	if (touchDisp_po != NULL)
    {
        touchDisp_po = new Ucglib_ILI9341_18x240x320_SWSPI(sclkPinNumber_u8, dataPinNumber_u8, cdPinNumber_u8, 
														   csPinNumber_u8, resetPinNumber_u8);
        touchDisp_po->begin(UCG_FONT_MODE_TRANSPARENT);
		//ucg->begin(UCG_FONT_MODE_SOLID);
		touchDisp_po->clearScreen();
        return true;
    }
    return false;
}


/*******************************************************************************
@Description   Used to clear the screen of the Touch display
--------------------------------------------------------------------------------
@Returns       true - if the process succeeds
               false - if the process fails
--------------------------------------------------------------------------------
@Parameters     none
*******************************************************************************/

bool TouchDisplay::ClearScreen_b()
{
    if (touchDisp_po != NULL)
    {
        touchDisp_po->clearScreen();
		    touchDisp_po->setPrintPos(0,0);
        WritingCursor_X_u8 = WritingCursor_Y_u8 = 0;
        return true;
    }

    return false;
}



/*******************************************************************************
@Description   Used to display a string to the Touch display
--------------------------------------------------------------------------------
@Returns       true - if the process succeeds
               false - if the process fails
--------------------------------------------------------------------------------
@Parameters    
*******************************************************************************/
bool TouchDisplay::DisplayString_b(char* StringToDisplay_pc /*color, direction,indent*/)
{
	// maximum for filling the connected LCD display
	if (strlen(StringToDisplay_pc) > (touchDisp_po->getWidth() * touchDisp_po->getHeight()))
	{
		ClearScreen_b();
		DisplayString_b("ERROR- STRING TOO BIG");
	}
	
	
	if (touchDisp_po != NULL && StringToDisplay_pc !=NULL)
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
bool TouchDisplay::DisplayFormatedString_b(
											char* StringToDisplay_pc,
											uint8_t R, 
											uint8_t G, 
											uint8_t B, 
											uint8_t direction, 
											uint8_t indent_x,  
											uint8_t indent_y,
											const ucg_fntpgm_uint8_t *font
											)
{
	// maximum for filling the connected LCD display
	if (strlen(StringToDisplay_pc) > (touchDisp_po->getWidth() * touchDisp_po->getHeight()))
	{
		ClearScreen_b();
		DisplayString_b("ERROR- STRING TOO BIG");
	}
	
	
	if (touchDisp_po != NULL && StringToDisplay_pc != NULL && font != NULL)
    {
		
		touchDisp_po->setFont(font);
		touchDisp_po->setPrintPos(indent_x, indent_y);
		touchDisp_po->setColor(R, G, B); 
		
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
bool TouchDisplay::SendCharacter_b(char CharacterToDisplay)
{
    if (touchDisp_po != NULL)
    {
        if (WritingCursor_Y_u8 == touchDisp_po->getWidth() - 1)
        {
			if (WritingCursor_X_u8 < 1) 
			{
                WritingCursor_X_u8++;
				WritingCursor_Y_u8 = 0;
			}
			else
			{
                (void)ClearScreen_b();
			}
        }
		
        touchDisp_po->setPrintPos(WritingCursor_Y_u8, WritingCursor_X_u8);
        touchDisp_po->print(CharacterToDisplay);
        WritingCursor_Y_u8++;
        return true;
    }
    return false;
}
