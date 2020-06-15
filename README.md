# filter_system_valve_controller

Valve controller for well water spin down filter system based on Adafruit METRO.

### Hardware

Adafruit METRO 328 https://github.com/adafruit/Adafruit-METRO-328-PCB  
Onset AC Current Transformer CTV-A https://www.onsetcomp.com/products/sensors/ctv-x
Irritrol 700B-.75 https://www.irritrol.com/en/valves/700-series

### File Structure

#### ```/documentation``` folder:  
A folder holding specifications and documentation on the device hardware.

#### ```filter_system_valve.ino``` file:
This file is the firmware that will run as the primary application on the METRO. It contains a `setup()` and `loop()` function written in C++.
