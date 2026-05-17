CXX = g++
SRCS = $(shell find ./src -name *.cpp)
CPPFLAGS = -Wall -Wextra -Werror -g
TARGET = p2

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(SRCS) $(CPPFLAGS) -o $(TARGET)


