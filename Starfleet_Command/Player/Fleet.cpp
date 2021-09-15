#include "Fleet.hpp"

int Fleet::fleet_size = 0;
std::array<int, 4> Fleet::ship_class {};
Fleet::Colour Fleet::fleet_colour {};

void Fleet::setFleetSize(int size)
{
    fleet_size = size;
}

int &Fleet::getFleetSize()
{
    return fleet_size;
}

void Fleet::setFleetColourRGB(int r, int g, int b)
{
    fleet_colour.rgb_r = r;
    fleet_colour.rgb_g = g;
    fleet_colour.rgb_b = b;
}

Fleet::Colour &Fleet::getFleetColourRGB()
{
    return fleet_colour;
}


void Fleet::setNumOfShips(int count, Fleet::ShipType shipType)
{
    for (int i = 0; i < SHIP_CLASSES; ++i)
    {
        ship_class[static_cast<size_t>(shipType)] = count;
    }
}

std::array<int, 4> &Fleet::getNumOfShips()
{
    return ship_class;
}


