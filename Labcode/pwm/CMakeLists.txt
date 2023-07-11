cmake_minimum_required(VERSION 3.12)

include(pico_sdk_import.cmake)

project(adc_fft_project)

pico_sdk_init()

add_executable(pwm_lab pwm_lab.c)
add_library(checker checker.c)

target_link_libraries(checker
	pico_stdlib
	hardware_adc
	hardware_dma
	hardware_pwm
	)

pico_add_extra_outputs(pwm_lab)

pico_enable_stdio_usb(pwm_lab 1)
pico_enable_stdio_uart(pwm_lab 1)

target_link_libraries(pwm_lab
	checker
	)

