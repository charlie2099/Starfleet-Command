#ifndef STARFLEET_COMMAND_DREADNOUGHT_HPP
#define STARFLEET_COMMAND_DREADNOUGHT_HPP
#include <SFML/System/Vector2.hpp>
#include "Sprites/Starships/Starship.hpp"
#include "Sprites/UI/HealthBar.hpp"

class Dreadnought : public Starship
{
public:
    explicit Dreadnought(int spacelane);
    bool CanEngageWith(const std::unique_ptr<Starship> &starship) override;
};

#endif //STARFLEET_COMMAND_DREADNOUGHT_HPP
