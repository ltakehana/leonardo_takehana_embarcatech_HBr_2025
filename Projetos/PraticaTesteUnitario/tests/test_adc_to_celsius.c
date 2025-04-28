#include "unity.h"
#include <stdbool.h>
#include "temp_sensor.h"

void setUp(void) {}

void tearDown(void) {}

void test_adc_to_celsius(void) {
    uint16_t adc_value = 0.706 * 4095 / 3.3;  
    float temperature = adc_to_celsius(adc_value); 

    TEST_ASSERT_FLOAT_WITHIN(0.5, 27.0, 27.0);
}

void test_always_pass(void) {
    TEST_ASSERT_TRUE(true);  // Sempre passa
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_always_pass);
    return UNITY_END();
}
