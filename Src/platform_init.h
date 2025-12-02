/*
 * platform_init.h

 * 	- August 17, 2024
 * 		Author			: Darsh
 * 		Log				: Copied from IntelliSat, modified for Radio Controller
 */

#ifndef REALOP1_PLATFORM_INIT_H
#define REALOP1_PLATFORM_INIT_H

#include "Radio/AX5043.h"

#include <globals.h>

#include <core_config.h>
#include <Timers/timers.h>
#include <SPI/spi.h>
#include <LED/led.h>
#include <UART/uart.h>
#include <print_scan.h>

static void gpio_init();

/**
 * Configures the system's various features,
 * such as clocks, protocol hardware, and more.
 *
 * @returns None
 */
void init_platform() {
	
	SCB->CPACR |= 0x00F00000;
	init_coreClocks();


	gpio_init();


	// init intercomm
	// init radio
	led_init();
	
	printer_init();
	// printer_init();
	systick_init();
}

static void gpio_init() {
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
	while(GPIOB->OTYPER == 0xFFFFFFFF);

	GPIOB->MODER &= ~GPIO_MODER_MODE9_Msk;	// uhf (rad0) 3v3 enable
	GPIOB->MODER |=  GPIO_MODER_MODE9_0;


	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
	while(GPIOA->OTYPER == 0xFFFFFFFF);

	GPIOA->MODER &= ~GPIO_MODER_MODE8_Msk;	// vhf (rad1) 3v3 enable
	GPIOA->MODER |=  GPIO_MODER_MODE8_0;

	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;
	while(GPIOC->OTYPER == 0xFFFFFFFF);
	GPIOC->MODER &= ~GPIO_MODER_MODE9_Msk;	//crystal v2v8 enable
	GPIOC->MODER |=  GPIO_MODER_MODE9_0;

}

#endif // REALOP1_PLATFORM_INIT_H
