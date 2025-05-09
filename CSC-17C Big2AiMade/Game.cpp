#include "Game.h"
#include <iostream>
#include <algorithm>

Game::Game() : currentPlayer(0), lastPlayedCount(0) {
    // Initialize players
    players[0] = new Player("Player 1");
    players[1] = new Player("Player 2");
    players[2] = new Player("Player 3");
    players[3] = new Player("Player 4");
    
    deck = new Deck();
    std::fill(lastPlayedCards.begin(), lastPlayedCards.end(), nullptr);
}

Game::~Game() {
    // Clean up players and deck
    for (auto player : players) {
        delete player;
    }
    delete deck;
}

void Game::startGame() {
    deck->shuffle();
    
    // Deal 13 cards to each player
    for (int i = 0; i < 13; i++) {
        for (int j = 0; j < 4; j++) {
            players[j]->addCard(deck->dealCard());
        }
    }
    
    // Sort each player's hand
    for (auto player : players) {
        player->sortHand();
    }
    
    // Find player with 3 of diamonds to start
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < players[i]->getHandSize(); j++) {
            Card* card = players[i]->removeCard(j);
            if (card->getRank() == 3 && card->getSuit() == "diamonds") {
                currentPlayer = i;
                delete card;
                break;
            }
            players[i]->addCard(card);
        }
    }
}

void Game::playTurn() {
    displayGameState();
    
    // TODO: Implement actual game logic for playing cards
    // This would include:
    // 1. Getting player input for cards to play
    // 2. Validating the play
    // 3. Updating game state
    // 4. Moving to next player
}

bool Game::isValidPlay(Card** cards, int count) {
    if (count <= 0 || count > 5) return false;
    
    // Check for single card
    if (count == 1) return true;
    
    // Check for pairs
    if (count == 2) {
        return cards[0]->getValue() == cards[1]->getValue();
    }
    
    // Check for three of a kind
    if (count == 3) {
        return cards[0]->getValue() == cards[1]->getValue() && 
               cards[1]->getValue() == cards[2]->getValue();
    }
    
    // Check for five card combinations
    if (count == 5) {
        // Check for straight
        bool isStraight = true;
        for (int i = 1; i < count; ++i) {
            if (cards[i]->getValue() != cards[i-1]->getValue() + 1) {
                isStraight = false;
                break;
            }
        }
        if (isStraight) return true;
        
        // Check for flush
        bool isFlush = true;
        for (int i = 1; i < count; ++i) {
            if (cards[i]->getSuit() != cards[0]->getSuit()) {
                isFlush = false;
                break;
            }
        }
        if (isFlush) return true;
        
        // Check for full house
        if (cards[0]->getValue() == cards[1]->getValue() && 
            cards[1]->getValue() == cards[2]->getValue() &&
            cards[3]->getValue() == cards[4]->getValue()) {
            return true;
        }
    }
    
    return false;
}

bool Game::isGameOver() const {
    // Check if any player has no cards left
    for (auto player : players) {
        if (player->getHandSize() == 0) {
            return true;
        }
    }
    return false;
}

void Game::displayGameState() const {
    std::cout << "\nCurrent game state:" << std::endl;
    for (auto player : players) {
        player->displayHand();
    }
    std::cout << "Current player: " << players[currentPlayer]->getName() << std::endl;
}

Player* Game::getPlayer(int index) const {
    if (index >= 0 && index < 4) {
        return players[index];
    }
    return nullptr;
}

void Game::setPlayer(int index, Player* player) {
    if (index >= 0 && index < 4) {
        // Delete existing player if any
        if (players[index]) {
            delete players[index];
        }
        players[index] = player;
    }
} 