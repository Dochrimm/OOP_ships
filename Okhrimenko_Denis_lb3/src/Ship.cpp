#include "Ship.h"

Ship::Ship(int length)
{
    if(length < 1){
        std::cout << "length of ship is too small, correct to size \"one\"\n";
        length=1;
    } else if (length > 4){
        std::cout << "length of ship is too big, correct to size \"four\"\n";
        length=4;
    };
    this->length=length;
    segments_of_ship.assign(length, SegmentsOfShip::intact);
};
int Ship::getSize() const
{
    return this->length;
};
Ship::SegmentsOfShip Ship::getSegment(int index) const
{
    return this->segments_of_ship.at(index);
};
void Ship::setSegment(int index, SegmentsOfShip segment)
{
    this->segments_of_ship.at(index) = segment;
};
void Ship::damageSegment(int index, int extraDamage) 
{
    if (extraDamage > 1) extraDamage = 1;
    if (segments_of_ship.at(index) == SegmentsOfShip::destroyed) {
        std::cout << "[WARNING] segment has already been destroyed!" << '\n';
    } else {
        if (extraDamage) {
            segments_of_ship.at(index) = SegmentsOfShip::destroyed;
        } else {
            if (segments_of_ship.at(index) == SegmentsOfShip::intact) {                       
            segments_of_ship.at(index) = SegmentsOfShip::damaged;
            } else {
                segments_of_ship.at(index) = SegmentsOfShip::destroyed;
            };
        };
    };
};
void Ship::printSegments() const
{
    for(size_t i=0; i<length; ++i){
        std::cout << static_cast<int>(segments_of_ship[i]) << ' ';
    };
    std::cout << '\n';
};
bool Ship::isDestroyed() const
{
    for (const auto& segment : segments_of_ship) {
        if (segment != SegmentsOfShip::destroyed) {
            return false; 
        };
    };
    return true; 
};
std::vector<Ship::SegmentsOfShip> Ship::getSegments() const
{
    return segments_of_ship;
};
void Ship::setSegmentsState(const std::vector<SegmentsOfShip>& newSegments) 
{
    segments_of_ship = newSegments;
};
void Ship::restore() {
    segments_of_ship.assign(length, SegmentsOfShip::intact);
};