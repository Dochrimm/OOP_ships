#include "Abilities.h"

void DoubleDamage::use(AbilityResponce& responce)
{
    responce.setLastAbility(AbilityResponce::Ability::DoubleDamage);
    responce.doubleDamageActivated();
};


Scanner::Scanner(int x, int y, Map& map) : map(map)
{
    this->x = x;
    this->y = y;
};
void Scanner::use(AbilityResponce& responce) {
    responce.setLastAbility(AbilityResponce::Ability::Scanner);
    int map_h = map.getHeight();
    int map_w = map.getWidth();
    
    if (x < 1 or x > map_w or y < 1 or y > map_h) {
        throw MapOutsideException("MapOutsideException: try to use scan off the map");
    };

    bool shipFound = false; 
    for (int i = -1; i < 1; ++i) {
        for (int j = -1; j < 1; ++j) {
            int check_x = x + j;
            int check_y = y + i;
            if (check_x >= map_h or check_y >= map_w) {
                continue; 
            };
            Ship* ship = map[check_x * map.getWidth() + check_y].getShipAdress(); 
            if (ship and ship->getSegment(map[check_x * map.getWidth() + check_y].getSegmentIndex()) != Ship::SegmentsOfShip::destroyed) {
                responce.scannerReturnTrue();
                shipFound = true; 
                break; 
            };
        };
        if (shipFound) break; 
    };
    
    if (!shipFound) {
        responce.scannerReturnFalse();
    };
};


Bombardment::Bombardment(Map& map) : map(map) {};
void Bombardment::use(AbilityResponce& responce)
{
    responce.setLastAbility(AbilityResponce::Ability::Bombardment);
    ShipManager& manager = map.getShipManager();
    std::vector<std::pair<int, int>> ship_segments;

    for (int y{}; y < manager.getShipCount(); ++y) {
        for (int x{}; x < manager.getShip(y).getSize(); ++x) {
            if (manager.getShip(y).getSegment(x) != Ship::SegmentsOfShip::destroyed) {
                ship_segments.emplace_back(y, x);
            };
        };
    };

    if (!ship_segments.empty()) {
        int random_index = rand() % ship_segments.size();
        int y = ship_segments[random_index].first;
        int x = ship_segments[random_index].second;
        try {
            manager.getShip(y).damageSegment(x, 0);
        } catch (const Accident& e) {
            throw Accident{"Accident: segment has already been destroyed"};  
        };
    } else {
        throw Accident{"Accident: no segments available"};  
    };
};