#ifndef STARFLEET_COMMAND_ISTARSHIP_HPP
#define STARFLEET_COMMAND_ISTARSHIP_HPP
#include "Components/SpriteComponent.hpp"
#include "Components/HealthComponent.hpp"

/*
 * Interface that all ships inherit from
 */
class IStarship
{
public:
    virtual void Update(sf::RenderWindow& window, sf::Time deltaTime) = 0;
    virtual void Render(sf::RenderWindow& window) = 0;

    virtual void SetDamage(float damage) = 0;
    virtual void SetSpeed(float speed) = 0;
    virtual void SetHealthBarVisibility(bool visible) = 0;

    virtual SpriteComponent& GetSpriteComponent() = 0;
    virtual HealthComponent& GetHealthComponent() = 0;
    //virtual std::unique_ptr<HealthBar>& GetHealthBar() = 0;
    virtual const float GetSpeed() = 0;
    virtual const float GetMaxHealth() = 0;
    virtual bool IsHealthBarVisible() =0;

protected:
    SpriteComponent _spriteComponent;
    HealthComponent _healthComponent;
    //std::unique_ptr<HealthBar> _healthBar;
    float _maxHealth;
    float _damage;
    float _speed;
    bool _healthBarIsVisible = false;
};

#endif //STARFLEET_COMMAND_ISTARSHIP_HPP
