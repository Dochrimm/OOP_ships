#include "CoordinateManagement.h"
#include <limits>

int CoordReader::readCoord(const std::string& prompt)
{
    int input;
    std::cout << prompt;
    while (true) {
        if (std::cin >> input) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return input;
        } else {
            std::cout << "Uncorrect input. Try again: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        };
    };
};


void CoordHolder::requestData()
{   
    int x = coord_reader->readCoord("Input \"x\" for scan: ");
    int y = coord_reader->readCoord("Input \"y\" for scan: ");
    std::cout << "coordinate have been entered: (" << x << "; " << y << ')' << '\n';
    coordinates = std::make_pair(x, y);
};
std::pair<int, int> CoordHolder::getCoords() const
{
    return coordinates;
};