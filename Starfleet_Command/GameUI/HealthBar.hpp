#ifndef STARFLEET_COMMAND_HEALTHBAR_HPP
#define STARFLEET_COMMAND_HEALTHBAR_HPP
#include <SFML/Graphics/RenderWindow.hpp>
#include "../Components/SpriteComponent.hpp"
#include <iostream>

class HealthBar
{
public:
    HealthBar();
    ~HealthBar() = default;
    void Update();
    void Render(sf::RenderWindow& window);

    void SetPos(sf::Vector2f pos);
    void SetMaxHealth(float health);
    void UpdateHealth(float health);

    SpriteComponent& GetSpriteComponent() { return spriteComponent; };
    float GetHealth() const { return _health; };
    sf::Vector2f GetPos() const { return _position; };

private:
    SpriteComponent spriteComponent;
    SpriteComponent spriteComponent2;
    float _maxHealth = 100;
    float _health = _maxHealth;
    sf::Vector2f _position;
};

#endif //STARFLEET_COMMAND_HEALTHBAR_HPP
