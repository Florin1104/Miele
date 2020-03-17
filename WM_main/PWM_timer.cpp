#include "PWM_Timer.h"
#include "Arduino.h"
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
        if(currentChannel<8)
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