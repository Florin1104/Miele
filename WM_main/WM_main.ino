#include "ControlPanel.h"
#include "LED.h"
#include "TwinDos.h";

#define TWIN_DOS_PIN 35

static uint8_t lastButtonPressed_8;
static uint8_t R_pin_u8 = 25;
static uint8_t G_pin_u8 = 26;
static uint8_t B_pin_u8 = 27;

LED led(R_pin_u8, G_pin_u8, B_pin_u8);
TwinDos twinDos_o;
ControlPanel controlPanel_o;

bool doorButtonPressed_b = false;
bool startButtonPressed_b = false;


void setup()
{
    // put your setup code here, to run once:

    Serial.begin(9600);                 // serial init for test messages
    delay(1500);                        // give time to Wemos Lolin32 to finish setup
    controlPanel_o.Initialise_e();      //be sure to initialise "s_pinLocation_au8[]" with propper pins
    led.setColor_v(0, 0, 0);

    twinDos_o.Initialise_e(TWIN_DOS_PIN); //setup TwinDos pin number
}

void loop()
{ 
    // SCENARIO 1
    /*lastButtonPressed_8 = controlPanel_o.poolButtonsStateChanges_u8(); // constantly check if a button was pressed
  

    
    switch(lastButtonPressed_8)
    {
    case BUTTON_POWER_ID:
        Serial.println("Power button pressed");
        // TBD
        break;
    case BUTTON_START_STOP_ID:
        Serial.println("Start/Stop button pressed");       
        startButtonPressed_b = true;
        break;
    case BUTTON_WASH_ID:
        Serial.println("Wash button pressed");        
        break;
    case BUTTON_SPIN_ID:
        Serial.println("Spin button pressed");
        // TBD
        break;
    case BUTTON_DOOR_SWITCH_ID:
        Serial.println("Door button pressed");
        doorButtonPressed_b = true;
        break;
    default:        
        break;
    }

       
    // Check 
    if(doorButtonPressed_b == true)
    {
        if (startButtonPressed_b == true)
        {
   
            if(ControlButton::isDoorOpen_b() == true)
            {
                led.setColorRed_v();
                startButtonPressed_b = false;                
            }                
            else
            {
                led.setColorGreen_v();   
              
            }         
        }                        
    }
    */

    // SCENARIO 2
    lastButtonPressed_8 = controlPanel_o.poolButtonsStateChanges_u8(); // constantly check if a button was pressed
  

    
    switch(lastButtonPressed_8)
    {
    case BUTTON_POWER_ID:
        Serial.println("Power button pressed");
        // TBD
        break;
    case BUTTON_START_STOP_ID:
        Serial.println("Start/Stop button pressed");       
        startButtonPressed_b = true;
        break;
    case BUTTON_WASH_ID:
        Serial.println("Wash button pressed");        
        break;
    case BUTTON_SPIN_ID:
        Serial.println("Spin button pressed");
        // TBD
        break;
    case BUTTON_DOOR_SWITCH_ID:
        Serial.println("Door button pressed");
        doorButtonPressed_b = true;
        break;
    default:        
        break;
    }
    bool is_twindos = digitalRead(35);
    Serial.print("twindosul imi zice ca e: ");
    Serial.println(is_twindos);
    // Check 
    if(doorButtonPressed_b == true)
    {
        if (startButtonPressed_b == true)
        {
   
            if(ControlButton::isDoorOpen_b() == true || !(twinDos_o.isPresent_b()))
            {
                led.setColorRed_v();
                startButtonPressed_b = false;                
            }                
            else
            {
                if (twinDos_o.isPresent_b())
                {
                    led.setColorBlue_v();
                }              
            }         
        }                        
    }
    
}

