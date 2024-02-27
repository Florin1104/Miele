/*******************************************************************************
@Filename       WM_main.ino
--------------------------------------------------------------------------------
@Description    This is the main file. This is where the functions are called inside
        setup() function or in the loop() function

--------------------------------------------------------------------------------
@Author        Dragos B., Marian S., Stefan I.
@Date          23.03.2020

@Copyright     Miele  Cie Copyright 2020

*******************************************************************************/



/*******************************************************************************
@Project Includes
*******************************************************************************/
#include "ControlPanel.h"
#include "LED.h"
#include "TwinDos.h";
#include "LCDDisplay.h"
/*******************************************************************************
@Constants (global)
*******************************************************************************/

// Main TODO
// 2. TODO: Move all the Miele Libraries and CPP files into a separate folder than Adafruit, LiquidCrista_I2c and etc.
// details about the board ESP32 can be added
// 5. Create a fully functional washing machine using all the components
LCDDisplay disp_o(21, 22, 0x27);

void setup()
{
    // put your setup code here, to run once:

    Serial.begin(9600);                 // serial Init for test messages
    delay(1500);                        // give time to Wemos Lolin32 to finish setup
    disp_o.init_b();
}

void loop()
{ 
    disp_o.DisplayString_b("Hello world1");
    delay(1000);
    disp_o.ClearScreen_b();
    disp_o.DisplayString_b("Hello world2");    
}
