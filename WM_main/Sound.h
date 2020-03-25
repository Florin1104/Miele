/*******************************************************************************
--------------------------------------------------------------------------------
@Filename        Sound.h

--------------------------------------------------------------------------------
@Description   

--------------------------------------------------------------------------------
@Author          Dragos B., Fabian V.
@Date            20.03.2019

-------------------------------------------------------------------------------
@Copyright       Miele & Cie Copyright 2020
*******************************************************************************/
/*******************************************************************************

// Example
//void setup()
//{
//	InitialiseSound_v();
//}

//void loop()
//{
//	GenerateSounds(8, 500);
//  delay(10);
//	StopSound_v();
//}
*******************************************************************************/
#ifndef _SOUND_H_
#define _SOUND_H_


/*******************************************************************************
@Project Includes
*******************************************************************************/
#include "Arduino.h"

#define FUTURE_IMPLEMENATION    (0)


/*******************************************************************************
@Type definitions (global)
*******************************************************************************/




/*
Enum is a user defined data type where we specify a set of values for a variable
and the variable can only take one out of a small set of possible values. 
We use enum keyword to define a Enumeration.
By default, DOOR_OPEN_SOUND is 0, DOOR_CLOSED_SOUND is 1 and so on. 
You can change the default value of an enum element during declaration (if necessary).
In this case we changed the default values to the values of the frequency: 5000, 6000 etc.
*/

// This enum holds all the basic frequencies for the Sound module
// Possible values can be:
// - DOOR_OPEN_SOUND: Sound is produced when the door opens
// - DOOR_CLOSED_SOUND: Sound is produced when the door closes
// - PROGRAM_START_SOUND: Sound is produced when the washing program starts
// - PROGRAM_END_SOUND: Sound is produced when the washing program finishes


typedef enum Sounds_e
{
	DOOR_OPEN_SOUND = 5000,
	DOOR_CLOSED_SOUND = 6000,
	PROGRAM_START_SOUND = 6500,
	PROGRAM_END_SOUND = 7000

}Sounds_te;

/*******************************************************************************
@Function definitions (global)
*******************************************************************************/


/*******************************************************************************
@Prototypes global Functions
*******************************************************************************/

/*******************************************************************************
@Description   This method is used to initialize the module. It should be called
               after the object creation.

--------------------------------------------------------------------------------
@Returns       none

--------------------------------------------------------------------------------
@Parameters    none
*******************************************************************************/
void InitialiseSound_v();

/*******************************************************************************
@Description   This method is used to play a generated sound

--------------------------------------------------------------------------------
@Returns       none

--------------------------------------------------------------------------------
@Parameters    TimeInSeconds_u16, sounds
*******************************************************************************/
void PlaySound_v(uint16_t TimeInSeconds_u16, Sounds_te sounds);

/*******************************************************************************
@Description   This method is used in order to generate sounds by different
			   frequency
--------------------------------------------------------------------------------
@Returns       none

--------------------------------------------------------------------------------
@Parameters    sound_freq
*******************************************************************************/
int GenerateSounds(int sound_freq, int time);

/*******************************************************************************
@Description   This method is used in order to stop playing a sound 

--------------------------------------------------------------------------------
@Returns       none

--------------------------------------------------------------------------------
@Parameters    none
*******************************************************************************/
void StopSound_v();


#endif //_SOUND_H_
