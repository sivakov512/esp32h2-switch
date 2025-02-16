#pragma once

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

const char *const kTag = "BOILER";

#define ABORT_APP_ON_FAILURE(condition, fmt, ...) \
  do {                                            \
    if (!(unlikely(condition))) {                 \
      ESP_LOGE(kTag, fmt, ##__VA_ARGS__);         \
      vTaskDelay(5000 / portTICK_PERIOD_MS);      \
      abort();                                    \
    }                                             \
  } while (0)
