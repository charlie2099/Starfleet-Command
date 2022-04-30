#include "NewSpriteComponent.hpp"

void NewSpriteComponent::LoadSprite(const std::string &texture_filepath)
{
    m_texture.loadFromFile(texture_filepath);
    m_sprite.setTexture(m_texture);
}

sf::Sprite &NewSpriteComponent::GetSprite()
{
    return m_sprite;
}

void NewSpriteComponent::EventHandler(sf::RenderWindow &window, sf::Event &event) {}

void NewSpriteComponent::Update(sf::RenderWindow &window, sf::Time deltaTime) {}

void NewSpriteComponent::Render(sf::RenderWindow &window)
{
    window.draw(m_sprite);
}

