CXX = g++
CPPFLAGS = -Iinclude -Wall -Wextra -Werror
SRCS = $(shell find ./src -name *.cpp)
TEST = $(shell find ./Teste -name *.cpp)
TARGET = main

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CPPFLAGS) $(TEST) $(SRCS) -o $(TARGET)

clean:
	rm $(TARGET)
