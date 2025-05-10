#include "Sprites/Starships/StarshipClasses/Mothership.hpp"

Mothership::Mothership(int spawnSpacelane, const std::string& starshipTypeName) : Starship(spawnSpacelane, starshipTypeName)
{
    _spriteComponent.LoadSprite("Resources/Textures/starfleet_ship_5.png");
    _spriteComponent.GetSprite().scale({0.5F, 0.5F});
    _projectileSize = Projectile::LARGE;
    _projectileColour = Projectile::BLUE;
    _assignedLaneIndex = spawnSpacelane;
    _starshipIndex = 5;

    /// Change default origin to center
    sf::Vector2<float> centered_origin;
    centered_origin.x = _spriteComponent.GetSprite().getLocalBounds().width / 2;
    centered_origin.y = _spriteComponent.GetSprite().getLocalBounds().height / 2;
    _spriteComponent.GetSprite().setOrigin(centered_origin);

    //auto callbackFnc1 = std::bind(&TestClass::TestFncForObserverToCall, testClass);
    //_healthComponent.AddBasicObserver({HealthComponent::HEALTH_DEPLETED, callbackFnc1});
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

void Mothership::TakeDamage(float damageAmount)
{
    _healthComponent.TakeDamage(damageAmount, _damageLocation);
    _spriteComponent.GetSprite().setColor(sf::Color::Red);
    _isDamaged = true;
    _damageTimer = 0.05F;
}
