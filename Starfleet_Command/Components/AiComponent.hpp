#ifndef STARFLEET_COMMAND_AICOMPONENT_HPP
#define STARFLEET_COMMAND_AICOMPONENT_HPP
#include "IComponent.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include "../Utility/Vector.hpp"

class AiComponent : public IComponent
{
public:
    void MoveTowards(sf::Sprite& sprite, sf::Vector2f target, float speed, sf::Time deltaTime);
    //void MoveTowards(sf::Vector2f target, sf::Time deltaTime);
    //void ShootAt(Projectile::Type projectile, float fireRate, sf::Vector2f target);

private:
    void EventHandler(sf::RenderWindow &window, sf::Event &event) override;
    void Update(sf::RenderWindow &window, sf::Time deltaTime) override;
    void Render(sf::RenderWindow &window) override;
    // vector component?
};

#endif //STARFLEET_COMMAND_AICOMPONENT_HPP
