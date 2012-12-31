/* 
 *  Analog Switch Class :: Arduino Switch Library.
 * 
 *  This is the analog switch class that handles variable resistors, such as 
 *  potentiometers, photoresistors, flex sensors, etc. It features smoothing 
 *  functionality that helps to filter out noise from readings. 
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
    private:
        // range and averaging variables
        #define OUTPUT_RANGE            1024     
        #define AVG_READINGS            10
        #define STATE_CHANGE_THRESH     8

        // variables that manage switch state
        int last_reading;           // holds the current momentary state of the switch (on, off, or analog number)

        // variables that define and manage analog input range
        int range_min;              // holds the bottom of the range of an analog sensor
        int range_max;              // holds the top of the range of an analog sensor
        int range;                  // holds the size of the range of an analog sensor

    public:
        SwitchAnalog(int);             // constructor
        void set_analog_range(int, int);    // set range for analog switch
        bool available();                   // redefine the avaiable method
};

#endif