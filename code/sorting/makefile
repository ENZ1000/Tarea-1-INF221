CXX = g++
CXXFLAGS = -std=c++17 -O3 -Wall -pthread

TARGET = sorting

all: $(TARGET)

$(TARGET): sorting.cpp
	$(CXX) $(CXXFLAGS) sorting.cpp -o $(TARGET)

clean:
	rm -f $(TARGET)