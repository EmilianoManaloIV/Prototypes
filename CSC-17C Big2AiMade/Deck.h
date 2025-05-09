#ifndef DECK_H
#define DECK_H

#include "Card.h"
#include <list>
#include <random>
#include <algorithm>
#include <iterator>

/*
CLASS: Deck
PURPOSE: Manages a deck of cards for the Big 2 game
ATTRIBUTES:
    - cards: list<Card*>
    - currentIndex: int
METHODS:
    + Deck()
    + ~Deck()
    + shuffle()
    + dealCard(): Card*
    + reset()
    + begin(): iterator
    + end(): iterator
DATE: 2024-03-19
*/

class Deck {
private:
    std::list<Card*> cards;
    int currentIndex;

public:
    using iterator = std::list<Card*>::iterator;
    using const_iterator = std::list<Card*>::const_iterator;

    Deck();
    ~Deck();
    void shuffle();
    Card* dealCard();
    void reset();
    
    // Iterator methods
    iterator begin() { return cards.begin(); }
    iterator end() { return cards.end(); }
    const_iterator begin() const { return cards.begin(); }
    const_iterator end() const { return cards.end(); }
};

#endif 