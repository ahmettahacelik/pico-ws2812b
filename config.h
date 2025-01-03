#pragma once

#include "pico/stdlib.h"

extern void cycle_delay_t0h();
extern void cycle_delay_t0l();
extern void cycle_delay_t1h();
extern void cycle_delay_t1l();

#define LED_PIN 14
#define LED_NUM 120

struct one_led {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} LED_ARRAY[LED_NUM];

void send_color_data(uint8_t color) {
    for(uint8_t j = 7; j >= 0; j--) {
        if(color & (1 << j)) {
            gpio_put(LED_PIN, true);
            cycle_delay_t1h();
            gpio_put(LED_PIN, false);
            cycle_delay_t1l();
        } else {
            gpio_put(LED_PIN, true);
            cycle_delay_t0h();
            gpio_put(LED_PIN, false);
            cycle_delay_t0l();
        }
    }
}

void send_led_data() {
    uint8_t red, green, blue;
    for(uint32_t i = 0; i < LED_NUM; i++) {
        green = LED_ARRAY[i].green;
        red = LED_ARRAY[i].red;
        blue = LED_ARRAY[i].blue;

        send_color_data(green);
        send_color_data(red);
        send_color_data(blue);
    }
}


void shift_led(bool direction) {
    struct one_led temp;
    if(direction) { // right
        temp = LED_ARRAY[LED_NUM - 1];
        for(int i = 1; i < LED_NUM; i++) {
            LED_ARRAY[i] = LED_ARRAY[i - 1];
        }
        LED_ARRAY[0] = temp;
    }
    else {  //left
        temp = LED_ARRAY[0];
        for(int i = 0; i < LED_NUM - 1; i++) {
            LED_ARRAY[i] = LED_ARRAY[i + 1];
        }
        LED_ARRAY[LED_NUM - 1] = temp;
    }
}