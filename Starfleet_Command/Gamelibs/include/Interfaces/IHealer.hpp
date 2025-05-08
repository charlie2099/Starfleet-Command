#ifndef STARFLEET_COMMAND_IHEALER_HPP
#define STARFLEET_COMMAND_IHEALER_HPP
#include "Sprites/Starships/Starship.hpp"

class IHealer
{
public:
    virtual void ShootHealAt(const std::unique_ptr<Starship> &friendlyStarship) = 0;
};

#endif //STARFLEET_COMMAND_IHEALER_HPP
