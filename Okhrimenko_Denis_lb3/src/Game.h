#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include "Map.h"
#include "ShipManager.h"
#include "AbilityManager.h"
#include "AbilityResponce.h"
#include "Player.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"
#include "GameState.h"

// Цветовая подсветка для вывода в консоль
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define RESET "\033[0m"

class Game {
private:
    bool isRunningGame;
    bool isLoaded; // Флаг, указывающий, была ли игра загружена
    Map* my_map;
    Map* opponents_map;
    AbilityManager* skillManager;
    AbilityResponce* responce;
    Player* humanPlayer;
    Player* computerPlayer;
    CoordHolder* coordHolder;
    GameState* gameState;
    int roundNumber; // Номер раунда
    ShipManager* myship;
    ShipManager* opponentsship;

public:
    Game();
    ~Game();

    void cleanUp(); // Освобождение памяти
    void initializeGame(); // Инициализация игры
    void gameStart(); // Начало игры
    void gameOver(); // Завершение игры
    void Round(); // Один раунд игры
    void nextRound(); // Переход к следующему раунду
    void newGame(); // Начало новой игры
    void saveWithArrangement(); // Сохранение игры с размещением кораблей
    void printMaps(); // Вывод карт игрока и противника
};

#endif // GAME_H