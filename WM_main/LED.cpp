/*******************************************************************************
@Module         LED

--------------------------------------------------------------------------------
@Filename       LED.cpp

--------------------------------------------------------------------------------
@Description    This class is used to initialize the RGB LED and
                to change it's color.

--------------------------------------------------------------------------------
@Author         Bogdan Calinoiu
@Date           15.04.2019

-------------------------------------------------------------------------------
@Copyright      Miele & Cie Copyright 2020
*******************************************************************************/


/*******************************************************************************
@Project Includes
*******************************************************************************/
#include "LED.h"
#include "Arduino.h"


/*******************************************************************************
@Macros (global)
*******************************************************************************/
#define PWM_CHANNEL_ONE             (1)
#define PWM_CHANNEL_TWO             (2)
#define PWM_CHANNEL_THREE           (3)
#define PWM_FREQUENCY				(12000)
#define RESOLUTION_BITS             (8)


/*******************************************************************************
@Description    Default constructor without parameters.
				This will be called automatically when an object is created,
				unless we use other constructor.
--------------------------------------------------------------------------------
@Returns      	none
--------------------------------------------------------------------------------
@Parameters    	none
 *******************************************************************************/
LED::LED(void)
{
}


/*******************************************************************************
@Description    Constructor with parameters.
				Attaches the PWM channels to each pin assigned with a specific
				color.
--------------------------------------------------------------------------------
@Returns      none
--------------------------------------------------------------------------------
@Parameters    	R_pin_u8 - number of the pin assigned with color RED
				G_pin_u8 - number of the pin assigned with color GREEN
				B_pin_u8 - number of the pin assigned with color BLUE
 *******************************************************************************/
LED::LED(uint8_t R_pin_u8, uint8_t G_pin_u8, uint8_t B_pin_u8)
{
    this->R_pin_u8 = R_pin_u8;
    this->G_pin_u8 = G_pin_u8;
    this->B_pin_u8 = B_pin_u8;        
    ledcAttachPin(this->R_pin_u8,  PWM_CHANNEL_ONE);
    ledcSetup(PWM_CHANNEL_ONE, PWM_FREQUENCY, RESOLUTION_BITS);
    ledcAttachPin(this->G_pin_u8,  PWM_CHANNEL_TWO);
    ledcSetup(PWM_CHANNEL_TWO, PWM_FREQUENCY, RESOLUTION_BITS);
    ledcAttachPin(this->B_pin_u8,  PWM_CHANNEL_THREE);
    ledcSetup(PWM_CHANNEL_THREE, PWM_FREQUENCY, RESOLUTION_BITS);
}


/*******************************************************************************
@Description    Creates a specific tone of color by writing different PWM values
				to the PWM attached channels
--------------------------------------------------------------------------------
@Returns      	none
--------------------------------------------------------------------------------
@Parameters    	R_color_u8 - value of the color RED
				G_color_u8 - value of the color GREEN
				B_color_u8 - value of the color BLUE
 *******************************************************************************/
void LED::setColor_v(uint8_t R_color_u8, uint8_t G_color_u8, uint8_t B_color_u8)
{
    ledcWrite(PWM_CHANNEL_ONE,   R_color_u8);
    ledcWrite(PWM_CHANNEL_TWO,   G_color_u8);
    ledcWrite(PWM_CHANNEL_THREE, B_color_u8);
}


/*******************************************************************************
@Description    Creates the color RED by writing the maximum value on the 
				RED assigned channel
--------------------------------------------------------------------------------
@Returns      	none
--------------------------------------------------------------------------------
@Parameters    	none
 *******************************************************************************/
void LED::setColorRed_v()
{    
    ledcWrite(PWM_CHANNEL_ONE,     255);
    ledcWrite(PWM_CHANNEL_TWO,     	 0);
    ledcWrite(PWM_CHANNEL_THREE, 	 0);
}


/*******************************************************************************
@Description    Creates the color GREEN by writing the maximum value on the 
				GREEN assigned channel
--------------------------------------------------------------------------------
@Returns      	none
--------------------------------------------------------------------------------
@Parameters    	none
 *******************************************************************************/
void LED::setColorGreen_v()
{    
    ledcWrite(PWM_CHANNEL_ONE,     0);    
    ledcWrite(PWM_CHANNEL_TWO,   255);    
    ledcWrite(PWM_CHANNEL_THREE,   0);
}


/*******************************************************************************
@Description    Creates the color BLUE by writing the maximum value on the 
				BLUE assigned channel
--------------------------------------------------------------------------------
@Returns      	none
--------------------------------------------------------------------------------
@Parameters    	none
 *******************************************************************************/

void LED::setColorBlue_v()
{    
    ledcWrite(PWM_CHANNEL_ONE,   	0);    
    ledcWrite(PWM_CHANNEL_TWO,      0);
    ledcWrite(PWM_CHANNEL_THREE,   255);
}


/*******************************************************************************
@Description    Standard destructor
--------------------------------------------------------------------------------
@Returns      	none
--------------------------------------------------------------------------------
@Parameters    	none
 *******************************************************************************/
LED::~LED(void)
{
}
