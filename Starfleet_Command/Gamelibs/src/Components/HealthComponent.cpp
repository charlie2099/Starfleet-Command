#include "Components/HealthComponent.hpp"

/*HealthComponent::HealthComponent(SpriteComponent &_outsideBarSpriteComponent)
{
    _outsideBarSpriteComponent = _outsideBarSpriteComponent;
}*/

void HealthComponent::TakeDamage(float amount, sf::Vector2f damageLocation)
{
    _health -= amount;

    //auto& damagePopup = _damagePopUpEffect.emplace_back(std::make_unique<DamagePopUpEffect>(_health, _outsideBarSpriteComponent.GetPos()));
    auto& damagePopup = _damagePopUpEffect.emplace_back(std::make_unique<DamagePopUpEffect>(amount, damageLocation));
    if(amount > 60)
    {
        damagePopup->SetColour(sf::Color::Red);
        damagePopup->SetCharSize(15);
    }

    InvokeAgnosticEvent(HEALTH_UPDATED, _health);
}

void HealthComponent::ReplenishHealth(float amount)
{
    _health += amount;
    InvokeAgnosticEvent(HEALTH_UPDATED, _health);
}

void HealthComponent::SetHealth(int health)
{
    _health = health;
}

void HealthComponent::Update(sf::RenderWindow& window, sf::Time deltaTime)
{
    if(_health <= 0)
    {
        InvokeSimpleEvent(HEALTH_DEPLETED);
    }

    for(auto& popup : _damagePopUpEffect)
    {
        popup->Update(window, deltaTime);
    }

    for (int i = 0; i < _damagePopUpEffect.size(); ++i)
    {
        if(_damagePopUpEffect[i]->IsFaded())
        {
            _damagePopUpEffect.erase(_damagePopUpEffect.begin() + i);
        }
    }
}

void HealthComponent::Render(sf::RenderWindow &window)
{
    for(auto& popup : _damagePopUpEffect)
    {
        popup->Render(window);
    }
}

void HealthComponent::AddBasicObserver(BasicHealthEvent observer)
{
    _basicObservers.insert(observer);
}

void HealthComponent::AddAgnosticObserver(AgnosticHealthEvent observer)
{
    _agnosticObservers.insert(observer);
}

void HealthComponent::InvokeSimpleEvent(EventID eventId)
{
    /// Invokes the callback function assigned to the specified event id?
    auto range = _basicObservers.equal_range(eventId);
    for(auto iter = range.first; iter != range.second; ++iter)
    {
        iter->second();
    }
}

void HealthComponent::InvokeAgnosticEvent(EventID eventId, const std::any& anyData)
{
    /// SHIP_SPAWNED event is invoked (agnostic)
    auto ag_range = _agnosticObservers.equal_range(eventId);
    for(auto iter = ag_range.first; iter != ag_range.second; ++iter)
    {
        /// subscribed method is called
        iter->second(anyData);
    }
}









