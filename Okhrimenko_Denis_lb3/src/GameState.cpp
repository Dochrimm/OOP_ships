#include "GameState.h"

GameState::GameState(Map* my_map, Map* opponents_map, ShipManager* my_ship_manager, ShipManager* opponents_ship_manager, AbilityManager* abilityManager, CoordHolder* coordHolder)
    : my_map(my_map), opponents_map(opponents_map), my_ship_manager(my_ship_manager), opponents_ship_manager(opponents_ship_manager), abilityManager(abilityManager), coordHolder(coordHolder) {}

// Метод для сохранения состояния игры в файл
bool GameState::saveToFile() const {
    json savedGame;
    Serializable mySerializable(my_map, my_ship_manager, abilityManager, coordHolder);
    savedGame["my_state"] = mySerializable.serialize();

    Serializable opponentSerializable(opponents_map, opponents_ship_manager, abilityManager, coordHolder);
    savedGame["opponent_state"] = opponentSerializable.serialize();

    std::ofstream outFile(saveFilePath);
    if (!outFile) {
        std::cerr << "Ошибка: не удалось открыть файл для записи." << std::endl;
        return false;
    }
    outFile << savedGame.dump(4); // Сохраняем в файл с отступами
    outFile.close();
    std::cout << "Игра сохранена в файл: " << saveFilePath << '\n';
    return true;
}

// Метод для загрузки состояния игры из файла
bool GameState::loadFromFile() {
    if (!std::filesystem::exists(saveFilePath)) { // Проверяем, существует ли файл
        std::cout << "Файл сохранения не найден: " << saveFilePath << ". Начинаем новую игру." << '\n';
        return false;
    }

    std::ifstream inFile(saveFilePath);
    if (!inFile) {
        std::cerr << "Ошибка: не удалось открыть файл для чтения." << std::endl;
        return false;
    }

    json loadedGame;
    try {
        inFile >> loadedGame; // Загружаем состояние из файла
    } catch (const std::exception& e) {
        std::cerr << "Ошибка при чтении файла сохранения: " << e.what() << std::endl;
        return false;
    }
    inFile.close();

    try {
        Serializable mySerializable(my_map, my_ship_manager, abilityManager, coordHolder);
        mySerializable.deserialize(loadedGame["my_state"]);

        Serializable opponentSerializable(opponents_map, opponents_ship_manager, abilityManager, coordHolder);
        opponentSerializable.deserialize(loadedGame["opponent_state"]);
    } catch (const std::exception& e) {
        std::cerr << "Ошибка при загрузке состояния игры: " << e.what() << std::endl;
        return false;
    }

    std::cout << "Игра загружена из файла: " << saveFilePath << '\n';
    return true;
}