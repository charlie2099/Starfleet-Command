#ifndef STARFLEET_COMMAND_HEAVYFIGHTER_HPP
#define STARFLEET_COMMAND_HEAVYFIGHTER_HPP
#include <SFML/System/Vector2.hpp>
#include "Sprites/Starships/Starship.hpp"
#include "Sprites/UI/HealthBar.hpp"

class HeavyFighter : public Starship
{
public:
    explicit HeavyFighter(int spawnSpacelane, const std::string& starshipTypeName);
};

#endif //STARFLEET_COMMAND_HEAVYFIGHTER_HPP
