#include "Sprites/Starships/StarshipClasses/Battleship.hpp"

Battleship::Battleship(int spacelane)
{
    _spriteComponent.LoadSprite("Resources/Textures/starfleet_ship_4.png");
    _spriteComponent.GetSprite().scale({0.05F, 0.05F});
    _healthComponent.SetHealth(2500);
    _speed = 30;
    _startSpeed = _speed;
    _deployTimeSpeed = 5.0F;
    _maximumDamage = 100;
    _damageScaleFactor = 1.0F;
    _fireRate = 3.0f;
    _attackRange = 600.0F;
    _buildCost = 3000;
    _projectileSize = Projectile::LARGE;
    _projectileColour = Projectile::BLUE;
    _starshipName = "Battleship";
    _starshipAbbreviation = "BS";
    _assignedLaneIndex = spacelane;
    _starshipIndex = 4;

    _healthBar = std::make_unique<HealthBar>(_healthComponent, false);
    _healthBar->SetMaxHealth(_healthComponent.GetHealth());
    _maximumHealth = _healthComponent.GetHealth();

    /// Change default origin to center
    sf::Vector2<float> centered_origin;
    centered_origin.x = _spriteComponent.GetSprite().getLocalBounds().width / 2;
    centered_origin.y = _spriteComponent.GetSprite().getLocalBounds().height / 2;
    _spriteComponent.GetSprite().setOrigin(centered_origin);

    //auto callbackFnc1 = std::bind(&TestClass::TestFncForObserverToCall, testClass);
    //_healthComponent.AddBasicObserver({HealthComponent::HEALTH_DEPLETED, callbackFnc1});

    const int SPACELANE_COUNT = 4;
    int minLane = std::max(0, spacelane-1);
    int maxLane = std::min(SPACELANE_COUNT, spacelane+1);
    for (int i = minLane; i <= maxLane; ++i)
    {
        _attackableLanes.emplace_back(i);
    }
}

bool Battleship::CanEngageWith(const std::unique_ptr<Starship> &starship)
{
    if(this->GetLaneIndex() == starship->GetLaneIndex() - 1 or
            this->GetLaneIndex() == starship->GetLaneIndex() or
            this->GetLaneIndex() == starship->GetLaneIndex() + 1)
    {
        return true;
    }
    return false;
}
