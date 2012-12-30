/*
 SwitchEncoder Library
	By Julio Terra. Updated on November 21, 2011. Created on June 4, 2011.
 
	This library handles rotary encoder switches. Rotary encoders supported by
	this library feature two separate leads/pins. The first lead should be 
	attached a pin with interrupt functionality. 
 
 Hierarchy:
 - Parents: SwitchAbstract
 - Children: n/a 
 
 File name: SwitchEncoder.h
 
 */

#ifndef __SwitchEncoder_h__
#define __SwitchEncoder_h__

#include "utility/SwitchAbstract.h"

class SwitchEncoder: public SwitchAbstract {
    private: 
        int pin_b;                      // holds the second pin for the rotary encoder
        int interrupt_pin;              // holds the interrupt pin number associated to encoder pin A
        
    public:
        int direction;                  // holds encoder direction (which way is +1 and -1) 
        volatile int encoderPos;        // holds current encoder position
    
        SwitchEncoder(int, int);        // constructor, accepts an ID and number for encoder pins A and B
        int get_interrupt_pin();        // returns the appropriate interrupt pin number for pin_a of the encoder
        void set_direction(int);        // set direction of encoder based on whether number is greater or lesser than 0
        void event();                   // method to be called in the appropriate Arduino interrupt callback method 
        bool available();               // returns whether the state of the encoder has changed
};

#endif