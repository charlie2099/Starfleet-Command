#include "Sprites/Starships/StarshipClasses/LightFighter.hpp"

LightFighter::LightFighter(int spacelane)
{
    _spriteComponent.LoadSprite("Resources/Textures/starfleet_ship_0.png");
    _spriteComponent.GetSprite().scale({0.05F, 0.05F});
    _healthComponent.SetHealth(150);
    _speed = 160;
    _startSpeed = _speed;
    _deployTimeSpeed = 2.0F;
    _maximumDamage = 25;
    _damageScaleFactor = 1.0F;
    _fireRate = 0.5f;
    _attackRange = 400.0F;
    _buildCost = 50;
    _projectileSize = Projectile::SMALL;
    _projectileColour = Projectile::BLUE;
    _starshipName = "Light Fighter";
    _starshipAbbreviation = "LF";
    _assignedLaneIndex = spacelane;
    _starshipIndex = 0;

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

    _attackableLanes.emplace_back(spacelane);
}

bool LightFighter::CanEngageWith(const std::unique_ptr<Starship> &starship)
{
    return this->GetLaneIndex() == starship->GetLaneIndex();
}

