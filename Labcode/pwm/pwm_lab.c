#include "checker.h"

#ifndef PICO_LIBS
    #define PICO_LIBS
    #include "pico/stdlib.h"
    #include "hardware/pwm.h"
    #include "hardware/adc.h"
    #include "hardware/dma.h"
    #include "pico/time.h"
#endif


int main()
{
    stdio_init_all();
    setup_checker();

    /*
    ==================================
    TO-DO
    ==================================
    Implement a PWM signal on pin 8 with a period of 10ms and a duty cycle of 30%

    GPIO 8 will be connected to GPIO 1. The detected period length and active duration during the period will be displayed
    in the serial terminal
    */

    //Set pin 8 to PWM
    gpio_set_function(8, GPIO_FUNC_PWM);

    //Default clock rate of 125MHz, a clkdiv of 100 results in a 1.25Mhz effective clock.
    //The compare register increases by 1250000 every second.
    //Accepted div is 1 <= value <= 256
    pwm_set_clkdiv(pwm_gpio_to_slice_num(8), 100);

    //Set the wrap value to be 12500, The compare register will reset to 0 at this value
    //This corresponds to a 100Hz signal. (1250000/12500)
    //Max wrap is a 16bit integer
    pwm_set_wrap(pwm_gpio_to_slice_num(8), 12500);

    //Set the channel level to 3750. When the compare register is greater than this value, the output signal will be low.
    //A channel level of 3750 corresponds to a duty cycle of 30% (3750/12500)
    //Cannot be larger than wrap
    pwm_set_chan_level(pwm_gpio_to_slice_num(8), pwm_gpio_to_channel(8), 3750);

    //Enables the PWM signal
    pwm_set_enabled(pwm_gpio_to_slice_num(8), true);

    while (1)
    {
        printf("Period Length: ,%d\n", getSumCycle());
        printf("Active Period: ,%d\n", getSumDuration());
        sleep_ms(500);
    }
}

