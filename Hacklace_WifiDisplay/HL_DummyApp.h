/*
 * HL_ExampleApp.cpp
 *
 */

/**********************************************************************************

Description:	Hacklace Dummy App

		Simple dummy place holder to keep app-registry happy.

Author:		Stefan Wendler
Copyright 2014:	Stefan Wendler
License:	see "license.md"
Disclaimer:	This software is provided by the copyright holder "as is" and any
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

// ##### enter your app name here #####
#define APP_NAME		DummyApp		// <--- here
#define APP_CLASSNAME	CONCAT(APP_NAME, _class)	// do not change


/*********
 * class *
 *********/

class APP_CLASSNAME : public Hacklace_App
{
	public:
		const unsigned char* setup(const unsigned char* ee);
		void run();
		void finish();
};


APP_CLASSNAME APP_NAME;		// create an instance of the app class


/***********
 * methods *
 ***********/

const unsigned char* APP_CLASSNAME::setup(const unsigned char* ee)
{
	HL.printString_P(PSTR("READY"));
	return( ee );
}


void APP_CLASSNAME::run()
{
}


void APP_CLASSNAME::finish()
{
}
