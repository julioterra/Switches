/* 
 *  Rotary Encoder Class :: Arduino Switch Library.
 *
 *  This library handles 2-pin rotary encoder switches. The rotary encoder returns an 
 *      integer value within the ouput range. As the rotary encoder spins to either
 *      side the value is incremented or decremented
 *     
 *  Class Hierarchy 
 *  - Parents: SwitchAbstract
 *  - Children: n/a 
 *   
 *  @filename SwitchEncoder.h 
 *  @version 1.0.0
 *  @author Julio Terra
 *  @date 12/29/12
 * 
 */

#ifndef __SwitchEncoder_h__
#define __SwitchEncoder_h__

#include "utility/SwitchAbstract.h"

class SwitchEncoder: public SwitchAbstract {
    private: 
        int pin_b;                      // holds the second pin for the rotary encoder
        int interrupt_pin;              // holds the interrupt pin number associated to encoder pin A
        int direction;                  // holds encoder direction (which way is +1 and -1) 
        volatile int encoderPos;        // holds current encoder position
        
    public:    
        SwitchEncoder(int, int);        // constructor, accepts an ID and number for encoder pins A and B
        int get_interrupt_pin();        // returns the appropriate interrupt pin number for pin_a of the encoder
        void invert(bool);       // method that sets this switch to inverted mode, with pullup resistor
        void event();                   // method to be called in the appropriate Arduino interrupt callback method 
        bool available();               // returns whether the state of the encoder has changed
};

#endif