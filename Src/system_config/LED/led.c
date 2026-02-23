/*
 * led.c
 *
 *	- August 17, 2024
 *		Author	: Darsh
 *		Log		: Copied from IntelliSat
 */

#include "led.h"

/***************************** LED INITIALIZERS ******************************/

void led_init() {
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;

	while(GPIOC->OTYPER == 0xFFFFFFFF);

	GPIOC->MODER &= ~GPIO_MODER_MODE2_Msk;	// D6? - D5 on in kicad?
	GPIOC->MODER |=  GPIO_MODER_MODE2_0;
}

/******************************* LED TOGGLERS ********************************/

void blinky() {
	static int counter = 0;

	if (counter++ > 1000) {
		counter = 0;
	}
	if (counter > 900) {
		GPIOC->BSRR = GPIO_BSRR_BS2;
	} else {
		GPIOC->BSRR = GPIO_BSRR_BR2;
	}
}
