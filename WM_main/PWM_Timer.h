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
				etc..

--------------------------------------------------------------------------------
@Author        Marian S.
@Date          24.11.2019

@Copyright     Miele  Cie Copyright 2020

*******************************************************************************/
#pragma once
#include <stdint.h>
// A status buffer that holds the status of each timer. The ESP32 devKit module has 4 different PWM Timers
static bool AvailableTimer[4] = { 0 }; 

static uint8_t currentChannel = 0;
uint8_t GetAvailableChannel_u8();
