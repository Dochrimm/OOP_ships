#include "Cell.h"

void Cell::setState(MapCells state)
{
    this->state = state;
};
void Cell::setShipAdress(Ship* ship_adress)
{
    this->ship_pointer = ship_adress;
};
void Cell::setSegmentIndex(int segment_index)
{
    this->segment_index = segment_index;
};
void Cell::forbidAccess()
{
    this->is_available = false;
};
Ship* Cell::getShipAdress() const
{
    return ship_pointer;
};
int Cell::getSegmentIndex() const
{
    return segment_index;
};
Cell::MapCells Cell::getState() const
{
    return state;
};
bool Cell::isAvailable() const
{
    return is_available;
};
