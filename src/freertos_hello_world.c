/*
    Copyright (C) 2017 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
    Copyright (c) 2012 - 2022 Xilinx, Inc. All Rights Reserved.
	SPDX-License-Identifier: MIT


    http://www.FreeRTOS.org
    http://aws.amazon.com/freertos


    1 tab == 4 spaces!
*/

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
/* Xilinx includes. */
#include "xil_printf.h"
#include "xparameters.h"
#include "semphr.h"

#define TIMER_ID	1
#define DELAY_10_SECONDS	10000UL
#define DELAY_1_SECOND		1000UL
#define TIMER_CHECK_THRESHOLD	10
/*-----------------------------------------------------------*/

/* The Tx and Rx tasks as described at the top of this file. */
static void prvTxTask( void *pvParameters );
static void prvRxTask( void *pvParameters );
static void test1(void *pvParameters);
static void test2(void *pvParameters);
static void vTimerCallback( TimerHandle_t pxTimer );
/*-----------------------------------------------------------*/

/* The queue used by the Tx and Rx tasks, as described at the top of this
file. */
static TaskHandle_t xTxTask;
static TaskHandle_t xRxTask;
static TaskHandle_t test1handle;
static TaskHandle_t test2handle;
static QueueHandle_t xQueue = NULL;
static TimerHandle_t xTimer = NULL;
char HWstring[15] = "Hello World";
long RxtaskCntr = 0;

xSemaphoreHandle xSemaphore1 = NULL;
xSemaphoreHandle xSemaphore2 = NULL;

#if (configSUPPORT_STATIC_ALLOCATION == 1)
#define QUEUE_BUFFER_SIZE		100

uint8_t ucQueueStorageArea[ QUEUE_BUFFER_SIZE ];
StackType_t xStack1[ configMINIMAL_STACK_SIZE ];
StackType_t xStack2[ configMINIMAL_STACK_SIZE ];
StaticTask_t xTxBuffer,xRxBuffer;
StaticTimer_t xTimerBuffer;
static StaticQueue_t xStaticQueue;
#endif

int main( void )
{
	const TickType_t x10seconds = pdMS_TO_TICKS( DELAY_10_SECONDS );

	xil_printf( "Hello from Freertos example main\r\n" );

#if ( configSUPPORT_STATIC_ALLOCATION == 0 ) /* Normal or standard use case */
	/* Create the two tasks.  The Tx task is given a lower priority than the
	Rx task, so the Rx task will leave the Blocked state and pre-empt the Tx
	task as soon as the Tx task places an item in the queue. */
	xTaskCreate( 	prvTxTask, 					/* The function that implements the task. */
					( const char * ) "Tx", 		/* Text name for the task, provided to assist debugging only. */
					configMINIMAL_STACK_SIZE, 	/* The stack allocated to the task. */
					NULL, 						/* The task parameter is not used, so set to NULL. */
					tskIDLE_PRIORITY,			/* The task runs at the idle priority. */
					&xTxTask );

	xTaskCreate( test1,
					 ( const char * ) "test1",
					 configMINIMAL_STACK_SIZE,
					 NULL,
					 tskIDLE_PRIORITY,
					 &test1handle );

	xTaskCreate( test2,
					 ( const char * ) "test2",
					 configMINIMAL_STACK_SIZE,
					 NULL,
					 tskIDLE_PRIORITY,
					 &test2handle );

//	xTaskCreate( prvRxTask,
//					 ( const char * ) "GB",
//					 configMINIMAL_STACK_SIZE,
//					 NULL,
//					 tskIDLE_PRIORITY + 3,
//					 &xRxTask );

//	xTaskCreate( prvRxTask,
//					 ( const char * ) "test",
//					 configMINIMAL_STACK_SIZE,
//					 NULL,
//					 tskIDLE_PRIORITY + 2,
//					 &xRxTask );

	/* Create the queue used by the tasks.  The Rx task has a higher priority
	than the Tx task, so will preempt the Tx task and remove values from the
	queue as soon as the Tx task writes to the queue - therefore the queue can
	never have more than one item in it. */
	xQueue = xQueueCreate( 	1,						/* There is only one space in the queue. */
							sizeof( HWstring ) );	/* Each space in the queue is large enough to hold a uint32_t. */

	/* Check the queue was created. */
	configASSERT( xQueue );

	/* Create a timer with a timer expiry of 10 seconds. The timer would expire
	 after 10 seconds and the timer call back would get called. In the timer call back
	 checks are done to ensure that the tasks have been running properly till then.
	 The tasks are deleted in the timer call back and a message is printed to convey that
	 the example has run successfully.
	 The timer expiry is set to 10 seconds and the timer set to not auto reload. */
	xTimer = xTimerCreate( (const char *) "Timer",
							x10seconds,
							pdFALSE,
							(void *) TIMER_ID,
							vTimerCallback);
	/* Check the timer was created. */
	configASSERT( xTimer );

#else /* Use case where memories for tasks/queues/timers etc are provided statically by the users */
	xil_printf( "Using static memory for tasks, queue and timer creations. \r\n" );
	xTxTask = xTaskCreateStatic( 	prvTxTask, 				/* The function that implements the task. */
						( const char * ) "Tx", 					/* Text name for the task, provided to assist debugging only. */
						configMINIMAL_STACK_SIZE, 							/* The stack allocated to the task. */
						( void * ) NULL, 						/* The task parameter is not used, so set to NULL. */
						tskIDLE_PRIORITY,						/* The task runs at the idle priority. */
						xStack1,								/* Array to use the task's stack  */
						&xTxBuffer );               			/* variable to hold the task data structure */
	xRxTask =  xTaskCreateStatic( prvRxTask,
				 ( const char * ) "Rx",
				 configMINIMAL_STACK_SIZE,
				 ( void * ) NULL,
				 tskIDLE_PRIORITY + 1,
				 xStack2,
				 &xRxBuffer );

	xQueue = xQueueCreateStatic( 1,				/* Number of items in the queue. */
								sizeof( HWstring ),			/*size for each item to be stored in queue */
								ucQueueStorageArea,         /* Buffer to store the queue items*/
								&xStaticQueue);				/* Each space in the queue is large enough to hold a 1 byte. */
	/* Check the queue was created. */
	configASSERT( xQueue );
	xTimer = xTimerCreateStatic( (const char *) "Timer",
							x10seconds,
							pdFALSE,
							(void *) TIMER_ID,
							vTimerCallback,
							&xTimerBuffer);
	/* Check the timer was created. */
	configASSERT( xTimer );

#endif

	/* start the timer with a block time of 0 ticks. This means as soon
	   as the schedule starts the timer will start running and will expire after
	   10 seconds */
	xTimerStart( xTimer, 0 );

	/* Start the tasks and timer running. */
	vTaskStartScheduler();

	/* If all is well, the scheduler will now be running, and the following line
	will never be reached.  If the following line does execute, then there was
	insufficient FreeRTOS heap memory available for the idle and/or timer tasks
	to be created.  See the memory management section on the FreeRTOS web site
	for more details. */
	for( ;; );
}


