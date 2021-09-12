#include "Fleet.hpp"

int Fleet::fleet_size = 0;
std::array<int, 4> Fleet::ship_class {};
//sf::Color Fleet::fleet_colour{};

Fleet::Fleet()
{
    //fleet_size = 0;
    std::cout << fleet_size << std::endl;
}

void Fleet::setFleetSize(int size)
{
    fleet_size = size;
}

int &Fleet::getFleetSize()
{
    return fleet_size;
}

/*void Fleet::setFleetColour(sf::Color& colour)
{
    fleet_colour = colour;
}

sf::Color &Fleet::getFleetColour()
{
    return fleet_colour;
}*/

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


