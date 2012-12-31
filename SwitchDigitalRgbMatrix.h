/* 
 *  Digital RGB Matrix Switch Class :: Arduino Switch Library.
 * 
 *  This RGB matrix switch library creates buttons with multiple states, that use an rgb 
 *  led as a source of feedback. Buttons can be set with a variable number of states, and
 *  each state can be mapped to a different rgb color.  
 *
 *  This implementation of RGB digital switches library designed to work with leds that are 
 *  hooked-up in a matrix configuration. There are some limitations that should be considered
 *  when deciding to use an led matrix:
 * 	1. The number of colors supported is limited because PWM does not work well 
 * 	   with a LED matrix approach. You need to set R, G, B color on or off.
 * 	2. The leds flicker when the switches are pressed since the Arduino is not
 * 	   fast enough to handle input and manage the lights simultaneously.
 * 	   
 *  Class Hierarchy 
 *  - Parents Classes: SwitchAbstract, SwitchDigital, SwitchDigitalRgb
 *  - Child Classes: n/a 
 *   
 *  @filename SwitchDigitalRgbMatrix.h 
 *  @version 1.0.0
 *  @author Julio Terra
 *  @date 12/29/12
 * 
 */

#ifndef __SwitchDigitalRgbMatrix_h__
#define __SwitchDigitalRgbMatrix_h__

#include "./SwitchDigitalRgb.h"

class SwitchDigitalRgbMatrix: public SwitchDigitalRgb {    
    public:    
        int led_button_pin;						// holds the voltage pin that is attached to this led on the matrix 
        SwitchDigitalRgbMatrix(int, int);		// constructor
        SwitchDigitalRgbMatrix(int);			// constructor
        void set_led_pins(int, int, int, int);	// redefine set led pins method
        void update_leds();                     // redefine updated eleds method
};

#endif