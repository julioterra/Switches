#include "SwitchDigital.h"

/**
 * SwitchDigital::SwitchDigital Constructor that initializes an instance of this class
 * @params _pin The pin number where the switch is connected
 */
SwitchDigital::SwitchDigital(int _pin) : SwitchAbstract(_pin) {
    reading_debounce_time = 0;
    is_inverted = false;
    is_momentary = true;
    toggle_states = 2;
}

/**
 * SwitchDigital::invert_switch inverts this switch object, and turns on the pullup resistor.
 * @param _onState When true it inverts this switch object, when false it stops inversing the object
 */
void SwitchDigital::invert(bool _onState) {
    SwitchAbstract::invert(_onState);
    if (is_inverted) digitalWrite(pin, HIGH);
    else digitalWrite(pin, LOW);
}

/**
 * SwitchDigital::momentary_button Sets the switch to function as a momentary switch or a
 *     state-based button. By default buttons are set as momentary switches. 
 * @param _is_momentary Boolean value that sets the button to momentary mode when set to true
 */
void SwitchDigital::momentary (bool _is_momentary){
    is_momentary = _is_momentary;
}

/**
 * SwitchDigital::available Reads switch pin, debounces reading, and determines if state has changed
 * @return True if switch state has changed, false if state has not changed
 */
bool SwitchDigital::available() {
    int new_reading = digitalRead(pin);
    
    // if switch is inverted (pullup), then reverse the reading
    if (is_inverted) {
        if (new_reading == LOW) new_reading = HIGH;
        else new_reading = LOW;        
    }

    // if the current reading is difference than the last one then 
    if (new_reading != last_reading) reading_debounce_time = millis();
    
	// if the debounce interval has passed and the current state is different then the new reading
	// then update the switch's state, and the new state flag.
    if ((millis() - reading_debounce_time) > DIGITAL_SWITCH_DEBOUNCE) {
        if (new_reading != current_state) {
            new_state = true;
            current_state = new_reading;   

			// if switch is momentary then set output state to current state
            if (is_momentary) output_state = current_state; 
            else if (current_state > LOW) output_state = (output_state + 1) % toggle_states;

        }
    }    
    
    // save new_reading as last_reading for next loop
    last_reading = new_reading;
    
    // return true if state has changed, and false if state did not change
    if (new_state) {
        return true;
        new_state = false;
    }
    return false;
}