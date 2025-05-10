#include "Sprites/Starships/StarshipClasses/SupportFrigate.hpp"

SupportFrigate::SupportFrigate(int spawnSpacelane, const std::string& starshipTypeName) : Starship(spawnSpacelane, starshipTypeName)
{
    _spriteComponent.LoadSprite("Resources/Textures/starfleet_ship_2.png");
    _spriteComponent.GetSprite().scale({0.05F, 0.05F});
    _projectileSize = Projectile::SMALL;
    _projectileColour = Projectile::BLUE;
    _assignedLaneIndex = spawnSpacelane;
    _starshipIndex = 2;

    /// Change default origin to center
    sf::Vector2<float> centered_origin;
    centered_origin.x = _spriteComponent.GetSprite().getLocalBounds().width / 2;
    centered_origin.y = _spriteComponent.GetSprite().getLocalBounds().height / 2;
    _spriteComponent.GetSprite().setOrigin(centered_origin);

    //auto callbackFnc1 = std::bind(&TestClass::TestFncForObserverToCall, testClass);
    //_healthComponent.AddBasicObserver({HealthComponent::HEALTH_DEPLETED, callbackFnc1});
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


















