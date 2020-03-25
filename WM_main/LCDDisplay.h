/*******************************************************************************
@Module          LCD display

--------------------------------------------------------------------------------
@Filename        LCDDisplay.h

--------------------------------------------------------------------------------
@Description     Used mainly for driving the 1600/2004 LCD display with the I2C 
                 adapter
--------------------------------------------------------------------------------
@Author          Marian S., Fabian V.
@Date            20.03.2019
-------------------------------------------------------------------------------
@Copyright       Miele & Cie Copyright 2020
*******************************************************************************/


// !!! USE CASE EXAMPLE !!!
// Create an object globally
// LCDDisplay disp_o(21, 22, 0x27);		For this LCD Screen the address will be 0x27. 
// In the setup function call .init() -> check for errors
// Whenever you want to display something on THE LCD, call DisplayString_b() 
// with the string you want to display.

//void setup()
//{
//   // put your setup code here, to run once:
//
//    Serial.begin(9600);                 // serial Init for test messages
//    delay(1500);                        // give time to Wemos Lolin32 to finish setup
//    disp_o.init_b();
//}

//void loop()
//{
//     disp_o.ClearScreen_b();
//    disp_o.DisplayString_b("Hello world1");
//    delay(1000);
//    disp_o.ClearScreen_b();
//    disp_o.DisplayString_b("Hello world2");
//    delay(1000);
//}

#ifndef _LCDDISPLAY_h
#define _LCDDISPLAY_h

// Initial starting point of the LCD cursor (0,0)
//#define CURSOR_INITIAL_INDEX 0		---->found now in GenericDisplay.h
//#define NUMBER_OF_COLUMNS    16		---->found now in GenericDisplay.h
//#define NUMBER_OF_ROWS       2		---->found now in GenericDisplay.h

/*******************************************************************************
@Project Includes
*******************************************************************************/
#include "Arduino.h"
//#include "LiquidCrystal_I2C.h"
#include "GenericDisplay.h"
#include "GeneralConfig.h"




class LCDDisplay: public GenericDisplay
{

private:
	// These are the pins that we use for the I2C protocol.
	// SdaPinNumber_u8 - is used to control the Serial Data Line
	// SclPinNumber_u8 - is used to control the Serial Clock Line 
	// DeviceAdress_u8 - holds the display device address
	
    //uint8_t SdaPinNumber_u8;		---->found now in GenericDisplay.h
    //uint8_t SclPinNumber_u8;		---->found now in GenericDisplay.h
    //uint8_t DeviceAdress_u8;		---->found now in GenericDisplay.h

    // Writing coordinates of the LCD cursor
    //uint8_t WritingCursorLine_u8;			---->found now in GenericDisplay.h
    //uint8_t WritingCursorColumn_u8;		---->found now in GenericDisplay.h

    // Send a character to the LCD display (it is mainly called to display a string)
    bool SendCharacter_b(char CharacterToSend_c);
	
	
	// TODO this is obvious what is the purpose of this pointer why is to LiquidCrystal_I2C
    // Pointer to the object 
    //LiquidCrystal_I2C * lcd_po;		---->found now in GenericDisplay.h


public:
   
    /*******************************************************************************
    @Description   Constructor used to initialize a LCD display object

    --------------------------------------------------------------------------------
    @Returns       none

    --------------------------------------------------------------------------------
	A list of valid I2C pins is available in GeneralConfig.h library.
	
    @Parameters    SdaPinNumber_u8 - for the data line in the I2C protocol 
									 It is recommended to use the hardware implemented
									 I2C pins for simplicity, in this case PIN 22.
									 
                   SclPinNumber_u8 - for the clock line in the I2C protocol
									 It is recommended to use the hardware implemented
									 I2C pins for simplicity, in this case PIN 21.
									 
                   DeviceAdress_u8 - device's address in the I2C protocol 
									The address of the device varies.
									You can find the address of the specific display by consulting
									the device datasheet. In this case, the address is 0x27 for
									LCD 16x2.
    *******************************************************************************/
    LCDDisplay(uint8_t _SdaPinNumber_u8, uint8_t _SclPinNumber_u8, uint8_t _DeviceAdress_u8)
    {
        SclPinNumber_u8 = _SclPinNumber_u8;
        SdaPinNumber_u8 = _SdaPinNumber_u8;
        DeviceAdress_u8 = _DeviceAdress_u8;
        WritingCursorColumn_u8 = CURSOR_INITIAL_INDEX;
        WritingCursorLine_u8 = CURSOR_INITIAL_INDEX;
        lcd_po = NULL;
    }
	

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

	
	/*******************************************************************************
    @Description    This function initializes the display by writing to its internal
					registers using functions from LiquidCrystal_I2C library
    --------------------------------------------------------------------------------
    @Returns       none

    --------------------------------------------------------------------------------
    @Parameters    none
    *******************************************************************************/
    bool init_b();
    
	
    /*******************************************************************************
    @Description   Used to display a string to the LCD display

    --------------------------------------------------------------------------------
    @Returns       TRUE - if the process succeeds
                   FALSE - if the process fails

    --------------------------------------------------------------------------------
    @Parameters    StringToSend_pc - pointer to the beginning of the string to be 
                   sent
    *******************************************************************************/
    bool DisplayString_b(char* StringToSend_pc);

	
	
    /*******************************************************************************
    @Description   Used to clear the screen of the LCD display

    --------------------------------------------------------------------------------
    @Returns       TRUE - if the process succeeds
                   FALSE - if the process fails

    --------------------------------------------------------------------------------
    @Parameters     none
    *******************************************************************************/
    bool ClearScreen_b();

	
	/*******************************************************************************
    @Description   Private method to check if a pin is I2C capable.

    --------------------------------------------------------------------------------
    @Returns       TRUE if pin is I2C capable.
                   FALSE otherwise.

    --------------------------------------------------------------------------------
    @Parameters    Pin_u8 - Pin number to be checked.

    *******************************************************************************/
	bool m_isPinI2C_b(uint8_t Pin_u8);
};

#endif

