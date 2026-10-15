add_library(platform STATIC 
	startup.c
	system_stm32f103xb.c
)

target_link_libraries(platform PUBLIC cmsis)

target_link_options(platform PUBLIC
	-T${CMAKE_CURRENT_SOURCE_DIR}/stm32f103xb.ld
)
