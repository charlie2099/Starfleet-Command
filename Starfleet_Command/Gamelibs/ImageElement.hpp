#ifndef STARFLEET_COMMAND_IMAGEELEMENT_HPP
#define STARFLEET_COMMAND_IMAGEELEMENT_HPP
#include <SFML/Graphics/Sprite.hpp>
#include "UIElement.hpp"

class ImageElement : public UIElement
{
public:
    ImageElement(sf::Vector2f &pos, sf::Vector2f &size);
    ImageElement(sf::Texture& texture, sf::Vector2f &pos, sf::Vector2f &size);

    void EventHandler(sf::RenderWindow &window, sf::Event &event) override;
    void Update(sf::RenderWindow &window) override;
    void Render(sf::RenderWindow &window) override;

private:
    sf::Sprite _sprite;
};

#endif //STARFLEET_COMMAND_IMAGEELEMENT_HPP
