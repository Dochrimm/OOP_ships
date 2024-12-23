#ifndef ABILITIES_H 
#define ABILITIES_H

#include "Map.h"
#include "IAbility.h"
#include "AbilityResponce.h"

class DoubleDamage : public IAbility
{
public:
    void use(AbilityResponce& responce) override;
};


class Scanner : public IAbility
{
private:
    Map& map;
    int x;
    int y;

public:
    Scanner(int x, int y, Map& map);
    void use(AbilityResponce& responce) override;
};


class Bombardment : public IAbility 
{
private:
    Map& map;

public:
    Bombardment(Map& map);
    void use(AbilityResponce& responce) override;
};

#endif