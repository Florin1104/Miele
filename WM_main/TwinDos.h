/*******************************************************************************
@Module         Twin Dos

/*******************************************************************************
--------------------------------------------------------------------------------
@Filename       TwinDos.h

--------------------------------------------------------------------------------
@Description    TwinDos is a two-phase washing system built into the Miele W1
                range of front loader washing machines. It uses two integrated
                cartridges - 
                the first filled with a liquid detergent (UltraPhase 1)
                and the second a detergent enhancer liquid (UltraPhase 2),
                including oxygenated bleach for stain removals. 
                The liquids are dispensed at the appropriate time in the wash
                cycle and the appropriate ratio depending on the type of wash.

--------------------------------------------------------------------------------
@Author         Iulian G.
@Date           14.11.2018

-------------------------------------------------------------------------------
@Copyright      Miele & Cie Copyright 2018
*******************************************************************************/


/*******************************************************************************
@Example:
--------------------------------------------------------------------------------

#include "TwinDos.h";
TwinDos twinDos_o;

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(9600);
    delay(1000);

    twinDos_o.Initialise_e(26); //setup TwinDos pin number
}

void loop()
{
    // put your main code here, to run repeatedly:
    if(twinDos_o.isPresent_b())
    {
        Serial.println("Connected");
    }
    else
    {
        Serial.println("NOT connected");
    }

}

*******************************************************************************/


#ifndef _TWINDOS_H_
#define _TWINDOS_H_

#include <stdint.h>
#include "Arduino.h"


class TwinDos
{

 private:

     // Holds the pin number that the TwinDos system is attached to
     uint8_t m_InputPin_u8;

     // hold if init() has been called
     bool m_InitFlag_b;


 public:

     /*******************************************************************************
     @Description   Constructor used to initialise a TwinDos system object

     --------------------------------------------------------------------------------
     @Returns       none

     --------------------------------------------------------------------------------
     @Parameters    none
     *******************************************************************************/
     TwinDos();

     /*******************************************************************************
     @Description   Initialize TwinDos sytem with pin location (only once)

     --------------------------------------------------------------------------------
     @Returns       bool - whether or not TwinDos was successfully initialized

     --------------------------------------------------------------------------------
     @Parameters    pin_u8 - first pin number
     *******************************************************************************/
     bool Initialise_e(uint8_t pin_u8);

     /*******************************************************************************
     @Description   check if both cartridges are in

     --------------------------------------------------------------------------------
     @Returns       bool - true if both are in

     --------------------------------------------------------------------------------
     @Parameters    None
     *******************************************************************************/
     bool isPresent_b();
};

#endif