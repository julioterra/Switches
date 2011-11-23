/*
 SwitchDigital Library
	By Julio Terra. Updated on November 21, 2011. Created on June 4, 2011.
 
 	This library handles digital switches with two states (on and off). 
 	It supports both momentary and non-momentary switches, and enables you
 	to set the polarity of a switch. 
 
 	Hierarchy: 
	- Parents Classes: SwitchAbstract
	- Child Classes: SwitchDigitalRGB [SwitchDigitalRGB_Matrix, SwitchDigitalRGB_TLC] 
	
 Note: This library is part of the Switches family. To make sure that it runs 
 properly please make sure that all parent libraries are available in the 
 libraries folder of your Arduino folder.
 
 File name: SwitchDigital.h
 
 */

#ifndef __SwitchDigital_h__
#define __SwitchDigital_h__

#include "../SwitchAbstract/SwitchAbstract.h"

class SwitchDigital: public SwitchAbstract {
	public:
		// holds whether the signal is inverted (e.g. LOW switch state is equal to switch ON or HIGH)
		bool is_inverted;               // holds whether the switch is inverted (uses a pullup resistor)
		bool is_momentary;              // flag set to true if switch is momentary or physical toggle

		// variables that manage switch state
		int last_reading;						// holds the last reading from the switch
		long unsigned reading_debounce_time;	// holds the last time the switch state changed based on the reading 

		// constructors and methods
		SwitchDigital(int, int);               // class constructor
		void invert_switch(bool);       // method that sets this switch to inverted mode, with pullup resistor
		bool available();               // redefined method that returns whether switch state has changed
};

#endif