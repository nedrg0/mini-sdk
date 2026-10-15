add_library(cmsis INTERFACE)

target_include_directories(cmsis SYSTEM INTERFACE
	${cmsis_5_SOURCE_DIR}/CMSIS/Core/Include
	${cmsis_device_f1_SOURCE_DIR}/Include
)

target_compile_definitions(cmsis INTERFACE 
	STM32F103xB
)
