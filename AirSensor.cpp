#include "AirSensor.h"

AirSensor::AirSensor(int _ID, int _pin) : InputElement(_ID, _pin) {
    pin = _pin;

    // hand status related variables
    hand_active = false;
    hand_state_change = false;
    hand_state = STOPPED;
    
    // data input related variables
    new_state = false;
    new_reading = 0;
    sensor_range = SENSOR_MAX - SENSOR_MIN;
    output_range = OUTPUT_MAX - OUTPUT_MIN;
    
    for (int i = 0; i < READINGS_ARRAY_SIZE; i++) raw_readings[i] = 0;
    for (int i = 0; i < PRE_READING_BUFFER_SIZE; i++) median_buffer[i] = -1;
    
    // gesture capture related variables
    gest_on_off_time = millis(); 
    gest_on = false;
    gest_off = false;
    gest_up_down_filter_center = 0;
    
    // intialize VOLUME related variables
    current_state = 0;
    
    
} // *** END CONSTRUCTOR *** //

void AirSensor::reset() {    
    for (int i = 0; i < READINGS_ARRAY_SIZE; i++) raw_readings[i] = -1;
    for (int i = 0; i < PRE_READING_BUFFER_SIZE; i++) median_buffer[i] = -1;
} 

// *** ADD NEW READING FUNCTION ***
// add new reading into the readings array
void AirSensor::add_new_reading() {
    int avgSum = 0;
    int validAvgReadings = 0;
    
    raw_reading = analogRead(pin);
    
    // ****** PREPARE BUFFER AND READING ARRAYS ****** //   
    // prepare to add new value to arrays - move values back in array by one position, starting at the end of the array and moving to the beginning
    for(int i = READINGS_ARRAY_SIZE-1; i > 0; i--) raw_readings[i] = raw_readings[i-1]; 
    for(int j = PRE_READING_BUFFER_SIZE-1; j > 0; j--) { median_buffer[j] = median_buffer[j-1]; }
    
    // ****** CHECK READING IS WITHIN RANGE AND MAP VALUE ACCORDINGLY ****** //   
    // adjust the value by checking if it is within acceptable range, and adjusting value
    if (raw_reading > SENSOR_MIN && raw_reading < SENSOR_MAX) { median_buffer[0] = sensor_range - (raw_reading - SENSOR_MIN); }
    else if (raw_reading < SENSOR_MIN) { median_buffer[0] = -1; }
    else if (raw_reading > SENSOR_MAX) { median_buffer[0] = -1; }
    
    // ****** RESORT THE ARRAY WITH THE NEW DATA READING ****** //   
    // array values are resorted from smallest to greatest and then 
    int reorderBuffer[PRE_READING_BUFFER_SIZE];
    for(int j = PRE_READING_BUFFER_SIZE-1; j > 0; j--) { reorderBuffer[j] = -2; }
    
    for(int i = 0; i < PRE_READING_BUFFER_SIZE; i++) {
        int orderCounter = 0;
        int repeatCounter = 0;
        for(int j = 0; j < PRE_READING_BUFFER_SIZE; j++) {
            if(median_buffer[i] < median_buffer[j]) orderCounter++;             
            if(median_buffer[i] == median_buffer[j]) repeatCounter++;             
        }    
        if (repeatCounter == 1) { reorderBuffer[orderCounter] = median_buffer[i]; } 
        else {
            for(int k = 0; k < repeatCounter; k++) {
                if(reorderBuffer[orderCounter + k] == -2) { reorderBuffer[orderCounter + k] = median_buffer[i]; }
            }
        }
    }
    
    int new_reading = reorderBuffer[PRE_READING_BUFFER_SIZE/2];
            
    // ****** CHECK HAND ACTIVE STATUS ****** // 
    // check if the hand status has changed
    if (new_reading < 0 && hand_active == true) {
        hand_active = false;
        hand_state_change = true;
    } else if (new_reading >= 0  && hand_active == false) {
        hand_active = true;
        hand_state_change = true;
    }
    
    raw_readings[0] = new_reading;
    
} // *** END NEW READING FUNCTION ***

