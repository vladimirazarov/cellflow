CXX = g++
CXXFLAGS = -Wall -std=c++11
TARGET = road
SRCDIR = src
ZIPFILE = 08_xazaro00.zip

# Source files
SOURCES = $(SRCDIR)/sim.cpp

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

clean:
	$(RM) $(TARGET) $(ZIPFILE) out.txt

zip:
	zip $(ZIPFILE) -r src scripts doc LICENSE Makefile README.md .gitignore

# Optional: Add a target to run the python script
plot:
	python scripts/gen.py