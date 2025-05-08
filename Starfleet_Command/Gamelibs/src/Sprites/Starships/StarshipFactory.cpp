#include "Sprites/Starships/StarshipFactory.hpp"

std::unique_ptr<Starship> StarshipFactory::CreateShip(StarshipFactory::STARSHIP_TYPE shipType)
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

std::unique_ptr<Starship> StarshipFactory::CreateShip(StarshipFactory::STARSHIP_TYPE shipType, int spacelane)
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

StarshipFactory::STARSHIP_TYPE StarshipFactory::GetStarshipType(std::unique_ptr<Starship>& starship)
{
    std::string name = starship->GetStarshipName();

    if (name == "Light Fighter") return STARSHIP_TYPE::LIGHTFIGHTER;
    if (name == "Heavy Fighter") return STARSHIP_TYPE::HEAVYFIGHTER;
    if (name == "Support Frigate") return STARSHIP_TYPE::SUPPORT_FRIGATE;
    if (name == "Dreadnought") return STARSHIP_TYPE::DREADNOUGHT;
    if (name == "Battleship") return STARSHIP_TYPE::BATTLESHIP;
    if (name == "Mothership") return STARSHIP_TYPE::MOTHERSHIP;

    throw std::runtime_error("Unknown starship type");
}

StarshipFactory::STARSHIP_TYPE StarshipFactory::GetStarshipTypeFromString(const std::string& starshipTypeName)
{
    if(starshipTypeName == "LIGHTFIGHTER") return STARSHIP_TYPE::LIGHTFIGHTER;
    if(starshipTypeName == "HEAVYFIGHTER") return STARSHIP_TYPE::HEAVYFIGHTER;
    if(starshipTypeName == "SUPPORT_FRIGATE") return STARSHIP_TYPE::SUPPORT_FRIGATE;
    if(starshipTypeName == "DREADNOUGHT") return STARSHIP_TYPE::DREADNOUGHT;
    if(starshipTypeName == "BATTLESHIP") return STARSHIP_TYPE::BATTLESHIP;
    if(starshipTypeName == "MOTHERSHIP") return STARSHIP_TYPE::MOTHERSHIP;

    throw std::runtime_error("Unknown starship type name: " + starshipTypeName);
}
