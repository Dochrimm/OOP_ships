#ifndef ABILITY_MANAGER_H 
#define ABILITY_MANAGER_H

#include <queue>
#include <memory>
#include <algorithm>
#include <random>
#include "CoordinateManagement.h"
#include "Abilities.h"
#include "Factories.h"
#include "Exceptions.h"

class AbilityManager {
private:
    Map& map;
    CoordHolder& coordinates_holder;
    std::queue<IFactory*> abilities_creators;

public:
    AbilityManager(Map& map, CoordHolder& coordinates_holder);
    void addRandomSkill();
    void activateAbility(AbilityResponce& responce);
    std::queue<IFactory*> getAbilitiesCreators() const;
    void clearAbilities();
    void addAbility(IFactory* ability);
};

#endif