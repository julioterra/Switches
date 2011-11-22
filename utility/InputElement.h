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
 
 File name: InputElement.h 
 
 */

#ifndef InputElement_h
#define InputElement_h

#include "WProgram.h"
#include "AMUPconfig.h"

class InputElement {
    public:
        // pin variables
        int ID;                         // holds the id number for this input    
        int pin;                        // holds the arduino pin from where the input will be read

        bool new_state;                 // set to true when state changes, until get_state called
        float current_state;            // holds the current momentary state of the switch
        float output_state;             // holds the current output steate of the switch

        InputElement(int, int);         // initializes all variables
        virtual bool available() {};    // placeholder function that checks whether the switch's state has changed
        virtual void invert_switch(bool) {};
        virtual void set_analog_range(int, int) {};
        virtual void set_output_range(int) {};
        float get_state();              // function that returns current_state and resets new_state flag
        float get_print_state();        // same as get_state function but also prints current_state to serial port
        float get_print_byte_state();   // same as get_state function but also prints current_state to serial port
};

#endif