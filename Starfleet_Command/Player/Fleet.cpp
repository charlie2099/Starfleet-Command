#include "Fleet.hpp"

void Fleet::setNumOfShips(int count, Fleet::ShipType shipType)
{
    for (int i = 0; i < SHIP_CLASSES; ++i)
    {
        ship_class[static_cast<size_t>(shipType)] = count;
    }
}

const std::array<int, 4> &Fleet::getNumOfShips() const
{
    return ship_class;
}

void Fleet::setFleetSize(int size)
{
    fleet_size = size;
}

int Fleet::getFleetSize() const
{
    return fleet_size;
}
