/*
 * Hacklace_AppEngine.h
 *
 */ 

/**********************************************************************************

Author:				Frank Andre
Copyright 2013:		Frank Andre
License:			This software is distributed under a hardware-bound GPL license as
					follows:
					(1) This software must only be executed on the original Hacklace2 
					printed circuit board with the fab4U logo on it. 
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


#ifndef HACKLACE_APPENGINE_H_
#define HACKLACE_APPENGINE_H_

#include "Arduino.h"
#include "Hacklace_App.h"


/*************
 * constants *
 *************/

// version
#define HL_VERSION_MAJOR	0
#define HL_VERSION_MINOR	3

// start and end address of text/animation data in EEPROM
#define EE_START_ADDR		0x000
#define EE_END_ADDR			0x3FF

// app IDs
#define ANIMATION			0
#define SPIRAL				1
#define COUNTER				2
#define GAME_OF_LIFE		3
#define VOLTMETER			4
#define BATT_MONITOR		5
#define FREQMETER			6
#define EXAMPLE_APP			30
#define RESET_APP			31

// special App-ID (do not change)
#define END_OF_LIST			255			// app_id value that indicates the end of the app list

// select animation by index (starting from 0)
#define ANI(index)			(128 + index)

// maximum number of apps
#define MAX_APPS			32

// default EEPROM content
const char ee_default[] PROGMEM = {
	ANIMATION, 0x76, 0x01, ' ', 'H', 'a', 'c', 'k', 'l', 'a', 'c', 'e', '2', ' ', SKULL, SPC1, 0,
	ANIMATION, 0x85, 0x01, ' ', 'A', 'r', 'd', 'u', 'i', 'n', 'o', '-', 'k', 'o', 'm', 'p', 'a', 't', 'i', 'b', 'e', 'l', SPC8, 0,
	ANIMATION, 0x85, 0x01, ' ', 'I', ' ', HEART, ' ', 'y', 'o', 'u', ' ', 'a', 'l', 'l', '!', ' ', ' ', 0,
	ANIMATION, 0x86, 0x01, ' ', 'H', 'i', 'g', 'h', ' ', 'V', 'o', 'l', 't', 'a', 'g', 'e', ' ', 16, 0,
//	ANIMATION, 0x76, NO_SCROLLING, HAPPY_SMILEY, 0,			// Smiley
//	ANIMATION, 0x76, NO_SCROLLING, 0x1F, 8, 0x3E, 0x08, 0xFE, 0x80, 0x80, 0x19, 0x15, 0x12, 0,	// user defined character
	ANIMATION, 0x54, 0x08, SPC1, SPC1, HEART, SPC8, SPC1, SPC1, HEART, SPC8, 0,	// Heartbeat
	ANIMATION, 0x83, 0x21, 5, ' ', 6, ' ', 7, ' ', 8, 0,	// Monster
	ANIMATION, 0xB0, 0x08, ANI(1), 0,						// Fire
	ANIMATION, 0x99, 0x01, ANI(2), 0,						// Plug-in
	ANIMATION, 0x8B, 0x08, ANI(3), 0,						// Arrow
	ANIMATION, 0x99, 0x08, SPC8, ANI(4), SPC8, 0,			// Ball
	ANIMATION, 0xA8, 0x01, ANI(5), 0,						// ECG
	ANIMATION, 0x8A, 0x08, ANI(6), 0,						// Droplet
	ANIMATION, 0x88, 0x01, 0x7F, ANI(7), 0x7F, 0,			// Train
	ANIMATION, 0x88, 0x08, ANI(8), 0,						// Pong
	ANIMATION, 0x45, 0x08, ANI(9), 0,						// Wink
	ANIMATION, 0x7A, 0x08, ANI(10), 0x7F, 0,				// TNT
	ANIMATION, 0x24, 0x08, ANI(11), 0,						// House
//	ANIMATION, 0x38, 0x08, ANI(12), 0,						// Drowsy
	ANIMATION, 0x50, 0x08, ANI(14), 0,						// Dancer
	ANIMATION, 0x45, 0x08, ANI(15), 0,						// Snow
//	ANIMATION, 0x35, 0x08, ANI(16), 0,						// Sunset
	ANIMATION, 0x80, 0x08, ANI(17), 0,						// Radar
	ANIMATION, 0xA0, 0x08, ANI(18), 0,						// Propeller
	ANIMATION, 0x79, 0x08, ANI(19), 0,						// Flat cat
	ANIMATION, 0xA0, 0x08, ANI(20), 0,						// Squares
	ANIMATION, 0x35, 0x08, ANI(21), ANI(22), 0,				// Tetris
	EXAMPLE_APP,
	SPIRAL,
	COUNTER,
	GAME_OF_LIFE, 32, 15, 0x04, 0x05, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00,		// glider
	GAME_OF_LIFE,  5, 50, 0x00, 0x24, 0x5A, 0x24, 0x24, 0x5A, 0x24, 0x00,		// oktagon
	GAME_OF_LIFE,  6, 10, 0x00, 0x04, 0x6C, 0x38, 0x1C, 0x36, 0x20, 0x00,		// pulsate
//	GAME_OF_LIFE, 32, 12, 0x00, 0x04, 0x05, 0x06, 0x10, 0x60, 0x30, 0x00,		// mix
//	GAME_OF_LIFE, 36, 12, 0x00, 0x00, 0x00, 0x10, 0x38, 0x08, 0x00, 0x00,		// grow
//	GAME_OF_LIFE,  4, 30, 0x00, 0x42, 0x3C, 0x24, 0x24, 0x3C, 0x42, 0x00,		// 4 cycle
//	GAME_OF_LIFE, 12, 15, 0x00, 0x00, 0x24, 0x2C, 0x20, 0x00, 0x00, 0x00,		// bubble
//	GAME_OF_LIFE, 16, 15, 0x50, 0x08, 0x08, 0x48, 0x38, 0x00, 0x00, 0x00,		// spaceship
	VOLTMETER, 39,
	FREQMETER,
	BATT_MONITOR,
	END_OF_LIST
};


/***********
 * classes *
 ***********/

class Hacklace_AppEngine : public Hacklace
{
	public:
		static void initialize();
		static void copyToEeprom(const char* flash_ptr, unsigned int size);
		static Hacklace_App* getApp(byte app_id);
		static void resetApp();
		static void nextApp();
		static void run();

	private:
		static const unsigned char*	ee_ptr;
//###		static Hacklace_App*		app_registry[MAX_APPS];	// list of all available apps
		static Hacklace_App*		app;					// pointer to current app
		
		static void enterPowerDown();
};


extern Hacklace_AppEngine HL;


#endif /* HACKLACE_APPENGINE_H_ */
