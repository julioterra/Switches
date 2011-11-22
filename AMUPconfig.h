/*
 AMUP Config, configration file for AMUP Input Element Libraries Set.
 Created by Julio Terra, June 4, 2011.
 
 Configuration file with constants used across various different AMUP
 components and switch types. 
  
 File name: AMUPconfig.h 
 
 */

#ifndef __AMUP_config_h__
#define __AMUP_config_h__

#include "WProgram.h"

/** \file
 Configuration for AMUP sketches. This file holds constants that define variables that are used across multiple.  
 */

// switch states
#define OFF     0    // equivalent to LOW
#define ON      1    // equivalent to HIGH

// LED Related Constants
#define RGB_COUNT                 3   // holds the number of led pins associated to each light (set to three as default)
#define R                         0
#define G                         1
#define B                         2

// LED TLC Constants
#define LED_MAX_BRIGHT_TLC        1000
#define LED_MAX_BRIGHT_MATRIX     1

// Switch Debounce Constants
#define TOGGLE_MAX                10        // maximum number of toggle states supported by RGB Buttons
#define DIGITAL_SWITCH_DEBOUNCE   50       // interval of time that new input will be ignored via digital sensors

// I2C - Air 2 Console: Message Size 
// #define I2C_RECEIVE_MSG_SIZE     12        // size of the the i2C transmit messsage
// #define I2C_TRANSMIT_MSG_SIZE    13

// Serial - Air 2 Button: Message Size, followed by Init and Lock Flags
#define AIR_SERIAL_MSG_SIZE             9
#define AIR_CONNECT_REQUEST_CHAR        'c'
#define AIR_CONNECT_ACCEPT_CHAR         'a'
#define AIR_LOCK_ON_CHAR                '<'
#define AIR_LOCK_OFF_CHAR               '>'

// Midi Output Range - 
#define OUTPUT_MIN              0
#define OUTPUT_MAX              127
#define OUTPUT_RANGE            OUTPUT_MAX - OUTPUT_MIN

#define debug_code              false         // holds the arduino pin where the switch data can be read

// int add_number_to_string(int , char * , int );
// int add_string_to_string(char * , char * , int );
// int add_char_to_string(char , char * , int );
// void reset_string(char *);


#endif