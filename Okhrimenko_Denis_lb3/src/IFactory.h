#ifndef IFACTORY_H 
#define IFACTORY_H

#include "IAbility.h"

class IFactory
{
public:
    virtual IAbility* createAbility() = 0;
    virtual ~IFactory() = default;
};

#endif