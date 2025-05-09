#ifndef AIPLAYER_H
#define AIPLAYER_H

#include "Player.h"
#include <array>
#include <map>

/*
CLASS: AIPlayer
PURPOSE: Represents an AI player in the Big 2 game
INHERITS: Player
ATTRIBUTES:
    - difficulty: int (1-3, where 3 is hardest)
    - cardPatterns: map<string, array<Card*, 5>>
METHODS:
    + AIPlayer(name: string, difficulty: int)
    + ~AIPlayer()
    + makeMove(lastPlayed: array<Card*, 5>, count: int): array<Card*, 5>
    + analyzeHand(): void
    + findBestPlay(lastPlayed: array<Card*, 5>, count: int): array<Card*, 5>
    + shouldPass(lastPlayed: array<Card*, 5>, count: int): bool
DATE: 2024-03-19
*/

class AIPlayer : public Player {
private:
    int difficulty;
    std::map<std::string, std::array<Card*, 5>> cardPatterns;
    int patternCounts[5]; // Count of cards in each pattern

    // Helper methods
    void analyzeHand();
    std::array<Card*, 5> findBestPlay(const std::array<Card*, 5>& lastPlayed, int lastPlayedCount);
    bool shouldPass(const std::array<Card*, 5>& lastPlayed, int lastPlayedCount);
    std::array<Card*, 5> findLowestValidPlay(const std::array<Card*, 5>& lastPlayed, int lastPlayedCount);
    std::array<Card*, 5> findHighestValidPlay(const std::array<Card*, 5>& lastPlayed, int lastPlayedCount);
    bool isBetterPlay(const std::array<Card*, 5>& play1, int count1, 
                     const std::array<Card*, 5>& play2, int count2);

public:
    AIPlayer(const std::string& name, int diff = 2);
    ~AIPlayer();
    std::array<Card*, 5> makeMove(const std::array<Card*, 5>& lastPlayed, int lastPlayedCount);
};

#endif 