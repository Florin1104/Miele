#include <Wire.h>
#define LED_WASHING_STARTED             ()

#include "TwinDos.h";
#include "HM_HeaterModule.h"
#include "ControlPanel.h"
#include "MotorDriver.h"
#include "Sound.h" // TODO
#include "LCDDisplay.h"
#include "Potentiometer.h"


#define ENABLE_SERIAL_PRINT (1)


#if (ENABLE_SERIAL_PRINT == 1)
#define SERIAL_PRINTLN(Data) Serial.println(Data)
#else
#define SERIAL_PRINTLN(Data)
#endif



						//*** WEMOS LOLIN32 PINS ***\\



//******************************** LEDs *************************************
// Red   - 25				   
// Green - 26				   
// Blue  - 27				   
							   
//******************************** Buttons **********************************
// Power - 33				   
// Start - 18				  
// Wash  - 19				   
// Spin  - 13				   
// Door  - 14				   
							   
//******************************** TwinDos **********************************
// Phase 1 - 34				 
// Phase 2 - ground			  
							   
//******************************** Potentiometer ****************************
// Selection Wheel - 32		   
							   
//******************************** Heating Element **************************
// Sensor  - 15				   
// Heating - 35				   
							   
//******************************** Motor ************************************
// Motor A - 16				   
// Motor B - 17				   
							   
//******************************** LCD **************************************
// Clock - 22
// Data  - 21

//******************************** Sound ************************************
// Pin - TODO




bool powerButtonPressed = false;
bool startButtonPressed = false;
bool doorButtonPressed  = false;
bool washButtonPressed  = false;
bool spinButtonPressed  = false;
int  index_i            = 1    ;



// LED
uint8_t ledPinRed   = GPIO_NUM_25;
uint8_t ledPinGreen = GPIO_NUM_26;
uint8_t ledPinBlue  = GPIO_NUM_27;

// Buttons
ControlPanel       controlPanel_o;
static uint8_t     lastButtonPressed_8;
				   
// LCD			   
LCDDisplay         lcdDisplay(GPIO_NUM_21, GPIO_NUM_22, 0x3f);
				   
// TwinDos		   
TwinDos            twinBox;
				   
// Potentiometer   
Potentiometer      selectWheel(GPIO_NUM_32);
WashingProgram_te  WashProgram_e;
				   
// Heater		   
HeaterModule       heaterObject;
				   
// Motor		   
MotorDriver        motorObject;

// Sound
// TODO


void test_LED           ()
{
	digitalWrite(ledPinRed, HIGH);
	digitalWrite(ledPinBlue, LOW);
	digitalWrite(ledPinGreen, LOW);
	delay(1000);
	digitalWrite(ledPinRed, LOW);
	digitalWrite(ledPinBlue, LOW);
	digitalWrite(ledPinGreen, HIGH);
	delay(1000);
	digitalWrite(ledPinRed, LOW);
	digitalWrite(ledPinBlue, HIGH);
	digitalWrite(ledPinGreen, LOW);
	delay(1000);
	Serial.println("LED must blink in all 3 colors");
}
					    
void test_buttons       ()
{
	lastButtonPressed_8 = controlPanel_o.poolButtonsStateChanges_v();

	switch (lastButtonPressed_8)
	{
	case BUTTON_POWER_ID:
		powerButtonPressed = true;
		break;

	case BUTTON_START_STOP_ID:
		startButtonPressed = true;
		break;

	case BUTTON_DOOR_SWITCH_ID:
		doorButtonPressed = true;
		break;

	case BUTTON_WASH_ID:
		washButtonPressed = true;
		break;

	case BUTTON_SPIN_ID:
		spinButtonPressed = true;
		break;
	}

	if (!powerButtonPressed)
	{
		Serial.println("Power button not pressed");
	}
	if (!doorButtonPressed)
	{
		Serial.println("Door button not pressed");
	}
	if (!startButtonPressed)
	{
		Serial.println("Start button not pressed");
	}
	if (!washButtonPressed)
	{
		Serial.println("Wash button not pressed");
	}
	if (!spinButtonPressed)
	{
		Serial.println("Spin button not pressed");
	}
}
					    
