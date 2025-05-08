#include "Sprites/Starships/StarshipClasses/Dreadnought.hpp"

Dreadnought::Dreadnought(int spacelane)
{
    _spriteComponent.LoadSprite("Resources/Textures/starfleet_ship_3.png");
    _spriteComponent.GetSprite().scale({0.05F, 0.05F});
    _healthComponent.SetHealth(1500);
    _speed = 40;
    _startSpeed = _speed;
    _deployTimeSpeed = 8.0F;
    _maximumDamage = 500;
    _damageScaleFactor = 1.0F;
    _fireRate = 3.0f;
    _attackRange = 800.0F;
    _buildCost = 2000;
    _projectileSize = Projectile::LARGE;
    _projectileColour = Projectile::BLUE;
    _starshipName = "Dreadnought";
    _starshipAbbreviation = "DRN";
    _assignedLaneIndex = spacelane;
    _starshipIndex = 3;

    _healthBar = std::make_unique<HealthBar>(_healthComponent, false);
    _healthBar->SetMaxHealth(_healthComponent.GetHealth());
    _maximumHealth = _healthComponent.GetHealth();

    /// Change default origin to center
    sf::Vector2<float> centered_origin;
    centered_origin.x = _spriteComponent.GetSprite().getLocalBounds().width / 2;
    centered_origin.y = _spriteComponent.GetSprite().getLocalBounds().height / 2;
    _spriteComponent.GetSprite().setOrigin(centered_origin);

    //auto callbackFnc1 = std::bind(&TestClass::TestFncForObserverToCall, testClass);
    //_healthComponent.AddBasicObserver({HealthComponent::HEALTH_DEPLETED, callbackFnc1}); // NOTE: Or handle in Destructor instead of as an event?

    const int SPACELANE_COUNT = 4;
    int minLane = std::max(0, spacelane-2);
    int maxLane = std::min(SPACELANE_COUNT, spacelane+2);
    for (int i = minLane; i <= maxLane; ++i)
    {
        _attackableLanes.emplace_back(i);
    }
}

bool Dreadnought::CanEngageWith(const std::unique_ptr<Starship> &starship)
{
    if(this->GetLaneIndex() == starship->GetLaneIndex() - 2 or
            this->GetLaneIndex() == starship->GetLaneIndex() - 1 or
            this->GetLaneIndex() == starship->GetLaneIndex() or
            this->GetLaneIndex() == starship->GetLaneIndex() + 1 or
            this->GetLaneIndex() == starship->GetLaneIndex() + 2)
    {
        return true;
    }
    return false;
}

/*void Dreadnought::SetAttackRangeVisibility(bool visibility)
{
    _isAttackRangeCircleVisible = visibility;
}*/



















