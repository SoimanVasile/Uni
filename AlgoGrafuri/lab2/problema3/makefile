CC = g++
CPPFLAGS = -g -Wall -Wextra -std=c++11

SRCS = $(shell find -name '*.cpp')
TARGET = main

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CPPFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)


