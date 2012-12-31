#include "SwitchDigitalRgb.h"

/**
 * SwitchDigitalRgb::SwitchDigitalRgb Constructor that initializes an instance of this class
 * @params _pin Pin number where the switch is connected
 * @params _states Number of states that this switch supports
 */
SwitchDigitalRgb::SwitchDigitalRgb(int _pin, int _states) : SwitchDigital(_pin) {
    toggle_states = _states;
    is_momentary = false;
    max_bright = 255;
    
    led_available = false;
    led_on = true;
    led_midi_control = false;
    
    for (int j = 0; j < RGB_COUNT; j++) current_led_state[j] = 0;
    for (int i = 0; i < STATE_MAX; i++) 
        for (int j = 0; j < RGB_COUNT; j++) led_digital_states[i][j] = 0;
}

/**
 * SwitchDigitalRgb::SwitchDigitalRgb Constructor that initializes an instance of this class
 * @params _pin Pin number where the switch is connected
 */
SwitchDigitalRgb::SwitchDigitalRgb(int _input_pin) : SwitchDigital(_input_pin) {
    toggle_states = 2;
    is_momentary = false;
    max_bright = 255;
    
    led_available = false;
    led_on = false;
    led_midi_control = false;
    
    for (int j = 0; j < RGB_COUNT; j++) current_led_state[j] = 0;
    for (int i = 0; i < STATE_MAX; i++) 
        for (int j = 0; j < RGB_COUNT; j++) led_digital_states[i][j] = 0;
}

/**
 * SwitchDigitalRgb::set_number_of_states sets number of states for this RGB switch
 * @param _states Number of states that this switch supports
 */
void SwitchDigitalRgb::set_number_of_states(int _states) {
	toggle_states = _states;
}

/**
 * SwitchDigitalRgb::set_led_state Sets the R, G, B values of a button state.
 * @param  _state Index number of state whose color is being set
 * @param  _R     Red color value
 * @param  _G     Green color value
 * @param  _B     Blue color value
 * @return  Returns true if the state index was valid and the colors were saved       
 */
bool SwitchDigitalRgb::set_led_state(int _state, int _R, int _G, int _B) {
    if (_state >= toggle_states || _state < 0) return false;

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

/**
 * SwitchDigitalRgb::available Reads button and determines if state has changed. Updates the button
 *     state when appropriate. Include debouncing algorithm.
 * @return True if new data is available to be read.
 */
bool SwitchDigitalRgb::available() {    
	update_leds();
    if(SwitchDigital::available()) {
		if (is_momentary) {
			set_current_led_state(output_state);
            return true; 
        }

        else if (current_state > LOW) {
            set_current_led_state(output_state);
            return true;
        }
        else new_state = false;
    } 
    else return false;
}

/**
 * SwitchDigitalRgb::set_current_led_state Update the color of the led array to the colors
 *     from the specified state.
 * @param _state Index number of the state that will be activated.
 */
void SwitchDigitalRgb::set_current_led_state(int _state) {
    if (_state >= toggle_states || _state < 0 || !led_available) return;
    current_led_state[R] = led_digital_states[_state][R];
    current_led_state[G] = led_digital_states[_state][G];
    current_led_state[B] = led_digital_states[_state][B];
    Serial.print("R ");
    Serial.print(current_led_state[R]);
    Serial.print(" G ");
    Serial.print(current_led_state[G]);
    Serial.print(" B ");
    Serial.print(current_led_state[B]);
    Serial.print(" _state ");
    Serial.println(_state);
    update_leds();
}

/**
 * SwitchDigitalRgb::turn_on_leds turns on the leds by setting the led_on to true. 
 *     If the leds are off on the current button state, then this will not make the 
 *     lights turn on.
 */
void SwitchDigitalRgb::turn_on_leds() {
    led_on = true;
}

/**
 * SwitchDigitalRgb::turn_on_leds Turns on led to a specific color, as specified
 *     by the _R, _G, and _B parameters.
 * @param _R Red value for the color
 * @param _G Green value for the color
 * @param _B Blue value for the color
 */
void SwitchDigitalRgb::turn_on_leds(int _R, int _G, int _B) {
    current_led_state[R] = constrain(_R, 0, max_bright);
    current_led_state[G] = constrain(_G, 0, max_bright);
    current_led_state[B] = constrain(_B, 0, max_bright);
    turn_on_leds();
}

/**
 * SwitchDigitalRgb::turn_off_leds Turns of the leds by setting the led_on to false
 */
void SwitchDigitalRgb::turn_off_leds() {
    led_on = false;
}

/**
 * SwitchDigitalRgb::set_led_pins Set the number of the rgb led pins 
 * @param _R_pin Red led pin number
 * @param _G_pin Green led pin number
 * @param _B_pin Blue led pin number
 */
void SwitchDigitalRgb::set_led_pins(int _R_pin, int _G_pin, int _B_pin) {
    led_on = true;
    led_available = true;
    
    led_pins[R] = _R_pin; 
    led_pins[G] = _G_pin;
    led_pins[B] = _B_pin;

    pinMode(led_pins[R], OUTPUT);
    pinMode(led_pins[G], OUTPUT);
    pinMode(led_pins[B], OUTPUT);
}

/**
 * SwitchDigitalRgb::update_leds Updates the RGB states based on a change in button state
 */
void SwitchDigitalRgb::update_leds() {  
    if(led_available) {
        if (led_on) {
            digitalWrite(led_pins[R], current_led_state[R]);
            digitalWrite(led_pins[G], current_led_state[G]);
            digitalWrite(led_pins[B], current_led_state[B]);
            delayMicroseconds(30);
        } 
        else {
            digitalWrite(led_pins[R], LOW);
            digitalWrite(led_pins[G], LOW);
            digitalWrite(led_pins[B], LOW);
            delayMicroseconds(30);
        }
    }
}


