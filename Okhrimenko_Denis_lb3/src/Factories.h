#ifndef FACTORIES_H 
#define FACTORIES_H

#include "IFactory.h"
#include "Abilities.h"
#include "CoordinateManagement.h"

class DoubleDamageFactory : public IFactory
{
public:
    IAbility* createAbility();
};


class ScannerFactory : public IFactory
{
private:
    Map& map;
    CoordHolder& holder;

public:
    ScannerFactory(Map& map, CoordHolder& holder);
    IAbility* createAbility();
};


class BombardmentFactory : public IFactory
{
private:
    Map& map;

public:
    BombardmentFactory(Map& map);
    IAbility* createAbility();
};

#endif