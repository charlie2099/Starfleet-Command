#include "Sprites/Starships/StarshipFactory.hpp"

/*std::unique_ptr<IStarship> StarshipFactory::CreateShip(StarshipFactory::STARSHIP_TYPE shipType)
{
    switch (shipType)
    {
        case LIGHTFIGHTER: return std::make_unique<LightFighter>(0);
        case HEAVYFIGHTER: return std::make_unique<HeavyFighter>(0);
        case SUPPORT: return std::make_unique<SupportShip>(0);
        case DESTROYER: return std::make_unique<Destroyer>(0);
        case BATTLESHIP: return std::make_unique<Battleship>(0);
        case FLAGSHIP: return std::make_unique<Mothership>();
    }
}*/

std::unique_ptr<IStarship> StarshipFactory::CreateShip(StarshipFactory::STARSHIP_TYPE shipType, int spacelane)
{
    switch (shipType)
    {
        case LIGHTFIGHTER: return std::make_unique<LightFighter>(spacelane);
        case HEAVYFIGHTER: return std::make_unique<HeavyFighter>(spacelane);
        case SUPPORT: return std::make_unique<SupportShip>(spacelane);
        case DESTROYER: return std::make_unique<Destroyer>(spacelane);
        case BATTLESHIP: return std::make_unique<Battleship>(spacelane);
        case FLAGSHIP: return std::make_unique<Mothership>();
    }
}
