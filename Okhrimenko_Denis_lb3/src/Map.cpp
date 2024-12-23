#define BrightWhite "\x1B[97m"
#define Orange "\x1b[33m"
#define Red "\x1b[31m"
#define BrightRed "\x1B[91m"
#define Cyan "\x1B[36m"
#define Magenta "\x1B[95m"
#define EndOfFormatOutput "\033[0m\e[0m"
#define BOLD "\e[1m"

#include "Map.h"

Map::Map(int x, int y, ShipManager* ship_manager)
{
    if(x < 1){
        std::cout << "horizontal size of map must be natural number, exchange to 8" << '\n';
        x=8;
    };
    if(y < 1){
        std::cout << "horizontal size of map must be natural number, exchange to 8" << '\n';
        y=8;
    };

    this->sizes_of_map={x, y};
    for (int i{}; i < x*y; ++i) {
        map.emplace_back();
    };
    this->ship_manager = ship_manager;
};
bool Map::attack(int x, int y, std::optional<AbilityResponce*> abilities_status)
{
    if (x < 1 or y < 1 or x > this->sizes_of_map.first or y > this->sizes_of_map.second) {
        throw MapOutsideException("MapOutsideException: Attempting to off-field attack");
    };
    x-=1;
    y-=1;
    int width_of_map=sizes_of_map.second;
    Cell& attacked_cell = map.at(x*width_of_map+y);
    if (attacked_cell.getState() == Cell::MapCells::filled) {
        Ship* attacked_ship = attacked_cell.getShipAdress();
        int index_of_segment = attacked_cell.getSegmentIndex();
        if (attacked_ship->getSegment(index_of_segment) != Ship::SegmentsOfShip::destroyed) {
            if (abilities_status.has_value()) {
                if (abilities_status.value()->getDoubleDamageStatus() == AbilityResponce::DoubleDamageStatus::activated) {
                    attacked_ship->damageSegment(index_of_segment, 1);
                    std::cout << "There is a double penetration! (" << x+1 << "; " << y+1 << ')' << '\n';
                } else {
                    attacked_ship->damageSegment(index_of_segment, 0);
                    std::cout << "There is a penetration! (" << x+1 << "; " << y+1 << ')' << '\n';
                };
                abilities_status.value()->disableDoubleDamage();
            } else {
                attacked_ship->damageSegment(index_of_segment, 0);
                std::cout << "There is a penetration! (" << x+1 << "; " << y+1 << ')' << '\n';
            };
        } else {
            std::cout << "[WARNING] ship_segment has already been destroyed" << '\n';
        };
        if(attacked_ship->isDestroyed()) return true; 
    } else {
        if (attacked_cell.getState() == Cell::MapCells::unknown) {
            attacked_cell.setState(Cell::MapCells::empty);
        };
        std::cout << "A miss: (" << x+1 << "; " << y+1 << ')' << '\n';
    };
    return false;
};
void Map::placeShipOnTheMap(int index, int x, int y, std::string direction)
{
    x-=1;
    y-=1;
    Ship& ship = ship_manager->getShip(index);
    Directions direction_;
    if (direction == "vertical") {
        direction_ = Directions::vertical;
    } else if (direction == "horizontal") {
        direction_ = Directions::horizontal;
    } else {
        std::cout << "direction of ship must be \"horizontal\" or \"vertical\", direction will be change to \"horizontal\"" << '\n';
        direction_ = Directions::horizontal;
    };
    int width_of_map = this->sizes_of_map.second;

    // ship must be completely placed on the map
    int check = 0;
    check+=(x<0 or x>sizes_of_map.first-1)+(y<0 or y>this->sizes_of_map.second-1);
    if (direction_ == Directions::vertical) {
        check+=(x+ship.getSize()-1>this->sizes_of_map.first-1);
    } else {
        check+=(y+ship.getSize()-1>this->sizes_of_map.second-1);
    };

    if (check) {
        throw MapOutsideException("Attempting to place the ship off the map");
    };

    // ship cannot intersect another
    int flag = map.at(x*width_of_map+y).isAvailable() ? 0 : 1;
    for (int i=1; i < ship.getSize(); ++i) {
        if (direction_ == Directions::horizontal) {
            flag+=this->map.at(x*width_of_map+y+i).isAvailable() ? 0 : 1;
        } else {
            flag+=this->map.at((x+i)*width_of_map+y).isAvailable() ? 0 : 1;
        };
    };

    if (flag) {
        throw ShipsIntersectionException("Attempting to cross the ships");
    };
    
    // Ship placement and adding info
    for (int i{}; i < ship.getSize(); ++i) {
        if (direction_ == Directions::horizontal) {
            Cell& configured_cell = map.at(x*width_of_map+y+i);
            configured_cell.setState(Cell::MapCells::filled);
            configured_cell.setShipAdress(&ship);
            configured_cell.setSegmentIndex(i);
        } else {
            Cell& configured_cell = map.at((x+i)*width_of_map+y);
            configured_cell.setState(Cell::MapCells::filled);
            configured_cell.setShipAdress(&ship);
            configured_cell.setSegmentIndex(i);
        };
        
    };

    // filling the ordered_cells 
    if (direction_ == Directions::horizontal) {
        for (int index_x=x-1; index_x < x+2; ++index_x) {
            for (int index_y=y-1; index_y <= y+ship.getSize(); ++index_y) {
                int index = index_x*width_of_map + index_y;
                if (0 <= index_y and index_y <= width_of_map-1) {
                    if (0 <= index_x and index_x <= sizes_of_map.first-1) {
                        map.at(index).forbidAccess();
                    };
                };
            };
        };
    } else {
        for (int index_x=x-1; index_x <= x+ship.getSize(); ++index_x) {
            for (int index_y=y-1; index_y < y+2; ++index_y) {
                int index = index_x*width_of_map + index_y;
                if (0 <= index_y and index_y <= width_of_map-1) {
                    if (0 <= index_x and index_x <= sizes_of_map.first-1) {
                        map.at(index).forbidAccess();
                    };
                };
            };
        };
    };
};
void Map::printMap(bool side) const
{
    auto i_map {map.begin()};
    int width_of_map=sizes_of_map.second;
    std::cout << "Display map:" << '\n';

    for (int x{}; x < sizes_of_map.first; ++x){
        for (int y{}; y < sizes_of_map.second; ++y){
            int ind = x*width_of_map+y;
            if ((*(i_map + ind)).getState() == Cell::MapCells::filled) {
                Ship* ship = (*(i_map + ind)).getShipAdress();
                int segment_index = (*(i_map + ind)).getSegmentIndex();
                if (ship->getSegment(segment_index) == Ship::SegmentsOfShip::destroyed) {
                    std::cout << BOLD;
                    std::cout << Red;    
                } else if (ship->getSegment(segment_index) == Ship::SegmentsOfShip::damaged) {
                    std::cout << BOLD;
                    std::cout << Orange;
                } else {
                    if (side == true) {
                        std::cout << BOLD;
                        std::cout << BrightWhite;
                        std::cout.width(2);
                        std::cout << 'S';
                    } else {
                        std::cout << Magenta;
                        std::cout.width(2);
                        std::cout << '?';
                    };
                    std::cout << EndOfFormatOutput;
                    continue;
                };
            } else if ((*(i_map+ind)).getState() == Cell::MapCells::empty) {
                if (side == true) {
                    std::cout << Cyan;
                    std::cout.width(2);
                    std::cout << '~';
                    std::cout << EndOfFormatOutput;
                    continue;
                };
                std::cout << Cyan;
            } else {
                std::cout << Magenta;
            };
            std::cout.width(2);
            std::cout << static_cast<char>((*(i_map+ind)).getState());
            std::cout << EndOfFormatOutput;
        };
        std::cout << '\n';
    };
};
ShipManager& Map::getShipManager() const
{
    return *ship_manager;
};
int Map::getHeight() const
{
    return sizes_of_map.first;
};
int Map::getWidth() const
{
    return sizes_of_map.second;
};
Cell& Map::getCell(int x, int y)
{
    return map[x*sizes_of_map.second + y];
};
void Map::setSize(int height, int width) {
    sizes_of_map = std::make_pair(height, width);
    map.clear();
};
void Map::setCellState(Cell::MapCells state)
{
    map.emplace_back(state);
};
void Map::clear() {
    for (int x{}; x < sizes_of_map.first; ++x) {
        for (int y{}; y < sizes_of_map.second; ++y) {
            map[x*sizes_of_map.second + y].setState(Cell::MapCells::unknown);
            map[x*sizes_of_map.second + y].setShipAdress(nullptr);
            map[x*sizes_of_map.second + y].setSegmentIndex(-1);
        };
    };
};
Map::Map(const Map& other)
{
    sizes_of_map=other.sizes_of_map;
    map=other.map;
};
Map& Map::operator=(const Map& other)
{
    if (this == &other) return *this;
    sizes_of_map = other.sizes_of_map;
    map = other.map;
    return *this;
};
Map::Map(Map&& other) noexcept
{
    sizes_of_map = other.sizes_of_map;
    map = other.map;
};
Map& Map::operator=(Map&& other) noexcept
{
    if (this == &other) return *this;
    sizes_of_map = other.sizes_of_map;
    map = std::move(other.map);
    return *this;
};
Cell& Map::operator[](int ind)
{
    return map.at(ind);
};
