/*
 AirSensor.h - Library for the AMUP Air Sensor.
 Created by Julio Terra, June 2, 2011.
 */

#include "AMUPconfig.h"

// int add_number_to_string(int number, char * destination, int counter){
//     char live_message[12];
//     itoa(number, live_message, 10);
//     int msg_len = strlen(live_message);
//     for (int j = 0; j < msg_len; j++) {
//         destination[counter] = live_message[j];
//         counter++;
//     }
//     return counter;
// }
// 
// int add_string_to_string(char * source, char * destination, int counter){
//     int msg_len = strlen(source);
//     for (int j = 0; j < msg_len; j++) {
//         destination[counter] = source[j];
//         counter++;
//     }
//     return counter;
// }
// 
// int add_char_to_string(char source, char * destination, int counter){
//     destination[counter] = source;
//     counter++;
//     return counter;
// }
// 
// void reset_string(char * string) {
//     int msg_len = strlen(string);
//     for (int j = 0; j < msg_len; j++) {
//         string[j] = '\0';
//     }
// }
