/*
 AMUP Input Element Libraries, Analog Switch
 Created by Julio Terra, June 4, 2011.
 
 This is the analog switch library from the AMUP Input Element set. This 
 library handles analog switches such as potentiometers and other 
 variable resistors.
 
 Hierarchy:
 - Parents: Input Element
 - Children: n/a 
 
 File name: AnalogSwitch.h 
 */

#ifndef AnalogSwitch_h
#define AnalogSwitch_h

#include "WProgram.h"
#include "AMUPconfig.h"
#include "utility/InputElement.h"

class AnalogSwitch: public InputElement {
    public:
        // range and averaging variables
        #define OUTPUT_RANGE            127     
        #define AVG_READINGS            10
        #define STATE_CHANGE_THRESH     8

        // variables that manage switch state
        int last_reading;        // holds the current momentary state of the switch (on, off, or analog number)
		bool is_inverted;        // holds whether the switch is inverted (uses a pullup resistor)

        // variables that define and manage analog input range
        int range_min;      // holds the bottom of the range of an analog sensor
        int range_max;      // holds the top of the range of an analog sensor
        int range;          // holds the size of the range of an analog sensor
		int output_range;

        AnalogSwitch(int, int);             // constructor
        void set_analog_range(int, int);    // set range for analog switch
		void set_output_range(int);
		void invert_switch(bool);           // method that sets this switch to inverted mode, where 1024 equals 0
        bool available();                   // redefine the avaiable method
};

#endif