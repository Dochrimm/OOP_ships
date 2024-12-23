#include "ShipManager.h"

ShipManager::ShipManager(int amount_of_ships, std::vector<int>& ship_sizes_list)
{
    for (size_t i=0; i<amount_of_ships; ++i) {
        ship_list.emplace_back(ship_sizes_list[i]);
    };
};
Ship& ShipManager::getShip(int index)
{
    return ship_list.at(index);
};   
int ShipManager::getShipCount() const
{
    return ship_list.size();
};
void ShipManager::printShipsList() const
{
    for(int i{}; i<ship_list.size(); ++i){
        std::cout << i << ": ";
        ship_list.at(i).printSegments();
    };
};
std::vector<Ship>& ShipManager::getShipArray()
{
    return ship_list;
};
void ShipManager::addShip(const Ship& ship) {
    ship_list.push_back(ship);
};
Ship& ShipManager::addShip(int length) {
    int index = ship_list.size();
    ship_list.emplace_back(Ship(length));
    return ship_list.back();
};
void ShipManager::clearShips() {
    ship_list.clear();
};
void ShipManager::restoreShips() {
    for (auto& ship : ship_list) {
        ship.restore();
    }
}