#include "SpriteComponent.hpp"

void SpriteComponent::loadSprite(const std::string& texture_filepath)
{
    texture_.loadFromFile(texture_filepath);
    sprite.setTexture(texture_);
}

sf::Sprite &SpriteComponent::getSprite()
{
    return sprite;
}

void SpriteComponent::setPos(sf::Vector2<float> pos)
{
    sprite.setPosition(pos);
}

sf::Vector2<float> SpriteComponent::getPos()
{
    return sprite.getPosition();
}

void SpriteComponent::render(sf::RenderWindow &renderWindow)
{
    renderWindow.draw(sprite);
}

