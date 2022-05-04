#ifndef STARFLEET_COMMAND_STARSHIPFACTORY_HPP
#define STARFLEET_COMMAND_STARSHIPFACTORY_HPP
#include "Interfaces/IStarship.hpp"
#include "Sprites/Starships/StarshipClasses/StarshipFighter.hpp"
#include <memory>

class StarshipFactory
{
public:
    enum SHIP_TYPE
    {
        FIGHTER,
        REPAIR,
        SCOUT,
        DESTROYER,
        BATTLESHIP,
        FLAGSHIP
    };

    static std::unique_ptr<IStarship> CreateShip(SHIP_TYPE shipType);
};

#endif //STARFLEET_COMMAND_STARSHIPFACTORY_HPP
