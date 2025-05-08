#ifndef STARFLEET_COMMAND_STARSHIP_HPP
#define STARFLEET_COMMAND_STARSHIP_HPP
#include "Components/SpriteComponent.hpp"
#include "Components/HealthComponent.hpp"
#include "Sprites/Projectiles/Projectile.hpp"
#include "Sprites/UI/HealthBar.hpp"
#include "Utility/Constants.hpp"
#include "Utility/Colour.hpp"
#include "Utility/Vector.hpp"

/**
 * Base class for all starships
 */
class Starship
{
public:
    virtual ~Starship() = default;

    virtual void EventHandler(sf::RenderWindow& window, sf::Event& event);
    virtual void Update(sf::RenderWindow& window, sf::Time deltaTime);
    virtual void Render(sf::RenderWindow& window);

    /// Behaviours
    virtual void Move(float xOffset, float yOffset);
    virtual void ShootAt(sf::Vector2f target);
    virtual void DestroyProjectile(int projectileIndex);
    virtual void TakeDamage(float damageAmount);
    virtual void ReplenishHealth(float healthAmount);
    virtual bool IsEnemyInRange(const std::unique_ptr<Starship> &starship);
    virtual bool IsFriendlyStarshipAhead(const std::unique_ptr<Starship> &starship);
    virtual bool IsEnemyStarshipAhead(const std::unique_ptr<Starship> &enemyStarship);
    bool IsInSameLaneAs(const std::unique_ptr<Starship> &starship) { return this->GetLaneIndex() == starship->GetLaneIndex(); }
    virtual bool CanEngageWith(const std::unique_ptr<Starship> &starship)  = 0;
    virtual bool CollidesWith(sf::Rect<float> spriteBounds);
    bool IsHealthBarVisible() const { return _isHealthBarVisible; }
    bool IsMouseOver() const { return _isMouseOver; };

    /// Modifiers
    virtual void SetHealth(float health);
    virtual void SetHealthBarVisibility(bool visible);
    virtual void SetDamage(float damage);
    virtual void SetSpeed(float speed);
    virtual void SetAcceleration(float acceleration);
    virtual void SetAttackRange(float range);
    virtual void SetColour(sf::Color& colour);
    virtual void SetPosition(sf::Vector2f  pos);
    virtual void SetRotation(float rot);
    void SetProjectileColour(sf::Color colour);

    /// Accessors
    virtual SpriteComponent& GetSpriteComponent() { return _spriteComponent; }
    virtual HealthComponent& GetHealthComponent() { return _healthComponent; }
    virtual std::unique_ptr<HealthBar>& GetHealthBar() { return _healthBar; }
    virtual std::vector<std::unique_ptr<Projectile>>& GetProjectile() { return _projectile; }
    virtual Projectile::Size GetProjectileSize() { return _projectileSize; }
    virtual Projectile::Colour GetProjectileColour() { return _projectileColour; }
    virtual int GetProjectileCount() { return _projectile.size(); }
    virtual std::string& GetStarshipName() { return _starshipName; }
    virtual std::string& GetStarshipAbbreviation() { return _starshipAbbreviation; }
    virtual sf::Color& GetColour() { return _starshipColour; }
    virtual sf::Vector2<float> GetPos() { return _spriteComponent.GetPos(); }
    virtual float GetRotation() { return _rotation; }
    virtual float GetHealth() { return _healthComponent.GetHealth(); }
    virtual float GetMaxHealth() { return _maximumHealth; }
    virtual float GetMaxDamage() { return _maximumDamage; }
    virtual float GetDamageScaleFactor() { return _damageScaleFactor; }
    virtual float GetSpeed() { return _speed; }
    float GetStartingSpeed() const { return _startSpeed; }
    virtual float GetDeploymentTime() { return _deployTimeSpeed; }
    virtual float GetFireRate() { return _fireRate; }
    virtual float GetAcceleration() { return _acceleration; }
    virtual float GetAttackRange() { return _attackRange; }
    virtual int GetBuildCost() { return _buildCost; }
    virtual int GetLaneIndex() { return _assignedLaneIndex; }
    virtual std::vector<int> GetAttackableLanes() { return _attackableLanes; }
    virtual int GetStarshipIndex() { return _starshipIndex; }

protected:
    SpriteComponent _spriteComponent;
    HealthComponent _healthComponent;
    std::unique_ptr<HealthBar> _healthBar;
    std::vector<std::unique_ptr<Projectile>> _projectile;
    Projectile::Size _projectileSize;
    Projectile::Colour _projectileColour;
    std::string _starshipName;
    std::string _starshipAbbreviation;
    sf::Color _starshipColour;
    float _rotation;
    float _maximumHealth;
    float _maximumDamage;
    float _damageScaleFactor = 1.0F;
    float _speed = 1.0F;
    float _startSpeed = 1.0F;
    float _deployTimeSpeed = 3.0F;
    float _fireRate = 1.0F;
    float _acceleration = 0.0F;
    float _attackRange = 400.0F;
    int _buildCost = 100;
    bool _isHealthBarVisible = false;
    float _damagingProjectileSpawnTimer = 0;
    sf::Clock _damagingProjectileSpawnTimerClock;
    int _assignedLaneIndex;
    bool _isMouseOver = false;
    std::vector<int> _attackableLanes;
    int _starshipIndex;
};

#endif //STARFLEET_COMMAND_STARSHIP_HPP
