.PHONY: all clean format doxy test

CXX = g++
CXXFLAGS = -O2 -Wall -DNDEBUG -std=c++17
LDFLAGS = -lcryptopp -lboost_program_options -lUnitTest++ -pthread

TARGET = Server
SOURCES = communicator.cpp calc.cpp interface.cpp base.cpp log.cpp main.cpp
OBJECTS = $(SOURCES:.cpp=.o)

TEST_SOURCES = communicator.cpp calc.cpp interface.cpp base.cpp log.cpp testiki.cpp
TEST_OBJECTS = $(TEST_SOURCES:.cpp=.o)
TEST_TARGET = test

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) $(LDFLAGS) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

test: $(TEST_OBJECTS)
	$(CXX) $(TEST_OBJECTS) $(LDFLAGS) -o $(TEST_TARGET)

format:
	astyle *.cpp *.h

clean:
	rm -f $(TARGET) $(TEST_TARGET) *.o
