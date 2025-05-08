#include "Sprites/Starships/StarshipClasses/Mothership.hpp"

Mothership::Mothership(int spacelane)
{
    _spriteComponent.LoadSprite("Resources/Textures/starfleet_ship_5.png");
    _spriteComponent.GetSprite().scale({0.5F, 0.5F});
    _healthComponent.SetHealth(10000);
    _speed = 10;
    _startSpeed = _speed;
    _maximumDamage = 50;
    _fireRate = 1.0f;
    _attackRange = 400.0F;
    _projectileSize = Projectile::LARGE;
    _projectileColour = Projectile::BLUE;
    _starshipName = "Mothership";
    _starshipAbbreviation = "MS";
    _assignedLaneIndex = spacelane;
    _starshipIndex = 5;

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

    _attackableLanes.emplace_back(0);
    _attackableLanes.emplace_back(1);
    _attackableLanes.emplace_back(2);
    _attackableLanes.emplace_back(3);
    _attackableLanes.emplace_back(4);
}

void Mothership::Update(sf::RenderWindow &window, sf::Time deltaTime)
{
    Starship::Update(window, deltaTime);

    if(_isDamaged)
    {
        _damageTimer -= deltaTime.asSeconds();

        if(_damageTimer <= 0.0F)
        {
            _spriteComponent.GetSprite().setColor(_starshipColour);
            _isDamaged = false;
        }
    }
}

bool Mothership::CanEngageWith(const std::unique_ptr<Starship> &starship)
{
    return this->GetLaneIndex() == starship->GetLaneIndex();
}

void Mothership::TakeDamage(float damageAmount)
{
    _healthComponent.TakeDamage(damageAmount, _damageLocation);
    _spriteComponent.GetSprite().setColor(sf::Color::Red);
    _isDamaged = true;
    _damageTimer = 0.05F;
}
