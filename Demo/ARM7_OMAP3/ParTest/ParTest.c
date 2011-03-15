/*
    FreeRTOS V6.1.1 - Copyright (C) 2011 Real Time Engineers Ltd.

    ***************************************************************************
    *                                                                         *
    * If you are:                                                             *
    *                                                                         *
    *    + New to FreeRTOS,                                                   *
    *    + Wanting to learn FreeRTOS or multitasking in general quickly       *
    *    + Looking for basic training,                                        *
    *    + Wanting to improve your FreeRTOS skills and productivity           *
    *                                                                         *
    * then take a look at the FreeRTOS books - available as PDF or paperback  *
    *                                                                         *
    *        "Using the FreeRTOS Real Time Kernel - a Practical Guide"        *
    *                  http://www.FreeRTOS.org/Documentation                  *
    *                                                                         *
    * A pdf reference manual is also available.  Both are usually delivered   *
    * to your inbox within 20 minutes to two hours when purchased between 8am *
    * and 8pm GMT (although please allow up to 24 hours in case of            *
    * exceptional circumstances).  Thank you for your support!                *
    *                                                                         *
    ***************************************************************************

    This file is part of the FreeRTOS distribution.

    FreeRTOS is free software; you can redistribute it and/or modify it under
    the terms of the GNU General Public License (version 2) as published by the
    Free Software Foundation AND MODIFIED BY the FreeRTOS exception.
    ***NOTE*** The exception to the GPL is included to allow you to distribute
    a combined work that includes FreeRTOS without being obliged to provide the
    source code for proprietary components outside of the FreeRTOS kernel.
    FreeRTOS is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
    more details. You should have received a copy of the GNU General Public 
    License and the FreeRTOS license exception along with FreeRTOS; if not it 
    can be viewed here: http://www.freertos.org/a00114.html and also obtained 
    by writing to Richard Barry, contact details for whom are available on the
    FreeRTOS WEB site.

    1 tab == 4 spaces!

    http://www.FreeRTOS.org - Documentation, latest information, license and
    contact details.

    http://www.SafeRTOS.com - A version that is certified for use in safety
    critical systems.

    http://www.OpenRTOS.com - Commercial support, development, porting,
    licensing and training services.
*/

/*
	Changes from V2.5.2
		
	+ All LED's are turned off to start.
*/


#include "FreeRTOS.h"
#include "partest.h"
#include <stdlib.h>

#define partstNUM_LEDS			( 2 )
#define partstALL_OUTPUTS_OFF	( ( unsigned long ) 0xffffffff )

/*-----------------------------------------------------------
 * Simple parallel port IO routines.
 *-----------------------------------------------------------*/

void vParTestInitialise( void )
{
	struct gpio *gpio5_base = (struct gpio *)GPIO5_BASE;
	struct gpio *gpio6_base = (struct gpio *)GPIO6_BASE;

	/* GPIO5: 31,30,29,28,22,21,15,14,13,12
	 * GPIO6: 23,10,08,02,01 */
	gpio5_base->oe=~(PIN31|PIN30|PIN29|PIN28|PIN22|PIN21|PIN15|PIN14|PIN13|PIN12);
	gpio6_base->oe=~(PIN23|PIN10|PIN8|PIN2|PIN1);

	/* Free Memory */
	//free(gpio5_base);
	//free(gpio6_base);
}

void vParTestSetLED( unsigned portBASE_TYPE uxLED, signed portBASE_TYPE xValue )
{
	struct gpio *gpio5_base = (struct gpio *)GPIO5_BASE;
	unsigned long GPIO_PIN = 0;
	if( uxLED < partstNUM_LEDS){
		/* I define LED0 (GPIO_149) as 0
		 * and 	LED1 (GPIO_150) as 1 */
		switch(uxLED){
			case 0: GPIO_PIN=PIN21;break;
			case 1: GPIO_PIN=PIN22;break;
			default: break;
		};
		if ( xValue )
			gpio5_base->setdataout=GPIO_PIN;
		else
			gpio5_base->cleardataout=GPIO_PIN;
	}
	//free(gpio5_base);
}

void vParTestToggleLED( unsigned portBASE_TYPE uxLED )
{
	unsigned long ulCurrentState, mask=0, GPIO_PIN=0;
	struct gpio *gpio5_base = (struct gpio *)GPIO5_BASE;
	if( uxLED < partstNUM_LEDS )
	{
		/* Toggle LED Status
		 * LED0 = GPIO_149
		 * LED1 = GPIO_150 */
		switch(uxLED){
			case 0: GPIO_PIN=PIN21;break;
			case 1: GPIO_PIN=PIN22;break;
			default: break;
		};

		ulCurrentState = gpio5_base->datain;
		/* I have to ignore the rest of the bits */
		
		if ( ulCurrentState & uxLED )
			gpio5_base->cleardataout = GPIO_PIN;
		else
			gpio5_base->setdataout = GPIO_PIN;
	}
	//free(gpio5_base);
}
