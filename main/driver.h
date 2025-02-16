#pragma once

#include <esp_err.h>
#include <soc/gpio_num.h>

class Driver {
public:
  explicit Driver();

  esp_err_t Init();

  esp_err_t SetState(bool val);

private:
  gpio_num_t relay_gpio_;
};
