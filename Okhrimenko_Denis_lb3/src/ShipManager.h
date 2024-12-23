#ifndef SHIP_MANAGER_H 
#define SHIP_MANAGER_H

#include <iostream>
#include "Ship.h"

class ShipManager
{
private:
    std::vector<Ship> ship_list;
    
public:
    ShipManager(int amount_of_ships, std::vector<int>& ship_sizes_list);
    Ship& getShip(int index);
    std::vector<Ship>& getShipArray();
    int getShipCount() const;
    void printShipsList() const;
    void addShip(const Ship& ship);
    Ship& addShip(int length);
    void clearShips();
    void restoreShips();
};

#endif
