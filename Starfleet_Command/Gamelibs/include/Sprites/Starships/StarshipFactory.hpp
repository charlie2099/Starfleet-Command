#ifndef STARFLEET_COMMAND_STARSHIPFACTORY_HPP
#define STARFLEET_COMMAND_STARSHIPFACTORY_HPP
#include "Interfaces/IStarship.hpp"
#include "Sprites/Starships/StarshipClasses/LightFighter.hpp"
#include "Sprites/Starships/StarshipClasses/HeavyFighter.hpp"
#include "Sprites/Starships/StarshipClasses/SupportFrigate.hpp"
#include "Sprites/Starships/StarshipClasses/Dreadnought.hpp"
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
        SUPPORT_FRIGATE,
        DREADNOUGHT,
        BATTLESHIP,
        MOTHERSHIP,
        ENUM_COUNT
    };

    static std::unique_ptr<IStarship> CreateShip(STARSHIP_TYPE shipType);
    static std::unique_ptr<IStarship> CreateShip(STARSHIP_TYPE shipType, int spacelane);
    static STARSHIP_TYPE GetStarshipType(std::unique_ptr<IStarship>& starship);
};

#endif //STARFLEET_COMMAND_STARSHIPFACTORY_HPP
