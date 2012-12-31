#include "SwitchEncoder.h"

/**
 * SwitchEncoder::SwitchEncoder Constructor that initializes an instance 
 *     of this class
 * @params _pin_a Pin number where first lead will be connected (pin_a). For best performance this
 *         pin should be an Arduino interrupt pin.
 * @params _pin_b Pin number where second lead will be connected (pin_b).
 */
SwitchEncoder::SwitchEncoder(int _pin_a, int _pin_b) : SwitchAbstract(_pin_a) {
    // set pin numbers and pullup resistors (pin A set in parent class constructor)
    pin_b = _pin_b;
    pinMode(pin_b, INPUT);          // set pin mode to input
    digitalWrite(pin, HIGH);        // turn on pullup resistor
    digitalWrite(pin_b, HIGH);      // turn on pullup resistor

    // initialize variables
    encoderPos = 0;                 
    new_state = false;
    direction = 1;
    
    // set interrupt pin number
    if (pin == 2) interrupt_pin = 0;
    else if (pin == 3) interrupt_pin = 1;
    else if (pin == 18) interrupt_pin = 5;
    else if (pin == 19) interrupt_pin = 4;
    else if (pin == 20) interrupt_pin = 3;
    else if (pin == 21) interrupt_pin = 2;
    else interrupt_pin -1;
}

/**
 * SwitchEncoder::get_interrupt_pin Returns the interrupt pin number that corresponds to 
 *     encoder pin_a. If pin_a is not an interrupt pin then it will return -1 
 * @return Interrupt pin number corresponding to encoder pin_a
 */
int SwitchEncoder::get_interrupt_pin() {
    return interrupt_pin;
}

/**
 * SwitchEncoder::invert_switch Inverts the rotary encoder so that the direction that increments
 *     and decrements the switch's state are reversed. 
 * @param _onState When true it inverts the rotary encoder direction, when false the direction is
 *                 set back to default.
 */

void SwitchEncoder::invert(bool _onState) {
    SwitchAbstract::invert(_onState);
    if (is_inverted) direction = -1;
    else direction = 1;
}

/**
 * SwitchEncoder::event Reads both encoder pins to determine direction of movement, and
 *     then increments the encoderPos variable. Sets the new_state flag to true.
 */
void SwitchEncoder::event() {
    if (digitalRead(pin) == digitalRead(pin_b)) encoderPos = 1 * direction;
    else encoderPos = -1 * direction;
    new_state = true;    
}

/**
 * SwitchEncoder::available Updates the current_state variable using the encoderPos variable, 
 *     if the new_state flag is set to true. 
 * @return Returns true if new data is available, false if no new data is available 
 */
bool SwitchEncoder::available(){
    if (new_state) {
        current_state = encoderPos;
        output_state += current_state;
        output_state = abs(output_state % output_range);
        encoderPos = 0;         
    }
    return new_state;     
}