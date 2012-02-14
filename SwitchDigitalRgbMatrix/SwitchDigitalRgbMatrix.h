/*
 SwitchDigitalRgbTlc Library
	By Julio Terra. Updated on November 21, 2011. Created on June 4, 2011.
 
 	This library is an implementation of RGB digital switches library that uses
	a matrix approach to control the RGB leds for each switch. This implementation
	of the library is less robust than the TLC version. The benefit is that you do 
	not need additional components such as the TLC led drivers.	

	The main limitations include:
		1. The number of colors supported is limited because PWM does not work well 
			with a LED matrix approach
	 	1. The leds flicker when the switches are pressed since the Arduino is not
			fast enough to handle input and manage the lights simultaneously.
 
 	Hierarchy: 
	- Parents Classes: SwitchAbstract, SwitchDigital, SwitchDigitalRgb
	- Child Classes: n/a
	
 Note: This library is part of the Switches family. To make sure that it runs 
 properly please make sure that all parent libraries are available in the 
 libraries folder of your Arduino folder.
 
 File name: SwitchDigitalRgbTlc.h
 
 */


#ifndef __SwitchDigitalRgbMatrix_h__
#define __SwitchDigitalRgbMatrix_h__

#include "../SwitchDigital/SwitchDigitalRgb.h"

class SwitchDigitalRgbMatrix: public SwitchDigitalRgb {    
    public:    
        int led_button_pin;						// holds the voltage pin that is attached to this led on the matrix 
        SwitchDigitalRgbMatrix(int, int, int);	// constructor
        SwitchDigitalRgbMatrix(int, int);		// constructor
        void set_led_pins(int, int, int, int);	// redefine set led pins method
        void update_leds();                     // redefine updated eleds method
};

#endif