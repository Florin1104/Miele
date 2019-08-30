#include "motor.h"
#include "driver/gpio.h"
#include <esp_system.h>
#include "iostream"

int Motor::channelCount = 0;
int Motor::timerCount = 0;
int Motor::CalcultateDuty_Cycle(int duty, int Bits_used)
{
    int dutyCycle = (((1 << Bits_used) - 1) * duty) / 100;
    std::cout << dutyCycle << "\n";
    return dutyCycle;
}

void Motor::initMotor(ledc_channel_config_t motor_config, ledc_timer_config_t timer_config)
{
   
    motor_config.gpio_num = pinNumber;
    motor_config.speed_mode = LEDC_HIGH_SPEED_MODE;
    motor_config.channel = static_cast<ledc_channel_t>(channelCount);
    channelCount++;
    motor_config.duty = 0;
    motor_config.hpoint = 0;
    motor_config.intr_type = LEDC_INTR_DISABLE;
    motor_config.timer_sel = static_cast<ledc_timer_t>(timerCount);

    ledc_channel_config(&motor_config);

    //freq = 500

    timer_config.speed_mode = LEDC_HIGH_SPEED_MODE;
    timer_config.duty_resolution = LEDC_TIMER_8_BIT;
    timer_config.timer_num = static_cast<ledc_timer_t>(timerCount);
    timerCount++;
    timer_config.freq_hz = 500;

    ledc_timer_config(&timer_config);

    ledc_set_duty(motor_config.speed_mode, motor_config.channel, 0);
    ledc_update_duty(motor_config.speed_mode, motor_config.channel);
}

void Motor::setSpeed(ledc_channel_config_t motor_config, uint8_t throttlePercentage) noexcept(false)
{

    if (throttlePercentage > 100)
    {
        throw ERROR_OUT_OF_RANGE;
    }
    else
    {
        isOn = true;
        ledc_set_duty(motor_config.speed_mode, motor_config.channel, CalcultateDuty_Cycle(throttlePercentage, 8));
        ledc_update_duty(motor_config.speed_mode, motor_config.channel);
    }
}

void Motor::stopMotor(ledc_channel_config_t motor_config)
{
    if (isOn == true)
    {
        setSpeed(motor_config, 0);
        isOn = false;
    }
}