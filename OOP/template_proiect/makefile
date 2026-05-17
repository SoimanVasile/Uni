CXX = g++

MOC = /usr/lib/qt6/moc
ifeq ($(shell test -e $(MOC); echo $$?), 1)
    MOC = moc-qt6
endif

QT_FLAGS = $(shell pkg-config --cflags Qt6Widgets)
QT_LIBS = $(shell pkg-config --libs Qt6Widgets)

CXXFLAGS = -Iinclude -Isrc -Wall -Wextra -std=c++20 -g -fPIC $(QT_FLAGS) --coverage
LDFLAGS = --coverage

SRCS = $(shell find src -name '*.cpp' ! -name 'moc_*.cpp')
OBJS = $(SRCS:.cpp=.o)

TEST_SRCS = $(shell find test -name '*.cpp')
TEST_OBJS = $(TEST_SRCS:.cpp=.o)

MOC_HEADERS = $(shell grep -l "Q_OBJECT" include/*.h 2>/dev/null)
MOC_SRCS = $(patsubst include/%.h, src/moc_%.cpp, $(MOC_HEADERS))
MOC_OBJS = $(MOC_SRCS:.cpp=.o)

TARGET = main
TEST_TARGET = run_tests

.PHONY: all clean coverage test

all: $(TARGET)

$(TARGET): $(OBJS) $(MOC_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(QT_LIBS) $(LDFLAGS)

src/moc_%.cpp: include/%.h
	@mkdir -p src
	$(MOC) $(QT_FLAGS) $< -o $@

$(TEST_TARGET): $(filter-out src/main.o, $(OBJS)) $(MOC_OBJS) $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(QT_LIBS) $(LDFLAGS)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

coverage: test
	lcov --capture --directory . --output-file coverage.info --include "$(shell pwd)/src/*"
	genhtml coverage.info --output-directory out
	@echo "Report: file://$(shell pwd)/out/index.html"

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(TEST_TARGET) coverage.info
	find src -name "*.o" -delete
	find src -name "*.gcno" -delete
	find src -name "*.gcda" -delete
	find src -name "moc_*.cpp" -delete
	find test -name "*.o" -delete
	rm -rf out
