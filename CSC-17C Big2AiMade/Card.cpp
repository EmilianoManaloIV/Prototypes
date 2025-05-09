#include "Card.h"

// Initialize static member
std::set<std::string> Card::validSuits = {"hearts", "diamonds", "clubs", "spades"};

Card::Card(const std::string& s, int r) : suit(s), rank(r) {
    if (!isValidSuit(s)) {
        throw std::invalid_argument("Invalid suit");
    }
    
    // Calculate Big 2 specific value
    // In Big 2, 2 is highest, followed by A, K, Q, J, 10-3
    if (rank == 2) value = 15;
    else if (rank == 14) value = 14; // Ace
    else value = rank;
}

std::string Card::getSuit() const {
    return suit;
}

int Card::getRank() const {
    return rank;
}

int Card::getValue() const {
    return value;
}

bool Card::operator<(const Card& other) const {
    return value < other.value;
}

bool Card::operator==(const Card& other) const {
    return value == other.value;
}

bool Card::operator>(const Card& other) const {
    return value > other.value;
}

bool Card::isValidSuit(const std::string& s) {
    return validSuits.find(s) != validSuits.end();
}

std::string Card::toString() const {
    std::string rankStr;
    switch(rank) {
        case 11: rankStr = "J"; break;
        case 12: rankStr = "Q"; break;
        case 13: rankStr = "K"; break;
        case 14: rankStr = "A"; break;
        default: rankStr = std::to_string(rank);
    }
    return rankStr + suit[0];
} 