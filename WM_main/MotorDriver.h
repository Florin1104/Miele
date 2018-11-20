/*******************************************************************************
--------------------------------------------------------------------------------
@Filename        MotorDriver.h

--------------------------------------------------------------------------------
@Description   This class is used to control the motor using PWM signal from
               ESP32 module.
               The motor can be spined in clockwise and counterclockwise.
        
    Example: 
    #define ERROR_SERIAL(err){Serial.print(__LINE__);Serial.print("ERROR is: ");Serial.println((int)err);}
    // This should be in the setup
    ERROR_SERIAL(motor_ob.Initialise_u16(19, 25));

    // This should be in the loop
    ERROR_SERIAL(motor_ob.MoveMotor_u16(80, MOTOR_ROTATION_CLOCKWISE, 2));
    ERROR_SERIAL(motor_ob.StopMotor_u16(2));
    ERROR_SERIAL(motor_ob.MoveMotor_u16(80, MOTOR_ROTATION_COUNTER_CLOCKWISE, 2));
    ERROR_SERIAL(motor_ob.StopMotor_u16(2));

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
#define ERROR_PIN_NOT_COMPATIBLE_WITH_PWM   (3)
#define ERROR_VALUE_TOO_HIGH                (4)


#define FUTURE_IMPLEMENATION    (0)


/*******************************************************************************
@Type definitions (global)
*******************************************************************************/
// This specifies the motor direction
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
    @Returns       Nothing.

    --------------------------------------------------------------------------------
    @Parameters    None.
    *******************************************************************************/
    MotorDriver() {}

    /*******************************************************************************
    @Prototypes global Functions
    *******************************************************************************/

    /*******************************************************************************
    @Description   This method is used to initialise the module. It should be called
                   after the object creation.

    --------------------------------------------------------------------------------
    @Returns       ERROR_MODULE_IS_NOT_INTIALISED if the module was not intialised.
                   ERROR_PIN_NOT_COMPATIBLE_WITH_PWM - Pin not PWM capable.

    --------------------------------------------------------------------------------
    @Parameters    MotorPinClockwise_u8 and MotorPinCounterClockwise_u8 - Specifies 
                                    the PWM pins for controlling motor.
    *******************************************************************************/
    uint16_t Initialise_u16(uint8_t MotorPinClockwise_u8, uint8_t MotorPinCounterClockwise_u8);


    /*******************************************************************************
    @Description   This method is used to move the motor.

    --------------------------------------------------------------------------------
    @Returns       ERROR_MODULE_IS_NOT_INTIALISED if the module was not intialised.
                   ERROR_NO_ERROR - In case if no error is encountered.
                   ERROR_ROTATION_MOTOR - Rotation out of range.
                   ERROR_VALUE_TOO_HIGH - if the speed percentage is not in range
                                           (0-100%).

    --------------------------------------------------------------------------------
    @Parameters    SpeedPercentage_u8 - Speed percentage from 0-100%. Higher values
                   result in ERROR_VALUE_TOO_HIGH error.
                   Rotation_e - Direction for motor to move.
                   TimeInSeconds_u16 - Time in seconds in which motor will move.
    *******************************************************************************/
    uint16_t MoveMotor_u16(uint8_t SpeedPercentage_u8, MotorRotation_te Rotation_e, 
                                                          uint16_t TimeInSeconds_u16);



    /*******************************************************************************
    @Description   This method stops the motor.

    --------------------------------------------------------------------------------
    @Returns       ERROR_MODULE_IS_NOT_INTIALISED if the module was not intialised.
                   ERROR_NO_ERROR - In case if no error is encountered.

    --------------------------------------------------------------------------------
    @Parameters    TimeInSeconds_u16 - time in seconds the motor should be stopped.
    *******************************************************************************/
    uint16_t StopMotor_u16(uint16_t TimeInSeconds_u16);
#if FUTURE_IMPLEMENATION == 1
    /*******************************************************************************
    @Description   This method is used to get the motor direction. For the moment 
                   is not used.

    --------------------------------------------------------------------------------
    @Returns       Motor direction.

    --------------------------------------------------------------------------------
    @Parameters    None.
    *******************************************************************************/
    MotorRotation_te GetMotorRotation_e();

#endif
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

    /*******************************************************************************
    @Description   Private method to stop motor.

    --------------------------------------------------------------------------------
    @Returns       Nothing.

    --------------------------------------------------------------------------------
    @Parameters    None.

    *******************************************************************************/
    void m_StopMotor_v();


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



#endif //_MOTORDRIVER_H_
