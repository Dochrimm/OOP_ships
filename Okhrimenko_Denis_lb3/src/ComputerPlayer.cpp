#include "ComputerPlayer.h"


ComputerPlayer::ComputerPlayer(Map* map, ShipManager* shipManager, GameState* gameState)
    : Player(map, shipManager, gameState) {}

void ComputerPlayer::placeShips() {
    srand(static_cast<unsigned>(time(0)));

    int shipsPlaced = 0; // Счетчик успешно размещенных кораблей

    while (shipsPlaced < 2) { 
        int x = rand() % map->getWidth();
        int y = rand() % map->getHeight();
        std::vector<std::string> direct {"horizontal", "vetical"};
        std::string direction = direct.at(rand() % 2);

        try {
            map->placeShipOnTheMap(shipsPlaced, x, y, direction);
            shipsPlaced++; // Увеличиваем счетчик только при успешном размещении
        } catch (const ShipsIntersectionException& e) {
            // std::cout << "Ошибка размещения корабля: " << e.what() << ". Повторная попытка." << std::endl;
        }
    }

    std::cout << "Корабли противника размещены." << '\n';
}

void ComputerPlayer::makeMove(Map* opponentMap, AbilityResponce* responce, AbilityManager* skillManager) {
    std::cout << "Ход противника!" << '\n';
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> disWidth(0, opponentMap->getWidth() - 1);
    std::uniform_int_distribution<> disHeight(0, opponentMap->getHeight() - 1);

    std::set<std::pair<int, int>> attackedCells; // Множество для хранения атакованных клеток
    bool attacked = false;

    while (!attacked) {
        int x = disWidth(gen);
        int y = disHeight(gen);

        // Проверяем, была ли клетка уже атакована
        if (attackedCells.find({x, y}) == attackedCells.end()) {
            try {
                bool isDestroyed = opponentMap->attack(x, y, std::nullopt);
                attackedCells.insert({x, y}); // Добавляем клетку в множество атакованных
                attacked = true; // Успешная атака
            } catch (const MapOutsideException& e) {
                std::cout << e.what() << '\n';
            } catch (const Accident& e) {
                // Обработка исключения, если клетка уже была атакована
            }
        }
    }
}