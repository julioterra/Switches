/* 
 *  Digital Switch Class :: Arduino Switch Library.
 * 
 *  This is a class for handling input from switches and buttons with two states. Switches can be 
 *  	configured as momentary or toggle switches. They can also be configured to change their 
 *  	polarity. Features debouncing functionality that helps to filter out noise from readings. 
 *
 * 	Description of Different Modes:
 *  	- Momentary Mode: the switch state reflects the current physical state of the switch. If 
 *  	the switch is pressed it will return a 1, and if it is not pressed it will return a 0
 *  	- Toggle Mode: the switch state changes after every button press the physical state of the
 *  	switch needs to go HIGH and LOW to trigger a state change. When the switch is released the 
 *  	button state toggles its state.
 *  	
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
		bool is_momentary;              // flag set to true if switch is momentary or physical toggle
        int toggle_states;          	// holds number of toggle states for a given switch (6 Max)

		// variables that manage switch state
		int last_reading;						// holds the last reading from the switch
		long unsigned reading_debounce_time;	// holds the last time the switch state changed based on the reading 

		// constructors and methods
		SwitchDigital(int);     // class constructor
		void invert(bool);      // method that sets this switch to inverted mode, with pullup resistor
		bool available();       // redefined method that returns whether switch state has changed
		void momentary(bool);	// sets this button to function like a momentary or non-momentary button
};

#endif