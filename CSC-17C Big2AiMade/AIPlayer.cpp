#include "AIPlayer.h"
#include <algorithm>
#include <random>
#include <ctime>

AIPlayer::AIPlayer(const std::string& name, int diff) 
    : Player(name), difficulty(diff) {
    std::fill(patternCounts, patternCounts + 5, 0);
    analyzeHand();
}

AIPlayer::~AIPlayer() {
    // Clean up is handled by base class
}

void AIPlayer::analyzeHand() {
    cardPatterns.clear();
    std::fill(patternCounts, patternCounts + 5, 0);
    
    // Group cards by value
    std::map<int, std::array<Card*, 4>> valueGroups;
    int groupCounts[14] = {0}; // Count cards of each value
    
    for (const auto& pair : hand) {
        int value = pair.second->getValue();
        valueGroups[value][groupCounts[value]++] = pair.second;
    }
    
    // Find pairs
    int pairCount = 0;
    for (const auto& group : valueGroups) {
        if (groupCounts[group.first] >= 2) {
            cardPatterns["pair"][pairCount++] = group.second[0];
            cardPatterns["pair"][pairCount++] = group.second[1];
            patternCounts[0] = pairCount;
        }
    }
    
    // Find three of a kind
    int threeCount = 0;
    for (const auto& group : valueGroups) {
        if (groupCounts[group.first] >= 3) {
            cardPatterns["three"][threeCount++] = group.second[0];
            cardPatterns["three"][threeCount++] = group.second[1];
            cardPatterns["three"][threeCount++] = group.second[2];
            patternCounts[1] = threeCount;
        }
    }
    
    // Find potential straights
    std::array<Card*, 13> sortedCards;
    int cardCount = 0;
    for (const auto& pair : hand) {
        sortedCards[cardCount++] = pair.second;
    }
    
    std::sort(sortedCards.begin(), sortedCards.begin() + cardCount,
        [](Card* a, Card* b) { return a->getValue() < b->getValue(); });
    
    int straightCount = 0;
    for (int i = 0; i < cardCount - 4; ++i) {
        bool isStraight = true;
        for (int j = 0; j < 4; ++j) {
            if (sortedCards[i + j + 1]->getValue() != sortedCards[i + j]->getValue() + 1) {
                isStraight = false;
                break;
            }
        }
        if (isStraight) {
            for (int j = 0; j < 5; ++j) {
                cardPatterns["straight"][straightCount++] = sortedCards[i + j];
            }
            patternCounts[2] = straightCount;
        }
    }
}

std::array<Card*, 5> AIPlayer::makeMove(const std::array<Card*, 5>& lastPlayed, int lastPlayedCount) {
    if (lastPlayedCount == 0) {
        // First play of the game
        return findLowestValidPlay(lastPlayed, lastPlayedCount);
    }
    
    if (shouldPass(lastPlayed, lastPlayedCount)) {
        return std::array<Card*, 5>(); // Empty array indicates pass
    }
    
    return findBestPlay(lastPlayed, lastPlayedCount);
}

bool AIPlayer::shouldPass(const std::array<Card*, 5>& lastPlayed, int lastPlayedCount) {
    if (difficulty == 1) {
        // Easy AI: 30% chance to pass
        return (rand() % 100) < 30;
    }
    
    // Count remaining cards of each value
    int valueCount[15] = {0}; // 0-14 for card values
    for (const auto& pair : hand) {
        valueCount[pair.second->getValue()]++;
    }
    
    // If we have few cards left, be more aggressive
    if (getHandSize() <= 3) {
        return false;
    }
    
    // If we have many high cards, be more conservative
    int highCardCount = 0;
    for (int i = 10; i <= 14; ++i) {
        highCardCount += valueCount[i];
    }
    
    // Consider the last played card if available
    if (lastPlayedCount > 0 && lastPlayed[0] != nullptr) {
        int lastValue = lastPlayed[0]->getValue();
        // If last played card is high, be more likely to pass
        if (lastValue >= 10) {
            return true;
        }
    }
    
    if (difficulty == 2) {
        return highCardCount > 5;
    } else {
        // Hard AI: More strategic passing
        return highCardCount > 3 && getHandSize() > 5;
    }
}

std::array<Card*, 5> AIPlayer::findBestPlay(const std::array<Card*, 5>& lastPlayed, int lastPlayedCount) {
    if (difficulty == 1) {
        return findLowestValidPlay(lastPlayed, lastPlayedCount);
    }
    
    std::array<Card*, 5> bestPlay = findLowestValidPlay(lastPlayed, lastPlayedCount);
    std::array<Card*, 5> highestPlay = findHighestValidPlay(lastPlayed, lastPlayedCount);
    
    int bestCount = 0, highestCount = 0;
    for (int i = 0; i < 5; ++i) {
        if (bestPlay[i]) bestCount++;
        if (highestPlay[i]) highestCount++;
    }
    
    if (isBetterPlay(highestPlay, highestCount, bestPlay, bestCount)) {
        return highestPlay;
    }
    return bestPlay;
}

std::array<Card*, 5> AIPlayer::findLowestValidPlay(const std::array<Card*, 5>& lastPlayed, int lastPlayedCount) {
    std::array<Card*, 5> play;
    std::fill(play.begin(), play.end(), nullptr);
    
    // If no last play, play lowest single card
    if (lastPlayedCount == 0) {
        Card* lowestCard = nullptr;
        for (const auto& pair : hand) {
            if (!lowestCard || *pair.second < *lowestCard) {
                lowestCard = pair.second;
            }
        }
        if (lowestCard) {
            play[0] = lowestCard;
        }
        return play;
    }
    
    // Find lowest valid play that beats last play
    for (const auto& pair : hand) {
        if (*pair.second > *lastPlayed[0]) {
            play[0] = pair.second;
            return play;
        }
    }
    
    return play; // Empty array indicates no valid play
}

std::array<Card*, 5> AIPlayer::findHighestValidPlay(const std::array<Card*, 5>& lastPlayed, int lastPlayedCount) {
    std::array<Card*, 5> play;
    std::fill(play.begin(), play.end(), nullptr);
    
    // If no last play, play highest single card
    if (lastPlayedCount == 0) {
        Card* highestCard = nullptr;
        for (const auto& pair : hand) {
            if (!highestCard || *pair.second > *highestCard) {
                highestCard = pair.second;
            }
        }
        if (highestCard) {
            play[0] = highestCard;
        }
        return play;
    }
    
    // Find highest valid play that beats last play
    Card* highestCard = nullptr;
    for (const auto& pair : hand) {
        if (*pair.second > *lastPlayed[0] && (!highestCard || *pair.second > *highestCard)) {
            highestCard = pair.second;
        }
    }
    if (highestCard) {
        play[0] = highestCard;
    }
    
    return play;
}

bool AIPlayer::isBetterPlay(const std::array<Card*, 5>& play1, int count1,
                           const std::array<Card*, 5>& play2, int count2) {
    if (count1 == 0) return false;
    if (count2 == 0) return true;
    
    // Compare the highest card in each play
    Card* highest1 = nullptr;
    Card* highest2 = nullptr;
    
    for (int i = 0; i < count1; ++i) {
        if (!highest1 || *play1[i] > *highest1) {
            highest1 = play1[i];
        }
    }
    
    for (int i = 0; i < count2; ++i) {
        if (!highest2 || *play2[i] > *highest2) {
            highest2 = play2[i];
        }
    }
    
    return *highest1 > *highest2;
} 