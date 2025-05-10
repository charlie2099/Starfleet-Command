#ifndef STARFLEET_COMMAND_DREADNOUGHT_HPP
#define STARFLEET_COMMAND_DREADNOUGHT_HPP
#include <SFML/System/Vector2.hpp>
#include "Sprites/Starships/Starship.hpp"
#include "Sprites/UI/HealthBar.hpp"

class Dreadnought : public Starship
{
public:
    explicit Dreadnought(int spawnSpacelane, const std::string& starshipTypeName);
};

#endif //STARFLEET_COMMAND_DREADNOUGHT_HPP
