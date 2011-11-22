/*
 
 AMUP Input Element Libraries, Switch
 Created by Julio Terra, June 4, 2011.
 
 This is the switch library from the AMUP Input Element set. This library 
 handles simple switches with two states (on and off). It supports both 
 momentary and non-momentary switches. 
 
 Hierarchy:
 - Parents: Input Element
 - Children: RGBButton [RGBButtonMatrix, RGBButtonTLC] 
 
 File name: Switch.h
 
 */

#ifndef Switch_h
#define Switch_h

#include "WProgram.h"
#include "AMUPconfig.h"
#include "utility/InputElement.h"

class Switch: public InputElement {
    public:
        // holds whether the signal is inverted (e.g. LOW switch state is equal to switch ON or HIGH)
        bool is_inverted;               // holds whether the switch is inverted (uses a pullup resistor)
        bool is_momentary;              // flag set to true if switch is momentary
    
        // variables that manage switch state
        int last_reading;               // holds the last reading from the switch
        long unsigned reading_debounce_time;      // holds the last time the switch state changed based on the reading 
    
        // constructors and methods
        Switch(int, int);               // class constructor
        void invert_switch(bool);       // method that sets this switch to inverted mode, with pullup resistor
        bool available();               // redefined method that returns whether switch state has changed
};

#endif