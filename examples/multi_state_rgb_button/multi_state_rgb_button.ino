/* 
 *  Switch Library Example :: Digital Button RGB
 *
 *  This example sketch shows how to use the switch library to set-up a button with 6 
 *  states. The get_state method returns an integer, ranging from 0 to 5, that corresponds 
 *  to the switches current state. 
 *
 *  @filename  multi_state_rgb_button.ino
 *  @author    julio terra
 *  @date      12/29/12
 *
*/

#include <SwitchDigitalRgb.h>

// create instance of the SwitchDigitalRgb class
//   * first param: switch pin number
//   * second param: number of button states
SwitchDigitalRgb button = SwitchDigitalRgb(7,6);

void setup() {
  // set pin number of the R, G, and B pins
  button.set_led_pins(3, 5, 6);

  // set color for each button state
  button.set_led_state(0, 255, 0, 0);
  button.set_led_state(1, 255, 255, 0);
  button.set_led_state(2, 0, 255, 0);
  button.set_led_state(3, 0, 255, 255);
  button.set_led_state(4, 0, 0, 255);
  button.set_led_state(5, 255, 0, 255);

  // open serial connection
  Serial.begin(9600); 
}

void loop() {
    // check if the button state has changed
  if(button.available()) {
    // get the button state and print it to the serial monitor
    button.get_print_state();  
  }
}
