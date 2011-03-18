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
#define mainON_BOARD_LED_BIT		PIN21
/* Constants used by the vMemCheckTask() task. */
#define mainCOUNT_INITIAL_VALUE		( ( unsigned long ) 0 )
#define mainNO_TASK					( 0 )

/* The size of the memory blocks allocated by the vMemCheckTask() task. */
#define mainMEM_CHECK_SIZE_1		( ( size_t ) 51 )
#define mainMEM_CHECK_SIZE_2		( ( size_t ) 52 )
#define mainMEM_CHECK_SIZE_3		( ( size_t ) 151 )

/*-----------------------------------------------------------*/

/*
 * Helper instructions
 */

inline unsigned int RegRead(unsigned int base, unsigned int regOffs);
inline void RegWrite(unsigned int base, unsigned int regOffs, unsigned int value);
inline unsigned int AddrRead(unsigned int base, unsigned int regOffs);
void dumpinterrupts ( void );

/*
 * The Beagleboard has 2 LEDS available on the GPIO module
 * I will use LED0 to express errors on tasks
 */

void prvToggleOnBoardLED( void );

/*
 * Configure the processor of use with the BeagleBoard
 * Currently I assume that U-boot has done all the work for us
 */
static void prvSetupHardware( void );

/* Demo application blinking the LEDS
 */
static void setleds ( void );
static void setinterrupts ( void );
/*
 * Checks that all the demo application tasks are still executing without error
 * - as described at the top of the file.
 */
static long prvCheckOtherTasksAreStillRunning( unsigned long ulMemCheckTaskCount );

/*
 * The task that executes at the highest priority and calls
 * prvCheckOtherTasksAreStillRunning(). See the description at the top
 * of the file
 */
static void vErrorChecks ( void *pvParameters );

/*
 * Dynamically created and deleteted during each cycle of the vErrorChecks()
 * task. This is done to check the operation of the memory allocator.
 * See the top of vErrorChecks for more details
 */
static void vMemCheckTask( void *pvParameters );


/*-----------------------------------------------------------*/

/*
 * Starts all the other tasks, then starts the scheduler. 
 */
int main( void )
{
	/* Setup the hardware for use with the Beableboard. */
	serial_newline();
	serial_putstring("Initializing the hardware...");
	
	prvSetupHardware();
	
	serial_putstring("OK");
	serial_newline();
	
	/* Start the demo/test application tasks. */
	serial_putstring("Starting demo tasks...");
	
	vStartIntegerMathTasks ( tskIDLE_PRIORITY );
	vStartLEDFlashTasks ( mainLED_TASK_PRIORITY );
	vStartPolledQueueTasks ( mainQUEUE_POLL_PRIORITY );
	vStartMathTasks ( tskIDLE_PRIORITY );
	vStartSemaphoreTasks( mainSEM_TEST_PRIORITY );
	vStartDynamicPriorityTasks();
	vStartBlockingQueueTasks( mainBLOCK_Q_PRIORITY );
	
	serial_putstring("OK");
	serial_newline();
	
	/* start the check task - which is defined in this file!. */
	serial_putstring("Starting ErrorChecks task...");
	
	xTaskCreate( vErrorChecks, ( signed char *) "Check", configMINIMAL_STACK_SIZE, NULL, mainCHECK_TASK_PRIORITY, NULL );
	
	serial_putstring("OK");
	serial_newline();
	/* Now all the tasks have been stared - start the scheduler.
	 * NOTE : Tasks run in system mode and the scheduler runs in Supervisor mode.
	 * Te processor MUST be in supervisor mode when vTaskStartScheduler is called.
	 * The demo applications included in the the FreeRTOS.og download swith to supervisor
	 * mode prior to main being called. If you are not using one of these demo application
	 * projects then ensure Supervisor mode is used here */
	/* Should never reach here! */
	
	serial_putstring("Starting the scheduler...");
	vTaskStartScheduler();
	serial_putstring("OK");
//	serial_newline();
//	setinterrupts();
//	setleds();
	return 0;
}
/*-----------------------------------------------------------*/

static void prvSetupHardware( void )
{

	/* Initialize GPIOs */
	vParTestInitialise();
}


/*---------------------------------------------------------*/

