/*
 * Hacklace_Main.ino
 *
 */ 

/**********************************************************************************

Description:    Hacklace2 Main Program

                Note: The Hacklace library uses Timer1.
					
Author:		Frank Andre
Copyright 2013:	Frank Andre
License:	This software is distributed under a hardware-bound GPL license as
		follows:
		(1) This software must only be executed on the original Hacklace2 
		hardware as distributed by www.fab4U.de.
		(2) As long as (1) is not violated this software is licensed under 
		the GNU GPLv3 (see license.md or http://www.gnu.org/licenses/).
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
 

#include <avr/pgmspace.h>
#include <avr/eeprom.h>
#include "Hacklace.h"
#include "Hacklace_AppEngine.h"
#include "HL_AppRegistry.h"


// the setup routine runs once when you press reset:
void setup() {
  HL.initialize();
  
  // only for debugging purposes: always restore default EEPROM content
  // HL.copyToEeprom(ee_default, sizeof(ee_default));
}


// the loop routine runs over and over again forever:
void loop() {

  if (HL.sysTimerHasElapsed()) {    // system timer elapses every 10 ms
    HL.run();
  }

  HL.goToSleep();      // save battery power
}
