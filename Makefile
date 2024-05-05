CC = gcc
CFLAGS = -Iinclude -mconsole
LDFLAGS = -luser32 -lgdi32 # Additional libraries might be needed for console apps

SRCS = $(wildcard src/*.c)
OBJS = $(patsubst src/%.c,obj/%.o,$(SRCS))
MAIN_OBJ = main.o

obj/%.o: src/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

app: $(OBJS) $(MAIN_OBJ)
	@$(CC) $(CFLAGS) $^ $(LDFLAGS) -o app

main.o: main.c
	@$(CC) $(CFLAGS) -c $< -o $@

.PHONY: run clean

run: app
	@./app

clean:
	@rm -f $(OBJS) $(MAIN_OBJ) app