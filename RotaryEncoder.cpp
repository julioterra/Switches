#include "RotaryEncoder.h"

// CONSTRUCTOR: initializes an instance of the Rotary Encoder class
// PARAMETERS: switch ID number, pin a and pin b numbers.
RotaryEncoder::RotaryEncoder(int _ID, int _pin_a, int _pin_b) : InputElement(_ID, _pin_a) {
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

// GET INTERRUPT PIN: returns the interrupt pin associated to encoder pin A
// RETURN: interrupt pin number
int RotaryEncoder::get_interrupt_pin() {
    return interrupt_pin;
}

// SET DIRECTION: accepts a parameter that sets which direction returns 1s and -1s
// PARAMETERS: if the integer is greater then 0 one direction, if lesser than 0 it goes the other 
void RotaryEncoder::set_direction(int _direction) {
    if (_direction < 0) direction = -1;
    else direction = 1;
}

// EVENT: reads both current pins to determine direction of movement
void RotaryEncoder::event() {
    if (digitalRead(pin) == digitalRead(pin_b)) encoderPos = 1 * direction;
    else encoderPos = -1 * direction;
    new_state = true;    
}

// AVAILABLE: checks if the switch state has changed, and if so assigns it to current_state
// RETURN: returns whether the switch's state has changed
bool RotaryEncoder::available(){
    if (new_state) {
        current_state = encoderPos;
        output_state += current_state;
        if (output_state < 0) output_state = 127;
        else if (output_state > 127) output_state = 0;
        encoderPos = 0;         
    }
    return new_state;     
}