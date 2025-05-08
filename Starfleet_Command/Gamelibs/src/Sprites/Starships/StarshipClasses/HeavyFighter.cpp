#include "Sprites/Starships/StarshipClasses/HeavyFighter.hpp"

HeavyFighter::HeavyFighter(int spacelane)
{
    _spriteComponent.LoadSprite("Resources/Textures/starfleet_ship_1.png");
    _spriteComponent.GetSprite().scale({0.05F, 0.05F});
    _healthComponent.SetHealth(300);
    _speed = 80;
    _startSpeed = _speed;
    _deployTimeSpeed = 3.0F;
    _maximumDamage = 20;
    _damageScaleFactor = 1.0F;
    _fireRate = 0.25f;
    _attackRange = 300.0F;
    _buildCost = 250;
    _projectileSize = Projectile::REGULAR;
    _projectileColour = Projectile::BLUE;
    _starshipName = "Heavy Fighter";
    _starshipAbbreviation = "HF";
    _assignedLaneIndex = spacelane;
    _starshipIndex = 1;

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

bool HeavyFighter::CanEngageWith(const std::unique_ptr<Starship> &starship)
{
    return this->GetLaneIndex() == starship->GetLaneIndex();
}










