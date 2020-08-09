// See LICENSE for license details.
#include <stdio.h>
#include <stdlib.h>
#include "platform.h"
#include <string.h>
#include "plic/plic_driver.h"
#include "encoding.h"
#include <unistd.h>
#include "stdatomic.h"

#define CH0 0
#define CH1 1
#define CH2 2
#define CH3 3
#define CH4 4
#define CH5 5
#define CH6 9
#define CH7 10
uint32_t button_0_value;
uint32_t button_1_value;
uint32_t button_2_value;
uint32_t input_value;
unsigned int sum;
int main(void)
{
	/*GPIO_REG(GPIO_OUTPUT_EN)  &= ~((0x1 << CH0) | (0x1 << CH1) | (0x1 << CH2) | (0x1 << CH3) | (0x1 << CH4) | (0x1 << CH5) | (0x1 << CH6) | (0x1 << CH7));
	GPIO_REG(GPIO_PULLUP_EN)  &= ~((0x1 << BUTTON_0_GPIO_OFFSET) | (0x1 << BUTTON_1_GPIO_OFFSET) | (0x1 << BUTTON_2_GPIO_OFFSET));
	GPIO_REG(GPIO_INPUT_EN)   |=  ((0x1 << BUTTON_0_GPIO_OFFSET) | (0x1 << BUTTON_1_GPIO_OFFSET) | (0x1 << BUTTON_2_GPIO_OFFSET));*/

	GPIO_REG(GPIO_INPUT_EN) &= ~((0x1 << CH0) | (0x1 << CH1) | (0x1 << CH2) | (0x1 << CH3) | (0x1 << CH4) | (0x1 << CH5) | (0x1 << CH6) | (0x1 << CH7));
	GPIO_REG(GPIO_OUTPUT_EN) |= ((0x1 << CH0) | (0x1 << CH1) | (0x1 << CH2) | (0x1 << CH3) | (0x1 << CH4) | (0x1 << CH5) | (0x1 << CH6) | (0x1 << CH7));
	GPIO_REG(GPIO_OUTPUT_VAL) |= ((0x1 << CH0) | (0x1 << CH1) | (0x1 << CH2) | (0x1 << CH3) | (0x1 << CH4) | (0x1 << CH5) | (0x1 << CH6) | (0x1 << CH7));
	GPIO_REG(GPIO_OUTPUT_VAL) &= ~((0x1 << CH0) | (0x1 << CH1) | (0x1 << CH2) | (0x1 << CH3) | (0x1 << CH4) | (0x1 << CH5) | (0x1 << CH6) | (0x1 << CH7));
	sum=0;
	while(1){
		///////////////////R///////////////////////////////
		GPIO_REG(GPIO_OUTPUT_VAL) |= ((0x1 << CH0) | (0x1 << CH1) | (0x1 << CH2) | (0x1 << CH3) | (0x1 << CH4) | (0x1 << CH5) | (0x1 << CH6) | (0x1 << CH7));
		for (int i=0;i<10;i++){
		}
		GPIO_REG(GPIO_OUTPUT_VAL) &= ~((0x1 << CH0) | (0x1 << CH1) | (0x1 << CH2) | (0x1 << CH3) | (0x1 << CH4) | (0x1 << CH5) | (0x1 << CH6) | (0x1 << CH7));
		for (int i=0;i<10;i++){
		}
		///////////////////////////////////
		GPIO_REG(GPIO_OUTPUT_VAL) |= ((0x1 << CH0) | (0x0 << CH1) | (0x0 << CH2) | (0x1 << CH3) | (0x1 << CH4) | (0x0 << CH5) | (0x0 << CH6) | (0x0 << CH7));
		for (int i=0;i<10;i++){
		}
		GPIO_REG(GPIO_OUTPUT_VAL) &= ~((0x1 << CH0) | (0x1 << CH1) | (0x1 << CH2) | (0x1 << CH3) | (0x1 << CH4) | (0x1 << CH5) | (0x1 << CH6) | (0x1 << CH7));
		for (int i=0;i<10;i++){
		}
		///////////////////////////////////
		GPIO_REG(GPIO_OUTPUT_VAL) |= ((0x1 << CH0) | (0x0 << CH1) | (0x0 << CH2) | (0x1 << CH3) | (0x0 << CH4) | (0x1 << CH5) | (0x0 << CH6) | (0x0 << CH7));
		for (int i=0;i<10;i++){
		}
		GPIO_REG(GPIO_OUTPUT_VAL) &= ~((0x1 << CH0) | (0x1 << CH1) | (0x1 << CH2) | (0x1 << CH3) | (0x1 << CH4) | (0x1 << CH5) | (0x1 << CH6) | (0x1 << CH7));
		for (int i=0;i<10;i++){
		}
		////////////////////////////////////
		GPIO_REG(GPIO_OUTPUT_VAL) |= ((0x0 << CH0) | (0x1 << CH1) | (0x1 << CH2) | (0x0 << CH3) | (0x0 << CH4) | (0x0 << CH5) | (0x1 << CH6) | (0x0 << CH7));
		for (int i=0;i<10;i++){
		}
		GPIO_REG(GPIO_OUTPUT_VAL) &= ~((0x1 << CH0) | (0x1 << CH1) | (0x1 << CH2) | (0x1 << CH3) | (0x1 << CH4) | (0x1 << CH5) | (0x1 << CH6) | (0x1 << CH7));
		for (int i=0;i<10;i++){
		}
		///////////////////////////////////
		GPIO_REG(GPIO_OUTPUT_VAL) |= ((0x0 << CH0) | (0x0 << CH1) | (0x0 << CH2) | (0x0 << CH3) | (0x0 << CH4) | (0x0 << CH5) | (0x0 << CH6) | (0x1 << CH7));
		for (int i=0;i<10;i++){
		}
		GPIO_REG(GPIO_OUTPUT_VAL) &= ~((0x1 << CH0) | (0x1 << CH1) | (0x1 << CH2) | (0x1 << CH3) | (0x1 << CH4) | (0x1 << CH5) | (0x1 << CH6) | (0x1 << CH7));
		for (int i=0;i<10;i++){
		}
		//////////////I/////////////////////
		for (int i=0;i<10;i++){
			sum++;
		}
		GPIO_REG(GPIO_OUTPUT_VAL) |= ((0x1 << CH0) | (0x1 << CH1) | (0x1 << CH2) | (0x1 << CH3) | (0x1 << CH4) | (0x1 << CH5) | (0x1 << CH6) | (0x1 << CH7));
		for (int i=0;i<10;i++){
		}
		GPIO_REG(GPIO_OUTPUT_VAL) &= ~((0x1 << CH0) | (0x1 << CH1) | (0x1 << CH2) | (0x1 << CH3) | (0x1 << CH4) | (0x1 << CH5) | (0x1 << CH6) | (0x1 << CH7));
		for (int i=0;i<10;i++){
		}
		////////////////S///////////////////
		for (int i=0;i<10;i++){
			sum++;
		}
		GPIO_REG(GPIO_OUTPUT_VAL) |= ((0x0 << CH0) | (0x0 << CH1) | (0x1 << CH2) | (0x0 << CH3) | (0x0 << CH4) | (0x0 << CH5) | (0x1 << CH6) | (0x0 << CH7));
		for (int i=0;i<10;i++){
		}
		GPIO_REG(GPIO_OUTPUT_VAL) &= ~((0x1 << CH0) | (0x1 << CH1) | (0x1 << CH2) | (0x1 << CH3) | (0x1 << CH4) | (0x1 << CH5) | (0x1 << CH6) | (0x1 << CH7));
		for (int i=0;i<10;i++){
		}
		///////////////////////////////////
		GPIO_REG(GPIO_OUTPUT_VAL) |= ((0x0 << CH0) | (0x1 << CH1) | (0x0 << CH2) | (0x1 << CH3) | (0x0 << CH4) | (0x0 << CH5) | (0x1 << CH6) | (0x0 << CH7));
		for (int i=0;i<10;i++){
		}
		GPIO_REG(GPIO_OUTPUT_VAL) &= ~((0x1 << CH0) | (0x1 << CH1) | (0x1 << CH2) | (0x1 << CH3) | (0x1 << CH4) | (0x1 << CH5) | (0x1 << CH6) | (0x1 << CH7));
		for (int i=0;i<10;i++){
		}
		///////////////////////////////////
		GPIO_REG(GPIO_OUTPUT_VAL) |= ((0x1 << CH0) | (0x0 << CH1) | (0x0 << CH2) | (0x0 << CH3) | (0x1 << CH4) | (0x0 << CH5) | (0x0 << CH6) | (0x1 << CH7));
		for (int i=0;i<10;i++){
		}
		GPIO_REG(GPIO_OUTPUT_VAL) &= ~((0x1 << CH0) | (0x1 << CH1) | (0x1 << CH2) | (0x1 << CH3) | (0x1 << CH4) | (0x1 << CH5) | (0x1 << CH6) | (0x1 << CH7));
		for (int i=0;i<10;i++){
		}
		///////////////////////////////////
		GPIO_REG(GPIO_OUTPUT_VAL) |= ((0x1 << CH0) | (0x0 << CH1) | (0x0 << CH2) | (0x0 << CH3) | (0x1 << CH4) | (0x0 << CH5) | (0x0 << CH6) | (0x1 << CH7));
		for (int i=0;i<10;i++){
		}
		GPIO_REG(GPIO_OUTPUT_VAL) &= ~((0x1 << CH0) | (0x1 << CH1) | (0x1 << CH2) | (0x1 << CH3) | (0x1 << CH4) | (0x1 << CH5) | (0x1 << CH6) | (0x1 << CH7));
		for (int i=0;i<10;i++){
		}
		///////////////////////////////////
		GPIO_REG(GPIO_OUTPUT_VAL) |= ((0x0 << CH0) | (0x1 << CH1) | (0x0 << CH2) | (0x0 << CH3) | (0x0 << CH4) | (0x1 << CH5) | (0x1 << CH6) | (0x0 << CH7));
		for (int i=0;i<10;i++){
		}
		GPIO_REG(GPIO_OUTPUT_VAL) &= ~((0x1 << CH0) | (0x1 << CH1) | (0x1 << CH2) | (0x1 << CH3) | (0x1 << CH4) | (0x1 << CH5) | (0x1 << CH6) | (0x1 << CH7));
		for (int i=0;i<10;i++){
		}
		////////////////C///////////////////
		for (int i=0;i<10;i++){
			sum++;
		}
		GPIO_REG(GPIO_OUTPUT_VAL) |= ((0x0 << CH0) | (0x0 << CH1) | (0x0 << CH2) | (0x1 << CH3) | (0x1 << CH4) | (0x0 << CH5) | (0x0 << CH6) | (0x0 << CH7));
		for (int i=0;i<10;i++){
		}
		GPIO_REG(GPIO_OUTPUT_VAL) &= ~((0x1 << CH0) | (0x1 << CH1) | (0x1 << CH2) | (0x1 << CH3) | (0x1 << CH4) | (0x1 << CH5) | (0x1 << CH6) | (0x1 << CH7));
		for (int i=0;i<10;i++){
		}
		///////////////////////////////////
		GPIO_REG(GPIO_OUTPUT_VAL) |= ((0x0 << CH0) | (0x0 << CH1) | (0x1 << CH2) | (0x0 << CH3) | (0x0 << CH4) | (0x1 << CH5) | (0x0 << CH6) | (0x0 << CH7));
		for (int i=0;i<10;i++){
		}
		GPIO_REG(GPIO_OUTPUT_VAL) &= ~((0x1 << CH0) | (0x1 << CH1) | (0x1 << CH2) | (0x1 << CH3) | (0x1 << CH4) | (0x1 << CH5) | (0x1 << CH6) | (0x1 << CH7));
		for (int i=0;i<10;i++){
		}
		///////////////////////////////////
		GPIO_REG(GPIO_OUTPUT_VAL) |= ((0x0 << CH0) | (0x1 << CH1) | (0x0 << CH2) | (0x0 << CH3) | (0x0 << CH4) | (0x0 << CH5) | (0x1 << CH6) | (0x0 << CH7));
		for (int i=0;i<10;i++){
		}
		GPIO_REG(GPIO_OUTPUT_VAL) &= ~((0x1 << CH0) | (0x1 << CH1) | (0x1 << CH2) | (0x1 << CH3) | (0x1 << CH4) | (0x1 << CH5) | (0x1 << CH6) | (0x1 << CH7));
		for (int i=0;i<10;i++){
		}
		///////////////////////////////////
		GPIO_REG(GPIO_OUTPUT_VAL) |= ((0x1 << CH0) | (0x0 << CH1) | (0x0 << CH2) | (0x0 << CH3) | (0x0 << CH4) | (0x0 << CH5) | (0x0 << CH6) | (0x1 << CH7));
		for (int i=0;i<10;i++){
		}
		GPIO_REG(GPIO_OUTPUT_VAL) &= ~((0x1 << CH0) | (0x1 << CH1) | (0x1 << CH2) | (0x1 << CH3) | (0x1 << CH4) | (0x1 << CH5) | (0x1 << CH6) | (0x1 << CH7));
		for (int i=0;i<10;i++){
		}
		///////////////////////////////////
		GPIO_REG(GPIO_OUTPUT_VAL) |= ((0x1 << CH0) | (0x0 << CH1) | (0x0 << CH2) | (0x0 << CH3) | (0x0 << CH4) | (0x0 << CH5) | (0x0 << CH6) | (0x1 << CH7));
		for (int i=0;i<10;i++){
		}
		GPIO_REG(GPIO_OUTPUT_VAL) &= ~((0x1 << CH0) | (0x1 << CH1) | (0x1 << CH2) | (0x1 << CH3) | (0x1 << CH4) | (0x1 << CH5) | (0x1 << CH6) | (0x1 << CH7));
		for (int i=0;i<10;i++){
		}
		///////////////-////////////////////
		for (int i=0;i<10;i++){
			sum++;
		}
		GPIO_REG(GPIO_OUTPUT_VAL) |= ((0x0 << CH0) | (0x0 << CH1) | (0x0 << CH2) | (0x0 << CH3) | (0x1 << CH4) | (0x0 << CH5) | (0x0 << CH6) | (0x0 << CH7));
		for (int i=0;i<10;i++){
		}
		GPIO_REG(GPIO_OUTPUT_VAL) &= ~((0x1 << CH0) | (0x1 << CH1) | (0x1 << CH2) | (0x1 << CH3) | (0x1 << CH4) | (0x1 << CH5) | (0x1 << CH6) | (0x1 << CH7));
		for (int i=0;i<10;i++){
		}
		///////////////////////////////////
		GPIO_REG(GPIO_OUTPUT_VAL) |= ((0x0 << CH0) | (0x0 << CH1) | (0x0 << CH2) | (0x0 << CH3) | (0x1 << CH4) | (0x0 << CH5) | (0x0 << CH6) | (0x0 << CH7));
		for (int i=0;i<10;i++){
		}
		GPIO_REG(GPIO_OUTPUT_VAL) &= ~((0x1 << CH0) | (0x1 << CH1) | (0x1 << CH2) | (0x1 << CH3) | (0x1 << CH4) | (0x1 << CH5) | (0x1 << CH6) | (0x1 << CH7));
		for (int i=0;i<10;i++){
		}
		///////////////////////////////////
		GPIO_REG(GPIO_OUTPUT_VAL) |= ((0x0 << CH0) | (0x0 << CH1) | (0x0 << CH2) | (0x0 << CH3) | (0x1 << CH4) | (0x0 << CH5) | (0x0 << CH6) | (0x0 << CH7));
		for (int i=0;i<10;i++){
		}
		GPIO_REG(GPIO_OUTPUT_VAL) &= ~((0x1 << CH0) | (0x1 << CH1) | (0x1 << CH2) | (0x1 << CH3) | (0x1 << CH4) | (0x1 << CH5) | (0x1 << CH6) | (0x1 << CH7));
		for (int i=0;i<10;i++){
		}
		///////////////////////////////////
		GPIO_REG(GPIO_OUTPUT_VAL) |= ((0x0 << CH0) | (0x0 << CH1) | (0x0 << CH2) | (0x0 << CH3) | (0x1 << CH4) | (0x0 << CH5) | (0x0 << CH6) | (0x0 << CH7));
		for (int i=0;i<10;i++){
		}
		GPIO_REG(GPIO_OUTPUT_VAL) &= ~((0x1 << CH0) | (0x1 << CH1) | (0x1 << CH2) | (0x1 << CH3) | (0x1 << CH4) | (0x1 << CH5) | (0x1 << CH6) | (0x1 << CH7));
		for (int i=0;i<10;i++){
		}
		//////////////V////////////////////
		for (int i=0;i<10;i++){
			sum++;
		}
		GPIO_REG(GPIO_OUTPUT_VAL) |= ((0x1 << CH0) | (0x1 << CH1) | (0x0 << CH2) | (0x0 << CH3) | (0x0 << CH4) | (0x0 << CH5) | (0x0 << CH6) | (0x0 << CH7));
		for (int i=0;i<10;i++){
		}
		GPIO_REG(GPIO_OUTPUT_VAL) &= ~((0x1 << CH0) | (0x1 << CH1) | (0x1 << CH2) | (0x1 << CH3) | (0x1 << CH4) | (0x1 << CH5) | (0x1 << CH6) | (0x1 << CH7));
		for (int i=0;i<10;i++){
		}
		///////////////////////////////////
		GPIO_REG(GPIO_OUTPUT_VAL) |= ((0x0 << CH0) | (0x0 << CH1) | (0x1 << CH2) | (0x1 << CH3) | (0x0 << CH4) | (0x0 << CH5) | (0x0 << CH6) | (0x0 << CH7));
		for (int i=0;i<10;i++){
		}
		GPIO_REG(GPIO_OUTPUT_VAL) &= ~((0x1 << CH0) | (0x1 << CH1) | (0x1 << CH2) | (0x1 << CH3) | (0x1 << CH4) | (0x1 << CH5) | (0x1 << CH6) | (0x1 << CH7));
		for (int i=0;i<10;i++){
		}
		///////////////////////////////////
		GPIO_REG(GPIO_OUTPUT_VAL) |= ((0x0 << CH0) | (0x0 << CH1) | (0x0 << CH2) | (0x0 << CH3) | (0x1 << CH4) | (0x1 << CH5) | (0x0 << CH6) | (0x0 << CH7));
		for (int i=0;i<10;i++){
		}
		GPIO_REG(GPIO_OUTPUT_VAL) &= ~((0x1 << CH0) | (0x1 << CH1) | (0x1 << CH2) | (0x1 << CH3) | (0x1 << CH4) | (0x1 << CH5) | (0x1 << CH6) | (0x1 << CH7));
		for (int i=0;i<10;i++){
		}
		///////////////////////////////////
		GPIO_REG(GPIO_OUTPUT_VAL) |= ((0x0 << CH0) | (0x0 << CH1) | (0x0 << CH2) | (0x0 << CH3) | (0x0 << CH4) | (0x0 << CH5) | (0x1 << CH6) | (0x1 << CH7));
		for (int i=0;i<10;i++){
		}
		GPIO_REG(GPIO_OUTPUT_VAL) &= ~((0x1 << CH0) | (0x1 << CH1) | (0x1 << CH2) | (0x1 << CH3) | (0x1 << CH4) | (0x1 << CH5) | (0x1 << CH6) | (0x1 << CH7));
		for (int i=0;i<10;i++){
		}
		///////////////////////////////////
		GPIO_REG(GPIO_OUTPUT_VAL) |= ((0x0 << CH0) | (0x0 << CH1) | (0x0 << CH2) | (0x0 << CH3) | (0x1 << CH4) | (0x1 << CH5) | (0x0 << CH6) | (0x0 << CH7));
		for (int i=0;i<10;i++){
		}
		GPIO_REG(GPIO_OUTPUT_VAL) &= ~((0x1 << CH0) | (0x1 << CH1) | (0x1 << CH2) | (0x1 << CH3) | (0x1 << CH4) | (0x1 << CH5) | (0x1 << CH6) | (0x1 << CH7));
		for (int i=0;i<10;i++){
		}
		///////////////////////////////////
		GPIO_REG(GPIO_OUTPUT_VAL) |= ((0x0 << CH0) | (0x0 << CH1) | (0x1 << CH2) | (0x1 << CH3) | (0x0 << CH4) | (0x0 << CH5) | (0x0 << CH6) | (0x0 << CH7));
		for (int i=0;i<10;i++){
		}
		GPIO_REG(GPIO_OUTPUT_VAL) &= ~((0x1 << CH0) | (0x1 << CH1) | (0x1 << CH2) | (0x1 << CH3) | (0x1 << CH4) | (0x1 << CH5) | (0x1 << CH6) | (0x1 << CH7));
		for (int i=0;i<10;i++){
		}
		///////////////////////////////////
		GPIO_REG(GPIO_OUTPUT_VAL) |= ((0x1 << CH0) | (0x1 << CH1) | (0x0 << CH2) | (0x0 << CH3) | (0x0 << CH4) | (0x0 << CH5) | (0x0 << CH6) | (0x0 << CH7));
		for (int i=0;i<10;i++){
		}
		GPIO_REG(GPIO_OUTPUT_VAL) &= ~((0x1 << CH0) | (0x1 << CH1) | (0x1 << CH2) | (0x1 << CH3) | (0x1 << CH4) | (0x1 << CH5) | (0x1 << CH6) | (0x1 << CH7));
		for (int i=0;i<10;i++){
		}
		///////////////////////////////////
		for (int i=0;i<10;i++){
			sum++;
		}
		write_hex(STDERR_FILENO, sum);

	}
  return 0;
}

