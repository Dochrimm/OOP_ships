#ifndef COMPUTERPLAYER_H
#define COMPUTERPLAYER_H

#include "Player.h"
#include "Map.h"
#include "ShipManager.h"
#include "GameState.h"
#include "AbilityResponce.h"
#include "AbilityManager.h"
#include "Exceptions.h"
#include <set>
#include <random>
#include <ctime>
#include <iostream>

class ComputerPlayer : public Player {
public:
    ComputerPlayer(Map* map, ShipManager* shipManager, GameState* gameState);

    void placeShips() override; // Реализация метода для размещения кораблей
    void makeMove(Map* opponentMap, AbilityResponce* responce, AbilityManager* skillManager) override; // Реализация метода для хода
};

#endif // COMPUTERPLAYER_H