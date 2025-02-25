#include "Components/SpriteComponent.hpp"

void SpriteComponent::Move(float xOffset, float yOffset)
{
    _sprite.move(xOffset, yOffset);
}

void SpriteComponent::LoadSprite(const std::string& texture_filepath)
{
    _texture.loadFromFile(texture_filepath);
    _sprite.setTexture(_texture);
}

sf::Sprite &SpriteComponent::GetSprite()
{
    return _sprite;
}

void SpriteComponent::SetPos(sf::Vector2<float> pos)
{
    _sprite.setPosition(pos);
}

sf::Vector2<float> SpriteComponent::GetPos()
{
    return _sprite.getPosition();
}

void SpriteComponent::Render(sf::RenderWindow &renderWindow)
{
    renderWindow.draw(_sprite);
}

