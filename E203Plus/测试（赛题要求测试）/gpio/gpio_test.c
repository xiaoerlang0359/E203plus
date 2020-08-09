// See LICENSE for license details.
#include <stdio.h>
#include <stdlib.h>
#include "platform.h"
#include <string.h>
#include "plic/plic_driver.h"
#include "encoding.h"
#include <unistd.h>
#include "stdatomic.h"
uint32_t button_0_value;
uint32_t button_1_value;
uint32_t button_2_value;
uint32_t input_value;
int main(void)
{
	GPIO_REG(GPIO_OUTPUT_EN)  &= ~((0x1 << BUTTON_0_GPIO_OFFSET) | (0x1 << BUTTON_1_GPIO_OFFSET) | (0x1 << BUTTON_2_GPIO_OFFSET));
	GPIO_REG(GPIO_PULLUP_EN)  &= ~((0x1 << BUTTON_0_GPIO_OFFSET) | (0x1 << BUTTON_1_GPIO_OFFSET) | (0x1 << BUTTON_2_GPIO_OFFSET));
	GPIO_REG(GPIO_INPUT_EN)   |=  ((0x1 << BUTTON_0_GPIO_OFFSET) | (0x1 << BUTTON_1_GPIO_OFFSET) | (0x1 << BUTTON_2_GPIO_OFFSET));

	GPIO_REG(GPIO_INPUT_EN) &= ~((0x1<< RED_LED_GPIO_OFFSET) | (0x1<< GREEN_LED_GPIO_OFFSET) | (0x1 << BLUE_LED_GPIO_OFFSET));
	GPIO_REG(GPIO_OUTPUT_EN) |= ((0x1<< RED_LED_GPIO_OFFSET) | (0x1<< GREEN_LED_GPIO_OFFSET) | (0x1 << BLUE_LED_GPIO_OFFSET));
	GPIO_REG(GPIO_OUTPUT_VAL) |= ((0x1<< RED_LED_GPIO_OFFSET) | (0x1<< GREEN_LED_GPIO_OFFSET) | (0x1 << BLUE_LED_GPIO_OFFSET));
	GPIO_REG(GPIO_OUTPUT_VAL) &= ~((0x1<< RED_LED_GPIO_OFFSET) | (0x1<< GREEN_LED_GPIO_OFFSET) | (0x1 << BLUE_LED_GPIO_OFFSET));

	while(1){
		input_value = GPIO_REG(GPIO_INPUT_VAL);
		button_0_value = (input_value & (0x1 << BUTTON_0_GPIO_OFFSET)) >>BUTTON_0_GPIO_OFFSET;
		button_1_value = (input_value & (0x1 << BUTTON_1_GPIO_OFFSET)) >>BUTTON_1_GPIO_OFFSET;
		button_2_value = (input_value & (0x1 << BUTTON_2_GPIO_OFFSET)) >>BUTTON_2_GPIO_OFFSET;
		GPIO_REG(GPIO_OUTPUT_VAL) = ((button_0_value<< RED_LED_GPIO_OFFSET) | (button_1_value<< GREEN_LED_GPIO_OFFSET) | (button_2_value << BLUE_LED_GPIO_OFFSET));
	}
  return 0;
}

