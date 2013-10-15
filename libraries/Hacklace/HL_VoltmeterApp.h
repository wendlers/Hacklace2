/*
 * HL_VoltmeterApp.cpp
 *
 */ 

/**********************************************************************************

Description:		Hacklace Voltmeter App

					Measure a voltage and display its value in millivolts.

					Connect ground to GND. Use an input resistor between the voltage 
					that is to be measured and the input (ADC7). The value of the 
					input resistor (in kOhms) is entered as a byte-parameter.
					
					For protection against overvoltage and reverse polarity put a 
					zener diode of 3.6 V between ADC7 (zener cathode) and GND (zener anode).

					To compensate for tolerances of the internal reference voltage 
					apply a calibration voltage to the input and read the measurement 
					of the Hacklace. Enter both values below.
										
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

#define APP_NAME		VoltmeterApp
#define APP_CLASSNAME	CONCAT(APP_NAME, _class)

// input voltage divider
// Example: R_IN = 39 kOhm --> input range 0..5 V
#define R14				10.00	// value of resistor R14 (in kOhms)

// calibration
#define V_CALIBRATION	1.00	// calibration voltage applied to the input
#define V_MEASURED		1.00	// voltage measured by the Hacklace

// internal reference
#define V_REFERENCE		1.10	// nominal value of internal reference voltage (see ATMEL datasheet)

// factor for converting adc-value to millivolts
#define ADC2MV_FACTOR	( (V_CALIBRATION / V_MEASURED) * (V_REFERENCE / 1.023) )


/*********
 * class *
 *********/

class APP_CLASSNAME : public Hacklace_App
{
	public:
		const unsigned char* setup(const unsigned char* ee);
		void run();
		void finish();

	private:
		static float ratio;		// ratio of input voltage divider
};


APP_CLASSNAME APP_NAME;			// create an instance of the app class


/**************************
 * static class variables *
 **************************/

float 	APP_CLASSNAME::ratio;


/***********
 * methods *
 ***********/

const unsigned char* APP_CLASSNAME::setup(const unsigned char* ee)
{
	byte r_in;
	
	r_in = eeprom_read_byte(ee++);			// read input resistor value
	ratio = 1.0 + ((float) r_in) / R14;
	HL.setScrollSpeed(8, 6);
	HL.printString_P(PSTR(" Voltmeter  "));
	HL.scrollSync();						// clear sync flag
	analogReference(INTERNAL);
	return( ee );
}


void APP_CLASSNAME::run()
{
	float	volt;							// voltage in millivolts
	char	st[7];
	
	if (HL.scrollSync()) {					// wait until end of scrolling occurs
		volt = ratio * ADC2MV_FACTOR * (float) analogRead(A7);
		itoa((unsigned int)(volt + 0.5), st, 10);	// volt is rounded to next integer
		HL.cursorHome();
		HL.printString_P(PSTR("V="));
		HL.printString(st);
		//HL.printString_P(PSTR("mV"));
	}
}


void APP_CLASSNAME::finish()
{
}


