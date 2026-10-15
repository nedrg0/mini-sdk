include(FetchContent)

# ARM CMSIS Core 
FetchContent_Declare(
	cmsis_5
	GIT_REPOSITORY 	https://github.com/ARM-software/CMSIS_5.git
	GIT_TAG		5.9.0
	GIT_SHALLOW	TRUE
)

# ST device headers 
FetchContent_Declare(
	cmsis_device_f1
	GIT_REPOSITORY 	https://github.com/STMicroelectronics/cmsis_device_f1.git
	GIT_TAG		v4.3.5
	GIT_SHALLOW 	TRUE
)

FetchContent_MakeAvailable(cmsis_5 cmsis_device_f1)
