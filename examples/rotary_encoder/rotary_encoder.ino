/* 
 *  Switch Library Example :: Rotary Encoder
 *
 *  This example sketch shows how to use the switch library to set-up a rotary encoder. The get_state 
 *  method returns an integer within the output range, which is defined by the set_output_range method, 
 *  and defaults to 0 to 1024.
 *
 *  @filename  analog_switch.ino
 *  @author    julio terra
 *  @date      12/29/12
 *
*/

#include <SwitchEncoder.h>

// create instance of the SwitchAnalog class
//   * first param: switch pin number
SwitchEncoder button = SwitchEncoder( 2, 4 );

void setup() {
  // open serial connection
  Serial.begin( 9600 ); 
  
  // attach interrupt to the 
  attachInterrupt( button.get_interrupt_pin(), handleEvent, RISING );
}

void loop() {
    // check if the button state has changed
  if(button.available()) {
    // get the button state and print it to the serial monitor
    button.get_print_state();  
  }
}

void handleEvent() {
  button.event(); 
}
