
# Toolchain file for STM32
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

# Specify the cross compiler
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)

# Compiler flags for STM32 (adjust based on your STM32 board)
set(CMAKE_C_FLAGS "-mcpu=cortex-m4 -mthumb -mfloat-abi=soft -mfpu=fpv4-sp-d16")
