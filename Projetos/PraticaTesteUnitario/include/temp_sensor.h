#ifndef TEMP_SENSOR_H
#define TEMP_SENSOR_H

#include <stdint.h>

#define ADC_TEMPERATURE_CHANNEL 4

void temp_sensor_init(void);
uint16_t temp_sensor_read_raw(void);
float adc_to_celsius(uint16_t adc_value);

#endif // TEMP_SENSOR_H
