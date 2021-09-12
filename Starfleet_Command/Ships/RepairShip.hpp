#ifndef STARFLEET_COMMAND_REPAIRSHIP_HPP
#define STARFLEET_COMMAND_REPAIRSHIP_HPP
#include "Starship.hpp"

class RepairShip: public Starship
{
 public:
    RepairShip();
    ~RepairShip() = default;

    void render(sf::RenderWindow& window) override;
    SpriteComponent &getSpriteComp();

 private:
    SpriteComponent spriteComponent;
};

#endif //STARFLEET_COMMAND_REPAIRSHIP_HPP
