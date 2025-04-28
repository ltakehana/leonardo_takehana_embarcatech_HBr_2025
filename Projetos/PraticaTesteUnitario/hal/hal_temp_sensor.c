#include "hal_temp_sensor.h"
#include "temp_sensor.h"

float hal_read_temperature_celsius(void) {
    uint16_t adc_value = temp_sensor_read_raw();
    return adc_to_celsius(adc_value);
}
