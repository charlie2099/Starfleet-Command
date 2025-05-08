#ifndef STARFLEET_COMMAND_BATTLESHIP_HPP
#define STARFLEET_COMMAND_BATTLESHIP_HPP
#include <SFML/System/Vector2.hpp>
#include "Sprites/Starships/Starship.hpp"
#include "Sprites/UI/HealthBar.hpp"

class Battleship : public Starship
{
public:
    explicit Battleship(int spacelane);
    bool CanEngageWith(const std::unique_ptr<Starship> &starship) override;
};

#endif //STARFLEET_COMMAND_BATTLESHIP_HPP
