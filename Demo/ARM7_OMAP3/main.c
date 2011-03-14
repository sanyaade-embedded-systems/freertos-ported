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
	NOTE : Tasks run in system mode and the scheduler runs in Supervisor mode.
	The processor MUST be in supervisor mode when vTaskStartScheduler is 
	called.  The demo applications included in the FreeRTOS.org download switch
	to supervisor mode prior to main being called.  If you are not using one of
	these demo application projects then ensure Supervisor mode is used.
*/


/*
 * Creates all the demo application tasks, then starts the scheduler.  The WEB
 * documentation provides more details of the demo application tasks.
 * 
 * Main.c also creates a task called "Check".  This only executes every three 
 * seconds but has the highest priority so is guaranteed to get processor time.  
 * Its main function is to check that all the other tasks are still operational.
 * Each task (other than the "flash" tasks) maintains a unique count that is 
 * incremented each time the task successfully completes its function.  Should 
 * any error occur within such a task the count is permanently halted.  The 
 * check task inspects the count of each task to ensure it has changed since
 * the last time the check task executed.  If all the count variables have 
 * changed all the tasks are still executing error free, and the check task
 * toggles the onboard LED.  Should any task contain an error at any time 
 * the LED toggle rate will change from 3 seconds to 500ms.
 *
 * To check the operation of the memory allocator the check task also 
 * dynamically creates a task before delaying, and deletes it again when it 
 * wakes.  If memory cannot be allocated for the new task the call to xTaskCreate
 * will fail and an error is signalled.  The dynamically created task itself
 * allocates and frees memory just to give the allocator a bit more exercise.
 *
 */

/* 
	Changes from V2.4.2

	+ The vErrorChecks() task now dynamically creates then deletes a task each
	  cycle.  This tests the operation of the memory allocator.

	Changes from V2.5.2
		
	+ vParTestInitialise() is called during initialisation to ensure all the 
	  LED's start off.
*/


/* Standard includes. */
#include <stdlib.h>
#include <string.h>

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"

/* Demo application includes. */
#include "partest.h"
#include "flash.h"
#include "integer.h"
#include "PollQ.h"
#include "comtest2.h"
#include "semtest.h"
#include "flop.h"
#include "dynamic.h"
#include "BlockQ.h"
//#include "serial.h"

/*-----------------------------------------------------------*/

/* Constants to setup I/O. */
#define mainTX_ENABLE	( ( unsigned long ) 0x0001 )
#define mainRX_ENABLE	( ( unsigned long ) 0x0004 )
#define mainP0_14		( ( unsigned long ) 0x4000 )
#define mainJTAG_PORT	( ( unsigned long ) 0x3E0000UL )

/* Constants to setup the PLL. */
#define mainPLL_MUL_4		( ( unsigned char ) 0x0003 )
#define mainPLL_DIV_1		( ( unsigned char ) 0x0000 )
#define mainPLL_ENABLE		( ( unsigned char ) 0x0001 )
#define mainPLL_CONNECT		( ( unsigned char ) 0x0003 )
#define mainPLL_FEED_BYTE1	( ( unsigned char ) 0xaa )
#define mainPLL_FEED_BYTE2	( ( unsigned char ) 0x55 )
#define mainPLL_LOCK		( ( unsigned long ) 0x0400 )

/* Constants to setup the MAM. */
#define mainMAM_TIM_3		( ( unsigned char ) 0x03 )
#define mainMAM_MODE_FULL	( ( unsigned char ) 0x02 )

/* Constants to setup the peripheral bus. */
#define mainBUS_CLK_FULL	( ( unsigned char ) 0x01 )

/* Constants for the ComTest tasks. */
#define mainCOM_TEST_BAUD_RATE	( ( unsigned long ) 115200 )
#define mainCOM_TEST_LED		( 3 )

/* Priorities for the demo application tasks. */
#define mainLED_TASK_PRIORITY		( tskIDLE_PRIORITY + 3 )
#define mainCOM_TEST_PRIORITY		( tskIDLE_PRIORITY + 2 )
#define mainQUEUE_POLL_PRIORITY		( tskIDLE_PRIORITY + 0 )
#define mainCHECK_TASK_PRIORITY		( tskIDLE_PRIORITY + 4 )
#define mainSEM_TEST_PRIORITY		( tskIDLE_PRIORITY + 0 )
#define mainBLOCK_Q_PRIORITY		( tskIDLE_PRIORITY + 2 )

/* The rate at which the on board LED will toggle when there is/is not an 
error. */
#define mainNO_ERROR_FLASH_PERIOD	( ( portTickType ) 3000 / portTICK_RATE_MS  )
#define mainERROR_FLASH_PERIOD		( ( portTickType ) 500 / portTICK_RATE_MS  )
#define mainON_BOARD_LED_BIT		( ( unsigned long ) 0x80 )

/* Constants used by the vMemCheckTask() task. */
#define mainCOUNT_INITIAL_VALUE		( ( unsigned long ) 0 )
#define mainNO_TASK					( 0 )

/* The size of the memory blocks allocated by the vMemCheckTask() task. */
#define mainMEM_CHECK_SIZE_1		( ( size_t ) 51 )
#define mainMEM_CHECK_SIZE_2		( ( size_t ) 52 )
#define mainMEM_CHECK_SIZE_3		( ( size_t ) 151 )

/*-----------------------------------------------------------*/

static void prvSetupHardware( void );
static void setleds ( void );
/*-----------------------------------------------------------*/

/*
 * Starts all the other tasks, then starts the scheduler. 
 */
int main( void )
{
	/* Setup the hardware for use with the Olimex demo board. */
	prvSetupHardware();
	setleds();
	/* Should never reach here! */
	return 0;
}
/*-----------------------------------------------------------*/

static void prvSetupHardware( void )
{

	/* Initialize GPIOs */
	vParTestInitialise();
}
/*-----------------------------------------------------------*/

static void setleds ( void )
{
	unsigned int counter=0;
	int times=0;
	struct gpio *gpio5_base=(struct gpio *)GPIO5_BASE;
	gpio5_base->setdataout = PIN22|PIN21;
	while(times<10){
		for(counter=0;counter<0x2FFFF;counter++){}//delay
		counter=0;
		gpio5_base->setdataout = PIN21;
		for(counter=0;counter<0x2FFFF;counter++){}
		counter=0;
		gpio5_base->cleardataout = PIN22|PIN21;
		for(counter=0;counter<0x2FFFF;counter++){}
		counter=0;
		gpio5_base->setdataout = PIN22;
		for(counter=0;counter<0x2FFFF;counter++){}//delay
		counter=0;
		gpio5_base->cleardataout = PIN22|PIN21;
		times++;
	}
}
