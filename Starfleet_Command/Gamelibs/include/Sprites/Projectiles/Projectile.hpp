#ifndef STARFLEET_COMMAND_PROJECTILE_HPP
#define STARFLEET_COMMAND_PROJECTILE_HPP
#include "Components/SpriteComponent.hpp"
#include <cmath>

class Projectile
{
 public:
    enum Size
    {
        SMALL = 0,
        REGULAR = 1,
        LARGE = 2
    };

    enum Colour
    {
        BLUE,
        GREEN,
        RED
    };

 public:
    Projectile(Size size, Colour colour, sf::Vector2f spawn_pos, sf::Vector2f target_pos);
    ~Projectile() = default;

    void Update(sf::RenderWindow& window, sf::Time deltaTime);
    void Render(sf::RenderWindow& window);

    SpriteComponent& GetSpriteComponent();
    Size GetSize() { return _size; }
    Colour GetColour() { return _colour; }

 private:
    SpriteComponent _spriteComponent;
    sf::Vector2<float> _direction;
    Size _size;
    Colour _colour;
};

#endif //STARFLEET_COMMAND_PROJECTILE_HPP
