#include "Sprites/Starships/StarshipFactory.hpp"

std::unique_ptr<IStarship> StarshipFactory::CreateShip(StarshipFactory::STARSHIP_TYPE shipType)
{
    switch (shipType)
    {
        case LIGHTFIGHTER: return std::make_unique<LightFighter>(0);
        case HEAVYFIGHTER: return std::make_unique<HeavyFighter>(0);
        case SUPPORT: return std::make_unique<SupportShip>(0);
        case DESTROYER: return std::make_unique<Destroyer>(0);
        case BATTLESHIP: return std::make_unique<Battleship>(0);
        case MOTHERSHIP: return std::make_unique<Mothership>(0);
    }
}

std::unique_ptr<IStarship> StarshipFactory::CreateShip(StarshipFactory::STARSHIP_TYPE shipType, int spacelane)
{
    switch (shipType)
    {
        case LIGHTFIGHTER: return std::make_unique<LightFighter>(spacelane);
        case HEAVYFIGHTER: return std::make_unique<HeavyFighter>(spacelane);
        case SUPPORT: return std::make_unique<SupportShip>(spacelane);
        case DESTROYER: return std::make_unique<Destroyer>(spacelane);
        case BATTLESHIP: return std::make_unique<Battleship>(spacelane);
        case MOTHERSHIP: return std::make_unique<Mothership>(spacelane);
    }
}

StarshipFactory::STARSHIP_TYPE StarshipFactory::GetStarshipType(std::unique_ptr<IStarship>& starship)
{
    if(starship.get() == dynamic_cast<LightFighter*>(starship.get()))
    {
        return STARSHIP_TYPE::LIGHTFIGHTER;
    }
    else if(starship.get() == dynamic_cast<HeavyFighter*>(starship.get()))
    {
        return STARSHIP_TYPE::HEAVYFIGHTER;
    }
    else if(starship.get() == dynamic_cast<SupportShip*>(starship.get()))
    {
        return STARSHIP_TYPE::SUPPORT;
    }
    else if(starship.get() == dynamic_cast<Destroyer*>(starship.get()))
    {
        return STARSHIP_TYPE::DESTROYER;
    }
    else if(starship.get() == dynamic_cast<Battleship*>(starship.get()))
    {
        return STARSHIP_TYPE::BATTLESHIP;
    }
    else if(starship.get() == dynamic_cast<Mothership*>(starship.get()))
    {
        return STARSHIP_TYPE::MOTHERSHIP;
    }
}
