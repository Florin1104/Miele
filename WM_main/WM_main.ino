#include <Wire.h>
#define LED_WASHING_STARTED             ()

#include "TwinDos.h";
#include "HM_HeaterModule.h"
#include "ControlPanel.h"
#include "MotorDriver.h"
#include "Sound.h"
#include "LCDDisplay.h"
//#include "LCDDisplay.h"


#define ENABLE_SERIAL_PRINT (1)

#if (ENABLE_SERIAL_PRINT == 1)
#define SERIAL_PRINTLN(Data) Serial.println(Data)
#else
#define SERIAL_PRINTLN(Data)
#endif


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
// Temperature Sensor - 15
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
// { 33,         18,         19,         13,         14 };
ControlPanel controlPanel_o;







void setup()
{
    // put your setup code here, to run once:
#if (ENABLE_SERIAL_PRINT == 1)
    Serial.begin(115200);                 // serial init for test messages
    delay(1000);                        // give time to Wemos Lolin32 to finish setup
#endif
    controlPanel_o.Initialise_e();      //be sure to initialise "s_pinLocation_au8[]" with propper pins
    
    heaterModule_o.Initialise_u16(GPIO_NUM_25, GPIO_NUM_15);
  
    motorDriver_o.Initialise_u16(GPIO_NUM_16,  GPIO_NUM_17);
  
   lcd.init_b();
}


/* Global variables used in loop()*/
  bool isPowerButtonPressed = false;
  bool isSpinButtonPressed  = false;



void loop()
{


  
    // put your main code here, to run repeatedly:
    lastButtonPressed_8 = controlPanel_o.poolButtonsStateChanges_v(); // constantly check if a button was pressed
    
  switch(lastButtonPressed_8)
    {
    case BUTTON_POWER_ID:
        isPowerButtonPressed = true;
        SERIAL_PRINTLN("Power Button");
        break;

    case BUTTON_START_STOP_ID:

        break;

    case BUTTON_WASH_ID:

        // TBD
        break;

    case BUTTON_SPIN_ID:
      isSpinButtonPressed = true;
      SERIAL_PRINTLN("Spin Button");
        // TBD
        break;

    case BUTTON_DOOR_SWITCH_ID:

        SERIAL_PRINTLN("Door switch is pushed");
        isDoorClosed = true;
        break;

    }

  if((isPowerButtonPressed == true) && (isSpinButtonPressed == true))
  {

    SERIAL_PRINTLN("Spin Motor");
    motorDriver_o.MoveMotor_u16(50, MOTOR_ROTATION_CLOCKWISE,2);
    motorDriver_o.StopMotor_u16(1);

    isPowerButtonPressed = false;
    isSpinButtonPressed  = false;


    
  }


      //float t = heaterModule_o.GetTemperature_f();
      //SERIAL_PRINTLN(t);
      SERIAL_PRINTLN(isPowerButtonPressed);
      SERIAL_PRINTLN(isSpinButtonPressed);

      
      lcd.ClearScreen_b();
      lcd.DisplayString_b("Do something!");

      
      
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
