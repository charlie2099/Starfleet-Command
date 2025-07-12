#include "ExplosionEffect.hpp"

ExplosionEffect::ExplosionEffect(sf::Vector2f position)
{
    _explosionTexture.loadFromFile("Resources/Textures/explosion.png");
    _explosionEffect.setTexture(_explosionTexture);
    _explosionEffect.setScale(0.05F, 0.05F);
    _explosionEffect.setPosition({position.x - _explosionEffect.getGlobalBounds().width/2.0F, position.y - _explosionEffect.getGlobalBounds().height/2.0F});
}

void ExplosionEffect::Update(sf::RenderWindow &window, sf::Time &deltaTime)
{
    _timePassed += 1.0f * deltaTime.asSeconds();
}

void ExplosionEffect::Render(sf::RenderWindow &window)
{
    window.draw(_explosionEffect);
}

bool ExplosionEffect::IsFinished()
{
    return _timePassed >= 0.1F;
}