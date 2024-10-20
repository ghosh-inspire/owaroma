
# OWAroma Control System

This project implements a aroma delivery system with 6 aroma channels and a diaphragm pump. The communication with the host is via UART.

## Features
- Controls up to 6 aroma channels.
- Automatically closes each channel after 60 seconds.
- Can be controlled via UART commands.
- Supports a Keep Alive function.
- Assumes at a time only once channel is active.
- Enabling a channel, automatically disables any currently active channel.
- Cross-compilation support for STM32 using Ninja multi-config - untested, example only.
- User stories can be used to understand features required, better planning, epics, sprint etc.

## Design Overview
- The overall design implements as simple state machine which starts with platform init, processing commands and enabling/disabling channels.
- Command '0' or 'a' is used for Keep Alive.
- Command '1' to '6' is used for enabling channges 1 - 6.
- Command 'b' to 'g' is used for disbling channges 1 - 6.
- The system cycles through the various states and decides the next optimal state to transition into.
- To enable a channel, we first open the valve and then start the pump. Similarly, to disable a channel, we first disable the pump, then close the channel.
- The UART driver implements a circular buffer to account for flow control between host and device.
- The time is configured to trigger every one second, in this implementation we just use sleep.
- When the system is powered on, the host should poll for the "Platform Init Done" string and then start sending commands. A more simplified string can be used.
- There can be more system states added, for example power management, reading system config e.g number of channels, keeping multiple channels open, firmware update, factory reset etc.
- Any latency needs to be considered in between PUMP and Channel enabling/disabling.
- A non-volatile storage can be used to keep firmware and factory reset settings, device ID, device config, any calibration data etc.
- Some LEDs can be added to be more user interactive.
- Suitable unit testing framework can be used, for e.g mUnit (https://github.com/nemequ/munit.git)
- Using Ninja, the system can be built for running unit test on Host or Target device.
- Using CMAKE is very useful to manage multiple configs and integrate with many IDEs.

## Building the project
To build for the host or cross-compile for STM32:

1. **Host (Linux x86_64)**:
   ```bash
   mkdir build
   cd build
   cmake -G "Ninja Multi-Config" ..
   cmake --build . --config Host --clean-first
   ```

2. **STM32** (with cross-compilation toolchain, example only):
   ```bash
   cmake --build . --config STM32 --toolchain ../stm32_toolchain.cmake
   ```
## Running the project
   ```bash
   cd build
   ./Host/owaroma_system
   ```

## Requirements
- **CMake** version 3.22 or later
- **Ninja** build system
- **Cross-compiler toolchains** for STM32 (e.g., `arm-none-eabi-gcc`, `arm-linux-gnueabi-gcc`)
