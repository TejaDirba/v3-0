CXX       := g++
CXXFLAGS  := -std=c++17 -O2 -Wall -Wextra
INC_DIR   := include
SRC_DIR   := src
TEST_DIR  := tests

SRCS      := $(wildcard $(SRC_DIR)/*.cpp)
OBJS      := $(SRCS:.cpp=.o)
TARGET    := app

VECTEST   := VectorTests
STUTEST   := StudentTests

.PHONY: all bench test-std test-vec docs clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -o $@ $^

bench: CXXFLAGS += -DUSE_STD
bench: bench.o
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -o $@ bench.o

bench.o: bench.cpp
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -c $< -o $@

test-std: CXXFLAGS += -DUSE_STD -I$(INC_DIR)
test-std: $(TARGET) $(TEST_DIR)/VectorTests.cpp $(TEST_DIR)/StudentTests.cpp
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -lgtest -lpthread -o $(VECTEST) $(TEST_DIR)/VectorTests.cpp
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -lgtest -lpthread -o $(STUTEST) $(TEST_DIR)/StudentTests.cpp
	./$(VECTEST)
	./$(STUTEST)

test-vec: CXXFLAGS += -I$(INC_DIR)
test-vec: bench test-std

docs:
	doxygen docs/Doxyfile

clean:
	rm -f src/*.o bench.o $(TARGET) $(VECTEST) $(STUTEST)
	rm -rf html latex
