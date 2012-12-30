/* 
 *  Analog Switch Class :: Arduino Switch Library.
 * 
 *  This is the analog switch class for variable resistors, such as potentiometers
 *  and photoresistors. It features smoothing functionality that helps to filter out
 *  noise from readings. 
 * 
 *  Class Hierarchy 
 *  - Parents: AbstractSwitch
 *  - Children: n/a
 *
 *  @filename SwitchAnalog.h 
 *  @version 1.0.0
 *  @author Julio Terra
 *  @date 12/29/12
 * 
 */

#ifndef __SwitchAnalog_h__
#define __SwitchAnalog_h__

#include "utility/SwitchAbstract.h"

class SwitchAnalog: public SwitchAbstract {
    public:
        // range and averaging variables
        #define OUTPUT_RANGE            1024     
        #define AVG_READINGS            10
        #define STATE_CHANGE_THRESH     8

        // variables that manage switch state
        int last_reading;           // holds the current momentary state of the switch (on, off, or analog number)
		bool is_inverted;           // holds whether the switch is inverted (uses a pullup resistor)

        // variables that define and manage analog input range
        int range_min;              // holds the bottom of the range of an analog sensor
        int range_max;              // holds the top of the range of an analog sensor
        int range;                  // holds the size of the range of an analog sensor
		// int output_range;

        SwitchAnalog(int);             // constructor
        void set_analog_range(int, int);    // set range for analog switch
		void invert_switch(bool);           // method that sets this switch to inverted mode, where 1024 equals 0
        bool available();                   // redefine the avaiable method
};

#endif