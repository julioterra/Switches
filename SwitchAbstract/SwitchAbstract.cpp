#include "SwitchAbstract.h"

// CONSTRUCTOR: initializes an instance of the input element class
// PARAMS: an id number and input pin for each instance of an input element
SwitchAbstract::SwitchAbstract(int _ID, int _pin) {
    ID = _ID;
    pin = _pin;  
    pinMode(pin, INPUT);
    new_state = false;
    current_state = LOW;
    output_state = LOW;
}

// GET_STATE: returns the current state of the switch and sets new_state flag to false
// RETURN: current state
float SwitchAbstract::get_state() {
    new_state = false;
    return output_state;
}
// GET_STATE: returns the current state of the switch and prints the state to serial monitor
// RETURN: current state
float SwitchAbstract::get_print_state() {
    Serial.println(int(output_state));
    return get_state();
}

// GET_STATE: returns the current state of the switch and prints the state to serial monitor
// RETURN: current state
float SwitchAbstract::get_print_byte_state() {
    Serial.print(byte(int(output_state)));
    return get_state();
}