/*
 AMUP Input Element Libraries: Rotary Encoder
 Created by Julio Terra, June 4, 2011.
 
 This is the rotary encoder library from the AMUP Input Element set. This library 
 handles rotary encoder switches. Rotary encoders feature two separate leads. The
 first lead should be attached a pin with interrupt functionality. 
 
 Hierarchy:
 - Parents: Input Element
 - Children: n/a 
 
 File name: RotaryEncoder.h
 
 */

#ifndef RotaryEncoder_h
#define RotaryEncoder_h

#include "WProgram.h"
#include "AMUPconfig.h"
#include "utility/InputElement.h"

class RotaryEncoder: public InputElement {
    private: 
        int pin_b;                      // holds the second pin for the rotary encoder
        int interrupt_pin;              // holds the interrupt pin number associated to encoder pin A
        
    public:
        int direction;                  // holds encoder direction (which way is +1 and -1) 
        volatile int encoderPos;        // holds current encoder position
    
        RotaryEncoder(int, int, int);   // constructor, accepts an ID and number for encoder pins A and B
        int get_interrupt_pin();        // returns the appropriate interrupt pin number for pin_a of the encoder
        void set_direction(int);        // set direction of encoder based on whether number is greater or lesser than 0
        void event();                   // method to be called in the appropriate Arduino interrupt callback method 
        bool available();               // returns whether the state of the encoder has changed
};

#endif