#ifndef STARFLEET_COMMAND_LIGHTFIGHTER_HPP
#define STARFLEET_COMMAND_LIGHTFIGHTER_HPP
#include <SFML/System/Vector2.hpp>
#include "Sprites/Starships/Starship.hpp"
#include "Sprites/UI/HealthBar.hpp"

class LightFighter : public Starship
{
public:
    explicit LightFighter(int spawnSpacelane, const std::string& starshipTypeName);
};

#endif //STARFLEET_COMMAND_LIGHTFIGHTER_HPP
