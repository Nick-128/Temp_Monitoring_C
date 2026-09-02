CC     := gcc
CFLAGS := -std=c11 -Wall -Wextra -Werror -Isrc -Iservices -Ihal -Ihal/mock

# MinGW gcc appends .exe to the output, so the target name must match or
# make relinks on every invocation.
ifeq ($(OS),Windows_NT)
EXE := .exe
else
EXE :=
endif

BIN := build/demo$(EXE)

# PC build links the mock HAL; a target build would list hal/stm32 instead.
SRC := src/classify.c services/sensor.c services/config.c services/led_panel.c \
       hal/mock/hal_mock.c

all: $(BIN)

$(BIN): src/main.c $(SRC) | build
	$(CC) $(CFLAGS) -o $@ $^

build:
	mkdir -p build

run: all
	./$(BIN)

clean:
	rm -rf build

.PHONY: all run clean
