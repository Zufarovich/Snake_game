CXX = g++
CXXFLAGS = -Wall -g -O0 -O -std=c++11
PROJ = snake

all:
	$(CXX) main.cpp game.cpp view.cpp Tview.cpp Gview.cpp controller.cpp $(CXXFLAGS) -o $(PROJ)
