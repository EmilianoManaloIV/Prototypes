#ifndef CARD_H
#define CARD_H

#include <string>
#include <iostream>
#include <set>

/*
CLASS: Card
PURPOSE: Represents a playing card in the Big 2 game
ATTRIBUTES:
    - suit: string (hearts, diamonds, clubs, spades)
    - rank: int (2-14, where 14 is Ace)
    - value: int (Big 2 specific value)
METHODS:
    + Card(suit: string, rank: int)
    + getSuit(): string
    + getRank(): int
    + getValue(): int
    + operator<(const Card& other): bool
    + operator==(const Card& other): bool
    + operator>(const Card& other): bool
    + toString(): string
DATE: 2024-03-19
*/

class Card {
private:
    std::string suit;
    int rank;
    int value;
    static std::set<std::string> validSuits;

public:
    Card(const std::string& s, int r);
    std::string getSuit() const;
    int getRank() const;
    int getValue() const;
    bool operator<(const Card& other) const;
    bool operator==(const Card& other) const;
    bool operator>(const Card& other) const;
    std::string toString() const;
    
    // Static method to validate suit
    static bool isValidSuit(const std::string& s);
};

#endif 