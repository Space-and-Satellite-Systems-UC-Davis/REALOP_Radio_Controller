#include <stdint.h>
#include <print_scan.h>
#include <stm32l476xx.h>


#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

int main(void)
{
    /* Loop forever */
    printMsg("Hello");
    delay_ms(100);
//  RCC->AHB1ENR |= RCC_AHB2ENR_GPIOBEN;
//  RCC->APB2ENR |= RCC_APB2ENR_USART1EN;

#
    gpio_mode(GPIOA, 9, 2, 0, 3, 0);
    gpio_af(GPIOA, 9, 7);
    gpio_mode(GPIOA, 10, 2, 0, 3, 0);  // Alternate Function, Push-Pull, Very High Speed, No Pull
    gpio_af(GPIOA, 10, 7);  // Alternate function 7 (AF7) for USART1_RX




    if (!usart_init(USART1, 9600)) {
            // Handle error: Initialization failed
            while (1);  // Infinite loop to signal failure
        }
    while(1){

        usart_transmitChar(USART1, 'a');



    }
}
