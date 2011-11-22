/*
 AMUP Input Element Libraries, RGB Button Matrix
 Created by Julio Terra, June 4, 2011.
 
 This is the RGB Button Matrix library from the AMUP Input Element set. This is the
 library that handles RGB buttons that use a matrix for controlling the leds. 
 
 Hierarchy:
 - Parents: RGBButton, Switch, InputElement
 - Children: n/a 
 
 File name: RGBButtonMatrix.h
 
 */

#ifndef RGBButtonMatrix_h
#define RGBButtonMatrix_h

#include "WProgram.h"
#include "AMUPconfig.h"
#include "RGBButton.h"

class RGBButtonMatrix: public RGBButton {    
    public:    
        int led_button_pin;                     // holds the voltage pin that is attached to this led on the matrix 
        RGBButtonMatrix(int, int, int);         // constructor
        void set_led_pins(int, int, int, int);  // redefine set led pins method
        void update_leds();                     // redefine updated eleds method
};

#endif