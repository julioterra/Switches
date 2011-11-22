#include "Switch.h"

// CONSTRUCTOR: initializes an instance of the switch class
// PARAMS: an id number for the switch and the input pin number
Switch::Switch(int _ID, int _pin) : InputElement(_ID, _pin) {
    new_state = false;
    current_state = 0;
    last_reading = 0;
    reading_debounce_time = 0;
    is_inverted = false;
    is_momentary = true;

}

// INVERT SWITCH: inverts this switch object, and turns on the pullup resistor
// NOTE: if you are using a mux then you need to make sure that all switches are
//       set up with the same as inverted, or not.
void Switch::invert_switch(bool _onState) {
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
bool Switch::available() {
    int new_reading = digitalRead(pin);
    
    // if switch is inverted (pullup), then reverse the reading
    if (is_inverted) {
        if (new_reading == LOW) new_reading = HIGH;
        else new_reading = LOW;        
    }

    // if the current reading is difference than the last one then 
    if (new_reading != last_reading) reading_debounce_time = millis();
    
    // if the debounce interval has passed and the current state is different then the new reading
    if ((millis() - reading_debounce_time) > DIGITAL_SWITCH_DEBOUNCE) {
        if (new_reading != current_state) {
            // update the switch state and appropriate variables.
            new_state = true;
            current_state = new_reading;   
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


/*
 bool Switch::available() {
    current_state = digitalRead(pin);
    
    if (is_inverted) {
        if (current_state == LOW) current_state = HIGH;
        else current_state = LOW;        
    }
    
    if (current_state == last_reading) last_read_last_reading = millis();
    else if (current_state != last_reading) {
        if(((millis() - last_state_switch) > DIGITAL_SWITCH_DEBOUNCE) || ((millis() - last_read_previous_state) > DIGITAL_PREVIOUS_DEBOUNCE)) {
            new_state = true;
            last_state_switch = millis();
            last_reading = current_state;
            if (is_momentary) output_state = current_state;
            
            return true;   
        }
    }
    return false;
}
 */


