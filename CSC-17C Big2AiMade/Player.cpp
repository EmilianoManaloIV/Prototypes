#include "Player.h"
#include <iostream>
#include <algorithm>
#include <vector>

Player::Player(const std::string& name) : name(name), handSize(0), nextIndex(0) {
    // Map is automatically initialized empty
}

Player::~Player() {
    // Clean up any remaining cards in hand using for_each
    for (auto& pair : hand) {
        delete pair.second;
    }
    hand.clear();
}

void Player::addCard(Card* card) {
    hand[nextIndex++] = card;
    handSize++;
}

Card* Player::removeCard(int index) {
    auto it = hand.find(index);
    if (it != hand.end()) {
        Card* card = it->second;
        hand.erase(it);
        handSize--;
        return card;
    }
    return nullptr;
}

int Player::getHandSize() const {
    return handSize;
}

const std::string& Player::getName() const {
    return name;
}

void Player::sortHand() {
    // Convert map to vector for sorting
    std::vector<std::pair<int, Card*>> cards(hand.begin(), hand.end());
    
    // Sort by card value
    std::sort(cards.begin(), cards.end(),
        [](const auto& a, const auto& b) {
            return *a.second < *b.second;
        });
    
    // Clear and rebuild map
    hand.clear();
    for (const auto& pair : cards) {
        hand[pair.first] = pair.second;
    }
}

void Player::displayHand() const {
    std::cout << name << "'s hand: ";
    for (const auto& pair : hand) {
        std::cout << pair.second->toString() << " ";
    }
    std::cout << std::endl;
} 