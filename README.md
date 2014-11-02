Hacklace2
=========

Fork of Arduino firmware for [http://wiki.fab4u.de/wiki/Hacklace/en](Hacklace2). 

* Added Makefile to compile with [arduino-make](https://github.com/sudar/Arduino-Makefile) outside Arduino IDE

__Prerequisites__

* Arduino IDE installed
* Arduino-Makefile installed

For Ubuntu/Mint: 

`sudo apt-get install arduino arduino-make`

__Usage__

Build: 

`make`
  
Firmware could be found under ``Hacklace_Main/build-mega328``.

Clean:

`make clean`

__FW Upload__

E.g. with Hacklace connected to ttyUSB0:

`MONITOR_PORT=/dev/ttyUSB0 make upload`
