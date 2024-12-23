#ifndef PLAYER_H
#define PLAYER_H

#include "Map.h"
#include "ShipManager.h"
#include "GameState.h"
#include "AbilityResponce.h"
#include "AbilityManager.h"

class Player {
protected:
    Map* map;
    ShipManager* shipManager;
    GameState* gameState;

public:
    Player(Map* map, ShipManager* shipManager, GameState* gameState);

    virtual void placeShips() = 0; // Чисто виртуальный метод для размещения кораблей
    virtual void makeMove(Map* opponentMap, AbilityResponce* responce, AbilityManager* skillManager) = 0; // Чисто виртуальный метод для хода

    bool allShipsDestroyed(); // Метод для проверки, уничтожены ли все корабли

    // Метод для сохранения игры в файл
    bool saveGameToFile();

    // Метод для загрузки игры из файла
    bool loadGameFromFile();
};

#endif // PLAYER_H