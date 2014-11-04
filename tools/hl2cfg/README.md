Hacklace2 Simple Configuration Utility
======================================
2014-11-03, sw@kaltpost.de

Simple Python (v2.7) script to configure the [Hacklace2](http://wiki.fab4u.de/wiki/Hacklace/en).


__Prerequisites__

* [Hacklace2](http://wiki.fab4u.de/wiki/Hacklace/en)
* [Hack-Key](http://www.wiki.fab4u.de/wiki/Hack-Key) other 3.3v USB to serial converter
* Python with pyserial installed


__Usage__

Download Hacklace2 configuration file ``../../Hacklace_Main/Hacklace_DefaultConfig.txt`` via ``/dev/ttyUSB0``:

`./hl2cfg.py --cfgfile ../../Hacklace_Main/Hacklace_DefaultConfig.txt`

Or use different USB port: 

`./hl2cfg.py --port /dev/USB1 --cfgfile ../../Hacklace_Main/Hacklace_DefaultConfig.txt`

__NOTE__: ``hl2cfg.py`` will automatically reset your device to DL mode if DTR of the serial converter is connected.

Configure animation app to display text: 

`./hl2cfg.py --app ani --txt 'hl2cfg.py was here ...'`

Use some configuration: 

`./hl2cfg.py --app ani --cfg '70 01' --txt 'hl2cfg.py was here ...'`

Add icons:

`./hl2cfg.py --app ani --cfg '70 01' --txt 'hl2cfg.py was here [[:-)]] ...'`

Show all available icon macros:

`./hl2cfg.py --listicons`

Use predefined animation

`./hl2cfg.py --app ani --cfg '30 08' --txt '{{TRAIN}}'`

Show all available animation macros:

`./hl2cfg.py --listanims`

Run game-of-life:

`./hl2cfg.py --app gol --cfg '20 0F 04 05 06 00 00 00 00 00'`

Show spiral:

`./hl2cfg.py --app spiral`

Don't send anything to the device, just print the config-string:

`./hl2cfg.py --app ani --cfg '30 08' --txt '{{TRAIN}}' --nosend`