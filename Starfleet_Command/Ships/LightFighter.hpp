#ifndef STARFLEET_COMMAND_LIGHTFIGHTER_HPP
#define STARFLEET_COMMAND_LIGHTFIGHTER_HPP
#include "Starship.hpp"

class LightFighter : public Starship
{
 public:
     LightFighter();
     ~LightFighter() = default;

     void render(sf::RenderWindow& window) override;
     SpriteComponent &getSpriteComp();

 private:
    SpriteComponent spriteComponent;
};

#endif //STARFLEET_COMMAND_LIGHTFIGHTER_HPP
