/*******************************************************************************
@Module         Motor Driver used for WM module

--------------------------------------------------------------------------------
@Filename       MotorDriver.cpp
--------------------------------------------------------------------------------
@Description    Check the header and class description for more details.

--------------------------------------------------------------------------------
@Author        Dragos B.
@Date          13.11.2018
               
@Copyright     Miele  Cie Copyright 2020

*******************************************************************************/


/*******************************************************************************
@Project Includes
*******************************************************************************/
#include "MotorDriver.h"
#include "PWM_Timer.h"
/*******************************************************************************
@Macros (global)
*******************************************************************************/
#define SECOND_TO_MILLISECONDS      (1000)
//#define PWM_CHANNEL_ONE             (1)
//#define PWM_CHANNEL_TWO              (2)

#define PWM_FREQUENCY               (12000)
#define RESOLUTION_BITS             (8)

// This delay is used in order to call one line for
// a certain number of milliseconds.
// It should be used like this: DELAY_NON_BREAKING(WaitMs_u32) CodeToBeCalled();
#define DELAY_NON_BREAKING(WaitMs_u32) for (unsigned long time_now = millis(); millis() < time_now + WaitMs_u32;)

// This part is the replacement of delay form Arduino
#define DELAY_DO_NOTHING(WaitMs_u32) DELAY_NON_BREAKING(WaitMs_u32);
/*******************************************************************************
@Constants (global)
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
    uint16_t ErrorCode_u16 = ERROR_PIN_NOT_COMPATIBLE_WITH_PWM;
    

    // Check that the pins are not the same
    if (MotorPinClockwise_u8 != MotorPinCounterClockwise_u8)
    {
        // Are Pins provided PWM pins?
        if ((m_isPinPwm_b(MotorPinCounterClockwise_u8) == true) && 
             (m_isPinPwm_b(MotorPinClockwise_u8) == true))
        {
            m_MotorPinClockwise_u8 = MotorPinClockwise_u8;
            m_MotorPinCounterClockwise_u8 = MotorPinCounterClockwise_u8;

            // Initialize the channels.
            ledcAttachPin(MotorPinClockwise_u8, clockwiseChannel);
            ledcAttachPin(MotorPinCounterClockwise_u8, counter_clockwiseChannel);

            // Set PWM channel.
            ledcSetup(clockwiseChannel, PWM_FREQUENCY, RESOLUTION_BITS);
            ledcSetup(counter_clockwiseChannel, PWM_FREQUENCY, RESOLUTION_BITS);

            // The motor is not moving.
            m_StopMotor_v();

            // Module is now initialized.
            m_isModuleInitialised_b = true;


            ErrorCode_u16 = ERROR_NO_ERROR;
        }
    } 

    return ErrorCode_u16;

}

/*******************************************************************************
Function description and additional notes,
are given at the function prototype in the header file
*******************************************************************************/
uint16_t MotorDriver::MoveMotor_u16(uint8_t Speed_u8, MotorRotation_te Rotation_e, uint16_t TimeInSeconds_u16)
{
    uint16_t ErrorCode_u16 = ERROR_MODULE_IS_NOT_INTIALISED;

    // Is the module is initialized?
    if (m_isModuleInitialised_b == true)
    {
        // Speed value should be between 0-100
        ErrorCode_u16 = ERROR_VALUE_TOO_HIGH;
        
        // Check if the speed is in limit.
        if (Speed_u8 <= 100)
        {
            if (Rotation_e == m_MotorRotation_e || m_MotorRotation_e == MOTOR_ROTATION_NOT_SPECIFIED)
            {
                m_MotorRotation_e = Rotation_e;

                // Map the values from 0-100 to 0-255.
                Speed_u8 = map(Speed_u8, 0, 100, 0, 255);

                // Transform seconds in milliseconds.
                TimeInSeconds_u16 = TimeInSeconds_u16 * SECOND_TO_MILLISECONDS;

                // How the motor should spin?
                if (m_MotorRotation_e == MOTOR_ROTATION_CLOCKWISE)
                {

                    ledcWrite(clockwiseChannel, Speed_u8);

                    ErrorCode_u16 = ERROR_NO_ERROR;
                }
                else if (m_MotorRotation_e == MOTOR_ROTATION_COUNTER_CLOCKWISE)
                {
                    ledcWrite(counter_clockwiseChannel, Speed_u8);

                    ErrorCode_u16 = ERROR_NO_ERROR;

                }
            }
            else
            {
                // We have an error so stop the motor.
                m_StopMotor_v();
                Serial.println("We have an error, you want to change the direction while spinning. The motor will stop.");
                ErrorCode_u16 = ERROR_ROTATION_MOTOR;
                m_MotorRotation_e = MOTOR_ROTATION_NOT_SPECIFIED;
            }
        }
    }

    return ErrorCode_u16; 
}

/*******************************************************************************
Function description and additional notes,
are given at the function prototype in the header file
*******************************************************************************/
#if FUTURE_IMPLEMENATION == 1
MotorRotation_te MotorDriver::GetMotorRotation_e()
{
    // Is the module is initialized?
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

#endif // FUTURE_IMPLEMENATION

/*******************************************************************************
Function description and additional notes,
are given at the function prototype in the header file
*******************************************************************************/
uint16_t MotorDriver::StopMotor_u16(uint16_t TimeInSeconds_u16)
{
    uint16_t ErrorCode_u16 = ERROR_MODULE_IS_NOT_INTIALISED;

    // Is the module is initialized?
    if (m_isModuleInitialised_b == true)
    {
        m_StopMotor_v();
        ErrorCode_u16 = ERROR_NO_ERROR;
        
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
    ledcWrite(clockwiseChannel, 0);
    ledcWrite(counter_clockwiseChannel, 0);

    m_isMotorMoving_b = false;
    m_MotorRotation_e = MOTOR_ROTATION_NOT_SPECIFIED;

}

/*******************************************************************************
Function description and additional notes,
are given at the function prototype in the header file
*******************************************************************************/
bool MotorDriver::m_isPinPwm_b(uint8_t Pin_8)
{
    bool isPwmPinValid_b = false;
    
    // All the pins that are PWM capable for ESP32.
	
	// here in the code it can be used like this: 
	const uint8_t ValidPwmPins_au8[] = VALID_PWM_I2C_PINS;
	
    for (uint8_t i = 0; i< sizeof(ValidPwmPins_au8)/sizeof(ValidPwmPins_au8[0]); i++)
    {
        // Is pin PWM capable?
        if (Pin_8 == ValidPwmPins_au8[i])
        {
            isPwmPinValid_b = true;
            break;
        }
    }

    return isPwmPinValid_b;
}
