CC = g++
CFLAGS = -Wall -g -Iinclude

SRCS = $(wildcard src/*.cpp) \
       $(wildcard Teste/*.cpp)

OBJS = $(SRCS:.c=.o)

TARGET = app

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)
