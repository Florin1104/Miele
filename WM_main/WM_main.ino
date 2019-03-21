#define LED_WASHING_STARTED             ()

#include "TwinDos.h";
#include "HM_HeaterModule.h"
#include "ControlPanel.h"
#include "MotorDriver.h"
#include "Sound.h"
//#include "LCDDisplay.h"

TwinDos twinDos_o;
HeaterModule heaterModule_o;
MotorDriver motorDriver_o;
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

ControlPanel controlPanel_o;

void setup()
{
    // put your setup code here, to run once:

    Serial.begin(9600);                 // serial init for test messages
    delay(1000);                        // give time to Wemos Lolin32 to finish setup
    controlPanel_o.Initialise_e();      //be sure to initialise "s_pinLocation_au8[]" with propper pins
    heaterModule_o.Initialise_u16(GPIO_NUM_25,GPIO_NUM_15);
	motorDriver_o.Initialise_u16(GPIO_NUM_13, GPIO_NUM_12);

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
        Serial.println("Power button pressed");
		isPowerButtonPressed = true;

        // TBD
        break;
    case BUTTON_START_STOP_ID:
        Serial.println("Start/Stop button pressed");
		isStartButtonPressed = true;

    //    // TBD
    //    break;
    //case BUTTON_WASH_ID:
    //    Serial.println("Wash button pressed");
    //    // TBD
    //    break;
    //case BUTTON_SPIN_ID:
    //    Serial.println("Spin button pressed");
    //    // TBD
    //    break;
    //case BUTTON_DOOR_SWITCH_ID:
    //    Serial.println("Door button pressed");
    //    // TBD
        break;
    default:
        break;
    }

	if(isPowerButtonPressed == true)
	{
		heaterModule_o.StartHeating_v(120);
		float t= heaterModule_o.GetTemperature_f();
		Serial.print(t);
		motorDriver_o.MoveMotor_u16(50,MOTOR_ROTATION_CLOCKWISE,2);
	}


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
