#ifndef MAP_H 
#define MAP_H

#include "ShipManager.h"
#include "Cell.h"
#include "Exceptions.h"
#include "Abilities.h"
#include "AbilityResponce.h"
#include <optional>

class Map
{
public:
enum class Directions
{
    horizontal,
    vertical
};

private:
    std::pair<int, int> sizes_of_map;
    std::vector<Cell> map;
    ShipManager* ship_manager;

public:
    Map(int x, int y, ShipManager* ship_manager);
    bool attack(int x, int y, std::optional<AbilityResponce*> abilities_status = std::nullopt);
    void placeShipOnTheMap(int index, int x, int y, std::string direction="horizontal");
    void printMap(bool side) const;
    ShipManager& getShipManager() const;
    int getHeight() const;
    int getWidth() const;
    Cell& getCell(int x, int y);
    void setSize(int height, int width);
    void setCellState(Cell::MapCells state);
    void clear();
    
    Map(const Map& other);
    Map& operator=(const Map& other);
    Map(Map&& other) noexcept;
    Map& operator=(Map&& other) noexcept;
    Cell& operator[](int ind);
};

#endif