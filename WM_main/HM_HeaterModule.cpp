/*******************************************************************************
@Module         TODO
--------------------------------------------------------------------------------
@Filename       HD_HeaterModule.cpp
--------------------------------------------------------------------------------
@Description   TODO

--------------------------------------------------------------------------------
@Author        Dragos B.
@Date          13.11.2018

@Copyright     Miele  Cie Copyright 2018

*******************************************************************************/


/*******************************************************************************
@Project Includes
*******************************************************************************/
#include "HM_HeaterModule.h"

/*******************************************************************************
@Constants (global)
*******************************************************************************/
#define SECOND_TO_MILLISECONDS      (1000)
#define PWM_CHANNEL_THREE           (3)

#define PWM_FREQUENCY				(12000)
#define RESOLUTION_BITS             (8)

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
HeaterModule::HeaterModule()
{

}

/*******************************************************************************
Function description and additional notes,
are given at the function prototype in the header file
*******************************************************************************/
float HeaterModule::GetTemperature_f()
{
    // Read temperature as Celsius (the default)
    float t = dht_o.readTemperature();

    return t;
}

/*******************************************************************************
Function description and additional notes,
are given at the function prototype in the header file
*******************************************************************************/
uint16_t HeaterModule::Initialise_u16(uint8_t HeatingElementPin_u8, uint8_t HeaterSensorPin_u8)
{   

	uint16_t ErrorCode_u16 = ERROR_PIN_NOT_COMPATIBLE_WITH_PWM;

	// check that the pins are not the same
	if(HeatingElementPin_u8 !=HeaterSensorPin_u8)
	{
		if(m_isPinPwm_b(HeatingElementPin_u8)==true)
		{
			m_HeatingElementPin_u8=HeatingElementPin_u8;
			m_HeaterSensorPin_u8=HeaterSensorPin_u8;

			// Initialise the channels
			ledcAttachPin(HeatingElementPin_u8, PWM_CHANNEL_THREE);
			
			// Set PWM channel.
			ledcSetup(PWM_CHANNEL_THREE, PWM_FREQUENCY,RESOLUTION_BITS);

			// Initialise DHT module
			dht_o=DHT(HeaterSensorPin_u8,DHT_SENSOR_TYPE);
			dht_o.begin();
		
			// The element is not heating 
			StopHeating_v();

			// Module is now initialised
			m_isModuleInitialized_b=true;

			ErrorCode_u16 = ERROR_NO_ERROR;
			
		}
	}

	return ErrorCode_u16;
}

void HeaterModule::StartHeating_v(float value)

{   
	value=map(value,0,255,0,255);
	ledcWrite(PWM_CHANNEL_THREE,value);
}

void HeaterModule::StopHeating_v()
{   	
		ledcWrite(PWM_CHANNEL_THREE,0);
}

/*******************************************************************************
Function description and additional notes,
are given at the function prototype in the header file
*******************************************************************************/
HeaterModule::~HeaterModule()
{

}

/*******************************************************************************
Function description and additional notes,
are given at the function prototype in the header file
*******************************************************************************/
bool HeaterModule::m_isPinPwm_b(uint8_t Pin_u8)
{
	bool isPwmPinValid_b = false;
    
    // All the pins that are PWM capable for ESP32.
    const uint8_t ValidPwmPins_au8[] = { 15,2,0,4,16,17,5,18,23,19,21,22,13,12,14,27,26,25,35,34,33,32,39,36};

    for (uint8_t i = 0; i< sizeof(ValidPwmPins_au8)/sizeof(ValidPwmPins_au8[0]); i++)
    {
        // Is pin PWM capable?
        if (Pin_u8 == ValidPwmPins_au8[i])
        {
            isPwmPinValid_b = true;
            break;
        }
    }

    return isPwmPinValid_b;
}
