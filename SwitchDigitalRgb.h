/* 
 *  Digital RGB Switch Class :: Arduino Switch Library.
 * 
 *  This RGB switch library creates buttons with multiple states, that use an rgb led 
 *  as a source of feedback. Buttons can be set with a variable number of states, and
 *  each state can be mapped to a different rgb color.  
 * 
 *  Class Hierarchy 
 *  - Parents Classes: SwitchAbstract, SwitchDigital
 *  - Child Classes: SwitchDigitalRgbMatrix, SwitchDigitalRgbTlc 
 *  
 *  @filename SwitchDigitalRgb.h 
 *  @version 1.0.0
 *  @author Julio Terra
 *  @date 12/29/12
 * 
 */

#ifndef __SwitchDigitalRGB_h__
#define __SwitchDigitalRGB_h__

#include "./SwitchDigital.h"

class SwitchDigitalRgb: public SwitchDigital {

    public:    
        int led_pins[RGB_COUNT];    // holds the pin numbers for the R, G, and B pins
        int max_bright;             // holds the maximum brightness for each RBG output
        int led_digital_states[STATE_MAX][RGB_COUNT];  // holds brightness of each led for diff. toggle states 
    
        bool led_available;         // flag set to true if RGB's pins have been registered
        bool led_on;                // flag set to true when a button's RGB led is on
        bool led_midi_control;      // flag that identifies of button light controlled by external device
        int current_led_state[RGB_COUNT]; // holds the R, G, and B values associated to current led state   
    
        SwitchDigitalRgb(int, int);   		// constructor for RGB button class
        SwitchDigitalRgb(int);   			// constructor for RGB button class
        virtual void set_led_pins(int, int, int, int) {};   // method to be redefined in matrix child version of class
        void set_led_pins(int, int, int);                   // method that sets the led pins for r, g, and leds
		void set_number_of_states(int);						// sets the number of states 
        bool set_led_state(int, int, int, int);             // sets the RGB levels for a given button state
        bool available();                                   // redefined method, returns if true if switch state changed
        void update_leds();                      // method to be redefined in TLC and matrix child versions of class
        void turn_on_leds(int, int, int);                   // turns on the leds to the specified values
        void turn_on_leds();                                // turns on the leds to the current led state RBG values
        void turn_off_leds();                               // turns off leds, current state saved in current_led_state
        void set_current_led_state(int);                    // set the current RGB led state    
};

#endif