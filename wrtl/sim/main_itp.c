// See LICENSE for license details.
#include <stdio.h>
#include <stdlib.h>
#include "platform.h"
#include <string.h>
#include "plic/plic_driver.h"
#include "encoding.h"
#include <unistd.h>
#include "stdatomic.h"

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

volatile uint32_t *p;
int i;

// Structures for registering different interrupt handlers
// for different parts of the application.
typedef void (*function_ptr_t) (void);
void no_interrupt_handler (void) {};
function_ptr_t g_ext_interrupt_handlers[PLIC_NUM_INTERRUPTS];
plic_instance_t g_plic;

void handle_m_ext_interrupt(){
  plic_source int_num  = PLIC_claim_interrupt(&g_plic);
  if ((int_num >=1 ) && (int_num < PLIC_NUM_INTERRUPTS)) {
    g_ext_interrupt_handlers[int_num]();
  }
  else {
    exit(1 + (uintptr_t) int_num);
  }
  PLIC_complete_interrupt(&g_plic, int_num);
}

void handle_m_time_interrupt(){

  clear_csr(mie, MIP_MTIP);

  // Reset the timer for 3s in the future.
  // This also clears the existing timer interrupt.

  volatile uint64_t * mtime       = (uint64_t*) (CLINT_CTRL_ADDR + CLINT_MTIME);
  volatile uint64_t * mtimecmp    = (uint64_t*) (CLINT_CTRL_ADDR + CLINT_MTIMECMP);
  uint64_t now = *mtime;
  uint64_t then = now + 0.5 * RTC_FREQ;
  *mtimecmp = then;


  GPIO_REG(GPIO_OUTPUT_VAL) ^= (0x1 << RED_LED_GPIO_OFFSET);

  // Re-enable the timer interrupt.
  set_csr(mie, MIP_MTIP);
}

void emac_re_handler(void) {
	p=(uint32_t*)RX_PING_CON;
	if ((*p & 0x01)==1){
		p=(uint32_t*)RX_BASE;
		for (i=0;i<20;i++){
			printf("%x ",*(p+i));
		}
	}
	p=(uint32_t*)RX_PING_CON;
	*p=8;
};

void button_1_handler(void) {

  // Green LED On
  GPIO_REG(GPIO_RISE_IP) = (0x1 << BUTTON_1_GPIO_OFFSET);
  printf("handler1\n");
  __asm__ __volatile__(
		"fence"
		  :
		  :
		  :"memory"
  );

};

void register_plic_irqs (){

   /**************************************************************************
   * Set up the PLIC
   *
   *************************************************************************/
  PLIC_init(&g_plic,
	    PLIC_CTRL_ADDR,
	    PLIC_NUM_INTERRUPTS,
	    PLIC_NUM_PRIORITIES);


  for (int ii = 0; ii < PLIC_NUM_INTERRUPTS; ii ++){
    g_ext_interrupt_handlers[ii] = no_interrupt_handler;
  }

  g_ext_interrupt_handlers[PLIC_INT_EMAC_BASE] = emac_re_handler;
  g_ext_interrupt_handlers[PLIC_INT_DEVICE_BUTTON_1] = button_1_handler;

  PLIC_enable_interrupt (&g_plic, PLIC_INT_EMAC_BASE);
  PLIC_enable_interrupt (&g_plic, PLIC_INT_DEVICE_BUTTON_1);

  PLIC_set_priority(&g_plic, PLIC_INT_EMAC_BASE, 1);
  PLIC_set_priority(&g_plic, PLIC_INT_DEVICE_BUTTON_1, 1);

}

void setup_mtime (){

    // Set the machine timer to go off in 3 seconds.
    // The
    volatile uint64_t * mtime       = (uint64_t*) (CLINT_CTRL_ADDR + CLINT_MTIME);
    volatile uint64_t * mtimecmp    = (uint64_t*) (CLINT_CTRL_ADDR + CLINT_MTIMECMP);
    uint64_t now = *mtime;
    uint64_t then = now + 10 * RTC_FREQ;
    *mtimecmp = then;

}

uint8_t message[72]={
		0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0xec,0xaf,0xec,
		0x00,0x3a,0xff,0xff,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,
		0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0x99,0x99,
		0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0x99,0x99,
		0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0x99,0x99,
		0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0x99,0x99
};

int main(void)
{
	GPIO_REG(GPIO_PULLUP_EN)  &= ~((0x1 << BUTTON_1_GPIO_OFFSET));
	GPIO_REG(GPIO_INPUT_EN)   |=  ((0x1 << BUTTON_1_GPIO_OFFSET));
	GPIO_REG(GPIO_RISE_IE) |= (1 << BUTTON_1_GPIO_OFFSET);
	clear_csr(mie, MIP_MEIP);
	clear_csr(mie, MIP_MTIP);
	register_plic_irqs();

	//setup_mtime();

	  // Enable the Machine-External bit in MIE
	set_csr(mie, MIP_MEIP);
	  // Enable the Machine-Timer bit in MIE
//	set_csr(mie, MIP_MTIP);
	  // Enable interrupts in general.
	set_csr(mstatus, MSTATUS_MIE);
	volatile uint32_t pan;


	p = (uint32_t*)MDIO_RD;
	printf("%x\n", *p);
	p = (uint32_t*)MDIO_CTRL;
	*p |= 0x08;
	pan = *p;
	while ((pan & 0x01)==0x01){
		pan = *p;
	}
	p = (uint32_t*)MDIO_ADDR;
	*p = 0x0020;
	p =(uint32_t*) MDIO_WR;
	*p = 0x0100;
	p = (uint32_t*)MDIO_CTRL;
	*p = 9;
	pan = *p;
	while ((pan & 0x01) == 0x01){
		pan = *p;
	}
	p = (uint32_t*)MDIO_ADDR;
	*p = 0x0420;
	p = (uint32_t*)MDIO_CTRL;
	*p = 9;
	pan = *p;
	while ((pan & 0x01) == 0x01){
		pan = *p;
	}
	p = (uint32_t*)MDIO_RD;
	printf("%x\n", *p);

	printf("Hello World!" "\n");


	p=(uint32_t*)GIE;
	uint32_t * mess=(uint32_t*)message;
	*p=0x80000000;

	p=(uint32_t*)RX_PING_CON;
	*p=0x08;

	p=(uint32_t*)TX_BASE;
	for (i=0;i<18;i++){
		*(p+i) = *(mess+i);
	}

	p=(uint32_t*)TX_PING_LEN;
	*p=72;

	p=(uint32_t*)TX_BASE;
	for (i=0;i<18;i++){
		printf("%x ",*(p+i));
	}

	p=(uint32_t*)TX_PING_LEN;
	printf("%x\n",*p);

	p=(uint32_t*)TX_PING_CON;
	*p=0x11;

	pan = *p;
	while ((pan & 0x01)  == 0x01){
		pan=*p;
	};


	printf("Hello World!" "\n");
	printf("Hello World!" "\n");



//	p=(uint32_t*)RX_PING_CON;
//	pan = *p;
//	while ((pan & 0x01) == 0x00){
//		pan=*p;
//	};
//	printf("%x\n",pan);
//	p=(uint32_t*)RX_BASE;
//	for (i=0;i<20;i++){
//		printf("%x ",*(p+i));
//	}
//	p=(uint32_t*)RX_PING_CON;
//	*p=0;


	printf("Hello World!" "\n");
	printf("Hello World!" "\n");
	while(1){

	}
	return 0;
}

