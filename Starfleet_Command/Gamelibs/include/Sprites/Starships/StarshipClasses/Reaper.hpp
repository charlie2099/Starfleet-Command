#ifndef STARFLEET_COMMAND_REAPER_HPP
#define STARFLEET_COMMAND_REAPER_HPP
#include <SFML/System/Vector2.hpp>
#include "Sprites/Starships/Starship.hpp"
#include "Sprites/UI/HealthBar.hpp"

class Reaper : public Starship
{
public:
    explicit Reaper(int spawnSpacelane, const std::string& starshipTypeName);
};

#endif //STARFLEET_COMMAND_REAPER_HPP
