#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include <string>
#include <vector>
#include <queue>
#include <stdexcept>
#include <sstream>
#include <iomanip>
#include <openssl/sha.h>
#include <openssl/evp.h>
#include "../lib/json.hpp"
#include "Map.h"
#include "ShipManager.h"
#include "AbilityManager.h"
#include "Ship.h"
#include "IFactory.h"
#include "Abilities.h"

using json = nlohmann::json;

class Serializable {
private:
    Map* map;
    ShipManager* shipman;
    AbilityManager* abilityManager;
    CoordHolder* coordHolder;

public:
    Serializable(Map* map, ShipManager* shipman, AbilityManager* abilityManager, CoordHolder* coordHolder);

    // Метод для вычисления SHA-256 хеша с использованием EVP API
    std::string calculateHash(const std::string& input) const;

    // Сериализация данных
    json serialize() const;

    // Десериализация данных
    void deserialize(const json& j);
};

#endif // SERIALIZABLE_H