#ifndef STARFLEET_COMMAND_OLDSTARSHIP_HPP
#define STARFLEET_COMMAND_OLDSTARSHIP_HPP
#include "Sprites/Projectiles/Projectile.hpp"
#include "Components/SpriteComponent.hpp"
#include "Utility/Vector.hpp"
#include "Sprites/UI/HealthBar.hpp"
#include "Sprites/UI/Effects/DamagePopUpEffect.hpp"
#include <iostream>

class OLDStarship
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
    explicit OLDStarship(Type type);
    ~OLDStarship() = default;
    void Update(sf::RenderWindow& window, sf::Time deltaTime);
    void Render(sf::RenderWindow& window);

    // Functionality
    void MoveTowards(sf::Vector2f target, sf::Time deltaTime);
    void ShootAt(Projectile::Type projectile, float fireRate, sf::Vector2f target);
    //void TakeDamage(float damage);

    /// Modifiers
    void SetHealth(float health);
    void SetDamage(float damage);
    void SetSpeed(float speed); // Entity class?
    void SetAcceleration(float acceleration);
    void SetHealthBarVisibility(bool visible);

    /// Accessors
    SpriteComponent &GetSpriteComponent() { return _spriteComponent; };
    HealthComponent &GetHealthComponent() { return _healthComponent; };
    std::vector<std::unique_ptr<Projectile>>& GetProjectile() { return _projectile; };
    Projectile::Type& GetProjectileType() { return _projectileType; };
    std::unique_ptr<HealthBar>& GetHealthBar() { return _healthBar; };
    float GetHealth() const { return _healthComponent.GetHealth(); };
    float GetDamage() const { return _damage; };
    float GetDamageScaleFactor() const { return _damageScaleFactor; };
    float GetSpeed() const { return _speed; };
    float GetTrainingSpeed() const { return _trainingSpeed; };
    float GetFireRate() const { return _fireRate; };
    float GetAcceleration() const { return _acceleration; };
    float GetShipCost() const { return _shipCost; };
    bool IsHealthBarVisible() const { return _healthBarIsVisible; };

 private:
    HealthComponent _healthComponent;
    std::unique_ptr<HealthBar> _healthBar;
    SpriteComponent _spriteComponent;
    Type ship_type{};
    std::vector<std::unique_ptr<Projectile>> _projectile;
    Projectile::Type _projectileType;
    float _damage = 10.0F;
    float _damageScaleFactor = 1.0F;
    float _speed = 1.0F;
    float _trainingSpeed = 0.5f;
    float _fireRate = 1.0F;
    float _acceleration = 0.0F;
    float _shipCost = 100;
    bool _healthBarIsVisible = false;

    float _maxHealth;
    float timePassed = 0;
    sf::Clock clock;
};

#endif //STARFLEET_COMMAND_OLDSTARSHIP_HPP