static void vErrorChecks( void *pvParameters )
{
	portTickType xDelayPeriod = mainNO_ERROR_FLASH_PERIOD;
	unsigned long ulMemCheckTaskRunningCount;
	xTaskHandle xCreatedTask;

	/* The parameters are not used in this function */
	( void ) pvParameters;
	/* Cycle for ever, delaying then checking all the other tasks are still
	 * operating without error. If an error is detected then the delay period
	 * is decreased from mainNO_ERROR_FLASH_PERIOD to mainERROR_FLASH_PERIOD
	 * so the LEDO flash rate will increase. In addition to the standard
	 * tests the memory allocator is tested through the dynamic creation and 
	 * deletion of a task each cycle. Each time the 
	 * task is created memory must be allocated for its stack. When the task
	 * is deleted this memory is returned to the heap. If the task cannot be
	 * created then it is likely that the memory allocation failed */

	for ( ;; )
	{
		/* Dynamically create a task - passing ulMemCheckTaskRunningCount
		 * as parameter */
		ulMemCheckTaskRunningCount = mainCOUNT_INITIAL_VALUE;
		xCreatedTask = mainNO_TASK;

		if( xTaskCreate( vMemCheckTask, ( signed char *) "MEM_CHECK", configMINIMAL_STACK_SIZE, ( void * ) &ulMemCheckTaskRunningCount, tskIDLE_PRIORITY, &xCreatedTask) != pdPASS ){
			/* Could not create the task - we have probably run out of heap. */
			xDelayPeriod = mainERROR_FLASH_PERIOD;
		}
		/* Delay untl it is time to execute again. */
		vTaskDelay ( xDelayPeriod );

		/* Delete the dynamically created task. */
		if( xCreatedTask != mainNO_TASK )
			vTaskDelete( xCreatedTask );
		
		/* Check all the standard demo application tasks are executing without error.
		 * ulMemCheckTaskRunningCount is checked to ensure it was modified by the task
		 * just deleted */
		if (prvCheckOtherTasksAreStillRunning( ulMemCheckTaskRunningCount ) != pdPASS)
			xDelayPeriod = mainERROR_FLASH_PERIOD;
		prvToggleOnBoardLED();
	}
}
/*----------------------------------------------------------------------------------------*/

void prvToggleOnBoardLED( void )
{
	/* Toggle LED0 */
	unsigned long ulState;
	struct gpio *gpio5_base=(struct gpio *)GPIO5_BASE;
	ulState = gpio5_base->datain;
	if( ulState & mainON_BOARD_LED_BIT )
		gpio5_base->setdataout=mainON_BOARD_LED_BIT;
	else
		gpio5_base->cleardataout=mainON_BOARD_LED_BIT;
}
/*-----------------------------------------------------------------------------------------*/

static long prvCheckOtherTasksAreStillRunning( unsigned long ulMemCheckTaskCount )
{
long lReturn = ( long ) pdPASS;

	/* Check all the demo tasks (other than the flash tasks) to ensure
	that they are all still running, and that none of them have detected
	an error. */

	if( xAreIntegerMathsTaskStillRunning() != pdTRUE )
	{
		lReturn = ( long ) pdFAIL;
	}

	/*if( xAreComTestTasksStillRunning() != pdTRUE )
	{
		lReturn = ( long ) pdFAIL;
	}*/

	if( xArePollingQueuesStillRunning() != pdTRUE )
	{
		lReturn = ( long ) pdFAIL;
	}

	if( xAreMathsTaskStillRunning() != pdTRUE )
	{
		lReturn = ( long ) pdFAIL;
	}

	if( xAreSemaphoreTasksStillRunning() != pdTRUE )
	{
		lReturn = ( long ) pdFAIL;
	}

	if( xAreDynamicPriorityTasksStillRunning() != pdTRUE )
	{
		lReturn = ( long ) pdFAIL;
	}

	if( xAreBlockingQueuesStillRunning() != pdTRUE )
	{
		lReturn = ( long ) pdFAIL;
	}

	if( ulMemCheckTaskCount == mainCOUNT_INITIAL_VALUE )
	{
		/* The vMemCheckTask did not increment the counter - it must
		have failed. */
		lReturn = ( long ) pdFAIL;
	}

	return lReturn;
}
/*--------------------------------------------------------------------------*/

