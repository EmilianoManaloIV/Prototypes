#include <iostream>
#include <iomanip>
#include "StringCalculator.h"
#include "BigNumber.h"

// Helper function to display calculation results
void displayResult(const std::string& operation, const std::string& num1, const std::string& num2, const std::string& result) {
    std::cout << num1 << " " << operation << " " << num2 << " = " << result << std::endl;
}

// Helper function for unary operations
void displayUnaryResult(const std::string& operation, const std::string& num, const std::string& result) {
    std::cout << operation << "(" << num << ") = " << result << std::endl;
}

int main() {
    try {
        std::cout << "=== String Calculator Demonstration ===" << std::endl << std::endl;
        
        // Example 1: Basic addition
        std::string num1 = "123456789012345678901234567890";
        std::string num2 = "987654321098765432109876543210";
        std::string result = addNumericStrings(num1, num2);
        displayResult("+", num1, num2, result);
        
        // Example 2: Addition with decimal points
        num1 = "123.456";
        num2 = "789.012";
        result = addNumericStrings(num1, num2);
        displayResult("+", num1, num2, result);
        
        // Example 3: Addition with scientific notation
        num1 = "1.23e5";  // 123000
        num2 = "4.56e4";  // 45600
        result = addNumericStrings(num1, num2);
        displayResult("+", num1, num2, result);
        
        // Example 4: Addition with caret notation
        num1 = "1.23^5";  // 123000
        num2 = "4.56^4";  // 45600
        result = addNumericStrings(num1, num2);
        displayResult("+", num1, num2, result);
        
        // Example 5: Subtraction using BigNumber directly
        std::cout << "\n--- Using BigNumber class directly for subtraction ---" << std::endl;
        BigNumber bn1("987654321");
        BigNumber bn2("123456789");
        BigNumber subResult = bn1 - bn2;
        std::cout << bn1.toString() << " - " << bn2.toString() << " = " << subResult.toString() << std::endl;
        
        // Example 6: Multiplication
        std::cout << "\n--- Multiplication ---" << std::endl;
        num1 = "12345";
        num2 = "67890";
        result = multiplyNumericStrings(num1, num2);
        displayResult("*", num1, num2, result);
        
        // Example 7: Multiplication with decimals
        num1 = "123.45";
        num2 = "67.890";
        result = multiplyNumericStrings(num1, num2);
        displayResult("*", num1, num2, result);
        
        // Example 8: Division
        std::cout << "\n--- Division ---" << std::endl;
        num1 = "1000";
        num2 = "3";
        result = divideNumericStrings(num1, num2);
        displayResult("/", num1, num2, result);
        
        // Example 9: Division with decimal result
        num1 = "10";
        num2 = "3";
        result = divideNumericStrings(num1, num2);
        displayResult("/", num1, num2, result);
        
        // Example 10: Square root
        std::cout << "\n--- Square Root ---" << std::endl;
        num1 = "144";
        result = sqrtNumericString(num1);
        displayUnaryResult("sqrt", num1, result);
        
        // Example 11: Square root of large number
        num1 = "1234567890123456789";
        result = sqrtNumericString(num1);
        displayUnaryResult("sqrt", num1, result);
        
        // Example 12: Very large numbers
        std::cout << "\n--- Very Large Numbers ---" << std::endl;
        num1 = "9999999999999999999999999999999999999999";
        num2 = "1";
        result = addNumericStrings(num1, num2);
        displayResult("+", num1, num2, result);
        
        // Example 13: Error handling - negative square root
        std::cout << "\n--- Error Handling ---" << std::endl;
        try {
            num1 = "-100";
            result = sqrtNumericString(num1);
            displayUnaryResult("sqrt", num1, result);
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
        
        // Example 14: Error handling - division by zero
        try {
            num1 = "100";
            num2 = "0";
            result = divideNumericStrings(num1, num2);
            displayResult("/", num1, num2, result);
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
        
        // Example 15: Error handling - invalid character
        try {
            num1 = "123abc";
            num2 = "456";
            result = addNumericStrings(num1, num2);
            displayResult("+", num1, num2, result);
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
        
        return 0;
        
    } catch (const std::exception& e) {
        std::cerr << "Unhandled exception: " << e.what() << std::endl;
        return 1;
    }
} 