/*
 SwitchDigitalRgbTlc Library
	By Julio Terra. Updated on November 21, 2011. Created on June 4, 2011.
 
 	This library is an implementation of RGB digital switches library that works with
	Texas Instrument's TLC5940 led driver. 
 
 	Hierarchy: 
	- Parents Classes: SwitchAbstract, SwitchDigital, SwitchDigitalRgb
	- Child Classes: n/a
	
 Note: This library is part of the Switches family. To make sure that it runs 
 properly please make sure that all parent libraries are available in the 
 libraries folder of your Arduino folder.
 
 File name: SwitchDigitalRgbTlc.h
 
 */

#ifndef __SwitchDigitalRgbTlc_h__
#define __SwitchDigitalRgbTlc_h__

#include "../SwitchAbstract/SwitchDigitalRGB.h"
#include "../Tlc5940/Tlc5940.h"

class SwitchDigitalRgbTlc: public SwitchDigitalRgb {    
    public:    
		SwitchDigitalRgbTlc(int, int, int);		// constructor
		SwitchDigitalRgbTlc(int, int);			// constructor
		void set_led_pins(int, int, int);       // redefine set led pins method
		void update_leds();                     // redefine updated eleds method
};

#endif