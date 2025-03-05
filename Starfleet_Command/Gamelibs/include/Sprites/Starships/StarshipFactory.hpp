#ifndef STARFLEET_COMMAND_STARSHIPFACTORY_HPP
#define STARFLEET_COMMAND_STARSHIPFACTORY_HPP
#include "Interfaces/IStarship.hpp"
#include "Sprites/Starships/StarshipClasses/LightFighter.hpp"
#include "Sprites/Starships/StarshipClasses/HeavyFighter.hpp"
#include "Sprites/Starships/StarshipClasses/SupportShip.hpp"
#include "Sprites/Starships/StarshipClasses/Destroyer.hpp"
#include "Sprites/Starships/StarshipClasses/Battleship.hpp"
#include "Sprites/Starships/StarshipClasses/Mothership.hpp"
#include <memory>

class StarshipFactory
{
public:
    enum STARSHIP_TYPE
    {
        LIGHTFIGHTER,
        HEAVYFIGHTER,
        SUPPORT,
        DESTROYER,
        BATTLESHIP,
        MOTHERSHIP,
        ENUM_COUNT
    };

    //static std::unique_ptr<IStarship> CreateShip(STARSHIP_TYPE shipType);
    static std::unique_ptr<IStarship> CreateShip(STARSHIP_TYPE shipType, int spacelane);
};

#endif //STARFLEET_COMMAND_STARSHIPFACTORY_HPP
