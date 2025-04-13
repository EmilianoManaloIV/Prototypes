#ifndef BIG_NUMBER_H
#define BIG_NUMBER_H

#include <string>

/*
CLASS: BigNumber
PURPOSE: Handles arbitrarily large numbers with unlimited precision
OPERATIONS: Addition, subtraction, multiplication, and string conversion
LIMITATIONS: Performance may degrade with extremely large numbers
DATE: 2023-06-11
*/
class BigNumber {
private:
    std::string digits;  // Stores digits without decimal point
    int exponent;        // Position of decimal point
    bool isNegative;     // Sign of the number

public:
    // Constructor from string
    BigNumber(const std::string& numStr);
    
    // Default constructor - creates zero
    BigNumber();
    
    // Parse string to BigNumber
    void parse(const std::string& numStr);
    
    // Normalize the BigNumber representation
    void normalize();
    
    // Addition operator
    BigNumber operator+(const BigNumber& other) const;
    
    // Subtraction operator
    BigNumber operator-(const BigNumber& other) const;
    
    // Multiplication operator
    BigNumber operator*(const BigNumber& other) const;
    
    // Division operator
    BigNumber operator/(const BigNumber& other) const;
    
    // Compare absolute values of two BigNumbers
    static int compareAbsoluteValue(const BigNumber& a, const BigNumber& b);
    
    // Convert to string for output
    std::string toString() const;
    
    // Returns absolute value of this number
    BigNumber abs() const;
    
    // Square root operation
    BigNumber sqrt() const;
    
    // Check if the number is zero
    bool isZero() const;
    
    // Check if the number is negative
    bool isNeg() const;
    
    // Get the sign of the number (-1, 0, 1)
    int sign() const;
};

#endif // BIG_NUMBER_H 