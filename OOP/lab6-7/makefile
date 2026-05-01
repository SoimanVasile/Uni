CXX = g++

QT_FLAGS = $(shell pkg-config --cflags Qt6Widgets)
QT_LIBS = $(shell pkg-config --libs Qt6Widgets)

CXXFLAGS = -Iinclude -Wall -Wextra -Werror -g -std=c++20 -O3 -fPIC $(QT_FLAGS)

MOC= /usr/lib/qt6/moc

SRCS_RAW = $(shell find src -name '*.cpp')
SRCS = $(filter-out src/moc_%.cpp, $(SRCS_RAW))
SRCS_TEST = $(shell find test -name '*.cpp')
SRCS_NO_MAIN = $(filter-out src/main.cpp src/ui.cpp, $(SRCS))

TARGET = main
TEST_TARGET = test_suite

CXXFLAGS_COV = --coverage -O0 -g -fno-elide-constructors
LDFLAGS_COV = --coverage

UI_HEADERS=src/MainWindow.h
MOC_SRCS=$(UI_HEADERS:src/%.h=src/moc_%.cpp)

.PHONY: all coverage clean

all: $(TARGET)

src/moc_%.cpp: src/%.h
	$(MOC) $< -o $@

$(TARGET): $(MOC_SRCS) $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS) $(MOC_SRCS) $(QT_LIBS)

coverage:
	rm -f *.gcda *.gcno coverage.out
	$(CXX) $(CXXFLAGS) $(CXXFLAGS_COV) -Iinclude -o $(TEST_TARGET) $(SRCS_NO_MAIN) $(SRCS_TEST) $(LDFLAGS_COV) $(QT_LIBS)
	./$(TEST_TARGET) t
	lcov --capture --directory . --output-file coverage.out --base-directory $(PWD) --no-external --quiet --rc branch_coverage=1
	lcov --remove coverage.out '*/src/main.cpp' '*/src/ui.cpp' '*/test/*' -o coverage.out --ignore-errors unused,inconsistent
	genhtml coverage.out --output-directory out
	firefox ./out/index.html

clean:
	rm -f *.gcda *.gcno coverage.out $(TEST_TARGET) $(TARGET) $(MOC_SRCS)
	rm -rf out/