static void vMemCheckTask( void *pvParameters )
{
	unsigned long *pulMemCheckTaskRunningCounter;
	void *pvMem1, *pvMem2, *pvMem3;
	static long lErrorOccurred = pdFALSE;

	/* This task is dynamically created then deleted during each cycle of the
	vErrorChecks task to check the operation of the memory allocator.  Each time
	the task is created memory is allocated for the stack and TCB.  Each time
	the task is deleted this memory is returned to the heap.  This task itself
	exercises the allocator by allocating and freeing blocks. 
	
	The task executes at the idle priority so does not require a delay. 
	
	pulMemCheckTaskRunningCounter is incremented each cycle to indicate to the
	vErrorChecks() task that this task is still executing without error. */

	pulMemCheckTaskRunningCounter = ( unsigned long * ) pvParameters;

	for( ;; )
	{
		if( lErrorOccurred == pdFALSE )
		{
			/* We have never seen an error so increment the counter. */
			( *pulMemCheckTaskRunningCounter )++;
		}

		/* Allocate some memory - just to give the allocator some extra 
		exercise.  This has to be in a critical section to ensure the
		task does not get deleted while it has memory allocated. */
		vTaskSuspendAll();
		{
			pvMem1 = pvPortMalloc( mainMEM_CHECK_SIZE_1 );
			if( pvMem1 == NULL )
			{
				lErrorOccurred = pdTRUE;
			}
			else
			{
				memset( pvMem1, 0xaa, mainMEM_CHECK_SIZE_1 );
				vPortFree( pvMem1 );
			}
		}
		xTaskResumeAll();

		/* Again - with a different size block. */
		vTaskSuspendAll();
		{
			pvMem2 = pvPortMalloc( mainMEM_CHECK_SIZE_2 );
			if( pvMem2 == NULL )
			{
				lErrorOccurred = pdTRUE;
			}
			else
			{
				memset( pvMem2, 0xaa, mainMEM_CHECK_SIZE_2 );
				vPortFree( pvMem2 );
			}
		}
		xTaskResumeAll();

		/* Again - with a different size block. */
		vTaskSuspendAll();
		{
			pvMem3 = pvPortMalloc( mainMEM_CHECK_SIZE_3 );
			if( pvMem3 == NULL )
			{
				lErrorOccurred = pdTRUE;
			}
			else
			{
				memset( pvMem3, 0xaa, mainMEM_CHECK_SIZE_3 );
				vPortFree( pvMem3 );
			}
		}
		xTaskResumeAll();
	}
}


static void setleds ( void )
{
	unsigned int counter=0;
	int times=0;
	RegWrite(GPIO5_BASE,GPIO_SETDATAOUT,PIN22|PIN21);
	while(times<1000){
		for(counter=0;counter<0x2FFFF;counter++){}//delay
		counter=0;
		//serial_putstring("Current IRQ: ");
		//serial_putstring(*pointer);
		//serial_newline();
		RegWrite(GPIO5_BASE,GPIO_SETDATAOUT,PIN21);
		for(counter=0;counter<0x2FFFF;counter++){}
		counter=0;
		RegWrite(GPIO5_BASE,GPIO_CLEARDATAOUT,PIN22|PIN21);
		for(counter=0;counter<0x2FFFF;counter++){}
		counter=0;
		RegWrite(GPIO5_BASE,GPIO_SETDATAOUT,PIN22);
		for(counter=0;counter<0x2FFFF;counter++){}//delay
		counter=0;
		RegWrite(GPIO5_BASE,GPIO_CLEARDATAOUT,PIN22|PIN21);
		times++;
	}
}

