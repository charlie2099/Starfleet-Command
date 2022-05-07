#ifndef STARFLEET_COMMAND_ISTARSHIP_HPP
#define STARFLEET_COMMAND_ISTARSHIP_HPP
#include "Components/SpriteComponent.hpp"
#include "Components/HealthComponent.hpp"
#include "Components/PhysicsComponent.hpp"
#include "Components/AnimationComponent.hpp"
#include "Components/AudioComponent.hpp"

/*
 * Interface for all ships to inherit from
 */
class IStarship
{
public:
    virtual void Update(sf::RenderWindow& window, sf::Time time) = 0;
    virtual void Render(sf::RenderWindow& window) = 0;

    virtual void SetDamage(float damage) = 0;
    virtual void SetSpeed(float speed) = 0;

    // AiComponent?
    // InputComponent?
    // CollisionComponent?
    // HealthBarComponent
    virtual SpriteComponent& GetSpriteComponent() = 0;
    virtual HealthComponent& GetHealthComponent() = 0;
    virtual PhysicsComponent& GetMovementComponent() = 0; // or can be called PhysicsComponent
    virtual AnimationComponent& GetAnimationComponent() = 0; // or can be called GraphicsComponent
    virtual AudioComponent& GetAudioComponent() = 0;
    virtual const float GetSpeed() = 0;

    // Mediator pattern for sending messages to other components?

protected:
    SpriteComponent _spriteComponent;
    HealthComponent _healthComponent;
    PhysicsComponent _movementComponent;
    AnimationComponent _animationComponent;
    AudioComponent _audioComponent;
    float _damage;
    float _speed;
};

#endif //STARFLEET_COMMAND_ISTARSHIP_HPP
