#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <stdexcept>
#include <cstring>
#include <cmath>
#include "StringCalculator.h"
#include "BigNumber.h"

// Validates if a character is allowed in numeric strings
bool isValidNumericChar(char c) {
    // ASCII values for different character types
    // Digits: 48-57 ('0'-'9')
    // Decimal point: 46 ('.')
    // Plus sign: 43 ('+')
    // Minus sign: 45 ('-')
    // 'e': 101, 'E': 69
    // '^': 94
    
    // Check if digit (0-9)
    if (c >= 48 && c <= 57) {
        return true;
    }
    
    // Check if one of the special characters (., +, -, e, E, ^)
    switch (c) {
        case 46: // '.'
        case 43: // '+'
        case 45: // '-'
        case 101: // 'e'
        case 69: // 'E'
        case 94: // '^'
            return true;
        default:
            return false;
    }
}

// Validates all characters in a string
void validateNumericString(const char* str, const std::string& errorMsg) {
    for (const char* p = str; *p; p++) {
        if (!isValidNumericChar(*p)) {
            throw std::invalid_argument(errorMsg);
        }
    }
}

// Processes and normalizes a string for use in the BigNumber
std::string preprocessNumericString(const std::string& input) {
    // Manual allocation for string buffers
    char* cleanStr = new char[input.length() + 1];
    
    try {
        // Copy string to buffer and ensure null termination
        std::strcpy(cleanStr, input.c_str());
        
        // Remove spaces
        char* writePos = cleanStr;
        
        for (char* readPos = cleanStr; *readPos; readPos++) {
            if (*readPos != ' ') {
                *(writePos++) = *readPos;
            }
        }
        *writePos = '\0';
        
        // Validate characters
        validateNumericString(cleanStr, "Input contains invalid characters");
        
        // Convert ^ notation to e notation
        std::string result(cleanStr);
        size_t pos;
        while ((pos = result.find('^')) != std::string::npos) {
            result.replace(pos, 1, "e");
        }
        
        // Clean up
        delete[] cleanStr;
        
        return result;
        
    } catch (const std::exception& e) {
        // Clean up allocated memory before throwing
        delete[] cleanStr;
        throw;
    }
}

std::string addNumericStrings(const std::string& num1, const std::string& num2) {
    try {
        // Process input strings
        std::string cleanNum1 = preprocessNumericString(num1);
        std::string cleanNum2 = preprocessNumericString(num2);
        
        // Create BigNumber objects
        BigNumber bn1(cleanNum1);
        BigNumber bn2(cleanNum2);
        
        // Perform addition
        BigNumber result = bn1 + bn2;
        
        return result.toString();
        
    } catch (const std::exception& e) {
        throw std::invalid_argument(std::string("Error parsing numeric strings: ") + e.what());
    }
}

// Additional functions to demonstrate BigNumber capabilities

std::string multiplyNumericStrings(const std::string& num1, const std::string& num2) {
    try {
        // Process input strings
        std::string cleanNum1 = preprocessNumericString(num1);
        std::string cleanNum2 = preprocessNumericString(num2);
        
        // Create BigNumber objects
        BigNumber bn1(cleanNum1);
        BigNumber bn2(cleanNum2);
        
        // Perform multiplication
        BigNumber result = bn1 * bn2;
        
        return result.toString();
        
    } catch (const std::exception& e) {
        throw std::invalid_argument(std::string("Error in multiplication: ") + e.what());
    }
}

std::string divideNumericStrings(const std::string& num1, const std::string& num2) {
    try {
        // Process input strings
        std::string cleanNum1 = preprocessNumericString(num1);
        std::string cleanNum2 = preprocessNumericString(num2);
        
        // Create BigNumber objects
        BigNumber bn1(cleanNum1);
        BigNumber bn2(cleanNum2);
        
        // Check for division by zero
        if (bn2.isZero()) {
            throw std::invalid_argument("Division by zero");
        }
        
        // Perform division
        BigNumber result = bn1 / bn2;
        
        return result.toString();
        
    } catch (const std::exception& e) {
        throw std::invalid_argument(std::string("Error in division: ") + e.what());
    }
}

std::string sqrtNumericString(const std::string& num) {
    try {
        // Process input string
        std::string cleanNum = preprocessNumericString(num);
        
        // Create BigNumber object
        BigNumber bn(cleanNum);
        
        // Check for negative number
        if (bn.isNeg()) {
            throw std::invalid_argument("Cannot compute square root of negative number");
        }
        
        // Calculate square root
        BigNumber result = bn.sqrt();
        
        return result.toString();
        
    } catch (const std::exception& e) {
        throw std::invalid_argument(std::string("Error calculating square root: ") + e.what());
    }
} 