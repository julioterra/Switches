/*
 Input Element, Abstract Class for the AMUP Input Element Libraries Set.
 Created by Julio Terra, June 4, 2011.
 
 This is the abstract parent class for all AMUP input element libraries. It 
 holds the design pattern for all subclasses including the use of a available() 
 and get_state() methods, new_state flags, and current_state and output_state 
 variables. 
 
 Hierarchy:
 - Parents: n/a
 - Children: Switch [RGBButton, RGBButtonMatrix, RGBButtonTLC],
             AnalogSwitch, RotaryEncoder, AirSensor
 
 File name: SwitchAbstract.h 
 
 */

#ifndef __SwitchAbstract_h__
#define __SwitchAbstract_h__

#include "WProgram.h"
#include "./SwitchesConfig.h"

class SwitchAbstract {
    public:
        // pin variables
        int ID;                         // holds the id number for this input    
        int pin;                        // holds the arduino pin from where the input will be read

        bool new_state;                 // set to true when state changes, until get_state called
        int current_state;            // holds the current momentary state of the switch
        int output_state;             // holds the current output steate of the switch

        SwitchAbstract(int, int);         // initializes all variables
        virtual bool available() {};    // placeholder function that checks whether the switch's state has changed
        virtual void invert_switch(bool) {};
        virtual void set_analog_range(int, int) {};
        virtual void set_output_range(int) {};
        int get_state();              // function that returns current_state and resets new_state flag
        int get_print_state();        // same as get_state function but also prints current_state to serial port
        int get_print_byte_state();   // same as get_print_state function but prints state as a byte value
};

#endif