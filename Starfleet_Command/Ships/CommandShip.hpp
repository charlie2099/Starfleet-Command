#ifndef STARFLEET_COMMAND_COMMANDSHIP_HPP
#define STARFLEET_COMMAND_COMMANDSHIP_HPP
#include "Starship.hpp"

class CommandShip : public Starship
{
 public:
    explicit CommandShip(int health = 1);
    ~CommandShip() = default;

    void render(sf::RenderWindow& window) override;
    SpriteComponent &getSpriteComp();

 private:
    SpriteComponent spriteComponent;
    int health_test_;
};

#endif //STARFLEET_COMMAND_COMMANDSHIP_HPP
