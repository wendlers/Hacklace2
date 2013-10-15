/*
 * Hacklace_AppEngine.cpp
 *
 */ 

/**********************************************************************************

Description:		Hacklace 2 AppEngine
					
Author:				Frank Andre
Copyright 2013:		Frank Andre
License:			This software is distributed under a hardware-bound GPL license as
					follows:
					(1) This software must only be executed on the original Hacklace2 
					hardware as distributed by www.fab4U.de.
					(2) As long as (1) is not violated this software is licensed under 
					the GNU GPLv3 (see license.md or http://www.gnu.org/licenses/).
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
 

#include <avr/pgmspace.h>
#include <avr/eeprom.h>
#include <util/delay.h>
#include "Arduino.h"
#include "Hacklace.h"
#include "Hacklace_AppEngine.h"
#include "HL_DownloadApp.h"


/************
 * Instance *
 ************/

Hacklace_AppEngine HL;		// instantiate a Hacklace_AppEngine


/*************
 * variables *
 *************/

// app registry
extern const Hacklace_App* app_registry[MAX_APPS];

// static class variables
const unsigned char*	Hacklace_AppEngine::ee_ptr;
//Hacklace_App*			Hacklace_AppEngine::app_registry[MAX_APPS];	// list of all available apps
Hacklace_App*			Hacklace_AppEngine::app;					// pointer to current app


/***********
 * methods *
 ***********/

void Hacklace_AppEngine::initialize()
{
	byte i, app_id;
	
	Hacklace::initialize();

	printChar(HL2_LOGO);
	if (eeprom_read_byte(EE_START_ADDR) == 0xFF) {			// EEPROM empty?
		copyToEeprom(ee_default, sizeof(ee_default));		// -> restore default EEPROM content
		_delay_ms(1000);
	}

#ifdef ENTER_DOWNLOAD_AFTER_RESET
	cursorHome();
	app = &DownloadApp;
	app->setup(EE_START_ADDR);
#else
	app = NULL;
#endif

	ee_ptr = EE_START_ADDR;
//###	for (i=0; i< MAX_APPS; i++) { app_registry[i] = NULL; }	// clear app_registry
	app_id = eeprom_read_byte(ee_ptr);						// peek first app_id
	if (app_id == 0xFF) {									// eeprom empty?
		copyToEeprom(ee_default, sizeof(ee_default));		// -> load default data
	}
}


void Hacklace_AppEngine::copyToEeprom(const char* flash_ptr, unsigned int size)
{
	// Copy memory content from flash to EEROM.
	
	unsigned int i;
	char ch;
	byte* ee_ptr;

	ee_ptr = EE_START_ADDR;
	for(i = 0; i < size; i++) {
		ch = pgm_read_byte(flash_ptr++);
		eeprom_write_byte(ee_ptr++, ch);
	}
}


Hacklace_App* Hacklace_AppEngine::getApp(byte app_id)
{
	if (app_id >= MAX_APPS) { return (NULL); }
	else { return ( (Hacklace_App*) pgm_read_word(&app_registry[app_id]) ); }
//###	else { return (app_registry[app_id]); }
}


void Hacklace_AppEngine::resetApp()
{
	// Terminate the current app and set first app to be the next one.
	
	if (app) { app->finish(); }
	app = NULL;
	clearDisplay();
	ee_ptr = EE_START_ADDR;
}


void Hacklace_AppEngine::nextApp()
{
	// Switch to the next app as defined by the app_list in EEPROM.
	
	byte app_id;

	if (app) { app->finish(); }				// finish old app
	clearDisplay();
	setSpacing(1);
	setScrollSpeed(7, 7);
	setScrollMode(FORWARD, 1);
	app_id = eeprom_read_byte(ee_ptr++);	// read new app_id
	app = getApp(app_id);					// get pointer to app object
	if (app) {
		ee_ptr = app->setup(ee_ptr);
	} else {
		printString_P(PSTR("bad ID"));
	}

	app_id = eeprom_read_byte(ee_ptr);		// peek next app_id
	if (app_id == END_OF_LIST) {			// end of list?
		ee_ptr = EE_START_ADDR;				// -> restart from beginning
	}
}


void Hacklace_AppEngine::enterPowerDown()
{
	resetApp();										// terminate current app
	printChar(SAD_SMILEY);  _delay_ms(500);
	clearDisplay();
	while ((PIN(BTN_PORT) & BUTTON1) == 0) {}		// wait for button to be released
	_delay_ms(20);									// wait until bouncing has decayed
	powerDown();									// ---------- sleeping ----------
	while ((PIN(BTN_PORT) & BUTTON1) == 0) {}		// wait for button to be released
	_delay_ms(20);									// wait until bouncing has decayed
	
	printChar(HAPPY_SMILEY);
	if (PIN(BTN_PORT) & BUTTON2) {					// button2 not pressed
		_delay_ms(500);
		nextApp();									// start app
	} else {										// button2 pressed
		while ((PIN(BTN_PORT) & BUTTON2) == 0) {}	// wait for button to be released
		_delay_ms(20);								// wait until bouncing has decayed
		clearDisplay();
		app = &DownloadApp;
		app->setup(EE_START_ADDR);					// enter download mode
	}
}


void Hacklace_AppEngine::run()
{
	Hacklace::run();
	if (app) { app->run(); }
	if (button == BTN1_RELEASED) {					// switch to next app
		buttonAck();
		nextApp();
	}
	if (button == BTN1_LONGPRESSED) {				// turn Hacklace off
		buttonAck();
		enterPowerDown();
	}
}


