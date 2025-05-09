#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Deck.h"
#include <array>

/*
CLASS: Game
PURPOSE: Manages the Big 2 card game
ATTRIBUTES:
    - players: array<Player*, 4>
    - deck: Deck*
    - currentPlayer: int
    - lastPlayedCards: array<Card*, 5>
    - lastPlayedCount: int
METHODS:
    + Game()
    + ~Game()
    + startGame()
    + playTurn()
    + isValidPlay(cards: Card**, count: int): bool
    + isGameOver(): bool
    + displayGameState(): void
    + getPlayer(index: int): Player*
    + setPlayer(index: int, player: Player*): void
DATE: 2024-03-19
*/

class Game {
private:
    std::array<Player*, 4> players;
    Deck* deck;
    int currentPlayer;
    std::array<Card*, 5> lastPlayedCards;
    int lastPlayedCount;

public:
    Game();
    ~Game();
    void startGame();
    void playTurn();
    bool isValidPlay(Card** cards, int count);
    bool isGameOver() const;
    void displayGameState() const;
    Player* getPlayer(int index) const;
    void setPlayer(int index, Player* player);
};

#endif 