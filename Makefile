TARGET_MCU ?= stm32f103xb
BUILD_DIR  := build
BIN        := $(BUILD_DIR)/app/firmware.bin
FLASH_ADDR := 0x08000000

.PHONY: all configure build flash erase reset clean rebuild

all: build

# Configure only when the build directory doesn't exist yet
$(BUILD_DIR)/build.ninja:
	cmake -S . -B $(BUILD_DIR) -G Ninja -DTARGET_MCU=$(TARGET_MCU)

configure: $(BUILD_DIR)/build.ninja

build: configure
	cmake --build $(BUILD_DIR)

flash: build
	st-flash write $(BIN) $(FLASH_ADDR)
	st-flash reset

erase:
	st-flash erase

reset:
	st-flash reset

clean:
	rm -rf $(BUILD_DIR)

rebuild: clean all
