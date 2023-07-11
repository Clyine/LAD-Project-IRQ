#ifndef CHECKER_H
    #define CHECKER_H
    #include "pico/stdlib.h"
    #include "hardware/pwm.h"
    #include "hardware/adc.h"
    #include "hardware/dma.h"
    #include "pico/time.h"

    #include <stdio.h>
    #include <math.h>
    #define __STDC_FORMAT_MACROS
    #include <inttypes.h>

    #define pinENA 8
    #define pinENB 9

    #define sensor 1
    #define MAperiod 5

    uint32_t sum(uint32_t *array);
    uint32_t* append(uint32_t *array, uint32_t num);
    void setup_checker();
    void process();
    uint32_t getSumCycle();
    uint32_t getSumDuration();

#endif