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


    while (1)
    {
        printf("Period Length: ,%d\n", getSumCycle());
        printf("Active Period: ,%d\n", getSumDuration());
        sleep_ms(500);
    }
}

