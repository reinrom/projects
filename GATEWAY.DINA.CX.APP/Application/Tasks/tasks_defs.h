/********************************************************************
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *********************************************************************
 *********************************************************************
 * File Name    : tasks_defs.h
 * Version      : 
 * Description  : 
 * Creation Date: Nov 30, 2022
 * Author		: KarimHmidi
 *********************************************************************/

#ifndef TASKS_TASKS_DEFS_H_
#define TASKS_TASKS_DEFS_H_

/*
 *
 * Includes
 *
 *********************************************************************/
//#include "cmsis_os.h"

/*
 *
 * Defines
 *
 **********************************************************************/

/* Definitions for dinaCxTask */
extern osThreadId_t dinaCxTaskHandle;
extern const osThreadAttr_t dianCxTask_attributes;

/* Definitions for can1Task */
extern osThreadId_t can1TaskHandle;
extern const osThreadAttr_t can1Task_attributes;

/* Definitions for can2Task */
extern osThreadId_t can2TaskHandle;
extern const osThreadAttr_t can2Task_attributes;

/*
 *
 * Typedefs
 *
 **********************************************************************/

/*
 *
 * Prototypes defines
 *
 **********************************************************************/
void dinaCxTask(void *argument);
void can1Task(void *argument);
void can2Task(void *argument);


#endif /* TASKS_TASKS_DEFS_H_ */
