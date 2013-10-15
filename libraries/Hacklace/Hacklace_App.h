/*
 * Hacklace_App.h
 *
 */ 

/**********************************************************************************

Description:		Abstract base class for Hacklace apps.

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


#ifndef HACKLACE_APP_H_
#define HACKLACE_APP_H_


/*************
 * constants *
 *************/


/*********
 * class *
 *********/

class Hacklace_App
{
	public:
		// pure virtual methods
		virtual const unsigned char* setup(const unsigned char* ee) = 0;
		virtual void run() = 0;
		virtual void finish() = 0;
};


#endif /* HACKLACE_APP_H_ */
