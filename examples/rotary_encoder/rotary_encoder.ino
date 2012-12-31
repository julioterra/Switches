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
SwitchEncoder encoder = SwitchEncoder( 2, 4 );

void setup() {
  // open serial connection
  Serial.begin( 9600 ); 
  
  // attach interrupt to the 
  attachInterrupt( encoder.get_interrupt_pin(), handleEvent, RISING );
  encoder.set_output_range( 255 );
}

void loop() {
    // check if the encoder state has changed
  if(encoder.available()) {
    // get the encoder state and print it to the serial monitor
    encoder.get_print_state();  
  }
}

/**
 * handleEvent Callback method that triggered every time that state of the encoder 
 *   interrupt pin goes from LOW to HIGH. This method just calls the event method from
 *   the rotary encoder object, which updates the encoder position.
 */
void handleEvent() {
  encoder.event(); 
}
