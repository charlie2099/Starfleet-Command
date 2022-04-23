#ifndef STARFLEET_COMMAND_PROJECTILE_HPP
#define STARFLEET_COMMAND_PROJECTILE_HPP
#include "../Components/SpriteComponent.hpp"
#include <cmath>

class Projectile
{
 public:
    enum class Type
    {
        LASER_BLUE,
        LASER_RED,
        MISSILE_BLUE,
        MISSILE_RED
    };

 public:
    Projectile(Type type, sf::Vector2f spawn_pos, sf::Vector2f target_pos);
    ~Projectile() = default;

    void Update(sf::RenderWindow& window, sf::Time deltaTime);
    void Render(sf::RenderWindow& window);

    SpriteComponent& GetSprite();

 private:
    SpriteComponent sprite_;
    Type type_;
    sf::Vector2<float> direction_;
};

#endif //STARFLEET_COMMAND_PROJECTILE_HPP
