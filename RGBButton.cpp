#include "RGBButton.h"

// CONSTRUCTOR: initializes an instance of the switch class
// PARAMS: an id number for the switch and the input pin number
RGBButton::RGBButton(int _ID, int _input_pin, int _states) : Switch(_ID, _input_pin) {
    toggle_states = _states;
    is_momentary = false;
    
    led_available = false;
    led_on = false;
    led_midi_control = false;
    
    for (int j = 0; j < RGB_COUNT; j++) current_led_state[j] = 0;
    for (int i = 0; i < TOGGLE_MAX; i++) 
        for (int j = 0; j < RGB_COUNT; j++) led_digital_states[i][j] = 0;
}

// SET LED STATE: sets the R, G, B values of a button state
// PARAMS: a state number, and an R, G, and B value
bool RGBButton::set_led_state(int _state, int _R, int _G, int _B) {
    if (_state >= TOGGLE_MAX || _state < 0 || !led_available) return false;

    led_digital_states[_state][R] = constrain(_R, 0, max_bright);
    led_digital_states[_state][G] = constrain(_G, 0, max_bright);
    led_digital_states[_state][B] = constrain(_B, 0, max_bright);
    
    if (_state == 0) {
        if (current_led_state[R] != 0 || current_led_state[G] != 0 || current_led_state[B] != 0)
            current_led_state[R] = led_digital_states[_state][R];
            current_led_state[G] = led_digital_states[_state][G];
            current_led_state[B] = led_digital_states[_state][B];
    }
    return true;
}

void RGBButton::set_midi_control(bool _midi_in_control) {
    if (_midi_in_control) led_midi_control = true;
    else led_midi_control = false;
    
}

// AVAILABLE: method that reads button and determines if state has changed (new data available
// RETURNS: true if state has changed, false if state has not changed
bool RGBButton::available() {    
//	if (!led_midi_control) update_leds();
	update_leds();
    if(Switch::available()) {
        if (led_midi_control) {
			output_state = current_state;
            return true; 
		}
		else if (is_momentary) {
			set_current_led_state(current_state);
            return true; 
        }

        else if (current_state > LOW) {
            new_state = true;
            output_state++;
            if (output_state >= toggle_states) output_state = 0;
            set_current_led_state(output_state);
            return true;
        }
        else new_state = false;
    } 
    else return false;
}

// AVAILABLE: method that reads button and determines if state has changed (new data available
// RETURNS: true if state has changed, false if state has not changed
void RGBButton::set_current_led_state(int _state) {
    current_led_state[R] = led_digital_states[_state][R];
    current_led_state[G] = led_digital_states[_state][G];
    current_led_state[B] = led_digital_states[_state][B];
    update_leds();
}


// TURN ON LEDS: turns on the leds by setting the led_on to true
// NOTE: if the leds are off on the current button state, then this will not make the lights turn on
void RGBButton::turn_on_leds() {
    led_on = true;
}

// TURN ON LEDS: turns on the leds using the specified R, G, and B values
// PARAMS: R, G, and B values
void RGBButton::turn_on_leds(int _R, int _G, int _B) {
    current_led_state[R] = constrain(_R, 0, max_bright);
    current_led_state[G] = constrain(_G, 0, max_bright);
    current_led_state[B] = constrain(_B, 0, max_bright);
    turn_on_leds();
}

// TURN OFF LEDS: turns of the leds by setting the led_on to false
void RGBButton::turn_off_leds() {
    led_on = false;
}

// MOMENTARY BUTTON: methods sets the button to either momentary or not
// PARAMS: if input set to true then switch set to momentary
void RGBButton::momentary_button (bool _is_momentary){
    is_momentary = _is_momentary;
}


