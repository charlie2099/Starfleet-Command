#ifndef STARFLEET_COMMAND_ISTARSHIP_HPP
#define STARFLEET_COMMAND_ISTARSHIP_HPP
#include "Components/SpriteComponent.hpp"
#include "Components/HealthComponent.hpp"
#include "Sprites/Projectiles/Projectile.hpp"
#include "Sprites/UI/HealthBar.hpp"
#include "Utility/PredefinedColours.hpp"
#include "Utility/Constants.hpp"

/*
 * Interface that all starships should inherit from
 */
class IStarship
{
public:
    virtual ~IStarship() = default;

    /// General
    virtual void EventHandler(sf::RenderWindow& window, sf::Event& event) = 0;
    virtual void Update(sf::RenderWindow& window, sf::Time deltaTime) = 0;
    virtual void Render(sf::RenderWindow& window) = 0;

    /// Behaviours
    virtual void Move(float xOffset, float yOffset) = 0;
    virtual void ShootAt(sf::Vector2f target) = 0;
    virtual void DestroyProjectile(int projectileIndex) = 0;
    virtual void TakeDamage(float damageAmount) = 0;
    virtual void ReplenishHealth(float healthAmount) = 0;
    virtual bool IsProjectileOutOfRange(int projectileIndex) = 0;
    virtual bool IsStarshipInRange(const std::unique_ptr<IStarship> &starship) = 0;
    virtual bool CanEngageWith(const std::unique_ptr<IStarship> &starship)  = 0;
    virtual bool CollidesWith(sf::Rect<float> spriteBounds) = 0;
    virtual bool IsHealthBarVisible() = 0;
    virtual bool IsMouseOver() = 0;

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
    void SetProjectileColour(sf::Color colour)
    {
        if(colour == sf::Color::Cyan || colour == sf::Color::Blue || colour == _predefinedColours.LIGHTBLUE || colour == _predefinedColours.BLUEVIOLET)
        {
            _projectileColour = Projectile::BLUE;
        }
        else if(colour == sf::Color::Green || colour == _predefinedColours.LIGHTGREEN)
        {
            _projectileColour = Projectile::GREEN;
        }
        else if(colour == sf::Color::Red || colour == _predefinedColours.LIGHTRED)
        {
            _projectileColour = Projectile::RED;
        }
        else if(colour == _predefinedColours.ORANGE || colour == _predefinedColours.LIGHTORANGE)
        {
            _projectileColour = Projectile::ORANGE;
        }
        else
        {
            std::cout << "WARNING: Could not locate projectile of the desired colour. Defaulting to WHITE. (" + _starshipName + ")" << std::endl;
            _projectileColour = Projectile::WHITE;
        }
    };

    /// Accessors
    virtual SpriteComponent& GetSpriteComponent() = 0;
    virtual HealthComponent& GetHealthComponent() = 0;
    virtual std::unique_ptr<HealthBar>& GetHealthBar() = 0;
    virtual std::vector<std::unique_ptr<Projectile>>& GetProjectile() = 0;
    virtual Projectile::Size GetProjectileSize() = 0;
    virtual Projectile::Colour GetProjectileColour() = 0;
    virtual int GetProjectileCount() = 0;
    virtual std::string& GetStarshipName() = 0;
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
    virtual int GetBuildCost() = 0;
    virtual int GetLaneIndex() = 0;
    virtual std::vector<int> GetAttackableLanes() = 0;

protected:
    SpriteComponent _spriteComponent;
    HealthComponent _healthComponent;
    std::unique_ptr<HealthBar> _healthBar;
    std::vector<std::unique_ptr<Projectile>> _projectile;
    Projectile::Size _projectileSize;
    Projectile::Colour _projectileColour;
    std::string _starshipName;
    sf::Color _starshipColour;
    float _rotation;
    float _maxHealth;
    float _damage;
    float _damageScaleFactor = 1.0F;
    float _speed = 1.0F;
    float _trainingSpeed = 0.5f;
    float _fireRate = 1.0F;
    float _acceleration = 0.0F;
    float _attackRange = 400.0F;
    int _buildCost = 100;
    sf::CircleShape _attackRangeCircle;
    bool _isAttackRangeCircleVisible = false;
    bool _isHealthBarVisible = false;
    float _damagingProjectileSpawnTimer = 0;
    sf::Clock _damagingProjectileSpawnTimerClock;
    Chilli::PredefinedColours _predefinedColours;
    int _assignedLaneIndex;
    bool _isMouseOver = false;
    std::vector<int> _attackableLanes;
};

#endif //STARFLEET_COMMAND_ISTARSHIP_HPP
