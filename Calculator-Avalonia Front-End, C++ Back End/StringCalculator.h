#ifndef STRING_CALCULATOR_H
#define STRING_CALCULATOR_H

#include <string>

/*
FUNCTION: Validates if a character is allowed in numeric strings
INPUT: A single character (char)
OUTPUT: Boolean (true if the character is valid, false otherwise)
SCALE: O(1)
LIMITATIONS: Only checks for characters valid in numeric notation
DATE: 2023-06-11
*/
bool isValidNumericChar(char c);

/*
FUNCTION: Validates all characters in a string
INPUT: A C-string (const char*) and an error message (const std::string&)
OUTPUT: void (throws exception if invalid character found)
SCALE: O(n) where n is the length of the string
LIMITATIONS: None
DATE: 2023-06-11
*/
void validateNumericString(const char* str, const std::string& errorMsg);

/*
FUNCTION: Processes and normalizes a string for use in the BigNumber
INPUT: A std::string containing a numeric value
OUTPUT: A cleaned and normalized std::string
SCALE: O(n) where n is the length of the string
LIMITATIONS: Throws exception for invalid characters
DATE: 2023-06-11
*/
std::string preprocessNumericString(const std::string& input);

/*
FUNCTION: Adds two numeric strings that can be integers, floats, or in scientific notation
INPUT: Two std::string values representing numbers
OUTPUT: std::string containing the result of addition
SCALE: O(n) where n is the maximum length of the input strings
LIMITATIONS: Uses custom big number implementation for arbitrary precision. Not limited by C++ built-in numeric types.
DATE: 2023-06-11
*/
std::string addNumericStrings(const std::string& num1, const std::string& num2);

/*
FUNCTION: Multiplies two numeric strings
INPUT: Two std::string values representing numbers
OUTPUT: std::string containing the result of multiplication
SCALE: O(n^2) where n is the maximum length of the input strings
LIMITATIONS: Uses custom big number implementation for arbitrary precision
DATE: 2023-06-11
*/
std::string multiplyNumericStrings(const std::string& num1, const std::string& num2);

/*
FUNCTION: Divides two numeric strings
INPUT: Two std::string values representing numbers (dividend and divisor)
OUTPUT: std::string containing the result of division
SCALE: O(n^2) where n is the length of the dividend string
LIMITATIONS: Limited precision for recurring decimals
DATE: 2023-06-11
*/
std::string divideNumericStrings(const std::string& num1, const std::string& num2);

/*
FUNCTION: Calculates the square root of a numeric string
INPUT: A std::string representing a non-negative number
OUTPUT: std::string containing the square root result
SCALE: O(n^2 * iterations) where n is the length of the input string and iterations is the number of Newton's method iterations
LIMITATIONS: Approximation using Newton's method, limited by the number of iterations
DATE: 2023-06-11
*/
std::string sqrtNumericString(const std::string& num);

#endif // STRING_CALCULATOR_H