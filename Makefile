CXX = g++
CXXFLAGS = -std=c++17 -Wall -I/opt/homebrew/Cellar/sfml/3.0.0_1/include
LDFLAGS = -L/opt/homebrew/Cellar/sfml/3.0.0_1/lib -lsfml-network -lcurl
TARGET = vigilis
SRC = main.cpp
OBJ = $(SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(TARGET) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean
