/*
 AMUP Config, configration file for AMUP Input Element Libraries Set.
 Created by Julio Terra, June 4, 2011.
 
 Configuration file with constants used across various different AMUP
 components and switch types. 
  
 File name: AMUPconfig.h 
 
 */

#ifndef __SwitchesConfig_h__
#define __SwitchesConfig_h__

#include "WProgram.h"

/* GLOBAL CONSTANTS */
#define debug_code		false         // used for debugging library 

/* DIGITAL SWITCH CONSTANTS */
// time in milliseconds used for debouncing digital switch 
#define DIGITAL_SWITCH_DEBOUNCE   50       

/* DIGITAL RGB SWITCH CONSTANTS */
#define RGB_COUNT                 3 		// total number of pins for each rgb led
#define R                         0
#define G                         1
#define B                         2
#define STATE_MAX                10 		// maximum number of states supported by RGB switches
#define LED_MAX_BRIGHT_TLC        1000
#define LED_MAX_BRIGHT_MATRIX     1

/* ANALOG RGB SWITCH CONSTANTS */
#define OUTPUT_MIN              0
#define OUTPUT_MAX              127
#define OUTPUT_RANGE            OUTPUT_MAX - OUTPUT_MIN

#endif