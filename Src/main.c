#include <stdint.h>
#include <print_scan.h>
#include "platform_init.h"




#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

int main(void)
{
    init_platform();
    usart_init(USART1, 9600);


    while (1) {
        usart_transmitChar(USART1, 'a');
        nop(1000);
    }
}
