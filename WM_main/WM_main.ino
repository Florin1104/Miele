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
Motor A 16
Motor B 17
valid pvm pins 15,2,0,4,16,17,5,18,23,19,21,22,13,12,14,27,26,25,35,34,33,32,39,36
********************************************

******** Twindows pins *********************
Twindows Pin 12
********************************************

******** LCD pins **************************
LCD Pin 21 22
********************************************
******** Potentiometer pin *****************
Potentiometer Pin
********************************************

*/



//ControlButton DoorButton_o;
//ControlButton SpinButton_o;
MotorDriver Motor_o;
TwinDos Twin_Cartrige_o;
MotorRotation_te direction = MOTOR_ROTATION_CLOCKWISE;
MotorRotation_te direction2 = MOTOR_ROTATION_COUNTER_CLOCKWISE;
Sounds_te DoorSound = DOOR_OPEN_SOUND;
Sounds_te ProgramEndSound = PROGRAM_END_SOUND;
ControlPanel controlPanel_o;
LCDDisplay disp_o(21, 22, 0x3f);
Potentiometer Pot_o(27);
HeaterModule heaterModule_o;



static uint8_t lastButtonPressed_8;
static bool refresh_lcd_message_flag_b = false;



void setup()
{

    Serial.begin(9600);
    delay(1500);
    Twin_Cartrige_o.Initialise_e(34);
    Pot_o.Init_b();
    //DoorButton_o.Initialise_e(12);
    //SpinButton_o.Initialise_e(16);
    Motor_o.Initialise_u16(16, 17);
    controlPanel_o.Initialise_e();      //be sure to initialise "s_pinLocation_au8[]" with propper pins
    disp_o.init_b();
    InitialiseSound_v();
    heaterModule_o.Initialise_u16(15,25);
}





void loop()
{
   
    // 1. Add here control panel testing code
    lastButtonPressed_8 = controlPanel_o.poolButtonsStateChanges_u8(); // constantly check if a button was pressed
    
    switch (lastButtonPressed_8)
    {
    case BUTTON_POWER_ID:
        Serial.println("Power was button pressed");

        Serial.println("The motor shold spin right now MOTOR_ROTATION_CLOCKWISE!");
        Motor_o.MoveMotor_u16(30, MOTOR_ROTATION_CLOCKWISE, 3);

        disp_o.ClearScreen_b();
        disp_o.DisplayString_b("Power was button pressed");
      
        break;

    case BUTTON_START_STOP_ID:
        Serial.println("Start/Stop button pressed");
        StopSound_v();
        Motor_o.StopMotor_u16(1);

        disp_o.ClearScreen_b();
        disp_o.DisplayString_b("Start/Stop button pressed");

        break;

    case BUTTON_WASH_ID:
        Serial.println("Wash button pressed");
        GenerateSounds(8, 500);
        delay(10);

        disp_o.ClearScreen_b();
        disp_o.DisplayString_b("Wash button pressed");
   
        break;
    case BUTTON_SPIN_ID:
        Serial.println("Spin button pressed");          //!!! Water-in button activates the spin button
        Serial.println("The motor shold spin right now MOTOR_ROTATION_COUNTER_CLOCKWISE!");
        Motor_o.MoveMotor_u16(30, MOTOR_ROTATION_COUNTER_CLOCKWISE, 3);
        
        disp_o.ClearScreen_b();
        disp_o.DisplayString_b("Spin button pressed");


 
        break;
    case BUTTON_DOOR_SWITCH_ID:
        Serial.println("Door button pressed");

        disp_o.ClearScreen_b();
        disp_o.DisplayString_b("Door button pressed");
       

        break;
    default:
        
        break;
    }


    // 2. Add test for LCD -> Write "Hello World Miele 2019" on lcd
    // This flag is used in order not to refresh LCD.
    if (refresh_lcd_message_flag_b == false) 
    {
        disp_o.ClearScreen_b();
        disp_o.DisplayString_b("Hello World Miele 2019");
        refresh_lcd_message_flag_b = true;
    }

    // 3. Add here the code for potentiometer (vezi sa printezi valorile de la potentiometru)
    //WashingProgram_te Program_e = Pot_o.GetSelectedProgram();
    //switch (Program_e)
    //{
    //case WP_NONE:
    //    Serial.println("Program selected: 0");
    //    break;
    //case WP_WASH:
    //    Serial.println("Program selected: 1");
    //    break;
    //case WP_SPIN:
    //    Serial.println("Program selected: 2");
    //    break;
    //case WP_HANDWASH:
    //    Serial.println("Program selected: 3");
    //    break;
    //case WP_FAST_WASH:
    //    Serial.println("Program selected: 4");
    //    break;
    //case WP_INTENSE_WASH:
    //    Serial.println("Program selected: 5");
    //    break;
    //case WP_WHITE_CLOTHES:
    //    Serial.println("Program selected: 6");
    //    break;
    //case WP_CLEAN_WASHING_MACHINE:
    //    Serial.println("Program selected: 7");
    //    break;
    //case WP_SHIRTS:
    //    Serial.println("Program selected: 8");
    //    break;
    //case WP_NOT_USED:
    //    Serial.println("Program selected: 9");
    //    break;
    //default:
    //    break;
    //}

    // 4. Add here buzzer sound



    // 5. Add code here heater(37 grade Celsius) and get the temperature from sensor (37 grade Celsius)
    //heaterModule_o.StartHeating_v((float)10);       //works
    //Serial.println("StartHeating_v");

    //float t = heaterModule_o.GetTemperature_f();    //gets NAN
    //Serial.println("GetTemperature_f");
    //Serial.println(t);
    /*while (t > (float)2)
    {
        //Serial.println(t);
        //Serial.println("aici");
        t = heaterModule_o.GetTemperature_f();
    }
    heaterModule_o.StopHeating_v();*/

    // 6. Spin motor 2 sec clockwise and 2 second counter clockwise and then stop 2 seconds
    //Serial.println("MOTOR_ROTATION_COUNTER_CLOCKWISE");
    //Serial.println(Motor_o.counter_clockwiseChannel);

    //// 7. Twindows code detect if cartiges are insterted or not
    /*if (Twin_Cartrige_o.isPresent_b())
    {
        Serial.println("twin detected");
    }
    else
    {
        Serial.println("twin not here");
    }*/
}

