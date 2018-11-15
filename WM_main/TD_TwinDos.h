/*******************************************************************************
@Module         Twin Dos (TD)

/*******************************************************************************
--------------------------------------------------------------------------------
@Filename       TS_TwinDos.h

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

#ifndef _TS_TWINDOS_H_
#define _TS_TWINDOS_H_

#include <stdint.h>
#include "Arduino.h"


class TwinDos
{

 private:

     // Holds the numbers of pins that the TwinDos system is attached to
     uint8_t m_InputPin1_u8;
     uint8_t m_InputPin2_u8;

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
     @Parameters    pin1_u8 - first pin number
                    pin2_u8 - second pin number
     *******************************************************************************/
     bool Initialise_b(uint8_t pin1_u8, uint8_t pin2_u8);

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