#include "SwitchDigitalRgbMatrix.h"

/**
 * SwitchDigitalRgbMatrix::SwitchDigitalRgbMatrix Constructor that initializes an instance 
 *     of this class
 * @params _pin Pin number where the switch is connected
 */
SwitchDigitalRgbMatrix::SwitchDigitalRgbMatrix(int _input_pin) : SwitchDigitalRgb(_input_pin) {
    max_bright = LED_MAX_BRIGHT_MATRIX;
}

/**
 * SwitchDigitalRgbMatrix::SwitchDigitalRgbMatrix Constructor that initializes an instance of 
 *     this class
 * @params _pin Pin number where the switch is connected
 * @params _states Number of states that this switch supports
 */
SwitchDigitalRgbMatrix::SwitchDigitalRgbMatrix(int _input_pin, int _states) : SwitchDigitalRgb(_input_pin, _states) {
    max_bright = LED_MAX_BRIGHT_MATRIX;
}


/**
 * SwitchDigitalRgbMatrix::set_led_pins Set the rgb led pins, including the  
 * @param _LED_pin Shared pin for these three leds 
 * @param _R_pin Red led pin number
 * @param _G_pin Green led pin number
 * @param _B_pin Blue led pin number
 */
void SwitchDigitalRgbMatrix::set_led_pins(int _LED_pin, int _R_pin, int _G_pin, int _B_pin) {
    led_on = true;
    led_available = true;
    
    led_button_pin = _LED_pin;
    led_pins[R] = _R_pin; 
    led_pins[G] = _G_pin;
    led_pins[B] = _B_pin;

    pinMode(led_button_pin, OUTPUT);
    pinMode(led_pins[R], OUTPUT);
    pinMode(led_pins[G], OUTPUT);
    pinMode(led_pins[B], OUTPUT);
}

/**
 * SwitchDigitalRgbMatrix::update_leds Updates the RGB states based on the current state
 */
void SwitchDigitalRgbMatrix::update_leds() {  
    if(led_available) {
        if (led_on) {
            digitalWrite(led_pins[R], current_led_state[R]);
            digitalWrite(led_pins[G], current_led_state[G]);
            digitalWrite(led_pins[B], current_led_state[B]);
            digitalWrite(led_button_pin, LOW); 
            delayMicroseconds(30);
            digitalWrite(led_button_pin, HIGH); 
        } 
        else {
            digitalWrite(led_pins[R], LOW);
            digitalWrite(led_pins[G], LOW);
            digitalWrite(led_pins[B], LOW);
            digitalWrite(led_button_pin, LOW); 
            delayMicroseconds(30);
            digitalWrite(led_button_pin, HIGH); 
        }
    }
}



