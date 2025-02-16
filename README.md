# Matter-Enabled Thread Switch on ESP32-H2

This repository contains a minimal Matter + Thread project targeting the **ESP32-H2** MCU. It controls a relay via **GPIO5**, with the aim of managing a water heater or similar appliance. The project is written in **C++20** (with some C code) using the **ESP-IDF** and **ESP-Matter** frameworks.

## Overview
* **Core MCU**: [ESP32-H2](https://www.espressif.com/en/products/socs/esp32-h2)
* **Protocol**: Matter over Thread
* **Relay Control**: GPIO5
* **Language**: C++20 & C
* **Thread Config**: Enabled by default in sdkconfig.defaults
* **Commissioning Data**: Stored in a factory partition (fctry) at 0x3E0000

## Requirements
1. [ESP-IDF 5.4](https://github.com/espressif/esp-idf/tree/release/v5.4)
    - Follow the official ESP-IDF [documentation](https://docs.espressif.com/projects/esp-idf/en/stable/esp32h2/get-started/index.html#installation) for installation and setup.
2. [ESP-Matter 1.4](https://github.com/espressif/esp-matter/tree/release/v1.4)
    - Refer to the ESP-Matter repo for detailed instructions on integrating Matter into ESP-IDF.

## Setup

1. Clone this repository alongside your ESP-IDF and ESP-Matter installations.
2. Ensure that `sdkconfig.defaults` includes the necessary Thread and Matter configurations for ESP32-H2.
3. Verify that `GPIO5` is free to drive your relay hardware.

### Project Structure
Typical ESP-IDF directory layout:
```project_root/
├── CMakeLists.txt
├── sdkconfig.defaults
├── main/
│   ├── main.cpp
│   └── ...
└── partitions.csv
```

## Building

1. Set the target to **esp32h2**:
```sh
idf.py set-target esp32h2
```

2. Build the firmware:
```sh
idf.py build
```

3. Flash to your device (initial firmware, excluding commissioning info):
```sh
idf.py flash
```

## Commissioning Data (Factory Partition)

To avoid using test keys in production, generate your own commissioning data and flash it to the `fctry` partition at address `0x3E0000`.
* We recommend using [ESP Matter Manufacturing Tool (mfg_tool)](https://github.com/espressif/esp-matter-tools/tree/main/mfg_tool).
* Example command (using test keys) for building provisioning data:
```sh
esp-matter-mfg-tool -v 0xFFF2 -p 0x8001 \
  --vendor-name "Nikita Sivakov" \
  --product-name "Switch" \
  -cd $MATTER_SDK_PATH/credentials/test/certification-declaration/Chip-Test-CD-FFF2-8001.der
```
This generates a binary that contains the necessary credentials for Matter commissioning.

### Flashing the Commissioning Binary
Once the binary is generated, flash it to `0x3E0000`:
```sh
esptool.py -p <DEVICE_PORT> write_flash 0x3E0000 <PATH_TO_GENERATED_BINARY>
```
*Replace `<DEVICE_PORT>` (e.g. `COM3` or `/dev/ttyUSB0`) and `<PATH_TO_GENERATED_BINARY>` with your actual values.*

## Usage
1. Power up the board.
2. Join a Thread network and start the Matter commissioning process.
3. Once commissioned, toggle the relay connected to GPIO5 through Matter commands (e.g., from a Matter controller or CLI).

## Contributing
* For any issues, suggestions, or feature requests, please open an [issue](../../issues).
* Pull requests with improvements or bug fixes are welcome.

---

**Note**: This project is provided as-is for demonstration purposes. Always exercise caution when dealing with high-voltage equipment such as water heaters.
