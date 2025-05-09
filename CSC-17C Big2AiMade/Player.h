#pragma once

#include "Card.h"
#include <map>
#include <string>
#include <iterator>

/*
CLASS: Player
PURPOSE: Represents a player in the Big 2 game
ATTRIBUTES:
    - name: string
    - hand: map<int, Card*>
    - handSize: int
METHODS:
    + Player(name: string)
    + ~Player()
    + addCard(card: Card*)
    + removeCard(index: int): Card*
    + getHandSize(): int
    + getName(): string
    + sortHand()
    + displayHand(): void
    + begin(): iterator
    + end(): iterator
DATE: 2024-03-19
*/

class Player {
public:
    using iterator = std::map<int, Card*>::iterator;
    using const_iterator = std::map<int, Card*>::const_iterator;

    Player(const std::string& name);
    virtual ~Player();
    void addCard(Card* card);
    Card* removeCard(int index);
    int getHandSize() const;
    const std::string& getName() const;
    void sortHand();
    void displayHand() const;
    
    // Iterator methods
    iterator begin() { return hand.begin(); }
    iterator end() { return hand.end(); }
    const_iterator begin() const { return hand.begin(); }
    const_iterator end() const { return hand.end(); }

protected:
    std::map<int, Card*> hand;
    
private:
    std::string name;
    int handSize;
    int nextIndex;
}; 