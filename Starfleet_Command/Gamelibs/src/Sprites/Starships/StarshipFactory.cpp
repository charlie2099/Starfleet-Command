#include "Sprites/Starships/StarshipFactory.hpp"

std::unique_ptr<IStarship> StarshipFactory::CreateShip(StarshipFactory::SHIP_TYPE shipType)
{
    switch (shipType)
    {
        case FIGHTER: return std::make_unique<StarshipFighter>();
        case REPAIR: return std::make_unique<StarshipFighter>();
        case SCOUT: return std::make_unique<StarshipFighter>();
        case DESTROYER: return std::make_unique<StarshipFighter>();
        case BATTLESHIP: return std::make_unique<StarshipFighter>();
        case FLAGSHIP: return std::make_unique<StarshipFighter>();
        default: return std::make_unique<StarshipFighter>();
    }
}
