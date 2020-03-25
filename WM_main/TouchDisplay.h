/*******************************************************************************
@Module          Touch Display

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

#ifndef _TOUCHDISPLAY_h
#define _TOUCHDISPLAY_h
/*******************************************************************************
@Project Includes
*******************************************************************************/
	
#include <SPI.h>	
#include "Ucglib.h"
#include "XPT2046.h"	
#include "Arduino.h"
#include "GenericDisplay.h"

/*******************************************************************************
@Constants (global)
*******************************************************************************/

//colors
#define DISPLAY_COLOR_WHITE 			255,255,255
#define DISPLAY_COLOR_BLACK 			0,0,0
#define DISPLAY_COLOR_DK_RED 			178,31,53
#define DISPLAY_COLOR_RED	 			216,39,53
#define DISPLAY_COLOR_ORANGE 			255,116,53
#define DISPLAY_COLOR_MANDARIN 			255,161,53
#define DISPLAY_COLOR_SUNFLOWER 		255,203,53
#define DISPLAY_COLOR_YELLOW 			255,249,53
#define DISPLAY_COLOR_GRASS_GREEN 		0,117,58
#define DISPLAY_COLOR_GREEN 			0,158,71
#define DISPLAY_COLOR_LIGHT_GREEN 		22,221,53
#define DISPLAY_COLOR_NAVY				0,82,165
#define DISPLAY_COLOR_OCEAN 			0,121,231
#define DISPLAY_COLOR_SKY_BLUE 			0,169,252
#define DISPLAY_COLOR_PLUM 				104,30,126
#define DISPLAY_COLOR_INDIGO 			125,60,181
#define DISPLAY_COLOR_LIGHT_PURPLE 		181,122,246



//fonts
//TODO add tested fonts TBD
class TouchDisplay: public GenericDisplay
{
	
private:

	uint8_t sclkPinNumber_u8;
	uint8_t dataPinNumber_u8; 
	uint8_t cdPinNumber_u8;
	uint8_t csPinNumber_u8; 
	uint8_t resetPinNumber_u8;
	
	
	// Writing coordinates of the LCD cursor
    uint8_t WritingCursor_X_u8; //lines
    uint8_t WritingCursor_Y_u8; //columns
	
	
	// Pointer to the Ucglib_ILI9341_18x240x320_SWSPI object
    Ucglib_ILI9341_18x240x320_SWSPI  * touchDisp_po;
		
public:
   
    /*******************************************************************************
    @Description   Constructor used to initialize a TouchDisplay object

    --------------------------------------------------------------------------------
    @Returns       none

    --------------------------------------------------------------------------------
    @Parameters     sclkPinNumber_u8 is the number of the sclk pin
				    dataPinNumber_u8 is the number of the data pin
					cdPinNumber_u8 is the number of the cd pin
					csPinNumber_u8 is the number of the chip select pin
					resetPinNumber_u8 is the number of the reset pin
    *******************************************************************************/
    TouchDisplay(uint8_t sclkPinNumber_u8, uint8_t dataPinNumber_u8, uint8_t cdPinNumber_u8, 
				 uint8_t csPinNumber_u8, uint8_t resetPinNumber_u8)
    {
        this->sclkPinNumber_u8 = sclkPinNumber_u8;
        this->dataPinNumber_u8 = dataPinNumber_u8;
        this->cdPinNumber_u8 = cdPinNumber_u8;
		this->csPinNumber_u8 = csPinNumber_u8;
        this->resetPinNumber_u8 = resetPinNumber_u8;
		WritingCursor_X_u8 = 0;
		WritingCursor_Y_u8 = 0;
		touchDisp_po = NULL;
        
    }

	
	
	/*******************************************************************************
    @Description   	Destructor deletes TouchDisplay's objects and clears the screen
					of old messages
    --------------------------------------------------------------------------------
    @Returns       none

    --------------------------------------------------------------------------------
    @Parameters    none
    *******************************************************************************/
	~TouchDisplay()
    {
        (void)ClearScreen_b();
    }
	
	
	
	/*******************************************************************************
    @Description   Used to initialize the Touch display

    --------------------------------------------------------------------------------
    @Returns       none

    --------------------------------------------------------------------------------
    @Parameters    none
    *******************************************************************************/
	bool init_b();
	
	
	
	/*******************************************************************************
    @Description   Used to display a string to the Touch display

    --------------------------------------------------------------------------------
    @Returns       true - if the process succeeds
                   false - if the process fails

    --------------------------------------------------------------------------------
    @Parameters    
    *******************************************************************************/
	bool DisplayString_b(char* StringToDisplay_pc);
	
	
	
	/*******************************************************************************
    @Description   Used to clear the screen of the Touch display

    --------------------------------------------------------------------------------
    @Returns       true - if the process succeeds
                   false - if the process fails

    --------------------------------------------------------------------------------
    @Parameters     none
    *******************************************************************************/
	bool ClearScreen_b();
};
	
	
	
#endif