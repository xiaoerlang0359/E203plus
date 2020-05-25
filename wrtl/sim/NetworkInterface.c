// See LICENSE for license details.
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "FreeRTOS_IP.h"
#include "FreeRTOS_Sockets.h"
#include "FreeRTOS_IP_Private.h"
#include "FreeRTOS_DNS.h"
#include "NetworkBufferManagement.h"
#include "NetworkInterface.h"


#define GIE 0x100507f8
#define TX_PING_LEN 0x100507f4
#define TX_PING_CON 0x100507fc
#define TX_BASE 0x10050000;
#define RX_BASE 0x10051000;
#define RX_PING_CON 0x100517fc
#define MDIO_ADDR 0x100507e4
#define MDIO_WR 0x100507e8
#define MDIO_RD 0x100507ec
#define MDIO_CTRL 0x100507f0
#define configEMAC_TASK_STACK_SIZE 3*configMINIMAL_STACK_SIZE

static volatile uint32_t *p;
static int i;
static volatile uint32_t pan;

static TaskHandle_t xEMACTaskHandle = NULL;

static const TickType_t localportMAX_DELAY = pdMS_TO_TICKS( 100UL );

// Structures for registering different interrupt handlers
// for different parts of the application.

uint16_t ReceiveSize(){
	uint32_t reg;
	uint16_t lengthtype;
	p = (uint32_t *)RX_BASE;
	p = p+3;
	reg = *p;
	lengthtype = (uint16_t) ((reg>>16) & 0x0000ffff);
	lengthtype = (uint16_t) (((lengthtype & 0xFF00) >> 8) | ((lengthtype & 0x00FF) << 8));
	if (lengthtype > 1200)
		return 1214;
	else
		return (lengthtype+14);

}

static void prvEMACHandlerTask( void *pvParameters )
{
NetworkBufferDescriptor_t *pxBufferDescriptor;
size_t xBytesReceived;
/* Used to indicate that xSendEventStructToIPTask() is being called because
of an Ethernet receive event. */
IPStackEvent_t xRxEvent;
uint8_t *emac_rx_buffer=NULL;

    for( ;; )
    {
        /* Wait for the Ethernet MAC interrupt to indicate that another packet
        has been received.  The task notification is used in a similar way to a
        counting semaphore to count Rx events, but is a lot more efficient than
        a semaphore. */
        ulTaskNotifyTake( pdFALSE, localportMAX_DELAY );

        /* See how much data was received.  Here it is assumed ReceiveSize() is
        a peripheral driver function that returns the number of bytes in the
        received Ethernet frame. */
        xBytesReceived = ReceiveSize(); //TODO: complete ReceiveSize()

        if( xBytesReceived > 0 )
        {
            /* Allocate a network buffer descriptor that points to a buffer
            large enough to hold the received frame.  As this is the simple
            rather than efficient example the received data will just be copied
            into this buffer. */
            pxBufferDescriptor = pxGetNetworkBufferWithDescriptor( xBytesReceived, 0 );

            if( pxBufferDescriptor != NULL )
            {
                /* pxBufferDescriptor->pucEthernetBuffer now points to an Ethernet
                buffer large enough to hold the received data.  Copy the
                received data into pcNetworkBuffer->pucEthernetBuffer.  Here it
                is assumed ReceiveData() is a peripheral driver function that
                copies the received data into a buffer passed in as the function¡¯s
                parameter.  Remember! While is is a simple robust technique ¨C
                it is not efficient.  An example that uses a zero copy technique
                is provided further down this page. */
            	emac_rx_buffer= (uint8_t*)RX_BASE;
            	memcpy(pxBufferDescriptor->pucEthernetBuffer,emac_rx_buffer,xBytesReceived);
                pxBufferDescriptor->xDataLength = xBytesReceived;
                p=(uint32_t*)RX_PING_CON;
                *p=8;
                /* See if the data contained in the received Ethernet frame needs
                to be processed.  NOTE! It is preferable to do this in
                the interrupt service routine itself, which would remove the need
                to unblock this task for packets that don¡¯t need processing. */
                if( eConsiderFrameForProcessing( pxBufferDescriptor->pucEthernetBuffer )
                                                                      == eProcessBuffer )
                {
                    /* The event about to be sent to the TCP/IP is an Rx event. */
                    xRxEvent.eEventType = eNetworkRxEvent;

                    /* pvData is used to point to the network buffer descriptor that
                    now references the received data. */
                    xRxEvent.pvData = ( void * ) pxBufferDescriptor;

                    /* Send the data to the TCP/IP stack. */
                    if( xSendEventStructToIPTask( &xRxEvent, 0 ) == pdFALSE )
                    {
                        /* The buffer could not be sent to the IP task so the buffer
                        must be released. */
                        vReleaseNetworkBufferAndDescriptor( pxBufferDescriptor );

                        /* Make a call to the standard trace macro to log the
                        occurrence. */
                        iptraceETHERNET_RX_EVENT_LOST();
                    }
                    else
                    {
                        /* The message was successfully sent to the TCP/IP stack.
                        Call the standard trace macro to log the occurrence. */
                        iptraceNETWORK_INTERFACE_RECEIVE();
                    }
                }
                else
                {
                    /* The Ethernet frame can be dropped, but the Ethernet buffer
                    must be released. */
                    vReleaseNetworkBufferAndDescriptor( pxBufferDescriptor );
                }
            }
            else
            {
                /* The event was lost because a network buffer was not available.
                Call the standard trace macro to log the occurrence. */
                iptraceETHERNET_RX_EVENT_LOST();
            }
        }
    }
}


