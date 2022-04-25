#include "HealthBar.hpp"

HealthBar::HealthBar()
{
    spriteComponent.LoadSprite("images/panel_5.png");
    spriteComponent.GetSprite().setScale(0.2f, 0.075f);
    spriteComponent.GetSprite().setColor(sf::Color(0,255,0,255));
}

void HealthBar::Update()
{
    spriteComponent.SetPos({_position.x + spriteComponent.GetSprite().getGlobalBounds().width/2, _position.y});
}

void HealthBar::Render(sf::RenderWindow &window)
{
    spriteComponent.Render(window);
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

void HealthBar::UpdateHealth(float health)
{
    _health = health;
    spriteComponent.SetPos({_position.x + spriteComponent.GetSprite().getGlobalBounds().width/2, _position.y});
    spriteComponent.GetSprite().setScale((_health / _maxHealth)*0.2f, 0.075f);
}

