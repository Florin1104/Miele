/*******************************************************************************
--------------------------------------------------------------------------------
@Filename        MotorDriver.h

--------------------------------------------------------------------------------
@Description     TODO

--------------------------------------------------------------------------------
@Author          Dragos B.
@Date            13.11.2018

-------------------------------------------------------------------------------
@Copyright       Miele & Cie Copyright 2018
*******************************************************************************/

#ifndef _MOTORDRIVER_H_
#define _MOTORDRIVER_H_
/*******************************************************************************
@Project Includes
*******************************************************************************/
#include "Arduino.h"

#define ERROR_NO_ERROR                      (0)
#define ERROR_MODULE_IS_NOT_INTIALISED      (1)
#define ERROR_ROTATION_MOTOR                (2)

/*******************************************************************************
@Type definitions (global)
*******************************************************************************/
// TODO add description
typedef enum MotorRotation_e
{
    MOTOR_ROTATION_CLOCKWISE         = 0,
    MOTOR_ROTATION_COUNTER_CLOCKWISE = 1,
    MOTOR_ROTATION_NOT_SPECIFIED     = 99

}MotorRotation_te;

/*******************************************************************************
@Class definitions (global)
*******************************************************************************/
class MotorDriver
{
public:
    /*******************************************************************************
    @Description   Public constructor.

    --------------------------------------------------------------------------------
    @Returns       TODO

    --------------------------------------------------------------------------------
    @Parameters    TODO
    *******************************************************************************/
    MotorDriver() {}

    /*******************************************************************************
    @Prototypes global Functions
    *******************************************************************************/

    /*******************************************************************************
    @Description   This method is used to initialise the module.

    --------------------------------------------------------------------------------
    @Returns       TODO

    --------------------------------------------------------------------------------
    @Parameters    TODO
    *******************************************************************************/
    uint16_t Initialise_u16(uint8_t MotorPinClockwise_u8, uint8_t MotorPinCounterClockwise_u8);


    /*******************************************************************************
    @Description   This method is used to move the motor. TODO

    --------------------------------------------------------------------------------
    @Returns       TODO

    --------------------------------------------------------------------------------
    @Parameters    TODO
    *******************************************************************************/
    uint16_t MoveMotor_u16(uint8_t speed_u8, MotorRotation_te Rotation_e, uint16_t TimeInSeconds_u16);


    /*******************************************************************************
    @Description   This method is used to move the motor. TODO

    --------------------------------------------------------------------------------
    @Returns       TODO

    --------------------------------------------------------------------------------
    @Parameters    TODO
    *******************************************************************************/
    MotorRotation_te GetMotorRotation_e();

    /*******************************************************************************
    @Description   TODO

    --------------------------------------------------------------------------------
    @Returns       none

    --------------------------------------------------------------------------------
    @Parameters    TODO
    *******************************************************************************/
    uint16_t StopMotor_u16();

private:
    // This is used in order to check if the module
    // is inialised.
    bool m_isModuleInitialised_b = false;

    // Specify motor direction.
    MotorRotation_te m_MotorRotation_e = MOTOR_ROTATION_NOT_SPECIFIED;

    // Pins used for moving the motor clockwise and
    // counter clockwise.
    // This pins should be PWM capable. Check the pinout diagram.
    uint8_t m_MotorPinClockwise_u8;
    uint8_t m_MotorPinCounterClockwise_u8;

    // This is used to check wheter the module is moving
    bool m_isMotorMoving_b = false;

    // TODO add description
    void m_StopMotor_v();

};



#endif //_MOTORDRIVER_H_
