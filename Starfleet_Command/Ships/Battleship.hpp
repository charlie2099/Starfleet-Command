#ifndef STARFLEET_COMMAND_BATTLESHIP_HPP
#define STARFLEET_COMMAND_BATTLESHIP_HPP
#include "Starship.hpp"

class Battleship: public Starship
{
 public:
    Battleship();
    ~Battleship() = default;

    void render(sf::RenderWindow& window) override;
    SpriteComponent &getSpriteComp();

 private:
    SpriteComponent spriteComponent;
};

#endif //STARFLEET_COMMAND_BATTLESHIP_HPP
