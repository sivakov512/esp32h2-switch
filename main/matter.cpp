#include <esp_matter.h>
#include <esp_matter_attribute_utils.h>
#include <platform/CHIPDeviceEvent.h>

#include "common.h"
#include "matter.h"

namespace attribute = esp_matter::attribute;
namespace cluster = esp_matter::cluster;
namespace endpoint = esp_matter::endpoint;
namespace node = esp_matter::node;

static void EventCallback(const chip::DeviceLayer::ChipDeviceEvent *event,
                          intptr_t arg) {
  /* I will write something here later (or not) */
}

static esp_err_t IdentificationCallback(
    esp_matter::identification::callback_type_t type, uint16_t endpoint_id,
    uint8_t effect_id, uint8_t effect_variant, void *priv_data) {
  /* I will write something here later (or not) */
  return ESP_OK;
}

static esp_err_t AttributeUpdateCallback(
    esp_matter::attribute::callback_type_t type, uint16_t endpoint_id,
    uint32_t cluster_id, uint32_t attribute_id, esp_matter_attr_val_t *val,
    void *priv_data) {
  esp_err_t err = ESP_OK;

  if (type == esp_matter::attribute::PRE_UPDATE and priv_data != nullptr) {
    auto *driver = static_cast<Driver *>(priv_data);

    err = driver->SetState(val->val.b);
  }

  return err;
}

esp_err_t StartMatterStack(Driver *driver) {
  node::config_t node_config;
  esp_matter::node_t *node = node::create(&node_config, AttributeUpdateCallback,
                                          IdentificationCallback);
  ABORT_APP_ON_FAILURE(node != nullptr, "Failed to create matter node");

  endpoint::on_off_plugin_unit::config_t on_off_config;
  endpoint::on_off_plugin_unit::create(node, &on_off_config,
                                       esp_matter::ENDPOINT_FLAG_NONE, driver);

  return esp_matter::start(EventCallback);
}
