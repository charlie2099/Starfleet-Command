#include "Components/HealthComponent.hpp"

void HealthComponent::TakeDamage(float amount)
{
    _health -= amount;
    //InvokeEvent(HEALTH_UPDATED);
    InvokeEvent(HEALTH_UPDATED, _health);
}

void HealthComponent::ReplenishHealth(float amount)
{
    _health += amount;
    //InvokeEvent(HEALTH_UPDATED);
    InvokeEvent(HEALTH_UPDATED, _health);
}

void HealthComponent::SetHealth(float health)
{
    _health = health;
}

void HealthComponent::Update(sf::RenderWindow &window, sf::Time time)
{
    if(_health <= 0)
    {
        InvokeEvent(HEALTH_DEPLETED);
    }
}

void HealthComponent::AddObserver(HealthComponent::HealthEvent observer)
{
    _observers.insert(observer);
}

void HealthComponent::AddObserver1Param(HealthComponent::HealthEvent1Param observer)
{
    _observers1Param.insert(observer);
}

void HealthComponent::InvokeEvent(HealthComponent::EventID eventId)
{
    /// Invokes the callback function assigned to the specified event id?
    auto range = _observers.equal_range(eventId);
    for(auto iter = range.first; iter != range.second; ++iter)
    {
        iter->second();
    }
}

void HealthComponent::InvokeEvent(HealthComponent::EventID eventId, std::any anyData)
{
    /// SHIP_SPAWNED event is invoked (agnostic)
    auto ag_range = _observers1Param.equal_range(eventId);
    for(auto iter = ag_range.first; iter != ag_range.second; ++iter)
    {
        /// subscribed method is called
        iter->second(anyData);
    }
}





