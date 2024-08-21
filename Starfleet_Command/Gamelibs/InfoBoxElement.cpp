#include "InfoBoxElement.hpp"

InfoBoxElement::InfoBoxElement(std::string& title, std::string& info, sf::Texture& texture, sf::Vector2f& size, sf::Vector2f& pos) : UIElement(pos, size)
{
    _titleText.setString(title);
    _infoText.setString(info);
    _infoBoxImage = texture;
}

InfoBoxElement::InfoBoxElement(std::string& info, sf::Texture& texture, sf::Vector2f& size, sf::Vector2f& pos) : UIElement(pos, size)
{
    _infoText.setString(info);
    _infoBoxImage = texture;
}

InfoBoxElement::InfoBoxElement(std::string& info, sf::Vector2f& size, sf::Vector2f& pos) : UIElement(pos, size)
{
    _infoText.setString(info);
}

void InfoBoxElement::EventHandler(sf::RenderWindow &window, sf::Event &event)
{

}

void InfoBoxElement::Update(sf::RenderWindow &window)
{

}

void InfoBoxElement::Render(sf::RenderWindow &window)
{

}

void InfoBoxElement::SetTitle(std::string &title)
{
    _titleText.setString(title);
}

void InfoBoxElement::SetDescription(std::string &description)
{
    _infoText.setString(description);
}

void InfoBoxElement::SetImage(sf::Texture &texture)
{
    _infoBoxImage = texture;
}



