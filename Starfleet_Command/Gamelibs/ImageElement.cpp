#include "ImageElement.hpp"

ImageElement::ImageElement(sf::Vector2f &pos, sf::Vector2f &size) : UIElement(pos, size)
{
    // Use a shape instead of an image
    _sprite.setPosition(pos);
}

ImageElement::ImageElement(sf::Texture& texture, sf::Vector2f &pos, sf::Vector2f &size) : UIElement(pos, size)
{
    _sprite.setTexture(texture);
    _sprite.setPosition(pos);
}

void ImageElement::EventHandler(sf::RenderWindow &window, sf::Event &event)
{

}

void ImageElement::Update(sf::RenderWindow &window)
{

}

void ImageElement::Render(sf::RenderWindow &window)
{
    window.draw(_sprite);
}

