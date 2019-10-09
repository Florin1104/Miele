// Visual Micro is in vMicro>General>Tutorial Mode
// 
/*
Name:       WM_Play_Sound.ino
Created:	09.10.2019 11:33:10
Author:     RO\roilin
*/

#include "ControlButton.h"
#include "MotorDriver.h"
#include "ControlButton.h"
#include "LED.h"
#include "TwinDos.h"
#include "Sound.h"
#include "ControlPanel.h"
#include "LCDDisplay.h"
#include "Potentiometer.h"
#include "HM_HeaterModule.h"
/*
*********  Control Panel pins *************
PowerPin 33
StartPin 18
WashPin  19
SpinPin  13
DoorPin  14
********************************************

*********  Motor pins **********************
Motor A
Motor B
valid pvm pins 15,2,0,4,16,17,5,18,23,19,21,22,13,12,14,27,26,25,35,34,33,32,39,36
********************************************

******** Twindows pins *********************
Twindows Pin
********************************************

******** LCD pins **************************
LCD Pin 21 22
********************************************
******** Potentiometer pin *****************
Potentiometer Pin
********************************************

*/



ControlButton DoorButton_o;
ControlButton SpinButton_o;
MotorDriver Motor_o;
TwinDos Twin_Cartrige_o;
MotorRotation_te direction = MOTOR_ROTATION_CLOCKWISE;
MotorRotation_te direction2 = MOTOR_ROTATION_COUNTER_CLOCKWISE;
Sounds_te DoorSound = DOOR_OPEN_SOUND;
Sounds_te ProgramEndSound = PROGRAM_END_SOUND;
ControlPanel controlPanel_o;
LCDDisplay disp_o(21, 22, 0x3f);
Potentiometer Pot_o(25);
HeaterModule heaterModule_o;


static uint8_t lastButtonPressed_8;



void setup()
{

    Serial.begin(9600);
    delay(1500);
    Twin_Cartrige_o.Initialise_e(12);
    DoorButton_o.Initialise_e(19);
    SpinButton_o.Initialise_e(16);
    Motor_o.Initialise_u16(23, 18);
    controlPanel_o.Initialise_e();      //be sure to initialise "s_pinLocation_au8[]" with propper pins
    disp_o.init_b();
    heaterModule_o.Initialise_u16(GPIO_NUM_25, GPIO_NUM_15);
}





void loop()
{


    // 1. Add here control panel testing code
    lastButtonPressed_8 = controlPanel_o.poolButtonsStateChanges_u8(); // constantly check if a button was pressed
    switch (lastButtonPressed_8)
    {
    case BUTTON_POWER_ID:
        Serial.println("Power button pressed");
        // TBD
        break;
    case BUTTON_START_STOP_ID:
        Serial.println("Start/Stop button pressed");
        // TBD
        break;
    case BUTTON_WASH_ID:
        Serial.println("Wash button pressed");
        // TBD
        break;
    case BUTTON_SPIN_ID:
        Serial.println("Spin button pressed");
        // TBD
        break;
    case BUTTON_DOOR_SWITCH_ID:
        Serial.println("Door button pressed");
        // TBD
        break;
    default:
        break;
    }


    // 2. Add test for LCD -> Write "Hello World Miele 2019" on lcd
    disp_o.ClearScreen_b();
    disp_o.DisplayString_b("Hello World Miele 2019");

    // 3. Add here the code for potentiometer (vezi sa printezi valorile de la potentiometru)
    WashingProgram_te WashProgram_e = Pot_o.GetSelectedProgram();
    switch (WashProgram_e)
    {
    case WP_NONE:
        Serial.println("Program selected: 0");
        break;
    case WP_WASH:
        Serial.println("Program selected: 1");
        break;
    case WP_SPIN:
        Serial.println("Program selected: 2");
        break;
    case WP_HANDWASH:
        Serial.println("Program selected: 3");
        break;
    case WP_FAST_WASH:
        Serial.println("Program selected: 4");
        break;
    case WP_INTENSE_WASH:
        Serial.println("Program selected: 5");
        break;
    case WP_WHITE_CLOTHES:
        Serial.println("Program selected: 6");
        break;
    case WP_CLEAN_WASHING_MACHINE:
        Serial.println("Program selected: 7");
        break;
    case WP_SHIRTS:
        Serial.println("Program selected: 8");
        break;
    case WP_NOT_USED:
        Serial.println("Program selected: 9");
        break;
    default:
        break;
    }

    // 4. Add here buzzer sound
    PlaySound_v(2, DOOR_OPEN_SOUND);
    StopSound_v();
    PlaySound_v(2, DOOR_CLOSED_SOUND);
    StopSound_v();
    PlaySound_v(2, PROGRAM_END_SOUND);
    StopSound_v();

    // 5. Add code here heater(37 grade Celsius) and get the temperature from sensor (37 grade Celsius)
    heaterModule_o.StartHeating_v(64);
    float t = heaterModule_o.GetTemperature_f();
    while (t < (float)35)
    {
        Serial.print(t);
        t = heaterModule_o.GetTemperature_f();
    }
    heaterModule_o.StopHeating_v();

    // 6. Spin motor 2 sec clockwise and 2 second counter clockwise and then stop 2 seconds
    Motor_o.MoveMotor_u16(30, MOTOR_ROTATION_CLOCKWISE, 2);
    Serial.println("MOTOR_ROTATION_CLOCKWISE");
    Motor_o.StopMotor_u16(2);
    Motor_o.MoveMotor_u16(30, MOTOR_ROTATION_COUNTER_CLOCKWISE, 3);
    Serial.println("MOTOR_ROTATION_COUNTER_CLOCKWISE");

    // 7. Twindows code detect if cartiges are insterted or not
    if (Twin_Cartrige_o.isPresent_b())
    {
        Serial.println("twin detected");
    }
    else
    {
        Serial.println("twin not here");
    }
}

