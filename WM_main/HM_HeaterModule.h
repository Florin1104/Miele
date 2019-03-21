/*******************************************************************************
@Module          Heater module

/*******************************************************************************
--------------------------------------------------------------------------------
@Filename        HeaterModule.h

--------------------------------------------------------------------------------
@Description     TODO

--------------------------------------------------------------------------------
@Author          Dragos B., Fabian V.
@Date            20.3.2019

-------------------------------------------------------------------------------
@Copyright       Miele & Cie Copyright 2018
*******************************************************************************/
// Example
//HeaterModule heaterModule_o;
//
//void setup()
//{
//    // put your setup code here, to run once:
//    Serial.begin(9600);
//
//	  heaterModule_o.Initialise_u16(GPIO_NUM_25,GPIO_NUM_15);
//}
//
//void loop()
//{ 
//  Start heating the element 
//	heaterModule_o.StartHeating_v(64);

//  read the data from the temperature sensor
//	float t=heaterModule_o.GetTemperature_f();

//  Print the temperature data to serial port 
//	Serial.print(t);

//  Stop the heater module
//	heaterModule_o.StopHeating_v();
//}
#ifndef _HEATERMODULE_H_  
#define _HEATERMODULE_H_
/*******************************************************************************
@Project Includes
*******************************************************************************/
#include "Arduino.h"
#include "DHT.h"
#include "DHT_U.h"

#define HEATER_PIN									(25)
#define HEATER_TEMPERATURE_SENSOR_PIN				(15)
#define DHT_SENSOR_TYPE								(11)

// Maximum configurable values.
#define HEATING_ELEMENT_TEMPERATURE_MAX				(55)
#define MAX_POWER_PWM								(120)

// Error Codes for current module.
#define ERROR_HEATER_NO_ERROR					    (0)
#define ERRORH_HEATER_MODULE_IS_NOT_INTIALISED      (1)
#define ERROR_HEATER_PIN_NOT_COMPATIBLE_WITH_PWM    (2)
#define ERROR_VALUE_TOO_HIGH                        (3)



/*******************************************************************************
@Type definitions (global)
*******************************************************************************/

/*******************************************************************************
@Class definitions (global)
*******************************************************************************/
class HeaterModule
{

public:
	/*******************************************************************************
    @Description   Default constructor.

    *******************************************************************************/
	HeaterModule(); 

    /*******************************************************************************
    @Prototypes global Functions
    *******************************************************************************/
    /*******************************************************************************
    @Description   This method is used to get the heater temperature form the Heater

    --------------------------------------------------------------------------------
    @Returns       t- is the value for the temperature to be returened

    --------------------------------------------------------------------------------
    @Parameters    no parameters
    *******************************************************************************/
    float GetTemperature_f();

    /*******************************************************************************
    @Description   This method is used to initialise the module. It should be called
                   after the object creation.

    --------------------------------------------------------------------------------
    @Returns       ERROR_MODULE_IS_NOT_INTIALISED if the module was not intialised.
                   ERROR_PIN_NOT_COMPATIBLE_WITH_PWM - Pin not PWM capable.

    --------------------------------------------------------------------------------
    @Parameters    HeatingElementPin_u8 and HeaterSensorPin_u8 - Specifies the
				   PWM pin and the Heater digital data pin
    *******************************************************************************/
	uint16_t Initialise_u16(uint8_t HeatingElementPin_u8, uint8_t HeaterSensorPin_u8);

    /*******************************************************************************
    @Description   This method is used to produce PWM signals to the Heater module

    --------------------------------------------------------------------------------
    @Returns       none

    --------------------------------------------------------------------------------
    @Parameters    value- is used to map the PWM signal range
    *******************************************************************************/
	void StartHeating_v(float value);

    /*******************************************************************************
    @Description   This method is used to set the PWM signal to 0 for the Heater

    --------------------------------------------------------------------------------
    @Returns       no returns

    --------------------------------------------------------------------------------
    @Parameters    no parameters
    *******************************************************************************/
    void StopHeating_v();

	/*******************************************************************************
    @Description   Default destructor.

    *******************************************************************************/
    ~HeaterModule();

private:
    uint16_t m_TemperatureAndHumiditySensor_o;

	// This variable is used in order to chek if the module
	// is initalised
	bool m_isModuleInitialized_b = false;

	// m_HeatingElementPin_u8  shloud pe pwm capable
	uint8_t m_HeatingElementPin_u8;
	
	// Pin used for temperature sensor.
	uint8_t m_HeaterSensorPin_u8;

	// Object used for DHT sensor.
	DHT dht_o;

    /*******************************************************************************
    @Description   Private method to check if a pin is PWM capable.

    --------------------------------------------------------------------------------
    @Returns       True if pin is PWM capable.
                   False otherwise.

    --------------------------------------------------------------------------------
    @Parameters    Pin_u8 - Pin number to be checked.

    *******************************************************************************/
	bool m_isPinPwm_b(uint8_t Pin_u8);

};



#endif //_HEATERMODULE_H_
