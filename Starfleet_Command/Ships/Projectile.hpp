#ifndef STARFLEET_COMMAND_PROJECTILE_HPP
#define STARFLEET_COMMAND_PROJECTILE_HPP
#include "../Components/SpriteComponent.hpp"
#include <cmath>

class Projectile
{
 public:
    enum class Type
    {
        LASER_RED_SMALL,
        LASER_BLUE_SMALL,
        LASER_GREEN_SMALL,
        LASER_RED_REGULAR,
        LASER_BLUE_REGULAR,
        LASER_GREEN_REGULAR,
        LASER_RED_LARGE,
        LASER_BLUE_LARGE,
        LASER_GREEN_LARGE
    };

 public:
    Projectile(Type type, sf::Vector2f spawn_pos, sf::Vector2f target_pos);
    ~Projectile() = default;

    void Update(sf::RenderWindow& window, sf::Time deltaTime);
    void Render(sf::RenderWindow& window);

    SpriteComponent& GetSpriteComponent();
    Type& GetType() { return  _type; };

 private:
    SpriteComponent _spriteComponent;
    Type _type;
    sf::Vector2<float> _direction;
};

#endif //STARFLEET_COMMAND_PROJECTILE_HPP
