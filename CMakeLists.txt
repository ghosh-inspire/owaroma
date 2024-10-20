
cmake_minimum_required(VERSION 3.22)

# Set the project name
project(OWAromaControl LANGUAGES C CXX)

# Enable Ninja Multi-Config generator
set(CMAKE_GENERATOR "Ninja Multi-Config")

# Set standard
set(CMAKE_C_STANDARD 99)

# Define build configurations for different platforms
set(CMAKE_CONFIGURATION_TYPES "Debug;Release;Host;STM32")

# Add source files
add_executable(owaroma_system
    src/owaroma_uart_driver.c
    src/owaroma_timer_driver.c
    src/owaroma_gpio_driver.c
    src/owaroma_control.c
    src/main.c
)

include_directories(include)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")

# 1. Host build (x86_64)
if(CMAKE_BUILD_TYPE STREQUAL "Host")
    message(STATUS "Building for Linux Host")
    set(CMAKE_C_COMPILER gcc)
    set(CMAKE_CXX_COMPILER g++)
endif()

# 2. Example config STM32 cross-compilation
if(CMAKE_BUILD_TYPE STREQUAL "STM32")
    message(STATUS "Building for STM32")
    set(CMAKE_C_COMPILER arm-none-eabi-gcc)
    set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
    set(CMAKE_C_FLAGS "-mcpu=cortex-m4 -mthumb -mfloat-abi=soft -mfpu=fpv4-sp-d16")
    set(CMAKE_EXE_LINKER_FLAGS "-TSTM32.ld")  # Example linker script for STM32
endif()
