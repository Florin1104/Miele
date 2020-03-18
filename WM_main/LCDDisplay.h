/*******************************************************************************
@Module          LCD display

/******************************************************************************* // TODO delete this line you already have it
--------------------------------------------------------------------------------
@Filename        LCDDisplay.h

--------------------------------------------------------------------------------
@Description     Used mainly for driving the 1600/2004 LCD display with the I2C 
                 adapter

--------------------------------------------------------------------------------
@Author          Marian S., Fabian V.
@Date            20.03.2019

-------------------------------------------------------------------------------
@Copyright       Miele & Cie Copyright 2019
*******************************************************************************/


// !!! USE CASE EXAMPLE !!!
// Create an object globally
// LCDDisplay disp_o(21, 22, 0x27);		For this LCD Screen the address will be 0x27 // TODO this example does not work (trust me :P) please assure that each example provided it is working.
// In the setup function call .init() -> check for errors
// Whenever you want to display something on THE LCD, call DisplayString_b() with the string you want to display

//void setup()
//{
//  Serial.begin(9600);
//	lcd.init_b();
//}
//
//void loop()
//{   
//	lcd.DisplayString_b("Hello world1");
//	delay(1000);
//	lcd.ClearScreen_b();
//	lcd.DisplayString_b("Hello world2");
//}

#ifndef _LCDDISPLAY_h
#define _LCDDISPLAY_h

// Initial starting point of the LCD cursor (0,0)
#define CURSOR_INITIAL_INDEX 0
#define NUMBER_OF_COLUMNS    16
#define NUMBER_OF_ROWS       2

#include "Arduino.h"
#include "LiquidCrystal_I2C.h"
class LCDDisplay
{

private:
	// TODO missing description 
    uint8_t SdaPinNumber_u8;
    uint8_t SclPinNumber_u8;
    uint8_t DeviceAdress_u8;

    // Writing coordinates of the LCD cursor
    uint8_t WritingCursorLine_u8;
    uint8_t WritingCursorColumn_u8;

    // Send a character to the LCD display (it is mainly called to display a string)
    bool SendCharacter_b(char CharacterToSend_c);

    // Pointer to the object // TODO this is obvious what is the purpose of this pointer why is to LiquidCrystal_I2C
    LiquidCrystal_I2C * lcd_po;


public:
   
    /*******************************************************************************
    @Description   Constructor used to initialize a LCD display object

    --------------------------------------------------------------------------------
    @Returns       none

    --------------------------------------------------------------------------------
    @Parameters    SdaPinNumber_u8 - for the data line in the I2C protocol // TODO what pin number can i use here?
                   SclPinNumber_u8 - for the clock line in the I2C protocol
                   DeviceAdress_u8 - device's adress in the I2C protocol //TODO address, how can i find this address?
    *******************************************************************************/
    LCDDisplay(uint8_t SdaPinNumber_u8, uint8_t SclPinNumber_u8, uint8_t DeviceAdress_u8)
    {
        this->SclPinNumber_u8 = SclPinNumber_u8;
        this->SdaPinNumber_u8 = SdaPinNumber_u8;
        this->DeviceAdress_u8 = DeviceAdress_u8;
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

	// TODO add description
    bool init_b();
    
    /*******************************************************************************
    @Description   Used to display a string to the LCD display

    --------------------------------------------------------------------------------
    @Returns       true - if the process succeeds
                   false - if the process fails

    --------------------------------------------------------------------------------
    @Parameters    StringToSend_pc - pointer to the beginning of the string to be 
                   sent
    *******************************************************************************/
    bool DisplayString_b(char* StringToSend_pc);

    /*******************************************************************************
    @Description   Used to clear the screen of the LCD display

    --------------------------------------------------------------------------------
    @Returns       true - if the process succeeds
                   false - if the process fails

    --------------------------------------------------------------------------------
    @Parameters     none
    *******************************************************************************/
    bool ClearScreen_b();

	/*******************************************************************************
    @Description   Private method to check if a pin is I2C capable.

    --------------------------------------------------------------------------------
    @Returns       True if pin is I2C capable.
                   False otherwise.

    --------------------------------------------------------------------------------
    @Parameters    Pin_u8 - Pin number to be checked.

    *******************************************************************************/
	bool m_isPinI2C_b(uint8_t Pin_u8);
};

#endif

