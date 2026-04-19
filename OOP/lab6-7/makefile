CXX = g++
CXXFLAGS = -Iinclude -Wall -Wextra -Werror -g -std=c++20 -O3

# Caută fișiere .cpp în loc de .c
SRCS = $(shell find src -name '*.cpp')
SRCS_TEST = $(shell find test -name '*.cpp')
SRCS_NO_MAIN = $(filter-out src/main.cpp src/ui.cpp, $(SRCS))

TARGET = main
TEST_TARGET = test_suite

CXXFLAGS_COV = --coverage -O0 -g -fno-elide-constructors
LDFLAGS_COV = --coverage

# Declarăm țintele care nu sunt fișiere reale
.PHONY: all coverage clean

all: $(TARGET)

# Executabilul principal compilează DOAR codul sursă, FĂRĂ teste
$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

# Regula de coverage compilează codul sursă + testele
coverage:
	rm -f *.gcda *.gcno coverage.out
	$(CXX) $(CXXFLAGS) $(CXXFLAGS_COV) -Iinclude -o $(TEST_TARGET) $(SRCS_NO_MAIN) $(SRCS_TEST) $(LDFLAGS_COV)
	./$(TEST_TARGET) t
	lcov --capture --directory . --output-file coverage.out --base-directory $(PWD) --no-external --quiet --rc branch_coverage=1
	lcov --remove coverage.out '*/src/main.cpp' '*/src/ui.cpp' '*/test/*' -o coverage.out --ignore-errors unused,inconsistent
	genhtml coverage.out --output-directory out
	firefox ./out/index.html

clean:
	rm -f *.gcda *.gcno coverage.out $(TEST_TARGET) $(TARGET)
	rm -rf out/
