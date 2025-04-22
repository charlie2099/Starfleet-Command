#ifndef STARFLEET_COMMAND_ISTARSHIP_HPP
#define STARFLEET_COMMAND_ISTARSHIP_HPP
#include "Components/SpriteComponent.hpp"
#include "Components/HealthComponent.hpp"
#include "Sprites/Projectiles/Projectile.hpp"
#include "Sprites/UI/HealthBar.hpp"
#include "Utility/Constants.hpp"
#include "Utility/PredefinedColours.hpp"

/*
 * Interface that all starships should inherit from
 */
class IStarship // TODO: Make functions that are virtual but don't have different implementations non-virtual
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
    virtual bool IsEnemyInRange(const std::unique_ptr<IStarship> &starship) = 0;
    virtual bool IsFriendlyStarshipAhead(const std::unique_ptr<IStarship> &starship) = 0;
    virtual bool IsEnemyStarshipAhead(const std::unique_ptr<IStarship> &starship) = 0;
    bool IsInSameLaneAs(const std::unique_ptr<IStarship> &starship) { return this->GetLaneIndex() == starship->GetLaneIndex(); }
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
        if(colour == sf::Color::Cyan or colour == sf::Color::Blue or colour == Chilli::PredefinedColours::LIGHTBLUE or colour == Chilli::PredefinedColours::BLUEVIOLET)
        {
            _projectileColour = Projectile::BLUE;
        }
        else if(colour == sf::Color::Green or colour == Chilli::PredefinedColours::LIGHTGREEN)
        {
            _projectileColour = Projectile::GREEN;
        }
        else if(colour == sf::Color::Red or colour == Chilli::PredefinedColours::LIGHTRED)
        {
            _projectileColour = Projectile::RED;
        }
        else if(colour == Chilli::PredefinedColours::ORANGE or colour == Chilli::PredefinedColours::LIGHTORANGE)
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
    virtual std::string& GetStarshipAbbreviation() = 0;
    virtual sf::Color& GetColour() = 0;
    virtual sf::Vector2<float> GetPos() = 0;
    virtual float GetRotation() = 0;
    virtual float GetHealth() = 0;
    virtual float GetMaxHealth() = 0;
    virtual float GetMaxDamage() = 0;
    virtual float GetDamageScaleFactor() = 0;
    virtual float GetSpeed() = 0;
    float GetStartingSpeed() const { return _startSpeed; }
    virtual float GetDeploymentTime() = 0;
    virtual float GetFireRate() = 0;
    virtual float GetAcceleration() = 0;
    virtual float GetAttackRange() = 0;
    virtual int GetBuildCost() = 0;
    virtual int GetLaneIndex() = 0;
    virtual std::vector<int> GetAttackableLanes() = 0;
    virtual int GetStarshipIndex() = 0;

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

#endif //STARFLEET_COMMAND_ISTARSHIP_HPP
