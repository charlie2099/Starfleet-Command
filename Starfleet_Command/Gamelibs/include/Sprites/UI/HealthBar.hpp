#ifndef STARFLEET_COMMAND_HEALTHBAR_HPP
#define STARFLEET_COMMAND_HEALTHBAR_HPP
#include "Components/SpriteComponent.hpp"
#include "Components/HealthComponent.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>

class HealthBar
{
public:
    explicit HealthBar(HealthComponent& healthComponent);
    ~HealthBar() = default;
    void Update(sf::RenderWindow& window, sf::Time deltaTime);
    void Render(sf::RenderWindow& window);

    void SetPos(sf::Vector2f pos);
    void SetMaxHealth(float health);
    void UpdateHealth(std::any eventData);

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
