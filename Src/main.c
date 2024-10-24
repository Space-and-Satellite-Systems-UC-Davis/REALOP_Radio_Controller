#include <stdint.h>

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

int main(void)
{
    /* Loop forever */
	while (1) {

			if (get_buttonStatus_1()) {
				// Do whatever you’d want to do if Button 1 was pressed
				printf("Button 1 Pressed");
			}
			if (get_buttonStatus_0()) {
				// Do whatever you’d want to do if Button 1 was pressed
				printf("Button 0 Pressed");
			}

			int current_time = getSysTime();
			while (getSysTime() - current_time < 1000){
				continue;
			}
			// led_a(true);	// This turns on the LED marked as LED-A on the Orbital Platform
			current_time = getSysTime();
			while (getSysTime() - current_time < 500){
						continue;
					}
			// led_a(false);	// This turns off LED-A

			_gpio_high(GPIOD, pin);
			delay_ms(10);
			_gpio_low(GPIOD, pin);

		};
}
