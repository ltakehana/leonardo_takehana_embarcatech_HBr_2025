#ifndef MOCK_ADC_H
#define MOCK_ADC_H


#include <stdbool.h> 
#include <stdint.h>   


static inline void adc_init(void) {
}

static inline void adc_set_temp_sensor_enabled(bool enable) {
}

static inline void adc_select_input(int channel) {
}

static inline uint16_t adc_read(void) {
    return 512;
}

#define ADC_TEMPERATURE_CHANNEL 4

#endif // MOCK_ADC_H
