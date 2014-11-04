ARDMK_DIR         = /usr/share/arduino
BOARD_TAG         = pro328 

USER_LIB_PATH     = ../libraries

MONITOR_PORT	  = /dev/ttyUSB0
MONITOR_BAUDRATE  = 115200

-include ../userconfig.mk
include $(ARDMK_DIR)/Arduino.mk
