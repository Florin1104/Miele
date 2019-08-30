
#define ERROR_OUT_OF_RANGE 0x00;
#include "driver/ledc.h"

typedef enum MotorRotation{
    MOTOR_CLOCKWISE = 0,
    MOTOR_COUNTER_CLOCKWISE

}MotorRotation_t; 

class Motor {
    private:
        bool isOn;
        int speed;
        MotorRotation_t MotorRotation_e;
        static int channelCount;
        static int timerCount;
        int pinNumber;
        int CalcultateDuty_Cycle(int duty, int Bits_used);


    public: 
        Motor(int pinNumber) { 
            isOn= false;
            this->pinNumber = pinNumber;
        };
    
        void initMotor(ledc_channel_config_t motor_config, ledc_timer_config_t timer_config);
        void setSpeed(ledc_channel_config_t motor_config, uint8_t throttlePercentage) noexcept(false);
        void stopMotor(ledc_channel_config_t motor_config);

        ~Motor(){};

};
