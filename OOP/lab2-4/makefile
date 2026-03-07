CC = gcc
CFLAGS = -Iinclude -Wall -Wextra -Werror -g

SRCS = $(shell find src -name '*.c')
SRCS_TEST = $(shell find test -name '*.c')
TARGET = main

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS) $(SRCS_TEST)

clean:
	rm -f $(TARGET)

