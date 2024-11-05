#include <stdint.h>
#include <print_scan.h>
#include "UART/uart.h"


#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

int main(void)
{
    usart_init(USART1, 9600);


    while (1) {
        usart_transmitChar(USART1, 'a');
        for (volatile int i = 0; i < 100000; i++); // Delay to slow down transmission
    }
}
