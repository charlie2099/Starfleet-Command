#ifndef STARFLEET_COMMAND_HEALTHBAR_HPP
#define STARFLEET_COMMAND_HEALTHBAR_HPP
#include "Components/SpriteComponent.hpp"
#include "Components/HealthComponent.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>

class HealthBar
{
public:
    /// General
    HealthBar(HealthComponent& healthComponent, bool isRotated);
    ~HealthBar() = default;
    void Update(sf::RenderWindow& window, sf::Time deltaTime);
    void Render(sf::RenderWindow& window);

    /// Modifiers
    void SetPos(sf::Vector2f pos);
    void SetRot(float rot);
    void SetScale(float xScale, float yScale);
    void SetMaxHealth(float health);

    /// Accessors
    SpriteComponent& GetSpriteComponent() { return _healthBar; }
    float GetHealth() const { return _health; }
    sf::Vector2f GetPos() const { return _position; }

private:
    void UpdateHealth(std::any eventData);
    SpriteComponent _healthBar;
    SpriteComponent _healthBarMask;
    float _maxHealth = 100;
    float _health = _maxHealth;
    sf::Vector2f _position;
    float _rotation{};
    sf::Vector2f  _scale;
};

#endif //STARFLEET_COMMAND_HEALTHBAR_HPP
