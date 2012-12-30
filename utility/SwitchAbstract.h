/* 
 *  Abstract Switch Class :: Arduino Switch Library.
 * 
 *  This is the abstract parent class for all switch library classes. It defines 
 *  some of the base attributes and methods of all switch classes.
 * 
 *  Class Hierarchy 
 *  - Parents: n/a
 *  - Children: Switch [RGBButton, RGBButtonMatrix, RGBButtonTLC],
 *              AnalogSwitch, RotaryEncoder, AirSensor
 *
 *  @filename SwitchAbstract.h 
 *  @version 1.0.0
 *  @author Julio Terra
 *  @date 12/29/12
 * 
 */

#ifndef __SwitchAbstract_h__
#define __SwitchAbstract_h__

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
  #else
  #include "WProgram.h"
#endif

#include "./SwitchesConfig.h"

class SwitchAbstract {
  public:
    int pin;                    // holds the arduino pin from where the input will be read

    bool new_state;             // set to true when state changes, until get_state called
    int current_state;          // holds the current momentary state of the switch
    int output_state;           // holds the current output steate of the switch
    int output_range;

    SwitchAbstract(int);         // initializes all variables
    virtual bool available() {};    // placeholder function that checks whether the switch's state has changed
    virtual void invert_switch(bool) {};
    virtual void set_analog_range(int, int) {};
    void set_output_range(int);
    int get_state();              // function that returns current_state and resets new_state flag
    int get_print_state();        // same as get_state function but also prints current_state to serial port
    int get_print_byte_state();   // same as get_print_state function but prints state as a byte value
};

#endif