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
#include "HL_DownloadApp.h"
#include "HL_DummyApp.h"
#include "HL_WifiDisplayApp.h"

// make the app_registry globally available
extern const Hacklace_App* const app_registry[MAX_APPS];

// list of all apps
const Hacklace_App* const app_registry[MAX_APPS] PROGMEM = {
	&DummyApp,				// 0
	&DummyApp,				// 1
	&DummyApp,				// 2
	&DummyApp,				// 3
	&DummyApp,				// 4
	&DummyApp,				// 5
	&DummyApp,				// 6
	&DummyApp,				// 7
	&DummyApp,				// 8
	&DummyApp,				// 9
	&DummyApp,				// 10
	&DummyApp,				// 11
	&DummyApp,				// 12
	&DummyApp,				// 13
	&DummyApp,				// 14
	&DummyApp,				// 15
	&DummyApp,				// 16
	&DummyApp,				// 17
	&DummyApp,				// 18
	&DummyApp,				// 19
	&DummyApp,				// 20
	&DummyApp,				// 21
	&DummyApp,				// 22
	&DummyApp,				// 23
	&DummyApp,				// 24
	&DummyApp,				// 25
	&DummyApp,				// 26
	&DummyApp,				// 27
	&DummyApp,				// 28
	&DummyApp,				// 29
	&DummyApp,				// 30
	&WifiDisplayApp,	// 31 SerialDisplayApp
										// This app is called after a system reset (NULL -> no app is called)
};

#endif /* APP_REGISTRY_H_ */
