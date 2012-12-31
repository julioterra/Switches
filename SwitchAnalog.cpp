#include "SwitchAnalog.h"

/**
 * SwitchAnalog::SwitchAnalog Constructor that initializes an instance of this class
 * @param _pin The pin number where the switch is connected
 */
SwitchAnalog::SwitchAnalog(int _pin) : SwitchAbstract(_pin) {
    last_reading = 0;
    range_min = 0;
    range_max = 1023;
    range = range_max - range_min;
	output_range = OUTPUT_RANGE;
}

/**
 * SwitchAnalog::set_analog_range sets a custom sensor range for the current instance of the 
 *     switch. Standard range is from 0 to 1023.
 * @param _min the minimum values of the analog range
 * @param _max the max values of the analog range
 */
void SwitchAnalog::set_analog_range(int _min, int _max) {
    range_min = _min;      
    range_max = _max;   
    range = range_max - range_min;      
}

/**
 * SwitchAnalog::available Reads switch pin and determines if state has changed. Performs
 *     smoothing functions to stabilize the switch readings.
 * @return true if switch state has changed, false if state has not changed
 */
bool SwitchAnalog::available() {
    long currentTime = millis();    
    int raw_state = analogRead(pin);

	// if switch is inverted (pullup), then reverse the reading
    if (is_inverted) {
        raw_state = 1023 - raw_state;        
    }	
	
    // calculate a running average
    current_state = ((current_state * (AVG_READINGS -1)) + raw_state)/AVG_READINGS;

    // check if the sensor readings have exceeded a threshold
    if (current_state > (last_reading + STATE_CHANGE_THRESH) || current_state < (last_reading - STATE_CHANGE_THRESH)) {
        new_state = true;
        last_reading = current_state;
		if (current_state <= 5) current_state = 0;
        if (range == output_range) output_state = current_state;
        else output_state = int(float(float((current_state) - range_min)/float(range)) * float(output_range));
        return true;   
    }
    return false;
}