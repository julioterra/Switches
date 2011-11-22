#include "RGBButtonTLC.h"

// CONSTRUCTOR: initializes an instance of the switch class
// PARAMS: an id number for the switch and the input pin number and number of states
RGBButtonTLC::RGBButtonTLC(int _ID, int _input_pin, int _states) : RGBButton(_ID, _input_pin, _states) {
    max_bright = LED_MAX_BRIGHT_TLC;
}

void RGBButtonTLC::set_led_pins(int _R, int _G, int _B) {    
    led_pins[R] = _R;
    led_pins[G] = _G;
    led_pins[B] = _B;
    led_available = true;
    led_on = true;
}

// UPDATE LEDS: updates the state of the LEDs for this switch, based on the state of the switch
// PARAMS & RETURNS: N/A
void RGBButtonTLC::update_leds() {
    if(led_available) {
        if (led_on) {
            Tlc.set(led_pins[R], current_led_state[R]);
            Tlc.set(led_pins[G], current_led_state[G]);
            Tlc.set(led_pins[B], current_led_state[B]);
        } 
        else {
            Tlc.set(led_pins[R], LOW);
            Tlc.set(led_pins[G], LOW);
            Tlc.set(led_pins[B], LOW);
        }
    }
}
