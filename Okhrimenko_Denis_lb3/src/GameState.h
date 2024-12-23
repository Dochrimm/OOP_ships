#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <string>
#include <fstream>
#include <iostream>
#include <filesystem>
#include "json.hpp"

#include "Map.h"
#include "ShipManager.h"
#include "AbilityManager.h"
#include "Serializable.h"

using json = nlohmann::json;

class GameState {
private:
    Map* my_map;
    Map* opponents_map;
    ShipManager* my_ship_manager;
    ShipManager* opponents_ship_manager;
    AbilityManager* abilityManager;
    CoordHolder* coordHolder;
    std::string saveFilePath = "savefile.json"; // Путь к файлу сохранения

public:
    GameState(Map* my_map, Map* opponents_map, ShipManager* my_ship_manager, ShipManager* opponents_ship_manager, AbilityManager* abilityManager, CoordHolder* coordHolder);

    // Метод для сохранения состояния игры в файл
    bool saveToFile() const;

    // Метод для загрузки состояния игры из файла
    bool loadFromFile();
};

#endif // GAMESTATE_H