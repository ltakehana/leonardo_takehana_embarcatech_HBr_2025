#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/timer.h"
#include "ssd1306.h"

#define BUTTON_A 5
#define BUTTON_B 6
#define DEBOUNCE_TIME_MS 200

#define I2C_PORT i2c1
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_SDA_PIN  14  
#define OLED_SCL_PIN  15 
#define OLED_ADDR 0x3C  


volatile bool counting = false;
volatile int counter = 9;
volatile int click_count = 0;
volatile uint64_t last_press_a = 0;
volatile uint64_t last_press_b = 0;

ssd1306_t disp;

void update_display() {
    char buf[32];
    ssd1306_clear(&disp);
    sprintf(buf, "Contador: %d", counter);
    ssd1306_draw_string(&disp, 0, 16, 1, buf);
    sprintf(buf, "Cliques: %d", click_count);
    ssd1306_draw_string(&disp, 0, 32, 1, buf);
    ssd1306_show(&disp);
}

void gpio_callback(uint gpio, uint32_t events) {
    uint64_t now = to_ms_since_boot(get_absolute_time());

    if (gpio == BUTTON_A) {
        if (now - last_press_a < DEBOUNCE_TIME_MS) return;
        last_press_a = now;

        printf("Botao A pressionado\n");
        counting = true;
        counter = 9;
        click_count = 0;
        update_display();
    }

    if (gpio == BUTTON_B) {
        if (now - last_press_b < DEBOUNCE_TIME_MS) return;
        last_press_b = now;

        printf("Botao B pressionado\n");
        if (counting && counter > 0) {
            click_count++;
            update_display();
        }
    }
}


int main() {
    stdio_init_all();
    sleep_ms(500); 

    i2c_init(I2C_PORT, 400000);
    gpio_set_function(OLED_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(OLED_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(OLED_SDA_PIN);
    gpio_pull_up(OLED_SCL_PIN);


    gpio_init(BUTTON_A);
    gpio_set_dir(BUTTON_A, GPIO_IN);
    gpio_pull_up(BUTTON_A);
    gpio_set_irq_enabled_with_callback(BUTTON_A, GPIO_IRQ_EDGE_FALL, true, &gpio_callback);

    gpio_init(BUTTON_B);
    gpio_set_dir(BUTTON_B, GPIO_IN);
    gpio_pull_up(BUTTON_B);
    gpio_set_irq_enabled_with_callback(BUTTON_B, GPIO_IRQ_EDGE_FALL, true, &gpio_callback);


    if (!ssd1306_init(&disp, SCREEN_WIDTH, SCREEN_HEIGHT, OLED_ADDR, I2C_PORT)) {
        sleep_ms(20000);
        printf("Erro ao inicializar SSD1306!\n");
        return -1;
    }
    update_display();

    while (true) {
        if (counting) {
            sleep_ms(1000);
            counter--;
            update_display();

            if (counter <= 0) {
                counting = false;
            }
        } else {
            sleep_ms(100);
        }
    }

    return 0;
}
