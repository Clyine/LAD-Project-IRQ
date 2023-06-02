cmake_minimum_required(VERSION 3.12)

include(pico_sdk_import.cmake)

project(adc_fft_project)

pico_sdk_init()

add_executable(irq irq.c)
pico_add_extra_outputs(irq)

pico_enable_stdio_usb(irq 1)
pico_enable_stdio_uart(irq 1)


target_link_libraries(irq
	pico_stdlib
	hardware_adc
	hardware_dma
	hardware_pwm
	)
