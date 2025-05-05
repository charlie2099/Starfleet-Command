#include "Sprites/Starships/StarshipFactory.hpp"

std::unique_ptr<IStarship> StarshipFactory::CreateShip(StarshipFactory::STARSHIP_TYPE shipType)
{
    switch (shipType)
    {
        case LIGHTFIGHTER: return std::make_unique<LightFighter>(0);
        case HEAVYFIGHTER: return std::make_unique<HeavyFighter>(0);
        case SUPPORT_FRIGATE: return std::make_unique<SupportFrigate>(0);
        case DREADNOUGHT: return std::make_unique<Dreadnought>(0);
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
        case SUPPORT_FRIGATE: return std::make_unique<SupportFrigate>(spacelane);
        case DREADNOUGHT: return std::make_unique<Dreadnought>(spacelane);
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
    else if(starship.get() == dynamic_cast<SupportFrigate*>(starship.get()))
    {
        return STARSHIP_TYPE::SUPPORT_FRIGATE;
    }
    else if(starship.get() == dynamic_cast<Dreadnought*>(starship.get()))
    {
        return STARSHIP_TYPE::DREADNOUGHT;
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

StarshipFactory::STARSHIP_TYPE StarshipFactory::GetStarshipTypeFromString(const std::string& starshipTypeName)
{
    if(starshipTypeName == "LIGHTFIGHTER")
    {
        return STARSHIP_TYPE::LIGHTFIGHTER;
    }
    else if(starshipTypeName == "HEAVYFIGHTER")
    {
        return STARSHIP_TYPE::HEAVYFIGHTER;
    }
    else if(starshipTypeName == "SUPPORT_FRIGATE")
    {
        return STARSHIP_TYPE::SUPPORT_FRIGATE;
    }
    else if(starshipTypeName == "DREADNOUGHT")
    {
        return STARSHIP_TYPE::DREADNOUGHT;
    }
    else if(starshipTypeName == "BATTLESHIP")
    {
        return STARSHIP_TYPE::BATTLESHIP;
    }
    else if(starshipTypeName == "MOTHERSHIP")
    {
        return STARSHIP_TYPE::MOTHERSHIP;
    }
}
