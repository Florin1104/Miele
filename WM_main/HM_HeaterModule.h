/*******************************************************************************
@Module          Heater module

/*******************************************************************************
--------------------------------------------------------------------------------
@Filename        HeaterModule.h

--------------------------------------------------------------------------------
@Description     TODO

--------------------------------------------------------------------------------
@Author          Dragos B.
@Date            13.11.2018

-------------------------------------------------------------------------------
@Copyright       Miele & Cie Copyright 2018
*******************************************************************************/

#ifndef _HEATERMODULE_H_  
#define _HEATERMODULE_H_
/*******************************************************************************
@Project Includes
*******************************************************************************/
#include "Arduino.h"
//#include <DHT_U.h>
//#include <DHT.h>
/*******************************************************************************
@Type definitions (global)
*******************************************************************************/
//#define HEATER_PIN                        ()
//#define HEATER_TEMPERATURE_SENSOR_PIN     ()

#define HEATING_ELEMENT_TEMPERATURE_MAX (55)

/*******************************************************************************
@Class definitions (global)
*******************************************************************************/

class HeaterModule
{
public:
    HeaterModule();

    /*******************************************************************************
    @Prototypes global Functions
    *******************************************************************************/
    /*******************************************************************************
    @Description   TODO

    --------------------------------------------------------------------------------
    @Returns       TODO

    --------------------------------------------------------------------------------
    @Parameters    TODO
    *******************************************************************************/
    float GetTemperature_f();


    /*******************************************************************************
    @Description   TODO

    --------------------------------------------------------------------------------
    @Returns       TODO

    --------------------------------------------------------------------------------
    @Parameters    TODO
    *******************************************************************************/
    void Initialise_v(uint8_t HeatingElementPin_u8, uint8_t HeaterSensorPin_u8);

    /*******************************************************************************
    @Description   TODO

    --------------------------------------------------------------------------------
    @Returns       none

    --------------------------------------------------------------------------------
    @Parameters    TODO
    *******************************************************************************/
    void StartHeating_v();

    /*******************************************************************************
    @Description   TODO

    --------------------------------------------------------------------------------
    @Returns       none

    --------------------------------------------------------------------------------
    @Parameters    TODO
    *******************************************************************************/
    void StopHeating_v();
    ~HeaterModule();

private:
    uint16_t m_TemperatureAndHumiditySensor_o;

};



#endif //_HEATERMODULE_H_
