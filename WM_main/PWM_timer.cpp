/*******************************************************************************
@Module        PWM Timer
--------------------------------------------------------------------------------
@Filename      PWM_Timer.h
--------------------------------------------------------------------------------
@Description    This module controls the available PWM Timers and the PWM Channels
				The ESP32 has 16 PWM Channels , but only 4 different PWM Timers.
				This means that we can control independently only 4 devices that work
				with PWM. If all the Channels are occupied, then the devices will
				overlap on each other and create errors. 
				If we want to control 2 devices on the same time, we will put them
				on the same Timer, but on different channels.
				
				TIMER 1 ---> CHANNEL 1
					    ---> CHANNEL 2
					    ---> CHANNEL 3
					    ---> CHANNEL 4
						
				TIMER 2 ---> CHANNEL 1
					    ---> CHANNEL 2
					    ---> CHANNEL 3
					    ---> CHANNEL 4
				etc.

--------------------------------------------------------------------------------
@Author        Marian S.
@Date          24.11.2019

@Copyright     Miele  Cie Copyright 2020

*******************************************************************************/


/*******************************************************************************
@Project Includes
*******************************************************************************/

#include "PWM_Timer.h"
#include "Arduino.h"
// TODO add some comments explaining what are we doing here
uint8_t GetAvailableChannel_u8()
{
    uint8_t returnValue = 17;
    uint8_t timer = ((currentChannel / 2) % 4);
	
    if (AvailableTimer[timer] == 0) 
    {
        AvailableTimer[timer] = 1;
        returnValue = currentChannel;
        currentChannel++;

    }
    else
    {
        if(currentChannel<8) //TODO why is 8? IDK
        {
            currentChannel++;
            returnValue = currentChannel++;
        }

        
    }

    if (returnValue == 17) 
    {
        Serial.println("Error: No more channels left please try the TV it has more channels! :)");
    }
        
    return returnValue;
}