/*-----------------------------------------------------------*/
static void prvTxTask( void *pvParameters )
{
//const TickType_t x1second = pdMS_TO_TICKS( DELAY_1_SECOND );


//		/* Delay for 1 second. */
	while(xSemaphore1 == NULL && xSemaphore2 == NULL)
		taskYIELD();
//
//		/* Send the next value on the queue.  The queue should always be
//		empty at this point so a block time of 0 is used. */
//		xQueueSend( xQueue,			/* The queue being written to. */
//					HWstring, /* The address of the data being sent. */
//					0UL );			/* The block time. */

	xil_printf("%s\r\n", pcTaskGetName(xQueueGetMutexHolder(xSemaphore1)));
	xil_printf("%s\r\n", pcTaskGetName(xQueueGetMutexHolder(xSemaphore2)));
}

/*-----------------------------------------------------------*/
static void test1(void *pvParameters){
	xSemaphore1 = xSemaphoreCreateMutex();
	xSemaphoreTake( xSemaphore1, ( TickType_t ) 10 );
	while(xSemaphore2 == NULL)
		taskYIELD();
	xSemaphoreTake( xSemaphore2, ( TickType_t ) portMAX_DELAY );
}

static void test2(void *pvParameters){
	xSemaphore2 = xSemaphoreCreateMutex();
	xSemaphoreTake( xSemaphore2, ( TickType_t ) 10 );
	while(xSemaphore1 == NULL)
			taskYIELD();
	xSemaphoreTake( xSemaphore1, ( TickType_t ) portMAX_DELAY );
}

