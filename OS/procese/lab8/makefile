CXX = g++
SRCS = $(shell find ./ -name *.c)
CPPFLAGS = -Wall -Wextra -Werror
TARGET = main

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(SRCS) $(CPPFLAGS) -o $(TARGET)
