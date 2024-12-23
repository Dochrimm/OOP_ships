#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include <iostream>
#include "Player.h"
#include "Map.h"
#include "ShipManager.h"
#include "GameState.h"
#include "AbilityResponce.h"
#include "AbilityManager.h"
#include "CoordinateManagement.h"
#include "Exceptions.h"

class HumanPlayer : public Player {
public:
    HumanPlayer(Map* map, ShipManager* shipManager, GameState* gameState);

    void placeShips() override; // Реализация метода для размещения кораблей
    void makeMove(Map* opponentMap, AbilityResponce* responce, AbilityManager* skillManager) override; // Реализация метода для хода

private:
    void myAttack(Map* opponentMap, AbilityResponce* responce, AbilityManager* skillManager); // Метод для атаки
    void useAbility(AbilityManager* skillManager, AbilityResponce* responce); // Метод для использования способности
};

#endif // HUMANPLAYER_H