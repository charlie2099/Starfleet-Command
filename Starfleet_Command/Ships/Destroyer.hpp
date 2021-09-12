#ifndef STARFLEET_COMMAND_DESTROYER_HPP
#define STARFLEET_COMMAND_DESTROYER_HPP
#include "Starship.hpp"

class Destroyer: public Starship
{
 public:
    Destroyer();
    ~Destroyer() = default;

    void render(sf::RenderWindow& window) override;
    SpriteComponent &getSpriteComp();

 private:
    SpriteComponent spriteComponent;
};

#endif //STARFLEET_COMMAND_DESTROYER_HPP
