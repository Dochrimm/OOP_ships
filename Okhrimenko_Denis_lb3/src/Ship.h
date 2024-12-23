#ifndef SHIP_H 
#define SHIP_H
#include <iostream>
#include <vector>

class Ship
{
public:
    enum class SegmentsOfShip
{
    intact=2,
    damaged=1,
    destroyed=0
};

private:
    int length;
    std::vector<SegmentsOfShip> segments_of_ship;
    
public:
    Ship(int length);
    int getSize() const;
    SegmentsOfShip getSegment(int index) const;
    std::vector<SegmentsOfShip> getSegments() const;
    void printSegments() const;
    bool isDestroyed() const;
    void setSegment(int index, SegmentsOfShip segment);
    void damageSegment(int index, int extraDamage);
    void setSegmentsState(const std::vector<SegmentsOfShip>& newSegments);
    void restore();
};

#endif