#ifndef STARFLEET_COMMAND_ISTARSHIP_HPP
#define STARFLEET_COMMAND_ISTARSHIP_HPP
#include "Components/SpriteComponent.hpp"
#include "Components/HealthComponent.hpp"
#include "Sprites/Projectiles/Projectile.hpp"
#include "Sprites/UI/HealthBar.hpp"

/*
 * Interface that all ships should inherit from
 */
class IStarship
{
public:
    virtual ~IStarship() = default;

    virtual void Update(sf::RenderWindow& window, sf::Time deltaTime) = 0;
    virtual void Render(sf::RenderWindow& window) = 0;

    /// Behaviours
    virtual void MoveTowards(sf::Vector2f target, sf::Time deltaTime) = 0;
    virtual void ShootAt(Projectile::Type projectile, float fireRate, sf::Vector2f target) = 0;

    /// Modifiers
    virtual void SetHealth(float health) = 0;
    virtual void SetHealthBarVisibility(bool visible) = 0;
    virtual void SetDamage(float damage) = 0;
    virtual void SetSpeed(float speed) = 0;
    virtual void SetAcceleration(float acceleration) = 0;
    virtual void SetAttackRange(float range) = 0;
    virtual void SetColour(sf::Color& colour) = 0;
    virtual void SetPosition(sf::Vector2f  pos) = 0;
    virtual void SetRotation(float rot) = 0;

    /// Accessors
    virtual SpriteComponent& GetSpriteComponent() = 0;
    virtual HealthComponent& GetHealthComponent() = 0;
    virtual std::unique_ptr<HealthBar>& GetHealthBar() = 0;
    virtual std::vector<std::unique_ptr<Projectile>>& GetProjectile() = 0;
    virtual Projectile::Type& GetProjectileType() = 0;
    virtual std::string& GetShipName() = 0;
    virtual sf::Color& GetColour() = 0;
    virtual sf::Vector2<float> GetPos() = 0;
    virtual float GetRotation() = 0;
    virtual float GetHealth() = 0;
    virtual float GetMaxHealth() = 0;
    virtual float GetDamage() = 0;
    virtual float GetDamageScaleFactor() = 0;
    virtual float GetSpeed() = 0;
    virtual float GetTrainingSpeed() = 0;
    virtual float GetFireRate() = 0;
    virtual float GetAcceleration() = 0;
    virtual float GetAttackRange() = 0;
    virtual float GetShipCost() = 0;
    virtual bool IsHealthBarVisible() = 0;

protected:
    SpriteComponent _spriteComponent;
    HealthComponent _healthComponent;
    std::unique_ptr<HealthBar> _healthBar;
    std::vector<std::unique_ptr<Projectile>> _projectile;
    Projectile::Type _projectileType;
    std::string _shipName;
    sf::Color _shipColour;
    float _rotation;
    float _maxHealth;
    float _damage;
    float _damageScaleFactor = 1.0F;
    float _speed = 1.0F;
    float _trainingSpeed = 0.5f;
    float _fireRate = 1.0F;
    float _acceleration = 0.0F;
    float _attackRange = 400.0F;
    float _shipCost = 100;
    bool _healthBarIsVisible = false;
    float _nextFireTime = 0;
    sf::Clock _clock;
};

#endif //STARFLEET_COMMAND_ISTARSHIP_HPP
