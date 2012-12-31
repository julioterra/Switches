/* 
 *  Switch Library Example :: Digital Switch
 *
 *  This example sketch shows how to use the switch library to set-up a simple switch. The get_state 
 *  method returns a 1 when the button is pressed and a 0 when the button is released. 
 *  
 *  Since the switch on my prototype boards feature switches that are set-up to use the Arduino's 
 *  internal pullup resistor, I used the invert_switch method to turn on the pullup resistor 
 *  and to update the state logic to associate button press to a LOW state.
 *
 *  @filename  digital_switch.ino
 *  @author    julio terra
 *  @date      12/29/12
 *
*/

#include <SwitchDigital.h>

// create instance of the SwitchDigitalRgb class
//   * first param: switch pin number
SwitchDigital button = SwitchDigital(7);

void setup() {
  // open serial connection
  Serial.begin(9600); 
  
  // call invert_switch method to turn on the pullup resistor on the switch's input pin
  button.invert_switch(true);
}

void loop() {
    // check if the button state has changed
  if(button.available()) {
    // get the button state and print it to the serial monitor
    button.get_print_state();  
  }
}
