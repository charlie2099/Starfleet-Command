#ifndef STARFLEET_COMMAND_LIGHTFIGHTER_HPP
#define STARFLEET_COMMAND_LIGHTFIGHTER_HPP
#include "Starship.hpp"

class LightFighter : public Starship
{
 public:
     explicit LightFighter(int health = 1);
     ~LightFighter() = default;

     void render(sf::RenderWindow& window) override;
     SpriteComponent &getSpriteComp();

 private:
    SpriteComponent spriteComponent;
    int health_test_;
};

#endif //STARFLEET_COMMAND_LIGHTFIGHTER_HPP
