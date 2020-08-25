CXX = g++
CXXFLAGS = -std=gnu++17

default:
	$(CXX) $(CXXFLAGS) *.h *.cpp -o range

