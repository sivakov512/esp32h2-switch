#include <driver/gpio.h>

#include "driver.h"

static const gpio_num_t kRelayGPIO = GPIO_NUM_5;

Driver::Driver() : relay_gpio_(kRelayGPIO) {}

esp_err_t Driver::Init() {
  gpio_config_t gpio_conf = {
      .pin_bit_mask = (1ULL << relay_gpio_),
      .mode = GPIO_MODE_OUTPUT,
      .pull_up_en = GPIO_PULLUP_DISABLE,
      .pull_down_en = GPIO_PULLDOWN_DISABLE,
      .intr_type = GPIO_INTR_DISABLE,
  };
  return gpio_config(&gpio_conf);
}

esp_err_t Driver::SetState(bool val) {
  return gpio_set_level(relay_gpio_, static_cast<uint32_t>(val));
}