void test_LCD           ()
{
	lcdDisplay.ClearScreen_b();
	lcdDisplay.DisplayString_b("Working");
}
					    
void test_twinDos       ()
{
	if (twinBox.isPresent_b())
	{
		Serial.println("TwinDos deconectat");
	}
	else
	{
		Serial.println("TwinDos conectat");
	}
}
					    
void test_potentiometer ()
{
	WashProgram_e = selectWheel.GetSelectedProgram();

	if (WashProgram_e == WP_NONE)
	{
		Serial.println("Selected program is 0 (WP_NONE)");
	}
	else if (WashProgram_e == WP_WASH)
	{
		Serial.println("Selected program is 1 (WP_WASH)");
	}
	else if (WashProgram_e == WP_SPIN)
	{
		Serial.println("Selected program is 2 (WP_SPIN)");
	}
	else if (WashProgram_e == WP_HANDWASH)
	{
		Serial.println("Selected program is 3 (WP_HANDWASH)");
	}
	else if (WashProgram_e == WP_FAST_WASH)
	{
		Serial.println("Selected program is 4 (WP_FAST_WASH)");
	}
	else if (WashProgram_e == WP_INTENSE_WASH)
	{
		Serial.println("Selected program is 5 (WP_INTENSE_WASH)");
	}
	else if (WashProgram_e == WP_WHITE_CLOTHES)
	{
		Serial.println("Selected program is 6 (WP_WHITE_CLOTHES)");
	}
	else if (WashProgram_e == WP_CLEAN_WASHING_MACHINE)
	{
		Serial.println("Selected program is 7 (WP_CLEAN_WASHING_MACHINE)");
	}
	else if (WashProgram_e == WP_SHIRTS)
	{
		Serial.println("Selected program is 8 (WP_SHIRTS)");
	}
	else if (WashProgram_e == WP_NOT_USED)
	{
		Serial.println("Selected program is 9 (WP_NOT_USED)");
	}
	else
	{
		Serial.println("Result unknown");
	}
}
					    
void test_heater_module ()
{
	heaterObject.StartHeating_v(64);
	heaterObject.StopHeating_v();
	float t = heaterObject.GetTemperature_f();
	Serial.print(t);
}
					    
void test_motor         ()
{
	motorObject.MoveMotor_u16(50, MOTOR_ROTATION_CLOCKWISE, 2);
	motorObject.StopMotor_u16(1);
	delay(2000);
}

void test_sound         ()
{
	PlaySound_v(2, DOOR_OPEN_SOUND);
	StopSound_v();
}

void simulate_heating   ()
{

}





void setup()
{
#if (ENABLE_SERIAL_PRINT == 1)
    Serial.begin(115200);      // serial init for test messages
    delay(1000);               // give time to Wemos Lolin32 to finish setup
#endif


	// LED
	pinMode(ledPinRed,   OUTPUT);
	pinMode(ledPinGreen, OUTPUT);
	pinMode(ledPinBlue,  OUTPUT);
	
	// Buttons
	controlPanel_o.Initialise_e();

	// LCD
	lcdDisplay.init_b();
	
	// TwinDos
	twinBox.Initialise_e(34);

	// Potentiometer
	selectWheel.Init_b();

	// Heater
	heaterObject.Initialise_u16(GPIO_NUM_35, GPIO_NUM_15);

	// Motor
	motorObject.Initialise_u16 (GPIO_NUM_16, GPIO_NUM_17);

	// Sound
	InitialiseSound_v(); // TODO verify



	delay(1000); // give time for Wemos Lolin32 to finish setup
}

void loop()
{

	// Testing Baver
	for (int iindex = 0; iindex < 6; iindex++) {
		Serial.println();
	}
	Serial.print   ("Repeat : ");
	Serial.println (  index_i  );
	index_i++;




	//test_potentiometer ();

	//test_heater_module ();

	//test_buttons       ();

	//test_twinDos       ();

	//test_motor         ();

	//test_sound         (); // TODO verify

	//test_LED           ();

	test_LCD           ();


	delay(1000);
}
