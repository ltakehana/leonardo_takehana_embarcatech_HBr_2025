#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"

#define JOYSTICK_X_PIN 27  
#define JOYSTICK_Y_PIN 26  

int main() {
    stdio_init_all();   
    adc_init();      
    adc_gpio_init(JOYSTICK_X_PIN);
    adc_gpio_init(JOYSTICK_Y_PIN);

    while (true) {
        adc_select_input(0);
        uint16_t raw_x = adc_read();
        float voltage_x = raw_x * 3.3f / 4095.0f;

        adc_select_input(1); 
        uint16_t raw_y = adc_read();
        float voltage_y = raw_y * 3.3f / 4095.0f;

        printf("Joystick X: %u (%.2f V) | Y: %u (%.2f V)\n",
               raw_x, voltage_x, raw_y, voltage_y);

        sleep_ms(200);
    }

    return 0;
}
