#include "HealthBar.hpp"

HealthBar::HealthBar(float health)
{
    _health = health;
    spriteComponent.LoadSprite("images/panel_image.png");
    spriteComponent.GetSprite().setColor(sf::Color::Green);
    spriteComponent.GetSprite().scale({0.2f, 0.05f});
}

void HealthBar::Update(sf::RenderWindow &window, sf::Time deltaTime)
{
    spriteComponent.SetPos(_position);
}

void HealthBar::Render(sf::RenderWindow &window)
{
    spriteComponent.Render(window);
}

void HealthBar::SetPos(sf::Vector2f pos)
{
    _position = pos;
}

void HealthBar::SetHealth(float health)
{
    _health = health;
}
