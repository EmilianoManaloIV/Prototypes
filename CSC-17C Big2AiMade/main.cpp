#include "Game.h"
#include "AIPlayer.h"
#include <iostream>
#include <queue>
#include <stack>
#include <limits>
#include <sstream>
#include <ctime>

// Function to get valid card indices from user
std::vector<int> getCardIndices(const Player* player) {
    std::vector<int> indices;
    std::string input;
    
    std::cout << "Enter card indices to play (space-separated, -1 to pass): ";
    std::getline(std::cin, input);
    
    std::stringstream ss(input);
    int index;
    while (ss >> index) {
        if (index == -1) {
            indices.clear();
            indices.push_back(-1);
            break;
        }
        if (index >= 0 && index < player->getHandSize()) {
            indices.push_back(index);
        }
    }
    
    return indices;
}

// Function to validate card combination
bool isValidCombination(const std::vector<Card*>& cards) {
    if (cards.empty()) return false;
    if (cards.size() == 1) return true;
    
    // Check for pairs
    if (cards.size() == 2) {
        return cards[0]->getValue() == cards[1]->getValue();
    }
    
    // Check for three of a kind
    if (cards.size() == 3) {
        return cards[0]->getValue() == cards[1]->getValue() && 
               cards[1]->getValue() == cards[2]->getValue();
    }
    
    // Check for five card combinations
    if (cards.size() == 5) {
        // Check for straight
        bool isStraight = true;
        for (size_t i = 1; i < cards.size(); ++i) {
            if (cards[i]->getValue() != cards[i-1]->getValue() + 1) {
                isStraight = false;
                break;
            }
        }
        if (isStraight) return true;
        
        // Check for flush
        bool isFlush = true;
        for (size_t i = 1; i < cards.size(); ++i) {
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

int main() {
    srand(time(nullptr));
    Game game;
    
    // Create AI players with different difficulties
    game.setPlayer(0, new Player("Human")); // Human player
    game.setPlayer(1, new AIPlayer("AI Easy", 1));
    game.setPlayer(2, new AIPlayer("AI Medium", 2));
    game.setPlayer(3, new AIPlayer("AI Hard", 3));
    
    game.startGame();
    
    std::queue<Player*> turnOrder;
    std::stack<Card*> lastPlayedCards;
    
    // Initialize turn order
    for (int i = 0; i < 4; ++i) {
        turnOrder.push(game.getPlayer(i));
    }
    
    bool gameOver = false;
    while (!gameOver) {
        Player* currentPlayer = turnOrder.front();
        turnOrder.pop();
        
        std::cout << "\n=== " << currentPlayer->getName() << "'s turn ===\n";
        currentPlayer->displayHand();
        
        if (!lastPlayedCards.empty()) {
            std::cout << "Last played card: " << lastPlayedCards.top()->toString() << std::endl;
        }
        
        std::vector<Card*> cardsToPlay;
        
        // Handle AI or human player
        if (dynamic_cast<AIPlayer*>(currentPlayer)) {
            // Convert last played cards to array for AI
            std::array<Card*, 5> lastPlayed;
            std::fill(lastPlayed.begin(), lastPlayed.end(), nullptr);
            int lastPlayedCount = 0;
            
            if (!lastPlayedCards.empty()) {
                lastPlayed[0] = lastPlayedCards.top();
                lastPlayedCount = 1;
            }
            
            // Get AI's move
            std::array<Card*, 5> aiMove = dynamic_cast<AIPlayer*>(currentPlayer)->makeMove(lastPlayed, lastPlayedCount);
            
            // Convert AI's move to vector
            for (int i = 0; i < 5 && aiMove[i] != nullptr; ++i) {
                cardsToPlay.push_back(aiMove[i]);
            }
            
            if (cardsToPlay.empty()) {
                std::cout << currentPlayer->getName() << " passes.\n";
                turnOrder.push(currentPlayer);
                continue;
            }
        } else {
            // Human player's turn
            std::vector<int> cardIndices = getCardIndices(currentPlayer);
            
            if (cardIndices.empty() || (cardIndices.size() == 1 && cardIndices[0] == -1)) {
                std::cout << currentPlayer->getName() << " passes.\n";
                turnOrder.push(currentPlayer);
                continue;
            }
            
            // Collect cards to play
            for (int index : cardIndices) {
                Card* card = currentPlayer->removeCard(index);
                if (card) {
                    cardsToPlay.push_back(card);
                }
            }
        }
        
        // Validate and play cards
        if (isValidCombination(cardsToPlay)) {
            // Clear last played cards
            while (!lastPlayedCards.empty()) {
                delete lastPlayedCards.top();
                lastPlayedCards.pop();
            }
            
            // Add new cards to last played stack
            for (Card* card : cardsToPlay) {
                lastPlayedCards.push(card);
            }
            
            std::cout << currentPlayer->getName() << " plays: ";
            for (Card* card : cardsToPlay) {
                std::cout << card->toString() << " ";
            }
            std::cout << std::endl;
            
            // Check for game over
            if (currentPlayer->getHandSize() == 0) {
                std::cout << "\n" << currentPlayer->getName() << " wins!\n";
                gameOver = true;
            }
        } else {
            std::cout << "Invalid combination. Try again.\n";
            // Return cards to player's hand
            for (Card* card : cardsToPlay) {
                currentPlayer->addCard(card);
            }
            turnOrder.push(currentPlayer);
            continue;
        }
        
        turnOrder.push(currentPlayer);
    }
    
    // Clean up
    while (!lastPlayedCards.empty()) {
        delete lastPlayedCards.top();
        lastPlayedCards.pop();
    }
    
    return 0;
}
