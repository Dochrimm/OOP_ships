#ifndef EXCEPTIONS_H 
#define EXCEPTIONS_H

#include "IException.h"

class ShipsIntersectionException : public IException
{
public:
    explicit ShipsIntersectionException(const std::string& message) 
        : IException("ShipsIntersectionException: " + message) {};
};

class MapOutsideException : public IException
{
public:
    explicit MapOutsideException(const std::string& message) 
        : IException("MapOutsideException: " + message) {};
};

class NoAbilitiesException : public IException
{
public:
    explicit NoAbilitiesException(const std::string& message) 
        : IException("MapOutsideException: " + message) {};
};

class Accident : public IException {
public:
    explicit Accident(const std::string& message) 
        : IException("accident: " + message) {}
};

#endif