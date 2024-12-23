#include "Player.h"


Player::Player(Map* map, ShipManager* shipManager, GameState* gameState)
    : map(map), shipManager(shipManager), gameState(gameState) {}

bool Player::allShipsDestroyed() {
    for (int i = 0; i < shipManager->getShipCount(); ++i) {
        Ship& ship = shipManager->getShip(i);
        if (!ship.isDestroyed()) {
            return false; // Если хотя бы один корабль не уничтожен, возвращаем false
        }
    }
    return true; // Все корабли уничтожены
}

// Метод для сохранения игры в файл
bool Player::saveGameToFile() {
    return gameState->saveToFile();
}

// Метод для загрузки игры из файла
bool Player::loadGameFromFile() {
    return gameState->loadFromFile();
}