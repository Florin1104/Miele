/*******************************************************************************
@Module          LCD display

/*******************************************************************************
--------------------------------------------------------------------------------
@Filename        LCDDisplay.h

--------------------------------------------------------------------------------
@Description     Used mainly for driving the 1600/2004 LCD display with the I2C 
                 adapter

--------------------------------------------------------------------------------
@Author          Marian S.
@Date            13.11.2018

-------------------------------------------------------------------------------
@Copyright       Miele & Cie Copyright 2018
*******************************************************************************/


// !!! USE CASE EXAMPLE !!!
// Create an object globally
// In the setup function call .init() -> check for errors
// Whenever you want to display something on THE LCD, call DisplayString_b() with the string you want to display

// LCDDisplay lcd();

// void setup()
// { ... 
// lcd.init(); 
//  ... }

// void loop()
// { ... 
// lcd.DisplayString("Hello BuzzCamp !!"); 
//  ... }

#ifndef _LCDDISPLAY_h
#define _LCDDISPLAY_h

// Initial starting point of the LCD cursor (0,0)
#define CURSOR_INITIAL_INDEX 0
#define NUMBER_OF_COLUMNS    1
#define NUMBER_OF_ROWS       2

#include "Arduino.h"
#include "LiquidCrystal_I2C.h"
class LCDDisplay
{

private:

    uint8_t SdaPinNumber_u8;
    uint8_t SclPinNumber_u8;
    uint8_t DeviceAdress_u8;

    // Writing coordinates of the LCD cursor
    uint8_t WritingCursorLine_u8;
    uint8_t WritingCursorColumn_u8;
    // Send a specific command to the LCD display
    // TBD if needed
    //bool SendCommand_b();

    // Send a character to the LCD display (it is mainly called to display a string)
    bool SendCharacter_b(char CharacterToSend_c);

    // Pointer to the object 
    LiquidCrystal_I2C * lcd_po;


public:
   
    /*******************************************************************************
    @Description   Constructor used to initialize a LCD display object

    --------------------------------------------------------------------------------
    @Returns       none

    --------------------------------------------------------------------------------
    @Parameters    SdaPinNumber_u8 - for the data line in the I2C protocol
                   SclPinNumber_u8 - for the clock line in the I2C protocol
                   DeviceAdress_u8 - device's adress in the I2C protocol
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

};

#endif

