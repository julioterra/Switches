#Switches Libraries for Arduino

**Using a Switch Library:**  
  
In order to use these libraries with your Arduino you will need to copy the contents of the switches folders into your libraries folder. Otherwise, your Arduino will not be able to locate these resources. It is strongly recommended that you put all of these folders into your library folder to avoid potential issues and errors as all of these libraries contain references to one another.

Please refer to the image in the wiki that illustrates how all of these libraries are related to one another.

**Managing Physical Input:**  
  
This set of libraries was designed to handle several different types of physical switches using a consistent approach. An abstract switch class encapsulates the design pattern that is used across all of these libraries and serves as the parent class for all other classes.

The constructor for all classes accepts an ID number along with the pin number to which the physical switch will be connected. The exception is the rotary encoder class, which accepts two pin numbers, as required by these types of switches. Each implementation class features several other configuration options that are specific to the type of switch.

    SwitchAbstract(int _ID, int _pin)	// abstract class constructor  
  
All of these classes use the same interface for reading a switch's state. The available() instance method is responsible for reading the current state of a switch and determining if the state has changed. If the switch state has changed then it returns true, otherwise it returns false. The implementation of this method on the digital switch classes features debouncing capabilities, while the implementation for analog switches features smoothing capabilities.  
  
    bool available();       // checks whether switch's state and returns true if it has changed  
  
The get_state() method, and its variants, return the current switches state. Whenever a switch state changes the available() method will return true until one of the get\_state() methods are called to retrieve the new switch state.

    int get_state();        // returns the current_state and resets new_state flag to false
    int get_print_state();  // same as method above but also prints switch state to serial