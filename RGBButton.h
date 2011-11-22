/*
 AMUP Input Element Libraries, RGB Button Abstract
 Created by Julio Terra, June 4, 2011.
 
 This is the RGB Button library from the AMUP Input Element set. This is the
 abstract library that handles RGB buttons which can support multiple button states,
 and momentary behavior. 
 
 Hierarchy:
 - Parents: Switch, Input Element
 - Children: RGBButtonMatrix, RGBButtonTLC 
 
 File name: RGBButton.h
 
 */

#ifndef RGBButton_h
#define RGBButton_h

#include "WProgram.h"
#include "Switch.h"
#include "AMUPconfig.h"
#include <Tlc5940.h>

class RGBButton: public Switch {
    
    public:    
		#define DIGITAL_SWITCH_DEBOUNCE   50       // interval of time that new input will be ignored via digital sensors

		int led_pins[RGB_COUNT];    // holds the pin numbers for the R, G, and B pins
        int max_bright;             // holds the maximum brightness for each RBG output
        int toggle_states;          // holds number of toggle states for a given switch (6 Max)
        int led_digital_states[TOGGLE_MAX][RGB_COUNT];  // holds brightness of each led for diff. toggle states 
    
        bool led_available;         // flag set to true if RGB's pins have been registered
        bool led_on;                // flag set to true when a button's RGB led is on
        bool led_midi_control;
        int current_led_state[RGB_COUNT]; // holds the R, G, and B values associated to current led state   

        RGBButton(int, int, int);   // constructor for RGB button class
        virtual void set_led_pins(int, int, int, int) {};   // method to be redefined in matrix child version of class
        virtual void set_led_pins(int, int, int) {};        // method to be redefined in TLC child version of class
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