BaseType_t xNetworkInterfaceInitialise(void){
	uint8_t * tx_pr;
	p = (uint32_t*)MDIO_CTRL;
	*p |= 0x08;
	pan = *p;
	while ((pan & 0x01)==0x01){
		pan = *p;
	}
	//////////////////////////////////////////
	p = (uint32_t*)MDIO_ADDR;
	*p = 0x0024;
	p =(uint32_t*) MDIO_WR;
	*p = 0x0061;
	p = (uint32_t*)MDIO_CTRL;
	*p = 9;
	pan = *p;
	while ((pan & 0x01) == 0x01){
		pan = *p;
	}
	/////////////////////////////////////////
	//////////////////////////////////////////
	p = (uint32_t*)MDIO_ADDR;
	*p = 0x0020;
	p =(uint32_t*) MDIO_WR;
	*p = 0x1200;
	p = (uint32_t*)MDIO_CTRL;
	*p = 9;
	pan = *p;
	while ((pan & 0x01) == 0x01){
		pan = *p;
	}
	/////////////////////////////////////////
	while ((pan & 0x20)==0x20){
		p = (uint32_t*)MDIO_ADDR;
		*p = 0x0421;
		p = (uint32_t*)MDIO_CTRL;
		*p = 9;
		pan = *p;
		while ((pan & 0x01) == 0x01){
			pan = *p;
		}
		p = (uint32_t*)MDIO_RD;
		pan = *p;
	}

	tx_pr = (uint8_t*)TX_BASE;
	*tx_pr = 0x00;
	tx_pr++;
	*tx_pr = 0x11;
	tx_pr++;
	*tx_pr = 0x22;
	tx_pr++;
	*tx_pr = 0x33;
	tx_pr++;
	*tx_pr = 0x44;
	tx_pr++;
	*tx_pr = 0x46;
	p = (uint32_t*)TX_PING_CON;
	*p = 0x03;
	pan = *p;
	while ((pan & 0x01) == 0x01){
		pan = *p;
	}
	p=(uint32_t*)GIE;
	*p=0x80000000;

	p=(uint32_t*)RX_PING_CON;
	*p=0x08;

	/*static BaseType_t state = pdFALSE;
	if(state == pdFALSE){
		state = xTaskCreate( prvEMACHandlerTask, "EMAC", configEMAC_TASK_STACK_SIZE, NULL, configMAX_PRIORITIES - 1, &xEMACTaskHandle );
	}*/
	return pdPASS;
}

BaseType_t xNetworkInterfaceOutput (NetworkBufferDescriptor_t * const pxDescriptor, BaseType_t xReleaseAfterSend){
	uint8_t * sendbuffer;
	sendbuffer = (uint8_t*)TX_BASE;
	memcpy(sendbuffer, pxDescriptor->pucEthernetBuffer, pxDescriptor->xDataLength);
	p = (uint32_t*)TX_PING_LEN;
	*p = pxDescriptor->xDataLength;
	p = (uint32_t*)TX_PING_CON;
	*p=0x01;
	pan = *p;
	while ((pan & 0x01)  == 0x01){
		pan=*p;
	};
	iptraceNETWORK_INTERFACE_TRANSMIT();
	if( xReleaseAfterSend != pdFALSE )
	{
	        /* It is assumed SendData() copies the data out of the FreeRTOS+TCP Ethernet
	        buffer.  The Ethernet buffer is therefore no longer needed, and must be
	        freed for re-use. */
	        vReleaseNetworkBufferAndDescriptor( pxDescriptor );
	}
	return pdPASS;
}

void emac_rv_handler(void){
	p=(uint32_t*)RX_PING_CON;
	if ((*p & 0x01)==1){
		BaseType_t xHigherPriorityTaskWoken = pdFALSE;
		if( xEMACTaskHandle != NULL )
		{
			vTaskNotifyGiveFromISR( xEMACTaskHandle, &xHigherPriorityTaskWoken );
			portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
		}
	}
}


//	clear_csr(mie, MIP_MEIP);
//	clear_csr(mie, MIP_MTIP);
//	register_plic_irqs();

	  // Enable the Machine-External bit in MIE
//	set_csr(mie, MIP_MEIP);
	  // Enable the Machine-Timer bit in MIE
//	set_csr(mie, MIP_MTIP);
	  // Enable interrupts in general.
//	set_csr(mstatus, MSTATUS_MIE);





