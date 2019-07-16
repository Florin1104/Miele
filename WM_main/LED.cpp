#include "LED.h"
#include "Arduino.h"

#define PWM_CHANNEL_ONE             (1)
#define PWM_CHANNEL_TWO             (2)
#define PWM_CHANNEL_THREE           (3)

#define PWM_FREQUENCY				(12000)
#define RESOLUTION_BITS             (8)

LED::LED(void)
{
}

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

void LED::setColor_v(uint8_t B_color_u8, uint8_t G_color_u8, uint8_t R_color_u8)
{
    ledcWrite(PWM_CHANNEL_ONE,   B_color_u8);
    ledcWrite(PWM_CHANNEL_TWO,   G_color_u8);
    ledcWrite(PWM_CHANNEL_THREE, R_color_u8);
}

void LED::setColorRed_v()
{    
    ledcWrite(PWM_CHANNEL_ONE,     0);
    ledcWrite(PWM_CHANNEL_TWO,     0);
    ledcWrite(PWM_CHANNEL_THREE, 255);
}

void LED::setColorGreen_v()
{    
    ledcWrite(PWM_CHANNEL_ONE,     0);    
    ledcWrite(PWM_CHANNEL_TWO,   255);    
    ledcWrite(PWM_CHANNEL_THREE,   0);
}

void LED::setColorBlue_v()
{    
    ledcWrite(PWM_CHANNEL_ONE,   255);    
    ledcWrite(PWM_CHANNEL_TWO,     0);
    ledcWrite(PWM_CHANNEL_THREE,   0);
}

LED::~LED(void)
{
}
