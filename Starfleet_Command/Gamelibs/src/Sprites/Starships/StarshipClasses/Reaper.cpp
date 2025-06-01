#include "Sprites/Starships/StarshipClasses/Reaper.hpp"

Reaper::Reaper(int spawnSpacelane, const std::string& starshipTypeName) : Starship(spawnSpacelane, starshipTypeName)
{
    _spriteComponent.LoadSprite("Resources/Textures/starfleet_ship_5.png");
    _spriteComponent.GetSprite().scale({0.075F, 0.075F});
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