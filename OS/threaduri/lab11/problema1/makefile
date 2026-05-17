CXX = gcc
CXXFLAGS = -Wall -Wextra -Werror -g
SRCS=$(shell find ./ -name *.c)
TARGET=main

all:
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm $(TARGET)


