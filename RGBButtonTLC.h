/*
 AMUP Input Element Libraries, RGB Button TLC
 Created by Julio Terra, June 4, 2011.
 
 This is the RGB Button TLC library from the AMUP Input Element set. This is the
 library that handles RGB buttons that use a TLC5940 to control the leds. 
 
 Hierarchy:
 - Parents: RGBButton, Switch, InputElement
 - Children: n/a 
 
 File name: RGBButtonTLC.h
 
 */

#ifndef RGBButtonTLC_h
#define RGBButtonTLC_h

#include "WProgram.h"
#include "RGBButton.h"
#include "AMUPconfig.h"
    
class RGBButtonTLC: public RGBButton {    
    public:    
        RGBButtonTLC(int, int, int);            // constructor
        void set_led_pins(int, int, int);       // redefine set led pins method
        void update_leds();                     // redefine updated eleds method
};

#endif