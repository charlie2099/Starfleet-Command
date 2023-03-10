#include "Sprites/Starships/StarshipFactory.hpp"

std::unique_ptr<IStarship> StarshipFactory::CreateShip(StarshipFactory::SHIP_TYPE shipType)
{
    switch (shipType)
    {
        case LIGHTFIGHTER: return std::make_unique<LightFighter>();
        case HEAVYFIGHTER: return std::make_unique<HeavyFighter>();
        case SUPPORT: return std::make_unique<SupportShip>();
        case DESTROYER: return std::make_unique<Destroyer>();
        case BATTLESHIP: return std::make_unique<Battleship>();
        case MOTHERSHIP: return std::make_unique<Mothership>();
    }
}
