#include "SwitchAbstract.h"


/**
 * SwitchAbstract::SwitchAbstract Constructor that initializes an instance of the abstract
 *     switch class
 * @params _pin The pin number where the switch is connected
 */
SwitchAbstract::SwitchAbstract(int _pin) {
    pin = _pin;  
    pinMode(pin, INPUT);
    new_state = false;
    current_state = LOW;
    output_state = LOW;
}

/**
 * SwitchAbstract::get_state Returns the current state of the switch and sets new_state flag to false
 * @return current State of the switch
 */
int SwitchAbstract::get_state() {
    new_state = false;
    return output_state;
}

/**
 * SwitchAbstract::get_print_state returns the current state of the switch and prints the state 
 *     to serial monitor
 * @return current state
 */
int SwitchAbstract::get_print_state() {
    Serial.println(int(output_state));
    return get_state();
}

/**
 * SwitchAbstract::get_print_byte_state returns the current state of the switch and prints the state 
 *     to serial monitor
 * @return current state
 */
int SwitchAbstract::get_print_byte_state() {
    Serial.print(byte(int(output_state)));
    return get_state();
}

/**
 * SwitchAbstract::set_output_range sets the maximun value of the output range. The min value is always
 *     set to 0.
 * @param _output_range Maximum value for the output range
 */
void SwitchAbstract::set_output_range(int _output_range) {
    output_range = _output_range;
}
