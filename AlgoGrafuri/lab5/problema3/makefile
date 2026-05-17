CXX = g++
SRCS=$(shell find src -name *.cpp)
CXXFLAGS = -Wall -Wextra -Werror -g -std=c++20 -Iinclude
TARGET=p3

all: $(TARGET)

$(TARGET): 
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm $(TARGET)
