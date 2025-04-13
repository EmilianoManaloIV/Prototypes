# BigNumber String Calculator

A C++ library for arbitrary precision arithmetic operations on very large numbers represented as strings.

## Features

- Arbitrary precision arithmetic (not limited by built-in data types)
- Support for extremely large integers and floating-point numbers
- Scientific notation support (both 1.23e5 and 1.23^5 formats)
- Operations: addition, subtraction, multiplication, division, square root
- Robust error handling
- Clean separation of OOP and structured programming approaches

## Building the Project

### Using the Batch Script (Windows)

For convenience, a batch script is provided to build the project without requiring make:

```
# Build release version
build.bat

# Build debug version
build.bat debug

# Clean build files
build.bat clean

# Build and run the program
build.bat run
```

### Using Make (Windows with MinGW)

If you have Make installed with MinGW, you can use the provided Makefile:

```
# Build release version
make

# Build debug version
make debug

# Clean build files
make clean

# Build and run release version
make run

# Build and run debug version
make run_debug
```

### Manual Compilation

If you prefer to compile manually:

```
# Create directories
mkdir -p obj bin

# Compile source files
g++ -Wall -Wextra -std=c++11 -c -o obj/BigNumber.o BigNumber.cpp
g++ -Wall -Wextra -std=c++11 -c -o obj/StringCalculator.o StringCalculator.cpp
g++ -Wall -Wextra -std=c++11 -c -o obj/main.o main.cpp

# Link object files
g++ -Wall -Wextra -std=c++11 -o bin/calculator.exe obj/main.o obj/BigNumber.o obj/StringCalculator.o
```

## Usage Examples

The `main.cpp` file contains several examples demonstrating the functionality:

```cpp
// Addition of large numbers
std::string num1 = "123456789012345678901234567890";
std::string num2 = "987654321098765432109876543210";
std::string result = addNumericStrings(num1, num2);

// Multiplication with decimals
num1 = "123.45";
num2 = "67.890";
result = multiplyNumericStrings(num1, num2);

// Division
num1 = "1000";
num2 = "3";
result = divideNumericStrings(num1, num2);

// Square root
num1 = "144";
result = sqrtNumericString(num1);
```

## Class Structure

- **BigNumber**: Core class for arbitrary precision arithmetic
- **StringCalculator**: Functions for handling string inputs/outputs and conversions

## File Organization

- **BigNumber.h**: BigNumber class definition
- **BigNumber.cpp**: BigNumber class implementation
- **StringCalculator.h**: String calculator functions declarations
- **StringCalculator.cpp**: String calculator functions implementations
- **main.cpp**: Example program demonstrating functionality

## Error Handling

The library includes robust error handling for:
- Invalid input characters
- Division by zero
- Negative square roots
- Syntax errors in numeric strings

## Performance Considerations

- Operations on very large numbers may be slower than built-in types
- Memory usage scales with the size of the numbers being processed
- The implementation prioritizes correctness over maximum performance 