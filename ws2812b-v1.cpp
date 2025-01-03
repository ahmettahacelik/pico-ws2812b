#include <stdio.h>
#include "ws2812b.hpp"
#include "pico/stdlib.h"
#include "hardware/timer.h"

// Define a class to handle LED initialization and toggling
class LedController {
public:
    // Constructor to initialize the LED pin
    LedController(uint pin) : pin(pin) {
        gpio_init(pin);                   // Initialize the GPIO pin
        gpio_set_dir(pin, GPIO_OUT);      // Set the pin as output
        gpio_put(pin, false);             // Set the LED to off initially
    }

    // Method to toggle the LED
    void toggle() {
        gpio_xor_mask(1u << pin);         // Toggle the LED state
    }

private:
    uint pin; // Store the pin number
};

int main() {
    stdio_init_all(); // Initialize the standard input/output

    LedController led(PICO_DEFAULT_LED_PIN); // Create an instance of LedController for the default LED pin

    LED_ARRAY ledArray;
    ledArray.ConfigureGradient(0xFF0000, 0x0000FF); // Gradient from red to blue
    ledArray.SendData(); // Transmit the data to LEDs
    
    while (true) {
        sleep_ms(1000);    // Wait for 1000 ms
        led.toggle();      // Toggle the LED
    }
}
