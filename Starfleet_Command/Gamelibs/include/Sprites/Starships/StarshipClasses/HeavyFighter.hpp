#ifndef STARFLEET_COMMAND_HEAVYFIGHTER_HPP
#define STARFLEET_COMMAND_HEAVYFIGHTER_HPP
#include <SFML/System/Vector2.hpp>
#include "Interfaces/IStarship.hpp"
#include "Sprites/UI/HealthBar.hpp"
#include "Utility/Vector.hpp"

class HeavyFighter : public IStarship
{
public:
    explicit HeavyFighter(int spacelane);
    ~HeavyFighter() override = default;

    /// General
    void EventHandler(sf::RenderWindow &window, sf::Event &event) override;
    void Update(sf::RenderWindow& window, sf::Time deltaTime) override;
    void Render(sf::RenderWindow& window) override;

    /// Behaviours
    void Move(float xOffset, float yOffset) override;
    void ShootAt(sf::Vector2f target) override;
    void DestroyProjectile(int projectileIndex) override;
    void TakeDamage(float damageAmount) override;
    void ReplenishHealth(float healthAmount) override;
    bool IsEnemyInRange(const std::unique_ptr<IStarship> &starship) override;
    bool IsFriendlyStarshipAhead(const std::unique_ptr<IStarship> &starship) override;
    bool IsEnemyStarshipAhead(const std::unique_ptr<IStarship> &starship) override;
    bool CollidesWith(sf::Rect<float> spriteBounds) override;
    bool CanEngageWith(const std::unique_ptr<IStarship> &starship) override;
    bool IsHealthBarVisible() override { return _isHealthBarVisible; }
    bool IsMouseOver() override { return _isMouseOver; };

    /// Modifiers
    void SetHealth(float health) override;
    void SetHealthBarVisibility(bool visible) override;
    void SetDamage(float damage) override;
    void SetSpeed(float speed) override;
    void SetAcceleration(float acceleration) override;
    void SetAttackRange(float range) override;
    void SetColour(sf::Color &colour) override;
    void SetPosition(sf::Vector2f pos) override;
    void SetRotation(float rot) override;

    /// Accessors
    SpriteComponent& GetSpriteComponent() override { return _spriteComponent; }
    HealthComponent& GetHealthComponent() override { return _healthComponent; }
    std::unique_ptr<HealthBar>& GetHealthBar() override { return _healthBar; }
    std::vector<std::unique_ptr<Projectile>>& GetProjectile() override { return _projectile; }
    int GetProjectileCount() override { return _projectile.size(); }
    Projectile::Size GetProjectileSize() override { return _projectileSize; }
    Projectile::Colour GetProjectileColour() override { return _projectileColour; }
    std::string& GetStarshipName() override { return _starshipName; }
    std::string& GetStarshipAbbreviation() override { return _starshipAbbreviation; }
    sf::Color &GetColour() override { return _starshipColour; }
    sf::Vector2<float> GetPos() override { return _spriteComponent.GetPos(); }
    float GetRotation() override { return _rotation; }
    float GetHealth() override { return _healthComponent.GetHealth(); }
    float GetMaxHealth() override { return _maximumHealth; }
    float GetMaxDamage() override { return _maximumDamage; }
    float GetDamageScaleFactor() override { return _damageScaleFactor; }
    float GetSpeed() override { return _speed; }
    float GetDeploymentTime() override { return _deployTimeSpeed; }
    float GetFireRate() override { return _fireRate; }
    float GetAcceleration() override { return _acceleration; }
    float GetAttackRange() override { return _attackRange; }
    int GetBuildCost() override { return _buildCost; }
    int GetLaneIndex() override { return _assignedLaneIndex; }
    std::vector<int> GetAttackableLanes() override { return _attackableLanes; }
    int GetStarshipIndex() override { return _starshipIndex; }
};

#endif //STARFLEET_COMMAND_HEAVYFIGHTER_HPP
