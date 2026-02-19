CXX = g++
CXXFLAGS = -std=c++17 -Wall -g

SRC = src/main.cpp \
      src/renderer/renderer.cpp \
      src/renderer/background.cpp

OUT = void_wm

all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT)

clean:
	rm -f $(OUT)
