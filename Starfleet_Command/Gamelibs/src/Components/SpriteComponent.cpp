#include "Components/SpriteComponent.hpp"

void SpriteComponent::LoadSprite(const std::string& texture_filepath)
{
    texture_.loadFromFile(texture_filepath);
    sprite.setTexture(texture_);
}

sf::Sprite &SpriteComponent::GetSprite()
{
    return sprite;
}

void SpriteComponent::SetPos(sf::Vector2<float> pos)
{
    sprite.setPosition(pos);
}

sf::Vector2<float> SpriteComponent::GetPos()
{
    return sprite.getPosition();
}

void SpriteComponent::Render(sf::RenderWindow &renderWindow)
{
    renderWindow.draw(sprite);
}

