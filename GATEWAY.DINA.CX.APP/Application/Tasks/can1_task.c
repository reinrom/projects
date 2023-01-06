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
 * File Name    : can1_task.c
 * Version      : 
 * Description  : 
 * Creation Date: Nov 30, 2022
 * Author		: KarimHmidi
 *********************************************************************/

/*
 *
 * Includes
 *
 *********************************************************************/
#include "cmsis_os.h"
#include "tasks_defs.h"
#include "typedefs.h"
#include "stm32h7xx.h"
#include <stdio.h>
#include <string.h>

/*
 *
 * Defines
 *
 **********************************************************************/
#define CAN2_ZMV_SIMULATION 1



/*
 *
 * Variable defines
 *
 **********************************************************************/

osThreadId_t can1TaskHandle;
const osThreadAttr_t can1Task_attributes = {
  .name = "can1Task",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

extern FDCAN_HandleTypeDef hfdcan1;
FDCAN_FilterTypeDef sFilterConfig_1 = {};
FDCAN_TxHeaderTypeDef TxHeader_1 = {};
FDCAN_RxHeaderTypeDef RxHeader_1 = {};
uint8_t TxData_1[8] = {0};
uint8_t RxData_1[8] = {0};
uint32_t msgerror_1 = 0;
uint32_t index1 = 0;
uint32_t TxID2 = 0x788;

extern ZMV_CAN_FRAME_Rx_U zmv_rx;

/*
 *
 * Typedefs
 *
 **********************************************************************/

/**
  *
  * CAN1 Rx Callback
  *
  ********************************************************************/

void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs)
{
	if(RESET != (RxFifo0ITs & FDCAN_IT_RX_FIFO0_NEW_MESSAGE))
	{
		//
		// Retrieve Rx messages from RX FIFO0
		//
		if (HAL_OK != HAL_FDCAN_GetRxMessage(hfdcan, FDCAN_RX_FIFO0, &RxHeader_1, RxData_1))
		{
			//
			// Error TODO:
			//
		}
		else
		{
//			switch (RxHeader_1.Identifier)
//			{
//			case 0x788:
//				memcpy(zmv_rx.data.designer.dina_std, &RxData_1, sizeof zmv_rx.data.designer.dina_std);
//				break;
//
//			case 0x789:
//				memcpy(zmv_rx.data.error.dina_err, &RxData_1, sizeof zmv_rx.data.error.dina_err);
//				break;
//
//			case 0x78A:
//				memcpy(zmv_rx.data.encoder_1.all, &RxData_1, sizeof zmv_rx.data.encoder_1.all);
//				break;
//
//			case 0x78B:
//				memcpy(zmv_rx.data.encoder_2.all, &RxData_1, sizeof zmv_rx.data.encoder_2.all);
//				break;
//
//			case 0x78C:
//				memcpy(zmv_rx.data.encoder_3.all, &RxData_1, sizeof zmv_rx.data.encoder_3.all);
//				break;
//
//			case 0x78D:
//				memcpy(zmv_rx.data.encoder_4.all, &RxData_1, sizeof zmv_rx.data.encoder_4.all);
//				break;
//
//			case 0x78E:
//				memcpy(zmv_rx.data.encoder_5.all, &RxData_1, sizeof zmv_rx.data.encoder_5.all);
//				break;
//
//			case 0x78F:
//				memcpy(zmv_rx.data.encoder_6.all, &RxData_1, sizeof zmv_rx.data.encoder_6.all);
//				break;
//
//			default:
//				break;
//			}
		}

		//
		// Reactivate reception notification
		// TODO: Check if it is necessary to do so!
		//
		if (HAL_OK != HAL_FDCAN_ActivateNotification(hfdcan, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0))
		{
			//
			// Error TODO:
			//
		}
	}
}

/**
  *
  * @brief  Function implementing the can1Task thread.
  * @param  argument: Not used
  * @retval None
  *
  *********************************************************************/

void can1Task(void *argument)
{
	//
	// Configure reception filter to Rx FIFO 0
	// on FDCAN1 instances
	//
	sFilterConfig_1.IdType 			= FDCAN_STANDARD_ID;
	sFilterConfig_1.FilterIndex 	= 0;
	sFilterConfig_1.FilterType 		= FDCAN_FILTER_RANGE;//FDCAN_FILTER_MASK;
	sFilterConfig_1.FilterConfig 	= FDCAN_FILTER_TO_RXFIFO0;
	sFilterConfig_1.FilterID1 		= 0x788;
	sFilterConfig_1.FilterID2 		= 0x78F;
	sFilterConfig_1.RxBufferIndex 	= 0;

	if (HAL_OK != HAL_FDCAN_ConfigFilter(&hfdcan1, &sFilterConfig_1))
	{
		//
		// Error TODO:
		//
	}

	//
	// Activate reception notification
	// Necessary if interrupt is used
	//
	if (HAL_OK != HAL_FDCAN_ActivateNotification(&hfdcan1, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0))
	{
		//
		// Error TODO:
		//
	}

	//
	// Prepare Tx message Header
	//
	TxHeader_1.Identifier 			= 0x78A;
	TxHeader_1.IdType 				= FDCAN_STANDARD_ID;
	TxHeader_1.TxFrameType 			= FDCAN_DATA_FRAME;
	TxHeader_1.DataLength 			= FDCAN_DLC_BYTES_8;
	TxHeader_1.ErrorStateIndicator 	= FDCAN_ESI_ACTIVE;
	TxHeader_1.BitRateSwitch 		= FDCAN_BRS_OFF;
	TxHeader_1.FDFormat 			= FDCAN_CLASSIC_CAN; //FDCAN_FD_CAN;
	TxHeader_1.TxEventFifoControl 	= FDCAN_NO_TX_EVENTS;
	TxHeader_1.MessageMarker 		= 0;

	//
	// Start the FDCAN module
	// on FDCAN1 instance
	//
	if (HAL_OK != HAL_FDCAN_Start(&hfdcan1))
	{
		//
		// Error TODO:
		//
	}

	osDelay(1000);

	uint8_t xxx = 0;

	//
	// Infinite loop
	//
	for (;;)
	{
#if CAN2_ZMV_SIMULATION

		memset(TxData_1, xxx, sizeof TxData_1);
		xxx++;

		switch (TxID2)
		{
		case 0x788:
			TxHeader_1.Identifier = TxID2;
			TxID2++;
			break;

		case 0x789:
			TxHeader_1.Identifier = TxID2;
			TxID2++;
			break;

		case 0x78A:
			TxHeader_1.Identifier = TxID2;
			TxID2++;
			break;

		case 0x78B:
			TxHeader_1.Identifier = TxID2;
			TxID2++;
			break;

		case 0x78C:
			TxHeader_1.Identifier = TxID2;
			TxID2++;
			break;

		case 0x78D:
			TxHeader_1.Identifier = TxID2;
			TxID2++;
			break;

		case 0x78E:
			TxHeader_1.Identifier = TxID2;
			TxID2++;
			break;

		case 0x78F:
			TxHeader_1.Identifier = TxID2;
			TxID2++;
			break;

		default:
			TxID2 = 0x788;
			TxHeader_1.Identifier = TxID2;
			break;
		}
#else
		for (int i = 0; i < 8; i++)
		{
			TxData_1[i] = xxx;
			xxx++;
		}
#endif
		//
		// Add message to TX FIFO
		// of FDCAN instance 1
		//
		if (HAL_OK != HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &TxHeader_1, TxData_1))
		{
			//
			// Error TODO:
			//
			msgerror_1++;
		}

		osDelay(100);
	}
}
