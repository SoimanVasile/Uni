CC = gcc
CFLAGS = -Iinclude -Wall -Wextra -Werror -g -std=c23

SRCS = $(shell find src -name '*.c')
SRCS_TEST = $(shell find test -name '*.c')
TARGET = main
CFLAGS_COV = --coverage -O0 -g -std=c23
LDFLAGS_COV = --coverage

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS) $(SRCS_TEST)

coverage:
	rm -f *.gcda *.gcno coverage.out
	$(CC) $(CFLAGS_COV) -Iinclude -o test_suite $(SRCS) $(SRCS_TEST) $(LDFLAGS_COV)
	./test_suite t
	lcov --capture --directory . --output-file coverage.out --base-directory $(PWD) --quiet --rc branch_coverage=1
	genhtml coverage.out --output-directory out
	firefox ./out/index.html

clean:
	rm -f *.gcda *.gcno coverage.out test_suite main

