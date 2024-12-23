#ifndef IABILITY_H 
#define IABILITY_H

#include "AbilityResponce.h"
class Map;

class IAbility
{
public:
    virtual void use(AbilityResponce& responce) = 0;
    virtual~IAbility() = default;
};

#endif