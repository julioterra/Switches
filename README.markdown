#Switches Libraries for Arduino  
  
The Switch library for Arduino provides classes for reading the state of switches, buttons, analog switches, and rotary encoders.   
  
Please refer to the wiki for an illustration of [how all of these libraries are related to one another](https://github.com/julioterra/Switches/wiki).
  
##Installing a Switch Library  
  
* Download the library zip file from github repo
* Unzip the downloaded file
* Copy the Switches folder into the Arduino libraries folder
  
##Abstract Switch  
  
This set of libraries was designed to handle several different types of physical switches using a consistent approach. An abstract switch class encapsulates the design pattern that is used across all of the switch classes, serving as the parent class for all other classes.   
  
###Constructors  
The constructor for all classes accepts the pin number to which the physical switch will be connected. The exception is the rotary encoder class, which accepts two pin numbers. Each child class also features other configuration options, which are covered in the switch-specific sections.

```
SwitchAbstract(int _pin)  // abstract class constructor
```  
  
###Available Method  
The available method is responsible for reading the current state of a switch and determining if the state has changed. If the switch state has changed then it returns true, otherwise it returns false. 

The implementation of this method on the digital switch classes features debouncing capabilities, while  for analog switches if features smoothing capabilities.  
  
```
bool available();       // checks whether switch's state and returns true if it has changed
```  
  
###Get State Methods  
The get_state method and its variants return the current switches state. Whenever a switch state has changed the available() method will return true until one of the get_state() methods are called to retrieve the new switch state.
  
```
int get_state();        	 // returns the current_state and resets new_state flag to false
int get_print_state();  	 // same as method above but also prints switch state to serial
int get_print_byte_state();  // same as method above but also prints switch state to serial as byte
```

###Miscellaneous
A few additional virtual methods are included in the AbstractSwitch class. These include an invert_switch method, which is defined in the DigitalSwitch child class, and the set_analog_range and set_ouput_range methods, which are defined in the AnalogSwitch child class.

```
virtual void invert_switch(bool) {};
virtual void set_analog_range(int, int) {};
virtual void set_output_range(int) {};
```

##Switch Digital  
  

  


