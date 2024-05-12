CC := gcc
CFLAGS := -Iinclude -mconsole
LDFLAGS_MACOS := -framework Cocoa
LDFLAGS_WINDOWS := -luser32 -lgdi32

ifeq ($(OS),Windows_NT)
    OS := Windows
else
    OS := $(shell uname)
endif

# Set flags based on operating system
ifeq ($(OS),Darwin)
    LDFLAGS = $(LDFLAGS_MACOS)
else
    LDFLAGS = $(LDFLAGS_WINDOWS)
endif

SRCS := $(wildcard src/*.c)
OBJS := $(patsubst src/%.c,obj/%.o,$(SRCS))
MAIN_OBJ := main.o

obj/%.o: src/%.c | obj
	@$(CC) $(CFLAGS) -c $< -o $@

obj:
	@mkdir -p obj

app: $(OBJS) $(MAIN_OBJ)
	@$(CC) $(CFLAGS) $^ $(LDFLAGS) -o "BangkokMetro"

main.o: main.c
	@$(CC) $(CFLAGS) -c $< -o $@

.PHONY: run clean

run: app
	@./BangkokMetro

clean:
	@rm -rf obj/*.o obj "BangkokMetro" main.o
