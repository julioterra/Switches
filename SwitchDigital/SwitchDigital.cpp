#include "SwitchDigital.h"

// CONSTRUCTOR: initializes an instance of the switch class
// PARAMS: an id number for the switch and the input pin number
SwitchDigital::SwitchDigital(int _ID, int _pin) : SwitchAbstract(_ID, _pin) {
    reading_debounce_time = 0;
    is_inverted = false;
    is_momentary = true;
}

// INVERT SWITCH: inverts this switch object, and turns on the pullup resistor
// NOTE: if you are using a mux then you need to make sure that all switches have
//       the same setup.
void SwitchDigital::invert_switch(bool _onState) {
    if (_onState) { 
        is_inverted = true;    
        digitalWrite(pin, HIGH);
    }
    
    else {
        is_inverted = false;   
        digitalWrite(pin, LOW);
    }    
}

// AVAILBLE: reads switch pin, debounces reading, and determines if state has changed
// RETURNS: true if switch state has changed, false if state has not changed
// NOTE: if reading from mux, you need to set the control pins before calling this method
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