# Makefile for BigNumber String Calculator (Windows/MinGW)

# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11
DEBUGFLAGS = -g -O0 -DDEBUG
RELEASEFLAGS = -O3 -DNDEBUG

# Directories
SRCDIR = .
OBJDIR = obj
BINDIR = bin

# Target executable
TARGET = $(BINDIR)/calculator.exe

# Source files
SOURCES = $(SRCDIR)/main.cpp $(SRCDIR)/BigNumber.cpp $(SRCDIR)/StringCalculator.cpp
OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SOURCES))

# Default target
all: dirs release

# Create necessary directories
dirs:
	@if not exist "$(OBJDIR)" mkdir $(OBJDIR)
	@if not exist "$(BINDIR)" mkdir $(BINDIR)

# Debug build
debug: CXXFLAGS += $(DEBUGFLAGS)
debug: dirs $(TARGET)_debug

$(TARGET)_debug: $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Release build
release: CXXFLAGS += $(RELEASEFLAGS) 
release: dirs $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile source files to object files
$(OBJDIR)/main.o: $(SRCDIR)/main.cpp $(SRCDIR)/BigNumber.h $(SRCDIR)/StringCalculator.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OBJDIR)/BigNumber.o: $(SRCDIR)/BigNumber.cpp $(SRCDIR)/BigNumber.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OBJDIR)/StringCalculator.o: $(SRCDIR)/StringCalculator.cpp $(SRCDIR)/StringCalculator.h $(SRCDIR)/BigNumber.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Clean build files
clean:
	@if exist "$(OBJDIR)" rmdir /s /q $(OBJDIR)
	@if exist "$(BINDIR)" rmdir /s /q $(BINDIR)

# Run program
run: release
	$(TARGET)

# Run debug version
run_debug: debug
	$(TARGET)_debug

# Phony targets
.PHONY: all clean debug release run run_debug dirs 