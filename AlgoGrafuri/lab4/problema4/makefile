CXX = g++
SRCS = $(shell find ./src -name *.cpp)
CPPFLAGS = -Wall -Wextra -Werror -g -std=c++11
TARGET = p4

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(SRCS) $(CPPFLAGS) -o $(TARGET)

