#include "PWM_Timer.h"

uint8_t getChannel()
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

    return returnValue;
}