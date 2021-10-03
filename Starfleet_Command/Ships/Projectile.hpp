#ifndef STARFLEET_COMMAND_PROJECTILE_HPP
#define STARFLEET_COMMAND_PROJECTILE_HPP
#include "../Components/SpriteComponent.hpp"
#include <cmath>

class Projectile
{
 public:
    enum class Type;

 public:
    Projectile(Type type, sf::Vector2<float> start_pos, sf::Vector2<float> mouse_pos);
    ~Projectile() = default;

    void update(sf::RenderWindow& window, sf::Time deltaTime);
    void render(sf::RenderWindow& window);

    enum class Type { LASER_BLUE, LASER_RED, MISSILE_BLUE, MISSILE_RED };
    SpriteComponent& getSprite();

 private:
    SpriteComponent sprite_;
    Type type_;
    sf::Vector2<float> click_position_;
    sf::Vector2<float> direction_;
};

#endif //STARFLEET_COMMAND_PROJECTILE_HPP
