#ifndef _TOUCHDISPLAY_h
	#define _TOUCHDISPLAY_h
	
#include "Ucglib.h"
#include "XPT2046.h"	
#include "Arduino.h"
#include "GenericDisplay.h"


class TouchDisplay():public GenericDisplay
{
	
private:

	uint8_t sclkPinNumber_u8;
	uint8_t dataPinNumber_u8; 
	uint8_t cdPinNumber_u8;
	uint8_t csPinNumber_u8; 
	uint8_t resetPinNumber_u8;
		
public:
   
    /*******************************************************************************
    @Description   Constructor used to initialize a TouchDisplay object

    --------------------------------------------------------------------------------
    @Returns       none

    --------------------------------------------------------------------------------
    @Parameters    
    *******************************************************************************/
    LCDDisplay(uint8_t sclkPinNumber_u8, uint8_t dataPinNumber_u8, uint8_t cdPinNumber_u8, uint8_t csPinNumber_u8, uint8_t resetPinNumber_u8)
    {
        this->sclkPinNumber_u8 = sclkPinNumber_u8;
        this->dataPinNumber_u8 = dataPinNumber_u8;
        this->cdPinNumber_u8 = cdPinNumber_u8;
		this->csPinNumber_u8 = csPinNumber_u8;
        this->resetPinNumber_u8 = resetPinNumber_u8;
        
    }

	
	/*******************************************************************************
    @Description   Used to initialize the Touch display

    --------------------------------------------------------------------------------
    @Returns       none

    --------------------------------------------------------------------------------
    @Parameters    none
    *******************************************************************************/
	void init_b()
	{
		
	}
	
	
	/*******************************************************************************
    @Description   Used to display a string to the Touch display

    --------------------------------------------------------------------------------
    @Returns       true - if the process succeeds
                   false - if the process fails

    --------------------------------------------------------------------------------
    @Parameters    
    *******************************************************************************/
	bool DisplayString_b()
	{
			
	}
	
	/*******************************************************************************
    @Description   Used to clear the screen of the Touch display

    --------------------------------------------------------------------------------
    @Returns       true - if the process succeeds
                   false - if the process fails

    --------------------------------------------------------------------------------
    @Parameters     none
    *******************************************************************************/
	bool ClearScreen_b() = 0;
	
	
	

    /*******************************************************************************
    @Description   Destructor

    --------------------------------------------------------------------------------
    @Returns       none

    --------------------------------------------------------------------------------
    @Parameters    none
    *******************************************************************************/
    ~LCDDisplay()
    {
        (void)ClearScreen_b();
    }

	
		
};
	
	
	
#define _TOUCHDISPLAY_h