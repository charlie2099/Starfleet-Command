#include "Components/HealthComponent.hpp"

void HealthComponent::TakeDamage(float damageAmount, sf::Vector2f damageLocation)
{
    _health -= damageAmount;

    //auto& damagePopup = _damagePopUpEffect.emplace_back(std::make_unique<PopupText>(_health, _outsideBarSpriteComponent.GetPos()));
    auto& damagePopup = _damagePopUpEffect.emplace_back(std::make_unique<PopupText>(damageAmount, damageLocation));
    if(damageAmount > 200) // NOTE: Check if damage dealt is more than 75% of the max damage a starship can deal
    {
        damagePopup->SetColour(sf::Color::Red);
        //damagePopup->SetCharSize(15);
    }
    InvokeAgnosticEvent(HEALTH_UPDATED, _health);
}

void HealthComponent::ReplenishHealth(float maxHealth, float healAmount, sf::Vector2f healLocation)
{
    float newHealth = GetHealth() + healAmount;
    if (newHealth > maxHealth)
    {
        newHealth = maxHealth;
    }
    _health = newHealth;

    auto& healthPopup = _damagePopUpEffect.emplace_back(std::make_unique<PopupText>(healAmount, healLocation));
    healthPopup->SetColour(sf::Color::Green);
    healthPopup->SetCharSize(15);
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
        InvokeBasicEvent(HEALTH_DEPLETED);
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

void HealthComponent::InvokeBasicEvent(EventID eventId)
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
    /// Invokes the callback function assigned to the specified event id?
    auto ag_range = _agnosticObservers.equal_range(eventId);
    for(auto iter = ag_range.first; iter != ag_range.second; ++iter)
    {
        /// subscribed method is called
        iter->second(anyData);
    }
}









