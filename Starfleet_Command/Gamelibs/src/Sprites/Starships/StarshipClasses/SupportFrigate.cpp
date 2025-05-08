#include "Sprites/Starships/StarshipClasses/SupportFrigate.hpp"

SupportFrigate::SupportFrigate(int spacelane)
{
    _spriteComponent.LoadSprite("Resources/Textures/starfleet_ship_2.png");
    _spriteComponent.GetSprite().scale({0.05F, 0.05F});
    _healthComponent.SetHealth(500);
    _speed = 70;
    _startSpeed = _speed;
    _deployTimeSpeed = 3.0F;
    _maximumDamage = 30;
    _damageScaleFactor = 1.0F;
    _fireRate = 2.0f;
    _attackRange = 400.0F;
    _buildCost = 500;
    _projectileSize = Projectile::SMALL;
    _projectileColour = Projectile::BLUE;
    _starshipName = "Support Frigate";
    _starshipAbbreviation = "SF";
    _assignedLaneIndex = spacelane;
    _starshipIndex = 2;

    _healthBar = std::make_unique<HealthBar>(_healthComponent , false);
    _healthBar->SetMaxHealth(_healthComponent.GetHealth());
    _maximumHealth = _healthComponent.GetHealth();

    /// Change default origin to center
    sf::Vector2<float> centered_origin;
    centered_origin.x = _spriteComponent.GetSprite().getLocalBounds().width / 2;
    centered_origin.y = _spriteComponent.GetSprite().getLocalBounds().height / 2;
    _spriteComponent.GetSprite().setOrigin(centered_origin);

    //auto callbackFnc1 = std::bind(&TestClass::TestFncForObserverToCall, testClass);
    //_healthComponent.AddBasicObserver({HealthComponent::HEALTH_DEPLETED, callbackFnc1});

    _attackableLanes.emplace_back(spacelane);
}

bool SupportFrigate::CanEngageWith(const std::unique_ptr<Starship> &starship)
{
    return this->GetLaneIndex() == starship->GetLaneIndex();
}

void SupportFrigate::ShootHealAt(const std::unique_ptr<Starship> &friendlyStarship)
{
    if(_healingProjectileSpawnTimer < _healingProjectileSpawnTimerClock.getElapsedTime().asSeconds())
    {
        _healingProjectileSpawnTimer = _healingProjectileSpawnTimerClock.getElapsedTime().asSeconds();
    }

    if(_healingProjectileSpawnTimerClock.getElapsedTime().asSeconds() >= _healingProjectileSpawnTimer)
    {
        auto spawnPos = _spriteComponent.GetPos();
        _projectile.emplace_back(std::make_unique<Projectile>(_projectileSize, Projectile::Colour::GREEN, spawnPos, friendlyStarship->GetPos()));
        _healingProjectileSpawnTimer += (_fireRate/2.0F);
    }
}


