// ***** GESTURE ON AND OFF ***** // 
// Function that identifies gestures that turn on and off the sound of channel
// returns false it has captured an on or off gesture within the pause interval
float AirSensor::gest_on_off() {
    int timeCounter = 0;    // counter that identifies how many readings fit within the gesture interval time
    int onCounter = 0;      // counter that identifies how many readings support an on gesture
    int offCounter = 0;     // counter that identifies how many readings support an off gesture
    gest_on = false;         // boolean variable set to true if ON gesture detected
    gest_off = false;        // boolean variable set to false if OFF gesture detected
    
    // check that an on and off gesture has not been recorded recently 
    if (millis() - gest_on_off_time > ON_OFF_PAUSE_TIME) {
        int counterMin = 4;                        // set minimum number of requirements that need to be met to identify a gesture
        int lookback = READINGS_ARRAY_SIZE - 1;    // set how many readings will be read from the array to identify gesture
        
        // check that the most current and last readings are valid (they do not equal -1)
        if (raw_readings[0] > 0 && raw_readings[lookback] > 0) {
            int fullDelta = raw_readings[0] - raw_readings[lookback];
            if(abs(fullDelta) > ON_OFF_DELTA_THRESHOLD) {
                
                int noiseThreshold = 2;      // the maximum number of out of order readings for the on/off gesture
                int noiseCount = 0;          // the current count of out of order readings for the on/off gesture
                
                // loop through each element in raw_readings array to see which ones meet requirements
                for (int j = 0; j < lookback; j++) { 
                    int gradientDelta = 0;
                    int offsetCheck = j + 1;
                    
                    if(raw_readings[j] > 0) { 
                        
                        // if raw_readings value at offsetCheck equals less than 0, then loop through array to until you find the next value that is greater than 0 
                        if (raw_readings[offsetCheck] < 0) {
                            for(offsetCheck; offsetCheck <= lookback; offsetCheck++) {
                                if (offsetCheck == lookback) return false;
                                else if (raw_readings[offsetCheck] >= 0) break;
                            }
                        }
                        
                        // if a raw_readings value has been found that is more than or equal to 0 then check if the delta meets requirements 
                        if(raw_readings[offsetCheck] > 0) { 
                            gradientDelta = raw_readings[j] - raw_readings[offsetCheck];
                            if(fullDelta > 0) {
                                if (gradientDelta >= 0 && gradientDelta < ON_OFF_DELTA_MAX_STEP) { onCounter++; } 
                                else if (gradientDelta >= ON_OFF_DELTA_MAX_STEP) { break; }
                                else { noiseCount++; }
                                
                            } else if(fullDelta < 0) {
                                if (gradientDelta <= 0 && gradientDelta > (ON_OFF_DELTA_MAX_STEP * -1)) { offCounter++; } 
                                else if (gradientDelta <= (ON_OFF_DELTA_MAX_STEP * -1)) { break; }
                                else { noiseCount++; }
                            }
                            if (noiseCount >= TREND_NOISE_THRESHOLD) break;  
                        }
                    }
                }
            } 
        }
        
        if (onCounter > TREND_RECOGNITION_MIN) { 
            gest_on = true; 
            current_state = OUTPUT_MAX;
            gest_on_off_time = millis();
            hand_state = UP;
            return GEST_ON;
        }
        
        if (offCounter > TREND_RECOGNITION_MIN) { 
            gest_off = true; 
            current_state = OUTPUT_MIN;
            gest_on_off_time = millis();
            hand_state = DOWN;
            return GEST_OFF;
        }
        return STOPPED;
    } 
    return STOPPED; 
} // ****** END - GESTURE ON AND OFF ****** //

// ***** GESTURE VOLUME UP AND DOWN ***** // 
float AirSensor::gest_up_down() {
    int gestUpDown_Shift = 0;

    if (raw_readings[0] > 0) {
        if (gest_up_down_filter_center == -1) { 
            gest_up_down_filter_center = raw_readings[0];   
            gestUpDown_Shift = 0;
            hand_state = STOPPED;                  
        } else if (raw_readings[0] > (gest_up_down_filter_center + UP_DOWN_MIN_DELTA)) {
            gestUpDown_Shift = raw_readings[0] - (gest_up_down_filter_center + UP_DOWN_MIN_DELTA);
            gest_up_down_filter_center += gestUpDown_Shift; 
            hand_state = UP;
        } else if (raw_readings[0] < (gest_up_down_filter_center - UP_DOWN_MIN_DELTA)) {
            gestUpDown_Shift = raw_readings[0] - (gest_up_down_filter_center - UP_DOWN_MIN_DELTA);
            gest_up_down_filter_center += gestUpDown_Shift; 
            hand_state = DOWN;
        } else {
            gestUpDown_Shift = 0;
            hand_state = STOPPED;                  
        }
    } else {
        gest_up_down_filter_center = -1;   
        gestUpDown_Shift = 0;
        hand_state = STOPPED;                  
    }  
    return gestUpDown_Shift;
}

// function that converts up and down gesture values into a MIDI volume between 0 and 127 
void AirSensor::move_up_down() {
    float gestureUpDown = gest_up_down();
    float lastcurrent_state = current_state;
    current_state += (gestureUpDown / sensor_range) * output_range;
    if (current_state > OUTPUT_MAX) current_state = OUTPUT_MAX;
    else if (current_state < OUTPUT_MIN) current_state = OUTPUT_MIN;
    if(lastcurrent_state != current_state) {
        new_state = true;
    }
}

// function that converts that converts on and off shift values into a MIDI value between 0 and 127 
boolean AirSensor::turn_on_off(){
    float gestureOnOff = gest_on_off();
    if(gestureOnOff == GEST_ON) {
        current_state = OUTPUT_MAX;
        new_state = true;
        return true;
    } else if(gestureOnOff == GEST_OFF) {
        current_state = OUTPUT_MIN;
        new_state = true;
        return true;
    }
    return false; 
}

// AVAILABLE: reads the sensor if the appropriate interval of time has passed. Then calls the update_state function
//            to process the input and determine whether the sensor's state has passed the change threshold.
// RETURNS: true if the state of this air sensor has changed
bool AirSensor::available() {
    add_new_reading();
    if (!turn_on_off()) move_up_down(); 
    if (new_state) output_state = current_state;
    return new_state;
}

void AirSensor::print_raw_readings() {
    Serial.print(" - raw: ");
    Serial.println(raw_reading);
}

