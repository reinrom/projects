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
 * File Name    : can2_task.c
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
#include "../Common/typedefs.h"
#include "stm32h7xx.h"
#include <stdio.h>
#include <string.h>

/*
 *
 * Defines
 *
 **********************************************************************/
#define CAN_ZMV_SIMULATION 0



/*
 *
 * Variable defines
 *
 **********************************************************************/

osThreadId_t can2TaskHandle;
const osThreadAttr_t can2Task_attributes = {
  .name = "can2Task",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

ZMV_CAN_FRAME_Rx_U zmv_rx = {}; // TODO: Create a mailbox/queue for transmission

extern FDCAN_HandleTypeDef hfdcan2;
FDCAN_FilterTypeDef sFilterConfig_2 = {};
FDCAN_TxHeaderTypeDef TxHeader_2 = {};
FDCAN_RxHeaderTypeDef RxHeader_2 = {};
uint8_t TxData_2[8] = {0};
uint8_t RxData_2[8] = {0};
uint32_t msgerror_2 = 0;
uint32_t TxID = 0x788;


/*
 *
 * Typedefs
 *
 **********************************************************************/

/**
  *
  * CAN2 Rx Callback
  *
  * @note 	This callback is not used in this case
  *			The Rx buffer will be polled
  *
  ********************************************************************/

//void HAL_FDCAN_RxFifo1Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo1ITs)
//{
//	if(RESET != (RxFifo1ITs & FDCAN_IT_RX_FIFO1_NEW_MESSAGE))
//	{
//		//
//		// Retrieve Rx messages from RX FIFO1
//		//
//		if (HAL_OK != HAL_FDCAN_GetRxMessage(hfdcan, FDCAN_RX_FIFO1, &RxHeader_2, RxData_2))
//		{
//
//			msgerror_2++;
//		}
//		else
//		{
//			switch (RxHeader_2.Identifier)
//			{
//			case 0x788:
//				memcpy(zmv_rx.data.designer.dina_std, &RxData_2, sizeof zmv_rx.data.designer.dina_std);
//				break;
//
//			case 0x789:
//				memcpy(zmv_rx.data.error.dina_err, &RxData_2, sizeof zmv_rx.data.error.dina_err);
//				break;
//
//			case 0x78A:
//				memcpy(zmv_rx.data.encoder_1.all, &RxData_2, sizeof zmv_rx.data.encoder_1.all);
//				break;
//
//			case 0x78B:
//				memcpy(zmv_rx.data.encoder_2.all, &RxData_2, sizeof zmv_rx.data.encoder_2.all);
//				break;
//
//			case 0x78C:
//				memcpy(zmv_rx.data.encoder_3.all, &RxData_2, sizeof zmv_rx.data.encoder_3.all);
//				break;
//
//			case 0x78D:
//				memcpy(zmv_rx.data.encoder_4.all, &RxData_2, sizeof zmv_rx.data.encoder_4.all);
//				break;
//
//			case 0x78E:
//				memcpy(zmv_rx.data.encoder_5.all, &RxData_2, sizeof zmv_rx.data.encoder_5.all);
//				break;
//
//			case 0x78F:
//				memcpy(zmv_rx.data.encoder_6.all, &RxData_2, sizeof zmv_rx.data.encoder_6.all);
//				break;
//
//			default:
//				break;
//			}
//		}
//
//		//
//		// Reactivate reception notification
//		// TODO: Check if it is necessary to do so!
//		//
//		if (HAL_OK != HAL_FDCAN_ActivateNotification(hfdcan, FDCAN_IT_RX_FIFO1_NEW_MESSAGE, 0))
//		{
//
//		}
//	}
//}


/**
  *
  * @brief  Function implementing the can2Task thread.
  * @param  argument: Not used
  * @retval None
  *
  *********************************************************************/

void can2Task(void *argument)
{

//	hfdcan2.Init.MessageRAMOffset = sizeof(hfdcan1);

	//
	// Configure reception filter to Rx FIFO 0
	// on FDCAN1 instance
	//
	sFilterConfig_2.IdType 			= FDCAN_STANDARD_ID;
	sFilterConfig_2.FilterIndex 	= 0;
	sFilterConfig_2.FilterType 		= FDCAN_FILTER_RANGE;
	sFilterConfig_2.FilterConfig 	= FDCAN_FILTER_TO_RXFIFO1;
	sFilterConfig_2.FilterID1 		= 0x788;
	sFilterConfig_2.FilterID2 		= 0x78F;
	sFilterConfig_2.RxBufferIndex 	= 0;

	if (HAL_OK != HAL_FDCAN_ConfigFilter(&hfdcan2, &sFilterConfig_2))
	{
		//
		// Error TODO:
		//
	}

	//
	// Activate reception notification.
	// Necessary if interrupt is used
	//
	if (HAL_OK != HAL_FDCAN_ActivateNotification(&hfdcan2, FDCAN_IT_RX_FIFO1_NEW_MESSAGE, 0))
	{
		//
		// Error TODO:
		//
	}

	//
	// Prepare Tx message Header
	//
	TxHeader_2.Identifier 			= 0x790;
	TxHeader_2.IdType 				= FDCAN_STANDARD_ID;
	TxHeader_2.TxFrameType 			= FDCAN_DATA_FRAME;
	TxHeader_2.DataLength 			= FDCAN_DLC_BYTES_8;
	TxHeader_2.ErrorStateIndicator 	= FDCAN_ESI_ACTIVE;
	TxHeader_2.BitRateSwitch 		= FDCAN_BRS_OFF;
	TxHeader_2.FDFormat 			= FDCAN_CLASSIC_CAN; // FDCAN_FD_CAN;
	TxHeader_2.TxEventFifoControl 	= FDCAN_NO_TX_EVENTS;
	TxHeader_2.MessageMarker 		= 0;

	//
	// Start the FDCAN module
	// on FDCAN1 instance
	//
	if (HAL_OK != HAL_FDCAN_Start(&hfdcan2))
	{
		//
		// Error TODO:
		//
	}

	osDelay(1000);

#if CAN_ZMV_SIMULATION
	uint8_t yyy = 0;
#endif

	//
	// Infinite loop
	//
	for (;;)
	{
#if CAN_ZMV_SIMULATION
//		for (int i = 0; i < 8; i++)
//		{
//			TxData_2[i] = yyy;
//		}
		memset(TxData_2, yyy, sizeof TxData_2);
		yyy++;

		switch (TxID)
		{
		case 0x788:
			TxHeader_2.Identifier = TxID;
			TxID++;
			break;

		case 0x789:
			TxHeader_2.Identifier = TxID;
			TxID++;
			break;

		case 0x78A:
			TxHeader_2.Identifier = TxID;
			TxID++;
			break;

		case 0x78B:
			TxHeader_2.Identifier = TxID;
			TxID++;
			break;

		case 0x78C:
			TxHeader_2.Identifier = TxID;
			TxID++;
			break;

		case 0x78D:
			TxHeader_2.Identifier = TxID;
			TxID++;
			break;

		case 0x78E:
			TxHeader_2.Identifier = TxID;
			TxID++;
			break;

		case 0x78F:
			TxHeader_2.Identifier = TxID;
			TxID++;
			break;

		default:
			TxID = 0x788;
			TxHeader_2.Identifier = TxID;
			break;
		}

		//
		// Add message to TX FIFO
		// of FDCAN instance 2
		//
		if (HAL_OK != HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan2, &TxHeader_2, TxData_2))
		{
			//
			// Error TODO:
			//
			msgerror_2++;
		}

		osDelay(20);
#else
		//
		// Retrieve Rx messages from RX FIFO01
		// Polling mode
		//
		if (HAL_OK != HAL_FDCAN_GetRxMessage(&hfdcan2, FDCAN_RX_FIFO1, &RxHeader_2, RxData_2))
		{
			//
			// Error TODO:
			//
			msgerror_2++;
		}
		else
		{
			switch (RxHeader_2.Identifier)
			{
			case 0x788:
				memcpy(zmv_rx.data.designer.dina_std, &RxData_2, sizeof zmv_rx.data.designer.dina_std);
				break;

			case 0x789:
				memcpy(zmv_rx.data.error.dina_err, &RxData_2, sizeof zmv_rx.data.error.dina_err);
				break;

			case 0x78A:
				memcpy(zmv_rx.data.encoder_1.all, &RxData_2, sizeof zmv_rx.data.encoder_1.all);
				break;

			case 0x78B:
				memcpy(zmv_rx.data.encoder_2.all, &RxData_2, sizeof zmv_rx.data.encoder_2.all);
				break;

			case 0x78C:
				memcpy(zmv_rx.data.encoder_3.all, &RxData_2, sizeof zmv_rx.data.encoder_3.all);
				break;

			case 0x78D:
				memcpy(zmv_rx.data.encoder_4.all, &RxData_2, sizeof zmv_rx.data.encoder_4.all);
				break;

			case 0x78E:
				memcpy(zmv_rx.data.encoder_5.all, &RxData_2, sizeof zmv_rx.data.encoder_5.all);
				break;

			case 0x78F:
				memcpy(zmv_rx.data.encoder_6.all, &RxData_2, sizeof zmv_rx.data.encoder_6.all);
				break;

			default:
				break;
			}
		}

		//
		// Reactivate reception notification
		// TODO: Check if it is necessary to do so!
		//
		if (HAL_OK != HAL_FDCAN_ActivateNotification(&hfdcan2, FDCAN_IT_RX_FIFO1_NEW_MESSAGE, 0))
		{

		}

		osDelay(5);
#endif
	}
}




