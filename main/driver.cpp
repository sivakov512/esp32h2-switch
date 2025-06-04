#include <driver/gpio.h>
#include "soc/gpio_num.h"

#include "driver.h"

static const gpio_num_t kRelayGPIO = GPIO_NUM_27;
static const gpio_num_t kLedGPIO = GPIO_NUM_26;

Driver::Driver() : relay_gpio_(kRelayGPIO), led_gpio_(kLedGPIO) {}

esp_err_t Driver::Init() {
  gpio_config_t gpio_conf = {
      .pin_bit_mask = (1ULL << relay_gpio_) | (1ULL << led_gpio_),
      .mode = GPIO_MODE_OUTPUT,
      .pull_up_en = GPIO_PULLUP_DISABLE,
      .pull_down_en = GPIO_PULLDOWN_DISABLE,
      .intr_type = GPIO_INTR_DISABLE,
  };
  return gpio_config(&gpio_conf);
}

esp_err_t Driver::SetRelayState(bool val) {
  return gpio_set_level(relay_gpio_, static_cast<uint32_t>(val));
}

esp_err_t Driver::SetLedState(bool val) {
  return gpio_set_level(led_gpio_, static_cast<uint32_t>(val));
}
