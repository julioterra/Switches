/*
 SwitchAnalog Library
	By Julio Terra. Updated on November 21, 2011. Created on June 4, 2011.

	This library handles analog switches such as potentiometers and any other
	input elements that provide analog data.
 
 Hierarchy:
 - Parents: AbstractSwitch
 - Children: n/a
 
 File name: SwitchAnalog.h 
 
 */

#ifndef __SwitchAnalog_h__
#define __SwitchAnalog_h__

#include "../SwitchAbstract/SwitchAbstract.h"

class SwitchAnalog: public SwitchAbstract {
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

        SwitchAnalog(int, int);             // constructor
        void set_analog_range(int, int);    // set range for analog switch
		void set_output_range(int);
		void invert_switch(bool);           // method that sets this switch to inverted mode, where 1024 equals 0
        bool available();                   // redefine the avaiable method
};

#endif