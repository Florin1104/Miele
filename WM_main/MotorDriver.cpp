/*******************************************************************************
@Module         MD used for WM module.
--------------------------------------------------------------------------------
@Filename       MD_MotorDriver.cpp
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
#include "MotorDriver.h"

/*******************************************************************************
@Constants (global)
*******************************************************************************/
#define SECOND_TO_MILLISECONDS      (1000)
#define PWM_CHANNEL_ZERO             (0)
#define PWM_CHANNEL_ONE              (1)

#define PWM_FREQUENCY               (1000)
#define RESOLUTION_BITS             (8)
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
uint16_t MotorDriver::Initialise_u16(uint8_t MotorPinClockwise_u8, uint8_t MotorPinCounterClockwise_u8)
{
    // TODO check for channel

    m_MotorPinClockwise_u8        = MotorPinClockwise_u8;
    m_MotorPinCounterClockwise_u8 = MotorPinCounterClockwise_u8;

    // Set mode to OUTPUT.
    /*pinMode(m_MotorPinClockwise_u8,        OUTPUT);
    pinMode(m_MotorPinCounterClockwise_u8, OUTPUT);
*/
    ledcAttachPin(MotorPinClockwise_u8, PWM_CHANNEL_ZERO);
    ledcAttachPin(MotorPinCounterClockwise_u8, PWM_CHANNEL_ONE);

    // Set PWM channel.
    ledcSetup(PWM_CHANNEL_ZERO, PWM_FREQUENCY, RESOLUTION_BITS);
    ledcSetup(PWM_CHANNEL_ONE, PWM_FREQUENCY, RESOLUTION_BITS);

    // The motor is not moving.
    m_StopMotor_v();

    // Module is now initialised.
    m_isModuleInitialised_b = true;

}

/*******************************************************************************
Function description and additional notes,
are given at the function prototype in the header file
*******************************************************************************/
uint16_t MotorDriver::MoveMotor_u16(uint8_t Speed_u8, MotorRotation_te Rotation_e, uint16_t TimeInSeconds_u16)
{
    uint16_t ErrorCode_u16 = ERROR_MODULE_IS_NOT_INTIALISED;

    // Is the module is intialised?
    if (m_isModuleInitialised_b == true)
    {
        m_MotorRotation_e = Rotation_e;

        // TODO use mill or d
        if (m_MotorRotation_e == MOTOR_ROTATION_CLOCKWISE)
        {
            ledcWrite(PWM_CHANNEL_ZERO, Speed_u8);
            //delay(TimeInSeconds_u16 * SECOND_TO_MILLISECONDS);  
        } 
        else if (m_MotorRotation_e == MOTOR_ROTATION_COUNTER_CLOCKWISE)
        {
            ledcWrite(PWM_CHANNEL_ONE, Speed_u8);
            //delay(TimeInSeconds_u16 * SECOND_TO_MILLISECONDS); 
        }
        else
        {
            // We have an error so stop the motor.
            m_StopMotor_v();
            ErrorCode_u16 = ERROR_ROTATION_MOTOR;
        }
    }

    return ErrorCode_u16; 
}

/*******************************************************************************
Function description and additional notes,
are given at the function prototype in the header file
*******************************************************************************/
MotorRotation_te MotorDriver::GetMotorRotation_e()
{
    // Is the module is intialised?
    if (m_isModuleInitialised_b == true)
    {
        return m_MotorRotation_e;
    }
    else
    {
        // In case of an error.
        return MOTOR_ROTATION_NOT_SPECIFIED;
    }
}

/*******************************************************************************
Function description and additional notes,
are given at the function prototype in the header file
*******************************************************************************/
uint16_t MotorDriver::StopMotor_u16()
{
    uint16_t ErrorCode_u16 = ERROR_MODULE_IS_NOT_INTIALISED;

    // Is the module is intialised?
    if (m_isModuleInitialised_b == true)
    {
        m_StopMotor_v();
        ErrorCode_u16 = ERROR_NO_ERROR;
        delay(SECOND_TO_MILLISECONDS * 2);
    }

    return ErrorCode_u16;
}

/*******************************************************************************
Function description and additional notes,
are given at the function prototype in the header file
*******************************************************************************/
void MotorDriver::m_StopMotor_v()
{
    // Set PWM pins to LOW
    digitalWrite(m_MotorPinClockwise_u8,        LOW);
    digitalWrite(m_MotorPinCounterClockwise_u8, LOW);
    m_isMotorMoving_b = false;
}
