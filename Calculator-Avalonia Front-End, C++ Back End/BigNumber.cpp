#include "BigNumber.h"
#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <vector>

// Default constructor - creates zero
BigNumber::BigNumber() : digits("0"), exponent(0), isNegative(false) {}

// Constructor from string
BigNumber::BigNumber(const std::string& numStr) {
    parse(numStr);
}

// Parse string to BigNumber
void BigNumber::parse(const std::string& numStr) {
    digits = "";
    exponent = 0;
    isNegative = false;
    
    // Check for negative sign
    size_t startPos = 0;
    if (numStr[0] == '-') {
        isNegative = true;
        startPos = 1;
    } else if (numStr[0] == '+') {
        startPos = 1;
    }

    std::string mantissa;
    int expValue = 0;
    bool hasExponent = false;

    // Find 'e' or '^' for scientific notation
    size_t ePos = numStr.find_first_of("eE^", startPos);
    
    if (ePos != std::string::npos) {
        mantissa = numStr.substr(startPos, ePos - startPos);
        // Extract exponent value
        std::string expStr = numStr.substr(ePos + 1);
        expValue = std::stoi(expStr);
        hasExponent = true;
    } else {
        mantissa = numStr.substr(startPos);
    }

    // Find decimal point
    size_t decPos = mantissa.find('.');
    if (decPos != std::string::npos) {
        // Remove decimal point and adjust exponent
        std::string beforeDec = mantissa.substr(0, decPos);
        std::string afterDec = mantissa.substr(decPos + 1);
        digits = beforeDec + afterDec;
        exponent = -static_cast<int>(afterDec.length());
    } else {
        digits = mantissa;
        exponent = 0;
    }

    // Remove leading zeros
    size_t firstNonZero = digits.find_first_not_of('0');
    if (firstNonZero != std::string::npos) {
        digits = digits.substr(firstNonZero);
    } else {
        digits = "0";
        isNegative = false;
    }

    // Apply scientific notation exponent
    if (hasExponent) {
        exponent += expValue;
    }
    
    // Normalize representation
    normalize();
}

// Normalize the BigNumber representation
void BigNumber::normalize() {
    if (digits.empty() || digits == "0") {
        digits = "0";
        exponent = 0;
        isNegative = false;
        return;
    }

    // Remove trailing zeros for numbers with negative exponent
    if (exponent < 0) {
        int trailingZeros = 0;
        for (int i = digits.length() - 1; i >= 0; i--) {
            if (digits[i] == '0') {
                trailingZeros++;
            } else {
                break;
            }
        }
        
        int zerosToRemove = std::min(trailingZeros, -exponent);
        if (zerosToRemove > 0) {
            digits = digits.substr(0, digits.length() - zerosToRemove);
            exponent += zerosToRemove;
        }
    }
}

// Addition operator
BigNumber BigNumber::operator+(const BigNumber& other) const {
    // If one number is negative and the other is positive, use subtraction
    if (isNegative && !other.isNegative) {
        BigNumber temp = *this;
        temp.isNegative = false;
        return other - temp;
    }
    if (!isNegative && other.isNegative) {
        BigNumber temp = other;
        temp.isNegative = false;
        return *this - temp;
    }

    // Determine which number has more digits before decimal point
    int thisBeforeDecimal = digits.length() + exponent;
    int otherBeforeDecimal = other.digits.length() + other.exponent;
    
    // Align numbers for addition
    std::string alignedThis = digits;
    std::string alignedOther = other.digits;
    
    int resultExponent = std::min(exponent, other.exponent);
    
    // Pad with zeros to align decimal points
    if (exponent > resultExponent) {
        alignedThis.append(exponent - resultExponent, '0');
    } else if (other.exponent > resultExponent) {
        alignedOther.append(other.exponent - resultExponent, '0');
    }
    
    // Ensure both numbers have the same length by padding left with zeros
    if (alignedThis.length() < alignedOther.length()) {
        alignedThis = std::string(alignedOther.length() - alignedThis.length(), '0') + alignedThis;
    } else if (alignedOther.length() < alignedThis.length()) {
        alignedOther = std::string(alignedThis.length() - alignedOther.length(), '0') + alignedOther;
    }
    
    // Perform addition
    std::string resultDigits;
    int carry = 0;
    
    for (int i = alignedThis.length() - 1; i >= 0; i--) {
        int digit1 = alignedThis[i] - '0';
        int digit2 = alignedOther[i] - '0';
        
        int sum = digit1 + digit2 + carry;
        carry = sum / 10;
        sum %= 10;
        
        resultDigits.push_back(sum + '0');
    }
    
    if (carry > 0) {
        resultDigits.push_back(carry + '0');
    }
    
    std::reverse(resultDigits.begin(), resultDigits.end());
    
    // Create result
    BigNumber result("0");
    result.digits = resultDigits;
    result.exponent = resultExponent;
    result.isNegative = isNegative; // Both numbers have the same sign
    result.normalize();
    
    return result;
}

