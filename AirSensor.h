/*
 AirSensor.h - Library for the AMUP Air Sensor.
 Created by Julio Terra, June 2, 2011.
 */

#ifndef AirSensor_h
#define AirSensor_h

#include "WProgram.h"
#include "AMUPconfig.h"
#include "utility/InputElement.h"

class AirSensor : public InputElement {
    private: 
        #define PRE_READING_BUFFER_SIZE     20  
        #define READINGS_ARRAY_SIZE         10
        #define TREND_RECOGNITION_MIN       4      
        #define TREND_NOISE_THRESHOLD       4      
        #define TIME_INTERVAL               15

        #define SENSOR_MIN                  125
        #define SENSOR_MAX                  480

        #define ON_OFF_DELTA_THRESHOLD      170
        #define ON_OFF_DELTA_MAX_STEP       100
        #define ON_OFF_PAUSE_TIME           450
        #define UP_DOWN_MIN_DELTA           30

        #define UP                           0
        #define DOWN                         1
        #define STOPPED                     -1
        #define GEST_ON                      1
        #define GEST_OFF                     0
        
        int sensor_range;

        // hand sensing variables
        boolean hand_active;
        boolean hand_state_change;
        
        // On/Off Gesture
        unsigned long gest_on_off_time;
        boolean gest_on;
        boolean gest_off;
        
        // GEST_UP/Down Gesture
        int gest_up_down_filter_center;

        // data capture and processing variables
        int raw_reading;
        int raw_readings[READINGS_ARRAY_SIZE];
        int median_buffer[PRE_READING_BUFFER_SIZE];
        int new_reading;
        int hand_state;
        int output_range;

        void add_new_reading();
        void move_up_down();
        boolean turn_on_off();
        float gest_on_off();
        float gest_up_down();

    public:        
        AirSensor(int, int);
        void reset();
        bool available();
        void print_raw_readings();
    
};

#endif