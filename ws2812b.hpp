#pragma once

#include "pico/stdlib.h"

extern void cycle_delay_t0h();
extern void cycle_delay_t0l();
extern void cycle_delay_t1h();
extern void cycle_delay_t1l();

#define LED_PIN 14

#define LED_NUM 120

class LED {
    private:
        uint8_t red;
        uint8_t green;
        uint8_t blue;

        void SendColorData(uint8_t color) const {
            for (int8_t j = 7; j >= 0; j--) {
                if (color & (1u << j)) {
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
    
    public:
        LED(void): red(0), green(0), blue(0) {}

        LED(uint32_t color) {
            red = (color >> 16) & 0xFF;
            green = (color >> 8) & 0xFF;
            blue = (color >> 0) & 0xFF;
        }

        LED(uint8_t r, uint8_t g, uint8_t b): red(r), green(g), blue(b) {}

        void Color(uint32_t rgb) {
            red = (rgb >> 16) & 0xFF;
            green = (rgb >> 8) & 0xFF;
            blue = (rgb >> 0) & 0xFF;
        }

        uint32_t Color(void) {
            return ((red << 16) | (green << 8) | (blue << 0));
        }

        void SendData() const {
            SendColorData(green);
            SendColorData(red);
            SendColorData(blue);
        }
};

class LED_ARRAY {
    private:
        LED led_arr[LED_NUM];
        uint8_t shift_index;

    public:
        LED_ARRAY(): shift_index(0) {}

        void ShiftRight() {
            shift_index = (shift_index + 1) % LED_NUM;
        }

        void ShiftLeft() {
            shift_index = (shift_index - 1 + LED_NUM) % LED_NUM;
        }

        void SendData() {
            gpio_put(LED_PIN, false);
            sleep_us(50);
            for(int i = 0; i < LED_NUM; i++) {
                led_arr[(i + shift_index) % LED_NUM].SendData();
            }
        }

        void ConfigureGradient(uint32_t color_start, uint32_t color_end) {
            led_arr[0].Color(color_start);
            led_arr[60].Color(color_end);

            for (int i = 1; i < LED_NUM; i++) {
                if(i == 60) {continue;}
                
                float t = static_cast<float>(i) / (LED_NUM - 1);
                uint8_t red = ((1 - t) * ((color_start >> 16) & 0xFF)) + (t * ((color_end >> 16) & 0xFF));
                uint8_t green = ((1 - t) * ((color_start >> 8) & 0xFF)) + (t * ((color_end >> 8) & 0xFF));
                uint8_t blue = ((1 - t) * (color_start & 0xFF)) + (t * (color_end & 0xFF));
                led_arr[i].Color((red << 16) | (green << 8) | blue);
            }
        }

};