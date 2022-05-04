#include "Sprites/Starships/StarshipClasses/StarshipFighter.hpp"

StarshipFighter::StarshipFighter()
{
    _healthComponent.SetHealth(100);
    _damage = 20;
    _speed = 10;

    _spriteComponent.LoadSprite("Resources/Textures/starfleet_ship_fighter.png");
    _spriteComponent.GetSprite().setColor(sf::Color::Yellow);
    _spriteComponent.GetSprite().setScale(0.1F, 0.1F);
    _spriteComponent.GetSprite().setPosition(300, 300);

    //auto callbackFnc1 = std::bind(&TestClass::TestFncForObserverToCall, testClass);
    //_healthComponent.AddObserver({HealthComponent::HEALTH_DEPLETED, callbackFnc1});
}

void StarshipFighter::Update(sf::RenderWindow &window, sf::Time time)
{
    _healthComponent.Update(window, time);
}

void StarshipFighter::Render(sf::RenderWindow &window)
{
    _spriteComponent.Render(window);
}

void StarshipFighter::SetDamage(float damage)
{
    _damage = damage;
}

void StarshipFighter::SetSpeed(float speed)
{
    _speed = speed;
}

SpriteComponent &StarshipFighter::GetSpriteComponent()
{
    return _spriteComponent;
}

HealthComponent &StarshipFighter::GetHealthComponent()
{
    return _healthComponent;
}

MovementComponent &StarshipFighter::GetMovementComponent()
{
    return _movementComponent;
}

AnimationComponent &StarshipFighter::GetAnimationComponent()
{
    return _animationComponent;
}

AudioComponent &StarshipFighter::GetAudioComponent()
{
    return _audioComponent;
}

const float StarshipFighter::GetSpeed()
{
    return _speed;
}








