#include <Wire.h>
#define LED_WASHING_STARTED             ()

#include "TwinDos.h";
#include "HM_HeaterModule.h"
#include "ControlPanel.h"
#include "MotorDriver.h"
#include "Sound.h"
#include "LCDDisplay.h"
//#include "LCDDisplay.h"


/*******************************************************************************
@Typedefinitions (module-local)
*******************************************************************************/



/*******************************************************************************
@Description   TODO

--------------------------------------------------------------------------------
@Returns       none

--------------------------------------------------------------------------------
@Parameters    none
*******************************************************************************/
static uint8_t lastButtonPressed_8;

/***************************** Twindows Pins ***********************************/
TwinDos twinDos_o;

/****************************** Heater Module **********************************/
// Heating Element - 25   
// Temperature Sensor - 17
HeaterModule heaterModule_o;

/********************* Motor Power Control *************************************/
// Motor A - 16
// Motor B - 17
MotorDriver motorDriver_o;

/************************ LCD Display ******************************************/
// LCD Display
// Clock Pin 21
// Data  Pin 22
LCDDisplay lcd(GPIO_NUM_21, GPIO_NUM_22, 0x3f);

/************************* Control Panel Buttons *******************************/
// Control Panel Buttons
// PowerPin,   StartPin,   WashPin,    SpinPin,    DoorPin
// { 33,         18,         22,         13,         14 };
ControlPanel controlPanel_o;







void setup()
{
    // put your setup code here, to run once:

    Serial.begin(9600);                 // serial init for test messages
    delay(1000);                        // give time to Wemos Lolin32 to finish setup
    
    controlPanel_o.Initialise_e();      //be sure to initialise "s_pinLocation_au8[]" with propper pins
    
    heaterModule_o.Initialise_u16(GPIO_NUM_25, GPIO_NUM_15);
  
    motorDriver_o.Initialise_u16(GPIO_NUM_16,  GPIO_NUM_17);
  
   lcd.init_b();
}

void loop()
{
  bool isPowerButtonPressed = false;
  bool isStartButtonPressed = false;

  
    // put your main code here, to run repeatedly:
    lastButtonPressed_8 = controlPanel_o.poolButtonsStateChanges_v(); // constantly check if a button was pressed
    
  switch(lastButtonPressed_8)
    {
    case BUTTON_POWER_ID:
      lcd.ClearScreen_b();
      Serial.println("Power button pressed");
      lcd.DisplayString_b("Power button pressed");
      isPowerButtonPressed = true;

        break;

    case BUTTON_START_STOP_ID:
    lcd.ClearScreen_b();
    lcd.DisplayString_b("Start button pressed");

    isStartButtonPressed = true;

        break;

    case BUTTON_WASH_ID:
    lcd.ClearScreen_b();
    lcd.DisplayString_b("Wash button pressed");
        // TBD
        break;

    case BUTTON_SPIN_ID:
    
    lcd.ClearScreen_b();
    lcd.DisplayString_b("Spin button pressed");
        // TBD
        break;

    case BUTTON_DOOR_SWITCH_ID:

    lcd.ClearScreen_b();
    lcd.DisplayString_b("Door is closed");
        // TBD
        break;

    }

  if(isPowerButtonPressed == true)
  {
    //Serial.println("Start heating");
    //heaterModule_o.StartHeating_v(70);



    Serial.println("Spin Motor");
    motorDriver_o.MoveMotor_u16(50, MOTOR_ROTATION_CLOCKWISE,2);

    isPowerButtonPressed = false;
  }

  motorDriver_o.StopMotor_u16(1);
  float t = heaterModule_o.GetTemperature_f();
  Serial.print(t);
  lcd.ClearScreen_b();
  lcd.DisplayString_b("astept o comanda");
}

/*******************************************************************************
@Local Functions
*******************************************************************************/


/*******************************************************************************
@Description   TODO

--------------------------------------------------------------------------------
@Returns       TODO

--------------------------------------------------------------------------------
@Parameters    TODO
*******************************************************************************/
bool isDoorClosed_b()
{
    // TBD
  return false;
}


/*******************************************************************************
@Description   TODO

--------------------------------------------------------------------------------
@Returns       TODO

--------------------------------------------------------------------------------
@Parameters    TODO
*******************************************************************************/
bool AreCartridgesPresent_b()
{
    // TBD
  return false;
}
