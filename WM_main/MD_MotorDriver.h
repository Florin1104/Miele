/*******************************************************************************
--------------------------------------------------------------------------------
@Filename        MD_MotorDriver.h

--------------------------------------------------------------------------------
@Description     TODO

--------------------------------------------------------------------------------
@Author          Dragos B.
@Date            13.11.2018

-------------------------------------------------------------------------------
@Copyright       Miele & Cie Copyright 2018
*******************************************************************************/

#ifndef _MD_MOTORDRIVER_H_
#define _MD_MOTORDRIVER_H_
/*******************************************************************************
@Project Includes
*******************************************************************************/

#define MOTOR_CLOCKWISE_PIN           ()
#define MOTOR_COUNTER_CLOCKWISE_PIN   ()

/*******************************************************************************
@Type definitions (global)
*******************************************************************************/
// TODO add description
typedef enum motorRotation
{
    MOTOR_ROTATION_CLOCKWISE         = 0,
    MOTOR_ROTATION_COUNTER_CLOCKWISE = 1,

}MotorRotation_te;

/*******************************************************************************
@Class definitions (global)
*******************************************************************************/

/*******************************************************************************
@Prototypes global Functions
*******************************************************************************/
/*******************************************************************************
@Description   This method is used to move the motor. TODO

--------------------------------------------------------------------------------
@Returns       none

--------------------------------------------------------------------------------
@Parameters    TODO
*******************************************************************************/
void MoveMotor_v(unsigned int speed_uint, MotorRotation_te Rotation, unsigned int TimeInSeconds_uint);

/*******************************************************************************
@Description   TODO

--------------------------------------------------------------------------------
@Returns       none

--------------------------------------------------------------------------------
@Parameters    TODO
*******************************************************************************/
void StopMotor_v();

#endif //_MD_MOTORDRIVER_H_
