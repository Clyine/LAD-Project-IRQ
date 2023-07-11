#include "checker.h"

#ifndef ARRAYS
    #define ARRAYS
    uint32_t cycleDuration[MAperiod];
    uint32_t onDuration[MAperiod]; 
#endif

uint32_t sum(uint32_t *array) {
    uint32_t sum;
    for (int i = 0; i < MAperiod; i++) {
        sum += *(array+i);
    }
    return sum;
}

uint32_t* append(uint32_t *array, uint32_t num) {
    for (int i = 0; i < MAperiod-1; i++) {
        *(array+i) = *(array+i+1);
    }
    *(array+MAperiod-1) = num;
    return array;
}

void setup_checker() {
    gpio_set_irq_enabled(sensor, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true);
    gpio_add_raw_irq_handler_masked(sensor, process);
    irq_set_enabled(IO_IRQ_BANK0, true);
}

void process()
{
    // r--f--r--f
    // check interrupt flag and status
    static uint32_t rise = 0;
    static uint32_t fall = 0;
    uint32_t newRise;
    uint32_t newFall;

    if (gpio_get_irq_event_mask(sensor) & GPIO_IRQ_EDGE_RISE)
    {
        // clear interrupt
        gpio_acknowledge_irq(sensor, GPIO_IRQ_EDGE_RISE);
        if (rise != 0)
        newRise = to_ms_since_boot(get_absolute_time());
        {
            append(&cycleDuration[0], (newRise-rise));

        }
        rise = newRise;
    }

    if (gpio_get_irq_event_mask(sensor) & GPIO_IRQ_EDGE_FALL)
    {
        // clear interrupt
        gpio_acknowledge_irq(sensor, GPIO_IRQ_EDGE_FALL);
        if (rise != 0)
        newFall = to_ms_since_boot(get_absolute_time());
        {
            append(&onDuration[0], (newFall-rise));
        }
        fall = newFall;
    }
}
uint32_t getSumCycle() {
    return (sum(&cycleDuration[0])/5);
}

uint32_t getSumDuration() {
    return (sum(&onDuration[0])/5);
}