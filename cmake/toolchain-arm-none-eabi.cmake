set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(CMAKE_C_COMPILER 	arm-none-eabi-gcc)
set(CMAKE_OBJCOPY	arm-none-eabi-objcopy)
set(CMAKE_SIZE		arm-none-eabi-size)

set(CMAKE_EXECTUBALE_SUFFIX ".elf")
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

set(MCU_FLAGS "-mcpu=cortex-m3 -mthumb")

set(CMAKE_C_FLAGS_INIT "${MCU_FLAGS} -ffunction-sections -fdata-sections -Wall")
set(CMAKE_EXE_LINKER_FLAGS_INIT "${MCU_FLAGS} --specs=nosys.specs -W --data-sections")
