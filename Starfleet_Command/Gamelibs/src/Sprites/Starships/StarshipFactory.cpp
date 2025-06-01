#include "Sprites/Starships/StarshipFactory.hpp"

std::unique_ptr<Starship> StarshipFactory::CreateShip(StarshipFactory::STARSHIP_TYPE shipType)
{
    switch (shipType)
    {
        case LIGHTFIGHTER: return std::make_unique<LightFighter>(0, "Light Fighter");
        case HEAVYFIGHTER: return std::make_unique<HeavyFighter>(0, "Heavy Fighter");
        case SUPPORT_FRIGATE: return std::make_unique<SupportFrigate>(0, "Support Frigate");
        case DREADNOUGHT: return std::make_unique<Dreadnought>(0, "Dreadnought");
        case BATTLESHIP: return std::make_unique<Battleship>(0, "Battleship");
        case REAPER: return std::make_unique<Reaper>(0, "Reaper");
        case MOTHERSHIP: return std::make_unique<Mothership>(0, "Mothership");
    }
}

std::unique_ptr<Starship> StarshipFactory::CreateShip(StarshipFactory::STARSHIP_TYPE shipType, int spawnSpacelane)
{
    switch (shipType)
    {
        case LIGHTFIGHTER: return std::make_unique<LightFighter>(spawnSpacelane, "Light Fighter");
        case HEAVYFIGHTER: return std::make_unique<HeavyFighter>(spawnSpacelane, "Heavy Fighter");
        case SUPPORT_FRIGATE: return std::make_unique<SupportFrigate>(spawnSpacelane, "Support Frigate");
        case DREADNOUGHT: return std::make_unique<Dreadnought>(spawnSpacelane, "Dreadnought");
        case BATTLESHIP: return std::make_unique<Battleship>(spawnSpacelane, "Battleship");
        case REAPER: return std::make_unique<Reaper>(spawnSpacelane, "Reaper");
        case MOTHERSHIP: return std::make_unique<Mothership>(spawnSpacelane, "Mothership");
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
    if (name == "Reaper") return STARSHIP_TYPE::REAPER;
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
    if(starshipTypeName == "REAPER") return STARSHIP_TYPE::REAPER;
    if(starshipTypeName == "MOTHERSHIP") return STARSHIP_TYPE::MOTHERSHIP;

    throw std::runtime_error("Unknown starship type name: " + starshipTypeName);
}

std::string StarshipFactory::GetStarshipNameFromType(const StarshipFactory::STARSHIP_TYPE starshipType)
{
    if(starshipType == STARSHIP_TYPE::LIGHTFIGHTER) return "LIGHTFIGHTER";
    if(starshipType == STARSHIP_TYPE::HEAVYFIGHTER) return "HEAVYFIGHTER";
    if(starshipType == STARSHIP_TYPE::SUPPORT_FRIGATE) return "SUPPORT_FRIGATE";
    if(starshipType == STARSHIP_TYPE::DREADNOUGHT) return "DREADNOUGHT";
    if(starshipType == STARSHIP_TYPE::BATTLESHIP) return "BATTLESHIP";
    if(starshipType == STARSHIP_TYPE::REAPER) return "REAPER";
    if(starshipType == STARSHIP_TYPE::MOTHERSHIP) return "MOTHERSHIP";

    throw std::runtime_error("Unknown starship type name");
}
