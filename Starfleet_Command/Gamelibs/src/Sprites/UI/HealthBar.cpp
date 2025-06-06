#include "Sprites/UI/HealthBar.hpp"

HealthBar::HealthBar(HealthComponent& healthComponent, bool isRotated)
{
    _healthBar.LoadSprite("Resources/Textures/panel_5.png");
    _healthBar.GetSprite().setScale(0.2F, 0.075F);
    _healthBar.GetSprite().setColor(sf::Color::Green);

    _healthBarMask.LoadSprite("Resources/Textures/health_bar_mask.png");
    _healthBarMask.GetSprite().setScale(0.2F, 0.075F);

    _scale = {0.2F, 0.075F};

    if(isRotated)
    {
        _healthBar.GetSprite().setRotation(-90);
        _healthBarMask.GetSprite().setRotation(_healthBar.GetSprite().getRotation());
    }

    /// Observer to healthcomponent
    auto healthCallback = std::bind(&HealthBar::UpdateHealth, this, std::placeholders::_1);
    healthComponent.AddAgnosticObserver({HealthComponent::EventID::HEALTH_UPDATED, healthCallback});
}

void HealthBar::Update(sf::RenderWindow& window, sf::Time deltaTime)
{
    _healthBar.SetPos({_position.x + _healthBar.GetSprite().getGlobalBounds().width / 2, _position.y});
    _healthBarMask.SetPos({ _healthBar.GetPos().x, _healthBar.GetPos().y });

    if(_health > _maxHealth/2)
    {
        _healthBar.GetSprite().setColor(sf::Color::Green);
    }
    else if(_health <= _maxHealth/2 && _health >= _maxHealth/3)
    {
        _healthBar.GetSprite().setColor(sf::Color(255, 215, 0));
    }
    else if(_health <= _maxHealth/3)
    {
        _healthBar.GetSprite().setColor(sf::Color::Red);
    }
}

void HealthBar::Render(sf::RenderWindow &window)
{
    _healthBar.Render(window);
    _healthBarMask.Render(window);
}

void HealthBar::SetPos(sf::Vector2f pos)
{
    _position = pos;
}

void HealthBar::SetRot(float rot)
{
    _rotation = rot;
}

void HealthBar::SetScale(float xScale, float yScale)
{
    _healthBar.GetSprite().setScale(xScale, yScale);
    _healthBarMask.GetSprite().setScale(xScale, yScale);
    _scale = {xScale, yScale};
}

void HealthBar::SetMaxHealth(float health)
{
    _maxHealth = health;
    _health = _maxHealth;
}

void HealthBar::UpdateHealth(std::any eventData)
{
    //std::cout << "Health updated: " << std::any_cast<int>(eventData) << std::endl;
    _health = std::any_cast<int>(eventData);
    _healthBar.SetPos({_position.x + _healthBar.GetSprite().getGlobalBounds().width / 2, _position.y});
    _healthBarMask.SetPos({_healthBar.GetPos().x, _healthBar.GetPos().y});
    _healthBar.GetSprite().setScale((_health / _maxHealth) * _scale.x, _scale.y);
}



