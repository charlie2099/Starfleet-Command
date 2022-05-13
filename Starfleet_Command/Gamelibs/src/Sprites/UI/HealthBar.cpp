#include "Sprites/UI/HealthBar.hpp"

HealthBar::HealthBar(HealthComponent& healthComponent)
{
    spriteComponent.LoadSprite("Resources/Textures/panel_5.png");
    spriteComponent.GetSprite().setScale(0.2f, 0.075f);
    spriteComponent.GetSprite().setColor(sf::Color::Green);

    spriteComponent2.LoadSprite("Resources/Textures/health_bar_mask.png");
    spriteComponent2.GetSprite().setScale(0.2f, 0.075f);

    /// Observer to healthcomponent
    auto healthCallback = std::bind(&HealthBar::UpdateHealth, this, std::placeholders::_1);
    healthComponent.AddObserver1Param({HealthComponent::EventID::HEALTH_UPDATED, healthCallback});
}

void HealthBar::Update()
{
    spriteComponent.SetPos({_position.x + spriteComponent.GetSprite().getGlobalBounds().width/2, _position.y});
    spriteComponent2.SetPos({ spriteComponent.GetPos().x, spriteComponent.GetPos().y });

    if(_health <= _maxHealth/2 && _health >= _maxHealth/3)
    {
        spriteComponent.GetSprite().setColor(sf::Color(255, 215, 0));
    }
    else if(_health <= _maxHealth/3)
    {
        spriteComponent.GetSprite().setColor(sf::Color::Red);
    }
}

void HealthBar::Render(sf::RenderWindow &window)
{
    spriteComponent.Render(window);
    spriteComponent2.Render(window);
}

void HealthBar::SetPos(sf::Vector2f pos)
{
    _position = pos;
}

void HealthBar::SetMaxHealth(float health)
{
    _maxHealth = health;
    _health = _maxHealth;
}

void HealthBar::UpdateHealth(std::any eventData)
{
    std::cout << "Health updated: " << std::any_cast<int>(eventData) << std::endl;
    _health = std::any_cast<int>(eventData);
    spriteComponent.SetPos({_position.x + spriteComponent.GetSprite().getGlobalBounds().width/2, _position.y});
    spriteComponent.GetSprite().setScale((_health / _maxHealth)*0.2f, 0.075f);
}


