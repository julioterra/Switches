/* 
 *  Switch Library Example :: Analog Switch
 *
 *  This example sketch shows how to use the switch library to set-up an analog switch. The get_state 
 *  method returns an integer within the output range, which is defined by the set_output_range method, 
 *  and defaults to 0 to 1024.
 *
 *  @filename  analog_switch.ino
 *  @author    julio terra
 *  @date      12/29/12
 *
*/

#include <SwitchAnalog.h>

// create instance of the SwitchAnalog class
//   * first param: switch pin number
SwitchAnalog pot = SwitchAnalog( A0 );

void setup() {
  // open serial connection
  Serial.begin( 9600 ); 
  
  // set the range of the input values
  pot.set_analog_range( 0, 1023 );

  // set the max value of the output range, the min is 0
  pot.set_output_range( 255 );
}

void loop() {
    // check if the pot state has changed
  if(pot.available()) {
    // get the pot state and print it to the serial monitor
    pot.get_print_state();  
  }
}
