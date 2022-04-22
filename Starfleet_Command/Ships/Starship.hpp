#ifndef STARFLEET_COMMAND_STARSHIP_HPP
#define STARFLEET_COMMAND_STARSHIP_HPP
#include "Projectile.hpp"
#include "../Components/SpriteComponent.hpp"
#include "../Utility/Vector.hpp"
#include "../GameUI/HealthBar.hpp"
#include <iostream>

class Starship
{
 public:
    enum class Type
    {
        FIGHTER,
        REPAIR,
        SCOUT,
        DESTROYER,
        BATTLESHIP,
        FLAGSHIP
    };
    explicit Starship(Type type);
    ~Starship() = default;
    void Update(sf::RenderWindow& window, sf::Time deltaTime);
    void Render(sf::RenderWindow& window);

    // Functionality
    void MoveTowards(sf::Vector2f target, sf::Time deltaTime);

    /// Modifiers
    void SetHealth(float health);
    void SetDamage(float damage);
    void SetSpeed(float speed); // Entity class?
    void SetAcceleration(float acceleration);
    void SetHealthBarVisibility(bool visible);

    /// Accessors
    SpriteComponent &GetSpriteComponent();
    std::vector<std::unique_ptr<Projectile>>& GetProjectile();
    std::vector<HealthBar>& GetHealthBar() { return _healthBar; };
    float GetHealth() const;
    float GetDamage() const;
    float GetSpeed() const;
    float GetAcceleration() const;
    bool IsHealthBarVisible() const { return _healthBarIsVisible; };

 private:
    std::vector<HealthBar> _healthBar;
    SpriteComponent spriteComponent;
    std::vector<std::unique_ptr<Projectile>> projectile{};
    Type ship_type{};
    float _health = 0.0F;
    float _damage = 0.0F;
    float _speed = 0.0F;
    float _acceleration = 0.0F;
    bool _healthBarIsVisible = false;
    bool _isDead = false;
};

#endif //STARFLEET_COMMAND_STARSHIP_HPP
