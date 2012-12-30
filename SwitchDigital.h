/* 
 *  Digital Switch Class :: Arduino Switch Library.
 * 
 *  This is the digital switch class for switches and buttons with two states. It works only 
 *  	as a toggle switch, use the SwitchDigital RGB for a and enables changing the polarity of 
 *  	a switch. It also features debouncing functionality that helps to filter out noise 
 *  	from readings. 
 * 
 *  Class Hierarchy 
 *  - Parents Classes: SwitchAbstract
 *  - Child Classes: SwitchDigitalRGB [SwitchDigitalRGB_Matrix, SwitchDigitalRGB_TLC] 
 *
 *  @filename SwitchDigital.h 
 *  @version 1.0.0
 *  @author Julio Terra
 *  @date 12/29/12
 * 
 */

#ifndef __SwitchDigital_h__
#define __SwitchDigital_h__

#include "utility/SwitchAbstract.h"

class SwitchDigital: public SwitchAbstract {
	public:
		// holds whether the signal is inverted (e.g. LOW switch state is equal to switch ON or HIGH)
		bool is_inverted;               // holds whether the switch is inverted (uses a pullup resistor)
		bool is_momentary;              // flag set to true if switch is momentary or physical toggle

		// variables that manage switch state
		int last_reading;						// holds the last reading from the switch
		long unsigned reading_debounce_time;	// holds the last time the switch state changed based on the reading 

		// constructors and methods
		SwitchDigital(int);             // class constructor
		void invert_switch(bool);       // method that sets this switch to inverted mode, with pullup resistor
		bool available();               // redefined method that returns whether switch state has changed
		void momentary_button(bool);	// sets this button to function like a momentary or non-momentary button
};

#endif