CXX = g++
CXXFLAGS = -std=c++17 -O3 -Wall

TARGET = matrix_multiplication

all: $(TARGET)

$(TARGET): matrix_multiplication.cpp
	$(CXX) $(CXXFLAGS) matrix_multiplication.cpp -o $(TARGET)

clean:
	rm -f $(TARGET)