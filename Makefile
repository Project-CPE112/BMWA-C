CC = gcc
CFLAGS = -Iinclude -mconsole
LDFLAGS_MACOS = -framework Cocoa
LDFLAGS_WINDOWS = -luser32 -lgdi32
LDFLAGS = $(shell if [ `uname` = "Darwin" ]; then echo $(LDFLAGS_MACOS); else echo $(LDFLAGS_WINDOWS); fi)

SRCS = $(wildcard src/*.c)
OBJS = $(patsubst src/%.c,obj/%.o,$(SRCS))
MAIN_OBJ = main.o

obj/%.o: src/%.c | obj
	@$(CC) $(CFLAGS) -c $< -o $@

obj:
	@mkdir -p obj

app: $(OBJS) $(MAIN_OBJ)
	@$(CC) $(CFLAGS) $^ $(LDFLAGS) -o "Bangkok Metro"

main.o: main.c
	@$(CC) $(CFLAGS) -c $< -o $@

.PHONY: run clean

run: app
	@./Bangkok\ Metro

clean:
	@rm -f $(OBJS) $(MAIN_OBJ) "Bangkok Metro"
