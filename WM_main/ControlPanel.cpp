/*******************************************************************************
@Module         Control Panel
--------------------------------------------------------------------------------
@Filename       ControlPanel.cpp
--------------------------------------------------------------------------------
@Description    check in header file for more details

--------------------------------------------------------------------------------
@Author         Iulian G. , Dragos B. , Marian S. , Stefan I. 
@Date           15.11.2018

@Copyright      Miele  Cie Copyright 2020

*******************************************************************************/

/*******************************************************************************
@Project Includes
*******************************************************************************/
#include "ControlPanel.h"

/*******************************************************************************
@Constants (global)
*******************************************************************************/

/*******************************************************************************
@Macros (global)
*******************************************************************************/

/*******************************************************************************
@Type definitions  (global)
*******************************************************************************/

/*******************************************************************************
@Local Variables 
*******************************************************************************/

/*******************************************************************************
@External Prototypes
*******************************************************************************/

/*******************************************************************************
@Prototypes local Functions
*******************************************************************************/

// keep last button interrupt
static volatile ButtonsPanel_te LastButtonInterrupt_u8;

// button interrupt function
void BTN_PowerActive_v()
{
    LastButtonInterrupt_u8 = BUTTON_POWER_ID;
}

// button interrupt function
void BTN_StartStopActive_v()
{
    LastButtonInterrupt_u8 = BUTTON_START_STOP_ID;
}

// button interrupt function
void BTN_WashActive_v()
{
    LastButtonInterrupt_u8 = BUTTON_WASH_ID;
}

// button interrupt function
void BTN_SpinActive_v()
{
    LastButtonInterrupt_u8 = BUTTON_SPIN_ID;
}

// button interrupt function
void BTN_DoorActive_v()
{
    LastButtonInterrupt_u8 = BUTTON_DOOR_SWITCH_ID;
}

ControlPanel::ControlPanel()
{

	LastButtonInterrupt_u8 = BUTTON_LAST_ENTRY_ID;
    m_InitFlag_b = false;
}

/*******************************************************************************
Function description and additional notes,
are given at the function prototype in the header file
*******************************************************************************/
ButtonError_te ControlPanel::Initialise_e()
{
    
    ButtonError_te error = BUTTON_ERROR_INVALID_PIN;
    
    if(m_InitFlag_b == false)
    {
        uint8_t i,j;
        // search for duplicate pin number
        for(i = 0; i < BUTTON_LAST_ENTRY_ID-1; i++)
        {
            for(j = i+1; j < BUTTON_LAST_ENTRY_ID; j++)
            {
                if(s_pinLocation_au8[i] ==  s_pinLocation_au8[j])
                {
                    error = BUTTON_ERROR_DUPLICATE;
                    break;
                }
            }
        }
        if(error != BUTTON_ERROR_DUPLICATE)
        {
            // checks for valid pin number
            for(i = 0; i < BUTTON_LAST_ENTRY_ID; i++)
            {
				// m_btnList_ao is an array of ControlButton Objects and Initialise_e is not
				// the same as Initialise_e in this module
                error = m_btnList_ao[i].Initialise_e(s_pinLocation_au8[i]);
                
                if(error != BUTTON_ERROR_OK)
                {
					Serial.print("ControlPanel::Initialise_e()--ERROR--");
					Serial.println(error);
                    break;
					
                }
            }
        }
        if(BUTTON_ERROR_OK == error)
        {
			/********************************************
            *   	Register buttons interrupts			*
			*********************************************/		
			
			// The buttons are set in the Initialise_e() as INPUT_PULLUP.
			
			// Unlike pinMode(INPUT), there is no pull-down resistor necessary. 
			// An internal 20K-ohm resistor is pulled to 5V. 
			// When your button is not pressed, the internal pull-up resistor connects to 5 volts. 
			// This causes the board to report "1" or HIGH. When the button is pressed, 
			// the board pin is pulled to ground, causing the board report a "0", or LOW.
			
			// The Interrupt will trigger on the RISING edge of the signal, so when the button 
			// will bounce back, a new RISING edge will be produced and the Interrupt will be called
			
			
			// The programmer defines the code that is to be executed when a particular 
			// interrupt occurs within the program itself. 
			// In Arduino, we use a function called attachInterrupt() to do this and the 
			// recommended syntax looks similar to the output below.
			// attachInterrupt(digitalPinToInterrupt(pin), ISR, mode)
			// This function takes three parameters:
			// First Parameter (i.e. digitalPinToInterrupt(pin)) - 
			// Pin number of the interrupt, which tells the microprocessor which pin to monitor.
			// The pin depends on the microcontroller being used.

			// Second Parameter (i.e. ISR) - The location of code we want to execute if this interrupt 
			// is triggered.

			// Third Parameter (i.e.mode) - Tells it what type of trigger to look for: a logic high, 
			// a logic low or a transition between the two.
			
			
			/********************************************
            *   		How Does It Work?				*
			*********************************************/	
			
			// When the event or interrupt happens, the processor takes immediate notice, 
			// saves its execution state, runs a small chunk of code 
			// (often called the interrupt handler or interrupt service routine), and then returns 
			// back to whatever it was doing before.
			
            attachInterrupt(digitalPinToInterrupt(s_pinLocation_au8[BUTTON_POWER_ID]), BTN_PowerActive_v, RISING);
            attachInterrupt(digitalPinToInterrupt(s_pinLocation_au8[BUTTON_START_STOP_ID]), BTN_StartStopActive_v, RISING);
            attachInterrupt(digitalPinToInterrupt(s_pinLocation_au8[BUTTON_WASH_ID]), BTN_WashActive_v, RISING);
            attachInterrupt(digitalPinToInterrupt(s_pinLocation_au8[BUTTON_SPIN_ID]), BTN_SpinActive_v, RISING);
            attachInterrupt(digitalPinToInterrupt(s_pinLocation_au8[BUTTON_DOOR_SWITCH_ID]), BTN_DoorActive_v, RISING);
            m_InitFlag_b = true;
        }
    }
    return error;
}

/*******************************************************************************
Function description and additional notes,
are given at the function prototype in the header file
*******************************************************************************/
ButtonsPanel_te ControlPanel::poolButtonsStateChanges_e()
{

	// Whenever an interrupt is triggered, the code will stop its current execution flow
	// and will deal with the interrupt routine. In this case the button pressed activated interrupts 
	// Each interrupt updates the LastButtonInterrupt_u8 value with the ID of the current pressed button
    ButtonsPanel_te RetrunedLastButton = LastButtonInterrupt_u8;

    LastButtonInterrupt_u8 = BUTTON_LAST_ENTRY_ID;
 
  
    return RetrunedLastButton;
}

