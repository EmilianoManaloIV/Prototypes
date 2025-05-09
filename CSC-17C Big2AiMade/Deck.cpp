#include "Deck.h"

Deck::Deck() : currentIndex(0) {
    const std::string suits[] = {"hearts", "diamonds", "clubs", "spades"};
    
    // Create all 52 cards using transform
    for (const auto& suit : suits) {
        for (int rank = 2; rank <= 14; rank++) {
            cards.push_back(new Card(suit, rank));
        }
    }
}

Deck::~Deck() {
    // Clean up allocated memory using for_each
    std::for_each(cards.begin(), cards.end(), [](Card* card) { delete card; });
    cards.clear();
}

void Deck::shuffle() {
    // Convert list to vector for random shuffle
    std::vector<Card*> temp(cards.begin(), cards.end());
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(temp.begin(), temp.end(), gen);
    
    // Clear and refill list
    cards.clear();
    std::copy(temp.begin(), temp.end(), std::back_inserter(cards));
    currentIndex = 0;
}

Card* Deck::dealCard() {
    if (cards.empty()) return nullptr;
    
    Card* card = cards.front();
    cards.pop_front();
    currentIndex++;
    return card;
}

void Deck::reset() {
    currentIndex = 0;
    shuffle();
} 