#ifndef CELL_H 
#define CELL_H

#include "Ship.h"

class Cell
{
public:
    enum class MapCells
{
    unknown='?',
    empty='~',
    filled='S'
};

private:
    MapCells state;
    Ship* ship_pointer;
    int segment_index;
    bool is_available;

public:
    Cell(MapCells state=MapCells::unknown) : state{MapCells::unknown}, ship_pointer{nullptr}, segment_index{-1}, is_available{true} {this->state = state;};
    Ship* getShipAdress() const;
    int getSegmentIndex() const;
    Cell::MapCells getState() const;
    bool isAvailable() const;
    
    void setState(MapCells state);
    void setShipAdress(Ship* ship_adress);
    void setSegmentIndex(int segment_index);
    void forbidAccess();
};

#endif