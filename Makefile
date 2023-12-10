CXX = g++
CXXFLAGS = -Wall -std=c++11
TARGET = road

SRCDIR = src

# Source files
SOURCES = $(SRCDIR)/sim.cpp

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

clean:
	$(RM) $(TARGET)