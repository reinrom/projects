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
 * File Name    : dina_cx_task.c
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
#include "lwip/udp.h"
#include <string.h>

/*
 *
 * Defines
 *
 **********************************************************************/

/*
 *
 * Variable defines
 *
 **********************************************************************/

osThreadId_t dinaCxTaskHandle;
const osThreadAttr_t dianCxTask_attributes = {
  .name = "dianCxTask",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

extern ZMV_CAN_FRAME_Rx_U zmv_rx;

/*
 *
 * Typedefs
 *
 **********************************************************************/

/**
  *
  * @brief  Function implementing the dinaCxTask thread.
  * @param  argument: Not used
  * @retval None
  *
  *********************************************************************/

void dinaCxTask(void *argument)
{
	DINA_TO_LJU_CYCLIC_FRAME_Tx_U udp_tx = {};

	udp_tx.data.addr_dina 				= 100;
	udp_tx.data.addr_lju 				= 123;
	udp_tx.data.message_id				= 0x2;
	udp_tx.data.message_cnt.always_one 	= 1;
	udp_tx.data.frame_crc.byte.LB 		= 123; // TODO: Calculate the CRC of the frame

	osDelay(100);

	ip_addr_t PC_IPADDR;
	IP_ADDR4(&PC_IPADDR, 192, 168, 100, 123);

	struct udp_pcb* my_udp = udp_new();
	udp_connect(my_udp, &PC_IPADDR, 55151);
	struct pbuf* udp_buffer = NULL;

	//
	// Infinite loop
	//
	for (;;)
	{
		//
		// Encoder 1
		//
		udp_tx.data.encoder_1.position.byte.LB 	= zmv_rx.data.encoder_1.byte.pos_LSB;
		udp_tx.data.encoder_1.position.byte.MB 	= zmv_rx.data.encoder_1.byte.pos_MLB;
		udp_tx.data.encoder_1.position.byte.HB 	= zmv_rx.data.encoder_1.byte.pos_MHB;
		//
		udp_tx.data.encoder_1.speed.byte.LB 	= zmv_rx.data.encoder_1.byte.speed_LSB;
		udp_tx.data.encoder_1.speed.byte.HB 	= zmv_rx.data.encoder_1.byte.speed_HSB;
		//
		udp_tx.data.encoder_1.status_1.all 		= zmv_rx.data.encoder_1.byte.status_1;
		udp_tx.data.encoder_1.status_2.all 		= zmv_rx.data.encoder_1.byte.status_2;

		//
		// Encoder 2
		//
		udp_tx.data.encoder_2.position.byte.LB 	= zmv_rx.data.encoder_2.byte.pos_LSB;
		udp_tx.data.encoder_2.position.byte.MB 	= zmv_rx.data.encoder_2.byte.pos_MLB;
		udp_tx.data.encoder_2.position.byte.HB 	= zmv_rx.data.encoder_2.byte.pos_MHB;
		//
		udp_tx.data.encoder_2.speed.byte.LB 	= zmv_rx.data.encoder_2.byte.speed_LSB;
		udp_tx.data.encoder_2.speed.byte.HB 	= zmv_rx.data.encoder_2.byte.speed_HSB;
		//
		udp_tx.data.encoder_2.status_1.all 		= zmv_rx.data.encoder_2.byte.status_1;
		udp_tx.data.encoder_2.status_2.all 		= zmv_rx.data.encoder_2.byte.status_2;

		//
		// Encoder 3
		//
		udp_tx.data.encoder_3.position.byte.LB 	= zmv_rx.data.encoder_3.byte.pos_LSB;
		udp_tx.data.encoder_3.position.byte.MB 	= zmv_rx.data.encoder_3.byte.pos_MLB;
		udp_tx.data.encoder_3.position.byte.HB 	= zmv_rx.data.encoder_3.byte.pos_MHB;
		//
		udp_tx.data.encoder_3.speed.byte.LB 	= zmv_rx.data.encoder_3.byte.speed_LSB;
		udp_tx.data.encoder_3.speed.byte.HB 	= zmv_rx.data.encoder_3.byte.speed_HSB;
		//
		udp_tx.data.encoder_3.status_1.all 		= zmv_rx.data.encoder_3.byte.status_1;
		udp_tx.data.encoder_3.status_2.all 		= zmv_rx.data.encoder_3.byte.status_2;

		//
		// Encoder 4
		//
		udp_tx.data.encoder_4.position.byte.LB 	= zmv_rx.data.encoder_4.byte.pos_LSB;
		udp_tx.data.encoder_4.position.byte.MB 	= zmv_rx.data.encoder_4.byte.pos_MLB;
		udp_tx.data.encoder_4.position.byte.HB 	= zmv_rx.data.encoder_4.byte.pos_MHB;
		//
		udp_tx.data.encoder_4.speed.byte.LB 	= zmv_rx.data.encoder_4.byte.speed_LSB;
		udp_tx.data.encoder_4.speed.byte.HB 	= zmv_rx.data.encoder_4.byte.speed_HSB;
		//
		udp_tx.data.encoder_4.status_1.all 		= zmv_rx.data.encoder_4.byte.status_1;
		udp_tx.data.encoder_4.status_2.all 		= zmv_rx.data.encoder_4.byte.status_2;

		//
		// Encoder 5
		//
		udp_tx.data.encoder_5.position.byte.LB 	= zmv_rx.data.encoder_5.byte.pos_LSB;
		udp_tx.data.encoder_5.position.byte.MB 	= zmv_rx.data.encoder_5.byte.pos_MLB;
		udp_tx.data.encoder_5.position.byte.HB 	= zmv_rx.data.encoder_5.byte.pos_MHB;
		//
		udp_tx.data.encoder_5.speed.byte.LB 	= zmv_rx.data.encoder_5.byte.speed_LSB;
		udp_tx.data.encoder_5.speed.byte.HB 	= zmv_rx.data.encoder_5.byte.speed_HSB;
		//
		udp_tx.data.encoder_5.status_1.all 		= zmv_rx.data.encoder_5.byte.status_1;
		udp_tx.data.encoder_5.status_2.all 		= zmv_rx.data.encoder_5.byte.status_2;

		//
		// Encoder 6
		//
		udp_tx.data.encoder_6.position.byte.LB 	= zmv_rx.data.encoder_6.byte.pos_LSB;
		udp_tx.data.encoder_6.position.byte.MB 	= zmv_rx.data.encoder_6.byte.pos_MLB;
		udp_tx.data.encoder_6.position.byte.HB 	= zmv_rx.data.encoder_6.byte.pos_MHB;
		//
		udp_tx.data.encoder_6.speed.byte.LB 	= zmv_rx.data.encoder_6.byte.speed_LSB;
		udp_tx.data.encoder_6.speed.byte.HB 	= zmv_rx.data.encoder_6.byte.speed_HSB;
		//
		udp_tx.data.encoder_6.status_1.all 		= zmv_rx.data.encoder_6.byte.status_1;
		udp_tx.data.encoder_6.status_2.all 		= zmv_rx.data.encoder_6.byte.status_2;

		//
		// TODO: This is only for test reasons
		//
//		memcpy(udp_tx.data.logic_data, zmv_rx.data.designer.dina_std, sizeof zmv_rx.data.designer.dina_std);

		//
		// Logic data dummy
		//
		memset(udp_tx.data.logic_data, 0xff, sizeof udp_tx.data.logic_data);


		//
		// !! PBUF_RAM is critical for correct operation
		//
//		udp_buffer = pbuf_alloc(PBUF_TRANSPORT, sizeof UDP_Tx, PBUF_RAM);
//		Or
		udp_buffer = pbuf_alloc(PBUF_TRANSPORT, sizeof udp_tx.frame, PBUF_RAM);

		if (udp_buffer != NULL)
		{
			//
			// Heart beat!
			//
			udp_tx.data.message_cnt.alive_cnt += 1;

//			memcpy(udp_buffer->payload, &udp_tx, sizeof udp_tx);
//			Or
			memcpy(udp_buffer->payload, &udp_tx.frame, sizeof udp_tx.frame);
			udp_send(my_udp, udp_buffer);
			pbuf_free(udp_buffer);
		}

		osDelay(20);
	}

}
