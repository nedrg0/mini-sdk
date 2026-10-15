add_library(hal_ll STATIC
	src/hal_ll_gpio.c
)

target_include_directories(hal_ll PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(hal_ll PUBLIC cmsis)