// Subtraction operator
BigNumber BigNumber::operator-(const BigNumber& other) const {
    // Handle sign differences
    if (isNegative && !other.isNegative) {
        BigNumber temp = *this;
        temp.isNegative = false;
        BigNumber result = temp + other;
        result.isNegative = true;
        return result;
    }
    if (!isNegative && other.isNegative) {
        BigNumber temp = other;
        temp.isNegative = false;
        return *this + temp;
    }
    
    // Determine which number has greater absolute value
    bool thisGreater = (compareAbsoluteValue(*this, other) >= 0);
    
    // Align numbers for subtraction
    std::string alignedThis = digits;
    std::string alignedOther = other.digits;
    
    int resultExponent = std::min(exponent, other.exponent);
    
    // Pad with zeros to align decimal points
    if (exponent > resultExponent) {
        alignedThis.append(exponent - resultExponent, '0');
    } else if (other.exponent > resultExponent) {
        alignedOther.append(other.exponent - resultExponent, '0');
    }
    
    // Ensure both numbers have the same length by padding left with zeros
    if (alignedThis.length() < alignedOther.length()) {
        alignedThis = std::string(alignedOther.length() - alignedThis.length(), '0') + alignedThis;
    } else if (alignedOther.length() < alignedThis.length()) {
        alignedOther = std::string(alignedThis.length() - alignedOther.length(), '0') + alignedOther;
    }
    
    // Perform subtraction (greater - smaller)
    std::string resultDigits;
    int borrow = 0;
    
    // If this number is less than other, swap them and negate the result
    if (!thisGreater) {
        std::swap(alignedThis, alignedOther);
    }
    
    for (int i = alignedThis.length() - 1; i >= 0; i--) {
        int digit1 = alignedThis[i] - '0';
        int digit2 = alignedOther[i] - '0';
        
        digit1 -= borrow;
        
        if (digit1 < digit2) {
            digit1 += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        
        int diff = digit1 - digit2;
        resultDigits.push_back(diff + '0');
    }
    
    std::reverse(resultDigits.begin(), resultDigits.end());
    
    // Create result
    BigNumber result("0");
    result.digits = resultDigits;
    result.exponent = resultExponent;
    
    // Determine result sign
    result.isNegative = (isNegative == thisGreater);
    
    result.normalize();
    return result;
}

// Multiplication operator
BigNumber BigNumber::operator*(const BigNumber& other) const {
    // Handle special case: either number is zero
    if (isZero() || other.isZero()) {
        return BigNumber(); // Return zero
    }
    
    // Determine the sign of the result
    bool resultNegative = (isNegative != other.isNegative);
    
    // Calculate the resulting exponent
    int resultExponent = exponent + other.exponent;
    
    // Perform long multiplication, digit by digit
    std::vector<int> result(digits.length() + other.digits.length(), 0);
    
    for (int i = digits.length() - 1; i >= 0; i--) {
        int carry = 0;
        int digit1 = digits[i] - '0';
        
        for (int j = other.digits.length() - 1; j >= 0; j--) {
            int digit2 = other.digits[j] - '0';
            int product = digit1 * digit2 + result[i + j + 1] + carry;
            
            carry = product / 10;
            result[i + j + 1] = product % 10;
        }
        
        result[i] += carry;
    }
    
    // Convert result vector to string, removing leading zeros
    std::string resultDigits;
    bool leadingZeros = true;
    
    for (size_t i = 0; i < result.size(); i++) {
        if (leadingZeros && result[i] == 0) {
            continue;
        }
        leadingZeros = false;
        resultDigits.push_back(result[i] + '0');
    }
    
    // If all digits were zero (shouldn't happen because we checked earlier)
    if (resultDigits.empty()) {
        return BigNumber();
    }
    
    // Create the result BigNumber
    BigNumber resultNum;
    resultNum.digits = resultDigits;
    resultNum.exponent = resultExponent;
    resultNum.isNegative = resultNegative;
    resultNum.normalize();
    
    return resultNum;
}

// Division operator
BigNumber BigNumber::operator/(const BigNumber& other) const {
    // Check for division by zero
    if (other.isZero()) {
        throw std::invalid_argument("Division by zero");
    }
    
    // Handle special case: this number is zero
    if (isZero()) {
        return BigNumber(); // Return zero
    }
    
    // Determine the sign of the result
    bool resultNegative = (isNegative != other.isNegative);
    
    // Work with absolute values for division
    BigNumber dividend = abs();
    BigNumber divisor = other.abs();
    
    // Scale numbers to integers for easier division
    // We'll shift the decimal point right by adding zeros
    int shiftAmount = 20; // Precision control - adjust as needed
    
    // Adjust exponents
    int dividendExp = dividend.exponent;
    int divisorExp = divisor.exponent;
    
    // Create new numbers with adjusted exponents
    BigNumber scaledDividend = dividend;
    BigNumber scaledDivisor = divisor;
    
    // Ensure both numbers are integers by scaling
    scaledDividend.exponent = 0;
    scaledDivisor.exponent = 0;
    
    // Adjust the result exponent
    int resultExponent = dividendExp - divisorExp;
    
    // Pad dividend with zeros for precision
    scaledDividend.digits.append(shiftAmount, '0');
    
    // Long division algorithm
    std::string quotientDigits;
    std::string remainderDigits = scaledDividend.digits;
    
    // Perform division
    while (!remainderDigits.empty()) {
        // Find how many times divisor goes into the current remainder
        int quotientDigit = 0;
        std::string currentChunk;
        
        if (remainderDigits.length() < scaledDivisor.digits.length()) {
            // If remainder is smaller than divisor, add a zero to quotient and more digits from dividend
            if (!quotientDigits.empty()) {
                quotientDigits += '0';
            }
            break;
        }
        
        // Extract enough digits from remainder to be compared with divisor
        currentChunk = remainderDigits.substr(0, scaledDivisor.digits.length());
        
        if (currentChunk < scaledDivisor.digits) {
            // Need one more digit from remainder
            if (remainderDigits.length() > scaledDivisor.digits.length()) {
                currentChunk += remainderDigits[scaledDivisor.digits.length()];
                remainderDigits = remainderDigits.substr(scaledDivisor.digits.length() + 1);
            } else {
                // No more digits, so add 0 to quotient
                quotientDigits += '0';
                break;
            }
        } else {
            remainderDigits = remainderDigits.substr(scaledDivisor.digits.length());
        }
        
        // Find how many times divisor goes into currentChunk
        while (currentChunk.length() >= scaledDivisor.digits.length() && 
               (currentChunk.length() > scaledDivisor.digits.length() || currentChunk >= scaledDivisor.digits)) {
            BigNumber chunkNum("0");
            chunkNum.digits = currentChunk;
            chunkNum.exponent = 0;
            
            BigNumber subtractAmount = scaledDivisor;
            
            currentChunk = (chunkNum - subtractAmount).digits;
            quotientDigit++;
        }
        
        quotientDigits += std::to_string(quotientDigit);
        remainderDigits = currentChunk + remainderDigits;
        
        // Remove leading zeros from remainder
        size_t firstNonZero = remainderDigits.find_first_not_of('0');
        if (firstNonZero != std::string::npos) {
            remainderDigits = remainderDigits.substr(firstNonZero);
        } else {
            remainderDigits = "";
        }
    }
    
    // If quotient is empty, it's zero
    if (quotientDigits.empty()) {
        return BigNumber();
    }
    
    // Create result
    BigNumber result("0");
    result.digits = quotientDigits;
    result.exponent = resultExponent - shiftAmount; // Adjust for the scaling we did
    result.isNegative = resultNegative;
    result.normalize();
    
    return result;
}

// Compare absolute values of two BigNumbers
int BigNumber::compareAbsoluteValue(const BigNumber& a, const BigNumber& b) {
    // Compare number of digits before decimal point
    int aBeforeDecimal = a.digits.length() + a.exponent;
    int bBeforeDecimal = b.digits.length() + b.exponent;
    
    if (aBeforeDecimal != bBeforeDecimal) {
        return aBeforeDecimal > bBeforeDecimal ? 1 : -1;
    }
    
    // Align and compare digits
    std::string alignedA = a.digits;
    std::string alignedB = b.digits;
    
    // Align decimal points
    int minExponent = std::min(a.exponent, b.exponent);
    
    if (a.exponent > minExponent) {
        alignedA.append(a.exponent - minExponent, '0');
    } else if (b.exponent > minExponent) {
        alignedB.append(b.exponent - minExponent, '0');
    }
    
    // Pad to equal length
    if (alignedA.length() < alignedB.length()) {
        alignedA = std::string(alignedB.length() - alignedA.length(), '0') + alignedA;
    } else if (alignedB.length() < alignedA.length()) {
        alignedB = std::string(alignedA.length() - alignedB.length(), '0') + alignedB;
    }
    
    // Compare digit by digit
    return alignedA.compare(alignedB);
}

// Convert to string for output
std::string BigNumber::toString() const {
    if (digits == "0") {
        return "0";
    }
    
    std::string result = isNegative ? "-" : "";
    
    if (exponent >= 0) {
        // No decimal point needed, or it's after all digits
        result += digits;
        result.append(exponent, '0');
    } else {
        int absExp = -exponent;
        
        if (absExp >= digits.length()) {
            // 0.000...digits
            result += "0.";
            result.append(absExp - digits.length(), '0');
            result += digits;
        } else {
            // digits with decimal point in the middle
            result += digits.substr(0, digits.length() - absExp);
            result += ".";
            result += digits.substr(digits.length() - absExp);
        }
    }
    
    return result;
}

// Returns absolute value of this number
BigNumber BigNumber::abs() const {
    BigNumber result = *this;
    result.isNegative = false;
    return result;
}

// Square root operation - using Newton's method
BigNumber BigNumber::sqrt() const {
    // Check for negative number
    if (isNegative) {
        throw std::invalid_argument("Cannot compute square root of negative number");
    }
    
    // Special case for zero
    if (isZero()) {
        return BigNumber();
    }
    
    // Initial guess: 10^(exponent/2)
    BigNumber guess("1");
    int expGuess = exponent / 2;
    if (expGuess > 0) {
        std::string zeros(expGuess, '0');
        guess.digits += zeros;
    } else if (expGuess < 0) {
        // For numbers less than 1, start with 1
        guess.exponent = expGuess;
    }
    
    // Newton's method: x_next = (x + n/x) / 2
    const int maxIterations = 20;  // Adjust based on precision needs
    BigNumber two("2");
    BigNumber prev;
    
    for (int i = 0; i < maxIterations; i++) {
        prev = guess;
        
        // Calculate n/x
        BigNumber quotient = *this / guess;
        
        // Calculate (x + n/x)
        BigNumber sum = guess + quotient;
        
        // Calculate (x + n/x) / 2
        guess = sum / two;
        
        // Check for convergence (when guess doesn't change significantly)
        if (guess.toString() == prev.toString()) {
            break;
        }
    }
    
    return guess;
}

// Check if the number is zero
bool BigNumber::isZero() const {
    return digits == "0";
}

// Check if the number is negative
bool BigNumber::isNeg() const {
    return isNegative && !isZero();
}

// Get the sign of the number (-1, 0, 1)
int BigNumber::sign() const {
    if (isZero()) return 0;
    return isNegative ? -1 : 1;
} 