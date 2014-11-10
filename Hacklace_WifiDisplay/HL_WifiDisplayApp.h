/*
 * HL_DisplayApp.cpp
 *
 */

/**********************************************************************************

Description:		Hacklace Display App

					Receive a string from the serial interface and display it.
					Characters are interpreted according to character font.
					To enter binary values each byte must be preceeded by 0x1F.
					Use <CR> or <LF> to clear the display.

Author:				Frank Andre
Copyright 2013:		Frank Andre
License:			see "license.md"
Disclaimer:			This software is provided by the copyright holder "as is" and any
					express or implied warranties, including, but not limited to, the
					implied warranties of merchantability and fitness for a particular
					purpose are disclaimed. In no event shall the copyright owner or
					contributors be liable for any direct, indirect, incidental,
					special, exemplary, or consequential damages (including, but not
					limited to, procurement of substitute goods or services; loss of
					use, data, or profits; or business interruption) however caused
					and on any theory of liability, whether in contract, strict
					liability, or tort (including negligence or otherwise) arising
					in any way out of the use of this software, even if advised of
					the possibility of such damage.

**********************************************************************************/

#include <avr/eeprom.h>
#include "Arduino.h"
#include "Hacklace.h"
#include "Hacklace_AppEngine.h"
#include "Hacklace_App.h"


extern Hacklace_AppEngine HL;


/*************
 * constants *
 *************/

#ifdef APP_NAME
	#undef APP_NAME
	#undef APP_CLASSNAME
#endif

#define APP_NAME		WifiDisplayApp
#define APP_CLASSNAME	CONCAT(APP_NAME, _class)


/*********
 * class *
 *********/

class APP_CLASSNAME : public Hacklace_App
{
	private:
		static byte raw_mode;

	public:
		const unsigned char* setup(const unsigned char* ee);
		void run();
		void finish();

	private:

		void sendAt(const char* cmd, bool flush=true);
};


APP_CLASSNAME APP_NAME;		// create an instance of the app class


/**************************
 * static class variables *
 **************************/

byte 	APP_CLASSNAME::raw_mode;


/***********
 * methods *
 ***********/

const unsigned char* APP_CLASSNAME::setup(const unsigned char* ee)
{
	HL.clearDisplay();
	HL.setScrollSpeed(7, 7);
	HL.setScrollMode(FORWARD, 1);
	HL.disableButton2();

	raw_mode = 0;

	HL.clearDisplay();
	HL.printString_P(PSTR("?"));

	Serial.begin(115200);

	// connect to AP
	sendAt("AT+CWJAP=\"XYZ\",\"pass\"\r", true);
	delay(5000);

	HL.clearDisplay();
	HL.printString_P(PSTR("XZY"));

	return( ee );
}


void APP_CLASSNAME::run()
{
	byte ch;

	while( Serial.available() ) {
		ch = Serial.read();
		if (raw_mode) {							// ----- raw / binary mode --------
			HL.printByte(ch);
			raw_mode = 0;
		}
		else {									// ----- ASCII character mode -----
			if ( (ch == 13) || (ch == 10) ) {	// <CR> or <LF> ?
				HL.clearDisplay();
			}
			else if (ch == RAW_MODE_CHAR) {
				raw_mode = 1;
			}
			else {
				HL.printChar(ch);
				HL.printByte(0);				// space between characters
			}
		}
	}
}


void APP_CLASSNAME::finish()
{
	Serial.end();
	HL.enableButton2();
}

void APP_CLASSNAME::sendAt(const char* cmd, bool flush)
{
	Serial.write(cmd);

	if(flush)
	{
		do
		{
			delay(25);
		}
		while(Serial.read() > -1);
	}
}
