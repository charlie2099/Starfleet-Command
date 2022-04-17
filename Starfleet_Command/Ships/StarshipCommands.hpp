#ifndef STARFLEET_COMMAND_STARSHIPCOMMANDS_HPP
#define STARFLEET_COMMAND_STARSHIPCOMMANDS_HPP
#include <SFML/System/Vector2.hpp>

class StarshipCommands
{
 public:
    StarshipCommands() = default;
    ~StarshipCommands() = default;

    enum class Command { SHOOT, ATTACK, DEFEND, FOLLOW, MOVETO, SELF_DESTRUCT };
    Command command;

 private:
};

#endif //STARFLEET_COMMAND_STARSHIPCOMMANDS_HPP
