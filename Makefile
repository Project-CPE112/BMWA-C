CC = gcc
CFLAGS = -Wall -Wextra -std=c11

SRCDIR = src
INCDIR = include
BUILDDIR = build
TARGETDIR = bin

SOURCES := $(wildcard $(SRCDIR)/*.c)
OBJECTS := $(patsubst $(SRCDIR)/%.c, $(BUILDDIR)/%.o, $(SOURCES))
TARGET = $(TARGETDIR)/output

$(TARGET): $(OBJECTS)
	@mkdir -p $(TARGETDIR)
	$(CC) $(CFLAGS) $^ -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

clean:
	@rm -rf $(BUILDDIR) $(TARGET)

.PHONY: clean