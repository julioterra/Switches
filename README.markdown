#Switches Libraries for Arduino  
  
The Switch library for Arduino provides classes for reading the state of switches, buttons, analog switches, and rotary encoders. This library is structured as a set of individual libraries, therefore you should only import the class for the specific type of switch that you are using for your project. 

This library is enables you to handle input from different types of physical inputs using a consistent code/design pattern. As an added bonus, the digital switch classes featured debouncing capabilities while the analog switch classes feature smoothing capabilities (the latter could probably be improved).

**[Install the Library and Try it Out](#installing-the-switch-library)**

  
###Switch Library Classes  
Here are links to the documentation for all of the main switch library classes. Jump to these sections if you want to get started trying out the Switches library:
* [Abstract Switch Class](#abstract-switch-class)  
* [Switch Class](#switch-class)  
* [RGB Button Class](#rgb-button-class)  
* [Analog Switch Class](#analog-switch-class)  
* [Rotary Encoder Class](#rotary-encoder-class)  

###Library Hierarchy  
Here's is a digram that illustrates how all of the library classes relate to one another. The Abstract Switch Class serves as the parent class for all other classes, which are collectively referred to as implementation classes. ![Switch Class Hierarchy Diagram](https://a248.e.akamai.net/camo.github.com/8525553e9156d1bfd3140b5d08d7f90734cf3c60/687474703a2f2f6661726d372e737461746963666c69636b722e636f6d2f363034392f363338393930373232315f646365313437323437615f622e6a7067).
  
[back to top](#switches-libraries-for-arduino)  
  
Installing the Switch Library
-----------------------------

* Download the zip file from github repo (click on the button labeled 'zip' at the top of this page)
* Unzip the downloaded file
* Remane the "Switches-master" folder to "Switches"
* Copy this folder into the Arduino libraries folder
* Get Started with an example or tutorial (from below):
  * [Abstract Switch Class](#abstract-switch-class)  
	* [Switch Class](#switch-class)  
	* [RGB Button Class](#rgb-button-class)  
	* [Analog Switch Class](#analog-switch-class)  
	* [Rotary Encoder Class](#rotary-encoder-class)  

[back to top](#switches-libraries-for-arduino)  
  

##Abstract Switch Class
------------------------
  
An abstract switch class that encapsulates the design pattern that is used across all of the implementation switch classes. This class serves as the parent class for all other classes. This class does not need to be imported directly into your app.
  
###Constructors  
The constructor for all classes accepts the pin number to which the physical switch will be connected. The exception is the rotary encoder class, which accepts two pin numbers. Each child class also features other configuration options, which are covered in the switch-specific sections.

```
SwitchAbstract(int _pin)	// abstract class constructor
```  
  
###Available Method  
The `available` method is responsible for reading the current state of a switch and determining if the state has changed. If the switch state has changed then it returns true, otherwise it returns false. 

The implementation of this method on the digital switch classes features debouncing capabilities, while  for analog switches if features smoothing capabilities.  
  
```
bool available();       // checks whether switch's state and returns true if it has changed
```  
  
###Get State Methods  
The `get_state` method and its variants return the current switches state. Whenever a switch state has changed the available() method will return true until one of the get_state() methods are called to retrieve the new switch state.
  
```
int get_state();        	 // returns the current_state and resets new_state flag to false
int get_print_state();  	 // same as method above but also prints switch state to serial
int get_print_state(char*);  // same as method above but prints char array before state message
int get_print_byte_state();  // same as method above but also prints switch state to serial as byte
```

###Miscellaneous
A few additional virtual methods are included in the AbstractSwitch class. These include an invert_switch method, which is defined in the DigitalSwitch child class, and the set_analog_range and set_ouput_range methods, which are defined in the AnalogSwitch child class.
  
```
virtual void invert_switch(bool) {};
virtual void set_analog_range(int, int) {};
virtual void set_output_range(int) {};
```
  
[back to top](#switches-libraries-for-arduino)  
  
##Switch Class

An implementation class designed to handle input from switches and buttons with two states. Switches can be configured as momentary switches (default mode) or toggle buttons, more information about these modes in the Switch Modes section below. Switches can also be configured to change their polarity. This class uses debouncing to filter out noise from the physical input.

This is a child class of the Abstract Switch Class (`SwitchAbstract`).  

**Library Name** `SwitchDigital`
  
###Example Sketch  
```
#include <SwitchDigital.h>

SwitchDigital button = SwitchDigital(7);

void setup() {
  Serial.begin(9600);	// open serial connection to send switch state
  button.invert_switch(true);
}

void loop() {
  if(button.available()) {
    button.get_print_state();  
  }
}
```
  
###Sketch Walk-Through  
 
**1. Import Library**  
First, we import the Switch Library into the sketch.

```
#include <SwitchDigital.h>
```

**2. Create Switch Object**  
Next, we create a switch object to handle a input from a switch that is connected to digital pin 7. 
```
SwitchDigital button = SwitchDigital(7);
```

**3. Configure Switch**  
In the `setup` method we configure the switch by converting its polarity. This is only required if you are using a switch that uses an Arduino internal pullup resistor. 
```
button.invert_switch(true);
```

**4. Use the Switch**  
In the `loop` method we check whether the button state has changed by calling the `available` method. If it returns true, then we print the current button state to the serial port by calling `get_print_state`.
```
if(button.available()) {
  button.get_print_state();  
}
```
  
### Switch Modes  
  
Earlier we mentioned that switches can be configured as momentary switches or toggle buttons. Here is more informaiton about these two different modes, along with guidance on how to change a switch's mode.  
  
**Momentary Switch Mode**  
When in momentary mode, the switch object's state reflects the current physical state of the switch. If the switch is pressed it will return a 1, and if it is not pressed it will return a 0. This is the default mode for switch objects.

**Toggle Button Mode**  
When in toggle button mode, the switch object's state changes after every button press. This means that the physical state of the switch needs to go HIGH and LOW to trigger a state change. When the switch is released the button state toggles its state.

**Switching Modes**  
To turn momentary mode on and off you can use the `momentary(bool)` method. If you pass this method a true or a 1 momentary mode will be activated. If you pass it a false or a 0 the toggle button mode will be activated.  
```
  button.momentary(true);
```
  
[back to top](#switches-libraries-for-arduino)  
  
RGB Button Class
----------------  
An implementation class designed to handle input from switches and buttons with up to ten states. This library also links the button state to colors displayed on a RGB led. The color for each button state is defined by the users.  

This is a child class of the Switch Class (`SwitchDigital`), therefore, it also supports momentary switch and multi-state toggle button modes. If set to momentary mode, then the button state will only alternate between 0 and 1.  
   
**Library Name** `SwitchDigitalRgb`
  
###Example Sketch  
```
#include <SwitchDigitalRgb.h>

SwitchDigitalRgb button = SwitchDigitalRgb(7,3);

void setup() {
  button.set_led_pins(3, 5, 6);
  button.set_led_state(0, 255, 0, 0);
  button.set_led_state(1, 0, 255, 0);
  button.set_led_state(2, 0, 0, 255);
  Serial.begin(9600); 
}

void loop() {
  if(button.available()) {
    button.get_print_state();  
  }
}
```
  
###Sketch Walk-Through  
 
**1. Import Library**  
First, we import the RGB Button Library into the sketch.

```
#include <SwitchDigitalRgb.h>
```

**2. Create Switch Object**  
Next, we create a RGB button object with 3 states to handle input from a button that is connected to digital pin 7. The first parameter in the constructor identifies the pin number while the second parameter sets the number of toggle states.
```
SwitchDigitalRgb button = SwitchDigitalRgb(7,3);
```

**3. Register the RGB Led Pins**  
In the `setup` method we define the RGB led pin numbers. The `set_led_pins` method accepts three parameters, the first holds the red led pin number, then green, and blue. 
```
  button.set_led_pins(3, 5, 6);
```

**4. Register the RGB Led Pins**  
Also in the `setup` method we define the led color for each button state. The `set_led_state` method accepts four parameters, the first holds the button state, and the last three hold the brightness values for the red, green, and blue leds. 
```
  button.set_led_state(0, 255, 0, 0);
  button.set_led_state(1, 0, 255, 0);
  button.set_led_state(2, 0, 0, 255);
```

**5. Use the Button**  
In the `loop` method we check whether the button state has changed by calling the `available` method. If it returns true, then we print the current button state to the serial port by calling `get_print_state`.
```
if(button.available()) {
  button.get_print_state();  
}
```

###Other Features  

**Turn Leds On and Off**  
The `turn_on_leds` and `turn_off_leds` methods are used to turn and and off the leds as a source of feedback for the button state. Even when the leds in the button object are turned on, the physical led may be turned off, if the color of the current state is set to 0, 0, 0.  
```
void turn_on_leds();                   // turns on the leds to the current led state RBG values
void turn_off_leds();                  // turns off leds, current state saved in current_led_state
```

**Set Number of States**  
The `set_number_of_states` method is used to set the number of toggle button states supported by a rgb button object. The maximum number of toggle button states is 10. This method is useful when you initialize an instance of this class using the constructor that only accepts the button input pin number.  
```
void set_number_of_states(int);       // sets the number of toggle button states
```

**Turn On Led with Color**  
The `turn_on_leds` method turns on the leds to the color specified by the three paramaters that the method accepts. The three parameters are red, green, and blue, values should range from 0 to 255.  
```
void turn_on_leds(int, int, int);      // turns on the leds to the specified values
```
  
**Set Current Led State**  
The `set_current_led_state` method sets the button object to the state number specified by the integer parameter. It checks if the the integer corresponds to a valid button state before attempting to update the object's state.
```
void set_current_led_state(int);       // set the current RGB led state    
```
  
###Matrix Set-up Version  
Documentation Coming Soon.  
   
###TLC Driver Version  
Documentation Coming Soon.  
  

[back to top](#switches-libraries-for-arduino)  
  
Analog Switch Class
-------------------  
An implementation class designed to handle input from variable resistors, such as potentiometers, photoresistors, flex sensors, etc. It features smoothing functionality that helps to filter out noise from readings. 

This is a child class of the Abstract Switch Class (`SwitchAbstract`).  
   
**Library Name** `SwitchAnalog`
  
###Example Sketch  
```
#include <SwitchAnalog.h>

SwitchAnalog pot = SwitchAnalog( A0 );

void setup() {
  Serial.begin( 9600 ); 
  pot.set_analog_range( 0, 1023 );
  pot.set_output_range( 255 );
}

void loop() {
  if(pot.available()) {
    pot.get_print_state();  
  }
}
```
  
###Sketch Walk-Through  
 
**1. Import Library**  
First, we import the Analog Switch Library into the sketch.

```
#include <SwitchAnalog.h>
```

**2. Create Switch Object**  
Next, we create an analog switch object to handle input from an analog switch that is connected to digital pin A0. 
```
SwitchAnalog pot = SwitchAnalog( A0 );
```

**3. Configure Input Range**  
In the `setup` method we configure the input range for the analog switch. This is useful when you are using analog resistors with limited range. Maximum input range is 0 to 1023, since this is the range of the Arduino's analog to digital converter. 
```
pot.set_analog_range( 0, 1023 );
```

**4. Configure Output Range**  
Also in the `setup` method we configure the output range for the analog switch. You can only set the maximum value of the range, since the minimum value is always set to 0. 
```
pot.set_output_range( 255 );
```

**5. Use the Analog Switch**  
In the `loop` method we check whether the analog switch state has changed by calling the `available` method. If it returns true, then we print the current button state to the serial port by calling `get_print_state`.
```
if(button.available()) {
  button.get_print_state();  
}
```
  

[back to top](#switches-libraries-for-arduino)  
  
Rotary Encoder Class
--------------------
  
An implementation class designed to handle input from 2-pin rotary encoder switches. The rotary encoder class maintains a state values that ranges between 0 and the max ouput. When the physical rotary encoder rotates the state value is incremented or decremented accordingly.

This is a child class of the Abstract Switch Class (`SwitchAbstract`).  
   
**Library Name** `SwitchEncoder`
  
###Example Sketch  
```
#include <SwitchEncoder.h>

SwitchEncoder encoder = SwitchEncoder( 2, 4 );

void setup() {
  Serial.begin( 9600 ); 
  attachInterrupt( encoder.get_interrupt_pin(), handleEvent, RISING );
  encoder.set_output_range( 255 );
}

void handleEvent() {
  encoder.event(); 
}

void loop() {
  if(encoder.available()) {
    encoder.get_print_state();  
  }
}
```  
  
###Sketch Walk-Through  
 
**1. Import Library**  
First, we import the Rotary Encoder Library into the sketch.

```
#include <SwitchEncoder.h>
```

**2. Create Switch Object**  
Next, we create a rotary encoder object to handle input from an encoder that is connected to digital pins 2 and 4. The first pin should always be connected to an interrupt pin (pin 2 or 3 on the Arduino Uno). The second pin can be connected to any unused digital input pin.  
```
SwitchEncoder encoder = SwitchEncoder( 2, 4 );
```
  
**3. Configure Interrupt**  
In the `setup` method we configure the interrupt pin to which the encoder is attached. We link rising events on this pin to a method called `handleEvent`. This means that whenever this pin goes from LOW to HIGH the `handleEvent` method will be called. 
```
attachInterrupt( encoder.get_interrupt_pin(), handleEvent, RISING );
```

**4. Configure Interrupt**  
Also in the `setup` method we configure the range of the state values for the encoder. The encoder always returns a value between 0 and the max value set by this method. As you turn the encoder it just cycles through this range. By default the range is 0 to 1023. 
```
encoder.set_output_range( 255 );
```
  
**5. Define Interrupt Callback Method**  
Next up we define the `handleEvent` method, which is called every time the encoder interrupt pin goes from LOW to HIGH. In this method we just call the `event` method from the encoder object to read the current state of both encoder pins. 
```
void handleEvent() {
  encoder.event(); 
}
```

**6. Use the Rotary Encoder**  
In the `loop` method we check whether the rotary encoder state has changed by calling the `available` method. If it returns true, then we print the current button state to the serial port by calling `get_print_state`.
```
if(button.available()) {
  button.get_print_state();  
}
```

[back to top](#switches-libraries-for-arduino)  
  




