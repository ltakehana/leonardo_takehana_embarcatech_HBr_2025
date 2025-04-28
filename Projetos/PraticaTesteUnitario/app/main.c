#include <stdio.h>
#include "pico/stdlib.h"
#include "hal_temp_sensor.h"
#include "temp_sensor.h"

int main() {
    stdio_init_all();

    temp_sensor_init();  // inicializa o sensor de temperatura

    while (true) {
        float temperature = hal_read_temperature_celsius();
        printf("Temperatura: %.2f °C\n", temperature);
        sleep_ms(1000);
    }

    return 0;
}
