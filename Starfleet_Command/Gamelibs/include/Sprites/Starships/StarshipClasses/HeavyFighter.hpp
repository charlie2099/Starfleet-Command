#ifndef STARFLEET_COMMAND_HEAVYFIGHTER_HPP
#define STARFLEET_COMMAND_HEAVYFIGHTER_HPP
#include <SFML/System/Vector2.hpp>
#include "Interfaces/IStarship.hpp"
#include "Sprites/UI/HealthBar.hpp"
#include "Utility/Vector.hpp"

class HeavyFighter : public IStarship
{
public:
    HeavyFighter();
    ~HeavyFighter() override = default;

    void Update(sf::RenderWindow& window, sf::Time deltaTime) override;
    void Render(sf::RenderWindow& window) override;

    /// Behaviours
    void MoveTowards(sf::Vector2f target, sf::Time deltaTime) override;
    void ShootAt(Projectile::Type projectile, float fireRate, sf::Vector2f target) override;

    /// Modifiers
    void SetHealth(float health) override;
    void SetHealthBarVisibility(bool visible) override;
    void SetDamage(float damage) override;
    void SetSpeed(float speed) override;
    void SetAcceleration(float acceleration) override;

    /// Accessors
    SpriteComponent& GetSpriteComponent() override { return _spriteComponent; };
    HealthComponent& GetHealthComponent() override { return _healthComponent; };
    std::unique_ptr<HealthBar>& GetHealthBar() override { return _healthBar; };
    std::vector<std::unique_ptr<Projectile>>& GetProjectile() override { return _projectile; };
    Projectile::Type& GetProjectileType() override { return _projectileType; };
    std::string& GetShipName() override { return _shipName; };
    float GetHealth() override { return _healthComponent.GetHealth(); };
    float GetMaxHealth() override { return _maxHealth; };
    float GetDamage() override { return _damage; };
    float GetDamageScaleFactor() override { return _damageScaleFactor; };
    float GetSpeed() override { return _speed; };
    float GetTrainingSpeed() override { return _trainingSpeed; };
    float GetFireRate() override { return _fireRate; };
    float GetAcceleration() override { return _acceleration; };
    float GetShipCost() override { return _shipCost; };
    bool IsHealthBarVisible() override { return _healthBarIsVisible; };
};

#endif //STARFLEET_COMMAND_HEAVYFIGHTER_HPP
