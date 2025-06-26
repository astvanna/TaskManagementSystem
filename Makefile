# Compiler settings
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude
GTEST_FLAGS = -lgtest -lgtest_main -pthread

# Directories
SRC_DIR = src
TEST_DIR = tests

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(SRCS:.cpp=.o)
TEST_SRCS = $(wildcard $(TEST_DIR)/*.cpp)

# Executables
MAIN_EXEC = task_manager
TEST_EXEC = run_tests

.PHONY: all clean test

all: $(MAIN_EXEC)

$(MAIN_EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

test: $(TEST_EXEC)
	./$(TEST_EXEC)

$(TEST_EXEC): $(OBJS) $(TEST_SRCS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(GTEST_FLAGS)

clean:
	rm -f $(OBJS) $(MAIN_EXEC) $(TEST_EXEC)
