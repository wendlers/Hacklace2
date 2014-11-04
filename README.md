Hacklace2
=========

Fork of Arduino firmware for [Hacklace2](http://wiki.fab4u.de/wiki/Hacklace/en). 

* Added Makefile to compile with [arduino-make](https://github.com/sudar/Arduino-Makefile) outside Arduino IDE
* Added simple python script (``tools/hl2cfg``) to configure HL2
* Started firmware to connect HL2 with ESP8266 serial to wifi module for over the air texting
* Added 3D printable case (see ``case``)


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


__Customize Settings__

If you like to adjust settings (like serial port), copy ``config.mk`` to ``userconfig.mk`` and change
the settings there.
