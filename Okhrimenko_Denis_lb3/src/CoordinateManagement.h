#ifndef COORDINATE_MANAGEMENT_H 
#define COORDINATE_MANAGEMENT_H

#include <iostream>

class CoordReader
{
public:
    static int readCoord(const std::string& prompt);
};


class InfoHolder
{
public:
    virtual void requestData() = 0;
    virtual ~InfoHolder() = default;
};


class CoordHolder : public InfoHolder
{
private:
    CoordReader* coord_reader;
    std::pair<int, int> coordinates;

public:
    void requestData() override;
    std::pair<int, int> getCoords() const;
};

#endif