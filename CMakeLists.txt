cmake_minimum_required(VERSION 3.20)

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/toolchain-arm-none-eabi.cmake)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_C_FLAGS_DEBUG "-g3 -O0")

project(mini-sdk C)

set(TARGET_MCU "stm32f103xb" CACHE STRING "Target MCU variant")

include(cmake/dependencies.cmake)

add_subdirectory(thirdparty)

add_subdirectory(platform/arm/${TARGET_MCU})
add_subdirectory(targets/arm/stm32/${TARGET_MCU})

add_subdirectory(app)
