#include <app/server/Server.h>
#include <esp_err.h>
#include <esp_log.h>
#include <esp_matter.h>
#include <nvs_flash.h>
#include <platform/ESP32/OpenthreadLauncher.h>

#include "common.h"
#include "driver.h"
#include "matter.h"

static const uint8_t kThreadQueueSize = 10;

static Driver g_driver;

extern "C" void app_main() {  // NOLINT
  esp_err_t err;

  err = g_driver.Init();
  ABORT_APP_ON_FAILURE(err == ESP_OK, "Failed to initialize driver, err: %d",
                       err);

  nvs_flash_init();

  esp_openthread_platform_config_t config = {
      .radio_config = {.radio_mode = RADIO_MODE_NATIVE},
      .host_config = {.host_connection_mode = HOST_CONNECTION_MODE_NONE},
      .port_config =
          {
              .storage_partition_name = "nvs",
              .netif_queue_size = kThreadQueueSize,
              .task_queue_size = kThreadQueueSize,
          },
  };
  set_openthread_platform_config(&config);

  err = StartMatterStack(&g_driver);
  ABORT_APP_ON_FAILURE(err == ESP_OK, "Failed to start Matter, err: %d", err);
}
