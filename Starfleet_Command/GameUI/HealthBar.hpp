#ifndef STARFLEET_COMMAND_HEALTHBAR_HPP
#define STARFLEET_COMMAND_HEALTHBAR_HPP
#include <SFML/Graphics/RenderWindow.hpp>
#include "../Components/SpriteComponent.hpp"

class HealthBar
{
public:
    explicit HealthBar(float health);
    ~HealthBar() = default;
    void Update(sf::RenderWindow &window, sf::Time deltaTime);
    void Render(sf::RenderWindow& window);

    void SetHealth(float health);
    void SetPos(sf::Vector2f pos);

    SpriteComponent& GetSpriteComponent() { return spriteComponent; };
    float GetHealth() const { return _health; };
    sf::Vector2f GetPos() const { return _position; };

private:
    SpriteComponent spriteComponent;
    float _health;
    sf::Vector2f _position;
};

#endif //STARFLEET_COMMAND_HEALTHBAR_HPP
