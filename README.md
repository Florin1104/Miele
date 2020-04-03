# CreateYourOwnWashingMachine
```
                                          

███╗   ███╗██╗███████╗██╗     ███████╗    ██████╗  ██████╗ ██████╗  ██████╗     
████╗ ████║██║██╔════╝██║     ██╔════╝    ╚════██╗██╔═████╗╚════██╗██╔═████╗    
██╔████╔██║██║█████╗  ██║     █████╗       █████╔╝██║██╔██║ █████╔╝██║██╔██║    
██║╚██╔╝██║██║██╔══╝  ██║     ██╔══╝      ██╔═══╝ ████╔╝██║██╔═══╝ ████╔╝██║    
██║ ╚═╝ ██║██║███████╗███████╗███████╗    ███████╗╚██████╔╝███████╗╚██████╔╝    
╚═╝     ╚═╝╚═╝╚══════╝╚══════╝╚══════╝    ╚══════╝ ╚═════╝ ╚══════╝ ╚═════╝     
                                                                                

```                                                                                                                          
                                                                                      
										      
	 https://dl.espressif.com/dl/package_esp32_index.json
                                                                                         
                                                                                         
This is the instruction manual for the Miele Mini Washing Machine Workshop.
In the following lines the steps you need to take will be described.

Using the Arduino or VisualBasic IDE you will need to build a full functional
washing machine durig the time given at the workshop. A full functional washing machine
uses all of its features and resembles a real washig machine in terms of functionality.
Ex.: A real washig machine has different washing programs and comunicates with the user
The programming language that is beeing used is C++.

---------------------------------------------------------
The washing machine contains the following parts:
---------------------------------------------------------
- 12V DC motor
- RGB LED
- Dual H-Bridge
- DHT11 Temperature Sensor
- Piezoelectric buzzer
- Switch
- 100k Potentiometer
- 16x2 LCD Display
- Push Buttons
- 50 Ohm Resistors

The functionality that controls this Washing Machine Module is already written.
In order to create a functional apliance, you will need to use the code given and come up with a logic.
The code will be written in the folowing two sections. Everything that is written outside these sections
it is global.

---------------------------------------------------------
setup() function:
---------------------------------------------------------

The setup() function is called when a sketch starts. 
Use it to initialize variables, pin modes, start using libraries, etc. 
The setup() function will only run once, after each powerup or reset of the Arduino board.

---------------------------------------------------------
loop() function:
---------------------------------------------------------

After creating a setup() function, which initializes and sets the initial values, 
the loop() function does precisely what its name suggests, and loops consecutively, 
allowing your program to change and respond. Use it to actively control the Arduino board.


																		 