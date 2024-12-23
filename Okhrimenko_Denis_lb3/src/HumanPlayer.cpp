#include "HumanPlayer.h"


HumanPlayer::HumanPlayer(Map* map, ShipManager* shipManager, GameState* gameState)
    : Player(map, shipManager, gameState) {}

void HumanPlayer::placeShips() {
    try {
        map->placeShipOnTheMap(0, 1, 1, "horizontal");
        map->placeShipOnTheMap(1, 5, 9, "horizontal");
        std::cout << "Ваши корабли размещены." << '\n';
    } catch (const ShipsIntersectionException& e) {
        std::cout << "Ошибка размещения корабля: " << e.what() << '\n';
    } 
}

void HumanPlayer::makeMove(Map* opponentMap, AbilityResponce* responce, AbilityManager* skillManager) {
    std::cout << "Ваш ход!" << '\n';
    map->printMap(true);
    opponentMap->printMap(false);
    std::cout << "Выберите действие:\n1. Атаковать\n2. Использовать способность\n3. Сохранить игру\n4. Загрузить игру\n";
    int choice = CoordReader::readCoord("Введите номер действия: ");

    switch (choice) {
        case 1:
            myAttack(opponentMap, responce, skillManager);
            break;
        case 2:
            useAbility(skillManager, responce);
            makeMove(opponentMap, responce, skillManager);
            break;
        case 3:
            if (saveGameToFile()) { // Сохраняем игру в файл
                std::cout << "Игра сохранена." << '\n';
            }
            makeMove(opponentMap, responce, skillManager);
            break;
        case 4:
            if (loadGameFromFile()) { // Загружаем игру из файла
                std::cout << "Игра загружена." << '\n';
            }
            makeMove(opponentMap, responce, skillManager);
            break;
        default:
            std::cout << "Неверный выбор. Попробуйте снова." << '\n';
            makeMove(opponentMap, responce, skillManager);
            break;
    }
}

void HumanPlayer::myAttack(Map* opponentMap, AbilityResponce* responce, AbilityManager* skillManager) {
    int x = CoordReader::readCoord("Введите координату x: ");
    int y = CoordReader::readCoord("Введите координату y: ");
    auto res = opponentMap->attack(x, y, responce);
    if (res == 1) {
        skillManager->addRandomSkill();
    }
}

void HumanPlayer::useAbility(AbilityManager* skillManager, AbilityResponce* responce) {
    if (responce != nullptr) {
        skillManager->activateAbility(*responce);
        responce->getAbilityResult();
    } else {
        std::cout << "Ошибка: responce равен nullptr" << '\n';
    }
}