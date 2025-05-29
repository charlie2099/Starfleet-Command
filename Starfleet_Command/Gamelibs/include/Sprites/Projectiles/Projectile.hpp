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
        RED,
        GREEN,
        ORANGE,
        YELLOW,
        PURPLE,
        PINK,
        WHITE
    };

 public:
    Projectile(Size size, Colour colour, sf::Vector2f spawnPos, sf::Vector2f targetPos);
    ~Projectile() = default;

    void Update(sf::RenderWindow& window, sf::Time deltaTime);
    void Render(sf::RenderWindow& window);

    void SetPos(sf::Vector2<float> pos);

    SpriteComponent& GetSpriteComponent() { return _spriteComponent; }
    Size GetSize() { return _size; }
    Colour GetColour() { return _colour; }
    sf::Vector2<float> GetPos() { return _spriteComponent.GetPos(); }

 private:
    SpriteComponent _spriteComponent;
    sf::Vector2<float> _direction;
    sf::Vector2f _spawnPos;
    Size _size;
    Colour _colour;
};

#endif //STARFLEET_COMMAND_PROJECTILE_HPP
