#include "HealthBar.hpp"

HealthBar::HealthBar()
{
    spriteComponent.LoadSprite("images/panel_image.png");
    spriteComponent.GetSprite().setScale(0.2f, 0.05f);
    spriteComponent.GetSprite().setColor(sf::Color::Green);
}

void HealthBar::Update(sf::RenderWindow &window, sf::Time deltaTime)
{
    spriteComponent.SetPos({_position.x + spriteComponent.GetSprite().getGlobalBounds().width/2, _position.y});
    spriteComponent.GetSprite().setScale((_health / _maxHealth)*0.25f, 0.05f);
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

void HealthBar::TakeDamage(float damage)
{
    if(_health > 0)
    {
        _health -= damage;

        if(_health < 0)
        {
            _health = 0;
        }
    }
}
