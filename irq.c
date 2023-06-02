//for printf to work properly for uint64_t please refer to #971 on PicoSDK
//https://github.com/raspberrypi/pico-sdk/pull/971

#include <stdio.h>
#include <math.h>
#define __STDC_FORMAT_MACROS
#include <inttypes.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/adc.h"
#include "hardware/dma.h"
#include "pico/time.h"

#define pinENA 8
#define pinENB 9

#define sensor 1
#define MAperiod 5

//125000000

bool initPWM();
void process();
uint32_t sum(uint32_t *array);
uint32_t* append(uint32_t *array, uint32_t num);
uint32_t pwm_set_freq_duty(uint slice_num, uint chan, uint32_t f, int d);

uint32_t cycleDuration[MAperiod];
uint32_t onDuration[MAperiod]; 


int main()
{
    stdio_init_all();
    initPWM();

    gpio_set_irq_enabled(sensor, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true);

    gpio_add_raw_irq_handler_masked(sensor, process);
    irq_set_enabled(IO_IRQ_BANK0, true);



    while (1)
    {
        printf("0,%d\n", sum(&cycleDuration[0])/5);
        printf("1,%d\n", sum(&onDuration[0])/5);
        sleep_ms(500);
    }
}

bool initPWM()
{
    // PWM
    // Set pin to pwm function
    gpio_set_function(pinENA, GPIO_FUNC_PWM);
    gpio_set_function(pinENB, GPIO_FUNC_PWM);
    
    pwm_set_freq_duty(pwm_gpio_to_slice_num(pinENA), pwm_gpio_to_channel(pinENA), 100, 50);
    pwm_set_freq_duty(pwm_gpio_to_slice_num(pinENB), pwm_gpio_to_channel(pinENB), 50, 30);

    pwm_set_enabled(pwm_gpio_to_slice_num(pinENA), true);
    pwm_set_enabled(pwm_gpio_to_slice_num(pinENB), true);

    return true;
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


uint32_t pwm_set_freq_duty(uint slice_num, uint chan, uint32_t f, int d)
{
    uint32_t clock = 125000000;
    uint32_t divider16 = clock / f / 4096 + (clock % (f * 4096) != 0);
    if (divider16 / 16 == 0)
        divider16 = 16;
    uint32_t wrap = clock * 16 / divider16 / f - 1;
    pwm_set_clkdiv_int_frac(slice_num, divider16 / 16, divider16 & 0xF);
    pwm_set_wrap(slice_num, wrap);
    pwm_set_chan_level(slice_num, chan, wrap * d / 100);
    return wrap;
}