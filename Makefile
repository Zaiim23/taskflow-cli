CC ?= gcc
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic -O2
CPPFLAGS = -Iinclude
TARGET = taskflow
SOURCES = src/main.c src/task.c src/storage.c
HEADERS = include/task.h include/storage.h

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(SOURCES) $(HEADERS)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(SOURCES) -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) $(TARGET).exe
