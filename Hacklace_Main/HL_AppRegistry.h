/*
 * HL_AppRegistry.h
 *
 */ 

/**********************************************************************************

Author:		Frank Andre
Copyright 2013:	Frank Andre
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


#ifndef APP_REGISTRY_H_
#define APP_REGISTRY_H_

#include <avr/pgmspace.h>

#include "Hacklace_App.h"

// include Hacklace apps
#include "HL_AnimationApp.h"
#include "HL_SpiralApp.h"
#include "HL_CounterApp.h"
#include "HL_GameOfLifeApp.h"
#include "HL_VoltmeterApp.h"
#include "HL_BatteryMonitorApp.h"
#include "HL_FreqmeterApp.h"
#include "HL_DisplayApp.h"
#include "HL_ExampleApp.h"
#include "HL_DownloadApp.h"


// list of all available apps
const Hacklace_App* app_registry[MAX_APPS] PROGMEM = {
	&AnimationApp,			// app-ID 0
	&SpiralApp,			// app-ID 1
	&CounterApp,			// app-ID 2
	&GameOfLifeApp,			// app-ID 3
	&VoltmeterApp,			// app-ID 4
	&BatteryMonitorApp,		// app-ID 5
	&FreqmeterApp,			// app-ID 6
	&ExampleApp,			// app-ID 7
	&ExampleApp,			// app-ID 8
	&ExampleApp,			// app-ID 9
	&ExampleApp,			// app-ID 10
	&ExampleApp,			// app-ID 11
	&ExampleApp,			// app-ID 12
	&ExampleApp,			// app-ID 13
	&ExampleApp,			// app-ID 14
	&ExampleApp,			// app-ID 15
	&ExampleApp,			// app-ID 16
	&ExampleApp,			// app-ID 17
	&ExampleApp,			// app-ID 18
	&ExampleApp,			// app-ID 19
	&ExampleApp,			// app-ID 20
	&ExampleApp,			// app-ID 21
	&ExampleApp,			// app-ID 22
	&ExampleApp,			// app-ID 23
	&ExampleApp,			// app-ID 24
	&ExampleApp,			// app-ID 25
	&ExampleApp,			// app-ID 26
	&ExampleApp,			// app-ID 27
	&ExampleApp,			// app-ID 28
	&ExampleApp,			// app-ID 29
	&ExampleApp,			// app-ID 30
//	&DisplayApp			// app-ID 31 ResetApp
	&DownloadApp			// app-ID 31 ResetApp
					// This app is called after a system reset (NULL -> no app is called)
};

#endif /* APP_REGISTRY_H_ */
