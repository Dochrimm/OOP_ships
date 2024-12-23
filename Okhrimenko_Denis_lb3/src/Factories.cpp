#include "Factories.h"

IAbility* DoubleDamageFactory::createAbility()
{
    DoubleDamage* ability = new DoubleDamage();
    return ability;
};


ScannerFactory::ScannerFactory(Map& map, CoordHolder& holder) : map(map), holder(holder) {};
IAbility* ScannerFactory::createAbility()
{
    holder.requestData();
    std::pair<int, int> coordinates  = holder.getCoords();
    Scanner* ability = new Scanner(coordinates.first, coordinates.second, map);
    return ability;
};


BombardmentFactory::BombardmentFactory(Map& map) : map(map) {};
IAbility* BombardmentFactory::createAbility()
{
    Bombardment* ability = new Bombardment(map);
    return ability;
};