#ifndef STARFLEET_COMMAND_STARSHIPFIGHTERBEHAVIOUR_HPP
#define STARFLEET_COMMAND_STARSHIPFIGHTERBEHAVIOUR_HPP
#include <Interfaces/IBehaviour.hpp>

class StarshipFighterBehaviour : public IBehaviour
{
public:
    void Default() override;
    void Chase() override;
};

#endif //STARFLEET_COMMAND_STARSHIPFIGHTERBEHAVIOUR_HPP
