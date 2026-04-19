CXX = g++
SRCS = $(shell find ./src -name *.cpp)
CPPFLAGS = -Wall -Wextra -Werror
TARGET = main

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(SRCS) $(CPPFLAGS) -o $(TARGET)
