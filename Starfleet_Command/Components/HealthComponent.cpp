#include "HealthComponent.hpp"

void HealthComponent::SetHealth(float health)
{
    _health = health;
}

void HealthComponent::Update(sf::RenderWindow &window, sf::Time time)
{
    if(_health <= 0)
    {
        /// HEALTH DEPLETED event is invoked (non-agnostic)
        auto range = _observers.equal_range(EventID::HEALTH_DEPLETED);
        for(auto iter = range.first; iter != range.second; ++iter)
        {
            iter->second();
        }
    }
}

void HealthComponent::AddObserver(HealthComponent::HealthEvent observer)
{
    _observers.insert(observer);
}


