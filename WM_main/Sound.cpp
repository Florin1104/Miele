/*******************************************************************************
@Module         MD used for WM module.
--------------------------------------------------------------------------------
@Filename       MotorDriver.cpp
--------------------------------------------------------------------------------
@Description    Check the header and class description for more details.

--------------------------------------------------------------------------------
@Author        Dragos B., Fabian V.
@Date          13.11.2018

@Copyright     Miele  Cie Copyright 2018

*******************************************************************************/

/*******************************************************************************
@Project Includes
*******************************************************************************/
#include "Sound.h"

/*******************************************************************************
@Constants (global)
*******************************************************************************/
#define SECOND_TO_MILLISECONDS (1000)
#define PWM_CHANNEL            (1)
#define BUZZER_PIN             (12)
							   
							   
#define PWM_FREQUENCY          (2000)
#define RESOLUTION_BITS        (8)

// This delay is used in order to call one line for
// a certain number of milliseconds.
// It should be used like this: DELAY_NON_BREAKING(WaitMs_u32) CodeToBeCalled();
#define DELAY_NON_BREAKING(WaitMs_u32) for (unsigned long time_now = millis(); millis() < time_now + WaitMs_u32;)

// This part is the replacement of delay frm Arduino
#define DELAY_DO_NOTHING(WaitMs_u32) DELAY_NON_BREAKING(WaitMs_u32);
/*******************************************************************************
@Macros (global)
*******************************************************************************/

/*******************************************************************************
@Type definitions  (global)
*******************************************************************************/

/*******************************************************************************
@Local Variables
*******************************************************************************/

/*******************************************************************************
@External Prototypes
*******************************************************************************/

/*******************************************************************************
@Prototypes local Functions
*******************************************************************************/


/*******************************************************************************
Function description and additional notes,
are given at the function prototype in the header file
*******************************************************************************/

void InitialiseSound_v()
{
    ledcSetup(PWM_CHANNEL, PWM_FREQUENCY, PWM_CHANNEL);
    ledcAttachPin(BUZZER_PIN, PWM_CHANNEL);
}

/*******************************************************************************
Function description and additional notes,
are given at the function prototype in the header file
*******************************************************************************/
void PlaySound_v(uint16_t TimeInSeconds_u16, Sounds_te sounds)
{
	GenerateSounds(sounds);
}
/*******************************************************************************
Function description and additional notes,
are given at the function prototype in the header file
*******************************************************************************/
int GenerateSounds(int sound_freq)
{
	for(int freq= sound_freq; freq <7000; freq++)
	{
		sound_freq=ledcWriteTone(PWM_CHANNEL, freq);
	}

	return sound_freq;
}
/*******************************************************************************
Function description and additional notes,
are given at the function prototype in the header file
*******************************************************************************/
void StopSound_v()
{
    DELAY_NON_BREAKING(500) ledcWriteTone(PWM_CHANNEL, 0);
}