static void prvRxTask( void *pvParameters )
{
char Recdstring[15] = "";

	for( ;; )
	{
		/* Block to wait for data arriving on the queue. */
		xQueueReceive( 	xQueue,				/* The queue being read. */
						Recdstring,	/* Data is read into this address. */
						portMAX_DELAY );	/* Wait without a timeout for data. */

		//xil_printf("test");
		//char test[15] = "Tx";

		/* Print the received data. */
		//xil_printf( "Task: %s\r\n", test );
		//xil_printf( "State: %d\r\n", eTaskGetState(xTaskGetHandle("Tx")) );

		TaskStatus_t *pxTaskStatusArray;
		volatile UBaseType_t uxArraySize, x;
		configRUN_TIME_COUNTER_TYPE ulTotalRunTime, ulStatsAsPercentage;

		// Take a snapshot of the number of tasks in case it changes while this
		// function is executing.
		uxArraySize = uxTaskGetNumberOfTasks();

		// Allocate a TaskStatus_t structure for each task.  An array could be
		// allocated statically at compile time.
		pxTaskStatusArray = pvPortMalloc( uxArraySize * sizeof( TaskStatus_t ) );

		if( pxTaskStatusArray != NULL )
		{
			// Generate raw status information about each task.
			uxArraySize = uxTaskGetSystemState( pxTaskStatusArray, uxArraySize, &ulTotalRunTime );

			// For percentage calculations.
			//ulTotalRunTime /= 100UL;

			// Avoid divide by zero errors.
			//if( ulTotalRunTime > 0 )
			//{
			// For each populated position in the pxTaskStatusArray array,
			// format the raw data as human readable ASCII data
			for( x = 0; x < uxArraySize; x++ )
			{
				// What percentage of the total run time has the task used?
				// This will always be rounded down to the nearest integer.
				// ulTotalRunTimeDiv100 has already been divided by 100.
				//ulStatsAsPercentage = pxTaskStatusArray[ x ].ulRunTimeCounter / ulTotalRunTime;

//						if( ulStatsAsPercentage > 0UL )
//						{
//							sprintf( pcWriteBuffer, "%s\t\t%lu\t\t%lu%%\r\n", pxTaskStatusArray[ x ].pcTaskName, pxTaskStatusArray[ x ].ulRunTimeCounter, ulStatsAsPercentage );
//						}
//						else
//						{
//							// If the percentage is zero here then the task has
//							// consumed less than 1% of the total run time.
//							sprintf( pcWriteBuffer, "%s\t\t%lu\t\t<1%%\r\n", pxTaskStatusArray[ x ].pcTaskName, pxTaskStatusArray[ x ].ulRunTimeCounter );
//						}

				xil_printf( "Handle: %d\n", pxTaskStatusArray[ x ].xHandle);
				xil_printf( "Task: %s\n", pxTaskStatusArray[ x ].pcTaskName);
				xil_printf( "Number: %d\n", pxTaskStatusArray[ x ].xTaskNumber);
				xil_printf( "State: %d\n", pxTaskStatusArray[ x ].eCurrentState);
				xil_printf( "Current Priority: %d\n", pxTaskStatusArray[ x ].uxCurrentPriority);
				xil_printf( "Base Priority: %d\n", pxTaskStatusArray[ x ].uxBasePriority);
				xil_printf( "Runtime Counter: %d\n", pxTaskStatusArray[ x ].ulRunTimeCounter);
				xil_printf( "Stack Space Remaining: %d\n\n", pxTaskStatusArray[ x ].usStackHighWaterMark);

				//pcWriteBuffer += strlen( ( char * ) pcWriteBuffer );
			}
			//}

		    // The array is no longer needed, free the memory it consumes.
			vPortFree( pxTaskStatusArray );
		}

//		TaskHandle_t xHandle;
//		TaskStatus_t xTaskDetails;
//
//		// Obtain the handle of a task from its name.
//		xHandle = xTaskGetHandle( "Tx" );
//
//		// Check the handle is not NULL.
//		configASSERT( xHandle );
//
//		// Use the handle to obtain further information about the task.
//		vTaskGetInfo( xHandle,
//		              &xTaskDetails,
//		              pdTRUE, // Include the high water mark in xTaskDetails.
//		              eInvalid ); // Include the task state in xTaskDetails.
//		xil_printf( "Handle: %d\n", xTaskDetails.xHandle);
//		xil_printf( "Task: %s\n", xTaskDetails.pcTaskName);
//		xil_printf( "Number: %d\n", xTaskDetails.xTaskNumber);
//		xil_printf( "State: %d\n", xTaskDetails.eCurrentState);
//		xil_printf( "Current Priority: %d\n", xTaskDetails.uxCurrentPriority);
//		xil_printf( "Base Priority: %d\n", xTaskDetails.uxBasePriority);
//		xil_printf( "Runtime Counter: %d\n", xTaskDetails.ulRunTimeCounter);
//		xil_printf( "Stack Space Remaining: %d\n\n", xTaskDetails.usStackHighWaterMark);

		xil_printf("%s\n", xQueueGetMutexHolder(xQueue));

		RxtaskCntr=10;
		break;
	}
}

/*-----------------------------------------------------------*/
static void vTimerCallback( TimerHandle_t pxTimer )
{
	long lTimerId;
	configASSERT( pxTimer );

	lTimerId = ( long ) pvTimerGetTimerID( pxTimer );

	if (lTimerId != TIMER_ID) {
		xil_printf("FreeRTOS Hello World Example FAILED");
	}

	/* If the RxtaskCntr is updated every time the Rx task is called. The
	 Rx task is called every time the Tx task sends a message. The Tx task
	 sends a message every 1 second.
	 The timer expires after 10 seconds. We expect the RxtaskCntr to at least
	 have a value of 9 (TIMER_CHECK_THRESHOLD) when the timer expires. */
	if (RxtaskCntr >= TIMER_CHECK_THRESHOLD) {
		xil_printf("Successfully ran FreeRTOS Hello World Example");
	} else {
		xil_printf("FreeRTOS Hello World Example FAILED");
	}

	vTaskDelete( xRxTask );
	vTaskDelete( xTxTask );
}

