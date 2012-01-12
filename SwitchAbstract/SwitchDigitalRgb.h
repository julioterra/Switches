/*
 SwitchDigitalRBG Library
	By Julio Terra. Updated on November 21, 2011. Created on June 4, 2011.
 
 	This library is an abstract RGB digital switches library. It provides 
 	the base functionality that is extended by the TLC and Matrix libraries.
	The children libraries use different approach to control the RGB lights for 
	each switch.
 
 	Hierarchy: 
	- Parents Classes: SwitchAbstract, SwitchDigital
	- Child Classes: SwitchDigitalRGB_Matrix, SwitchDigitalRGB_TLC 
	
 Note: This library is part of the Switches family. To make sure that it runs 
 properly please make sure that all parent libraries are available in the 
 libraries folder of your Arduino folder.
 
 File name: RGBButton.h
 
 */

#ifndef __SwitchDigitalRGB_h__
#define __SwitchDigitalRGB_h__

#include "SwitchDigital.h"

class SwitchDigitalRgb: public SwitchDigital {
    
    public:    
		// #define DIGITAL_SWITCH_DEBOUNCE   50       // interval of time that new input will be ignored via digital sensors

		int led_pins[RGB_COUNT];    // holds the pin numbers for the R, G, and B pins
        int max_bright;             // holds the maximum brightness for each RBG output
        int toggle_states;          // holds number of toggle states for a given switch (6 Max)
        int led_digital_states[STATE_MAX][RGB_COUNT];  // holds brightness of each led for diff. toggle states 
    
        bool led_available;         // flag set to true if RGB's pins have been registered
        bool led_on;                // flag set to true when a button's RGB led is on
        bool led_midi_control;		// flag that identifies of button light controlled by external device
        int current_led_state[RGB_COUNT]; // holds the R, G, and B values associated to current led state   

        SwitchDigitalRgb(int, int, int);   		// constructor for RGB button class
        SwitchDigitalRgb(int, int);   			// constructor for RGB button class
        virtual void set_led_pins(int, int, int, int) {};   // method to be redefined in matrix child version of class
        virtual void set_led_pins(int, int, int) {};        // method to be redefined in TLC child version of class
		void set_number_of_states(int);						// sets the number of states 
        bool set_led_state(int, int, int, int);             // sets the RGB levels for a given button state
        void set_midi_control(bool);
        bool available();                                   // redefined method, returns if true if switch state changed
        virtual void update_leds() {};                      // method to be redefined in TLC and matrix child versions of class
        void turn_on_leds(int, int, int);                   // turns on the leds to the specified values
        void turn_on_leds();                                // turns on the leds to the current led state RBG values
        void turn_off_leds();                               // turns off leds, current state saved in current_led_state
        void set_current_led_state(int);                    // set the current RGB led state
        void momentary_button(bool);                        // set the current RGB switch to momentary
    
};

#endif