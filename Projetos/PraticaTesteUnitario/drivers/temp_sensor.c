#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "temp_sensor.h"
#include <stdbool.h>

void temp_sensor_init(void) {
    adc_init();
    adc_set_temp_sensor_enabled(true);
    adc_select_input(ADC_TEMPERATURE_CHANNEL);
}

uint16_t temp_sensor_read_raw(void) {
    return adc_read();
}

float adc_to_celsius(uint16_t adc_value){
    float temperature = 27.0f - (adc_value * 3.3f / 4095.0f - 0.706f) / 0.001721f;
    return temperature;
}
