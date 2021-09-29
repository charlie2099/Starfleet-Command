#include "TestComponent.hpp"

TestComponent::TestComponent(Object *object) : Component(object) {}

void TestComponent::loadSprite(const std::string& texture_filepath)
{
    texture_.loadFromFile(texture_filepath);
    sprite.setTexture(texture_);
}

sf::Sprite &TestComponent::getSprite()
{
    return sprite;
}

void TestComponent::setPos(sf::Vector2<float> pos)
{
    sprite.setPosition(pos);
}

sf::Vector2<float> TestComponent::getPos()
{
    return sprite.getPosition();
}

void TestComponent::render(sf::RenderWindow &renderWindow)
{
    renderWindow.draw(sprite);
}