static void setinterrupts( void ){
	serial_newline();
	serial_putstring("Setting up the timer interrupt...");
	
	unsigned long ulCompareMatch;
	extern void ( vTickISR )( void );
	//struct gptimer *gptimer1 = (struct gptimer *)GPT1;
	//struct InterruptController *intc = (struct InterruptController *)MPU_INTC;
	extern void ( vTckISR )( void );

	/* Setup interrupt handler */
	E_IRQ = ( long ) vTickISR;
	
	/* Enable IRQ 37 - bit 5 */
	RegWrite(MPU_INTC,INTCPS_SYSCONFIG,0x00000003);
	RegWrite(MPU_INTC,INTCPS_IDLE,0x00000001);
	RegWrite(MPU_INTC,INTCPS_ISR_SET1,0x00000020);
	RegWrite(MPU_INTC,INTCPS_MIR1,~(0x00000020));
	RegWrite(MPU_INTC,INTCPS_ILSR37,0x0);
	dumpinterrupts();
	serial_putstring("OK");
	
	serial_newline();
	serial_putstring("Setting up the timer values...");
	
	/* Calculate the match value required for our wanted tick rate */
	ulCompareMatch = configCPU_CLOCK_HZ / configTICK_RATE_HZ;
	
	/* Protect against divide by zero */
	#if portPRESCALE_VALUE != 0
		ulCompareMatch /= ( portPRESCALE_VALUE +1 );
	#endif
	/* The timer must be in compare mode, and should be the value
	 * holded in ulCompareMatch
	 * bit 0=1 -> enable timer
	 * bit 1=1 -> autoreload
	 * bit 6=1 -> compare mode
	 * The source is 32Khz
	 * */
	RegWrite(GPTI1,GPTI_TLDR,0);
	RegWrite(GPTI1,GPTI_TCRR,0);
	RegWrite(GPTI1,GPTI_TMAR,0x31111111); // load match value
	RegWrite(GPTI1,GPTI_TIER,0x1); //enable match interrupt
	
	serial_putstring("OK");
	__asm volatile (
		"STMDB	SP!, {R0}		\n\t"
		"MRS	R0, CPSR		\n\t"
		"BIC	R0, R0, #0xC0		\n\t"
		"MSR	CPSR, R0		\n\t"
		"LDMIA	SP!, {R0}		\n\t"
	);

	//gptimer1->tclr = 0x00000043;	// start timer
	RegWrite(GPTI1,GPTI_TCLR,0x00000043);
}

void dumpinterrupts( void ){
	serial_newline();
	serial_putstring("***Interrupt Dump (Memory)***");
	serial_newline();
	serial_newline();
	serial_putstring("SysConfig:0x ");
	serial_putint(RegRead(MPU_INTC,INTCPS_SYSCONFIG));
	serial_newline();
	serial_putstring("SysStatus:0x");
	serial_putint(RegRead(MPU_INTC,INTCPS_SYSSTATUS));
	serial_newline();
	serial_putstring("SirIRQ:0x");
	serial_putint(RegRead(MPU_INTC,INTCPS_SIR_IRQ));
	serial_newline();
	serial_putstring("SirFIQ:0x");
	serial_putint(RegRead(MPU_INTC,INTCPS_SIR_FIQ));
	serial_newline();
	serial_putstring("Control:0x");
	serial_putint(RegRead(MPU_INTC,INTCPS_CONTROL));
	serial_newline();
	serial_putstring("Protection:0x");
	serial_putint(RegRead(MPU_INTC,INTCPS_PROTECTION));
	serial_newline();
	serial_putstring("Idle:0x");
	serial_putint(RegRead(MPU_INTC,INTCPS_IDLE));
	serial_newline();
	serial_putstring("IrqPriority:0x");
	serial_putint(RegRead(MPU_INTC,INTCPS_IRQ_PRIORITY));
	serial_newline();
	serial_putstring("FiqPriority:0x");
	serial_putint(RegRead(MPU_INTC,INTCPS_FIQ_PRIORITY));
	serial_newline();
	serial_putstring("Threshold:0x");
	serial_putint(RegRead(MPU_INTC,INTCPS_THRESHOLD));
	serial_newline();
	serial_putstring("ITR1:0x");
	serial_putint(RegRead(MPU_INTC,INTCPS_ITR1));
	serial_newline();
	serial_putstring("MIR1:0x");
	serial_putint(RegRead(MPU_INTC,INTCPS_MIR1));
	serial_newline();
	serial_putstring("ILR37:0x");
	serial_putint(RegRead(MPU_INTC,INTCPS_ILSR37));
	serial_newline();

}



inline unsigned int RegRead(unsigned int base, unsigned int regOffs)
{
 	volatile unsigned int * regPtr = (unsigned int *)(base | regOffs);
	return *regPtr;
}

inline void RegWrite(unsigned int base, unsigned int regOffs, unsigned int value)
{
	volatile unsigned int * regPtr = (unsigned int*)(base | regOffs);
	*regPtr = value;
}

inline unsigned int AddrRead(unsigned int base, unsigned int regOffs){
	return (base|regOffs);
}
