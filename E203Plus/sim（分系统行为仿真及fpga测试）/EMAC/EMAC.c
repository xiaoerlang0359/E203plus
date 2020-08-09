// See LICENSE for license details.
#include <stdio.h>

uint8_t message[72]={
		0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0xec,0xaf,0xec,
		0x00,0x3a,0xff,0xff,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,
		0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0x99,0x99,
		0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0x99,0x99,
		0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0x99,0x99,
		0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0x99,0x99
};
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
int main(void)
{
	int i;
	volatile uint32_t *p;
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
	printf("Hello World!" "\n");
	printf("Hello World!" "\n");
	printf("Hello World!" "\n");
	printf("Hello World!" "\n");
	printf("Hello World!" "\n");

	p=(uint32_t*)GIE;
	uint32_t * mess=(uint32_t*)message;
	*p=0x00000000;

	p=(uint32_t*)RX_PING_CON;
	*p=0x08;

	p=(uint32_t*)TX_BASE;
	for (i=0;i<18;i++){
		*(p+i) = *(mess+i);
	}
	p=(uint32_t*)TX_PING_CON;
	*p=0x13;
	pan=*p;
	while (((pan & 0x01)==0x01) || ((pan & 0x02)==0x02)){
		pan=*p;
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


//	printf("Hello World!" "\n");
//	printf("Hello World!" "\n");



	p=(uint32_t*)RX_PING_CON;
	pan = *p;
	while ((pan & 0x01) == 0x00){
		pan=*p;
	};
	printf("%x\n",pan);
	p=(uint32_t*)RX_BASE;
	for (i=0;i<20;i++){
		printf("%x ",*(p+i));
	}
	p=(uint32_t*)RX_PING_CON;
	*p=0;


	printf("Hello World!" "\n");
	printf("Hello World!" "\n");
	return 0;
}

