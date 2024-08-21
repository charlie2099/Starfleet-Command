#ifndef STARFLEET_COMMAND_INFOBOXELEMENT_HPP
#define STARFLEET_COMMAND_INFOBOXELEMENT_HPP

#include <SFML/Graphics/Text.hpp>
#include "UIElement.hpp"

class InfoBoxElement : public UIElement
{
public:
    InfoBoxElement(std::string& title, std::string& info, sf::Texture& texture, sf::Vector2f& size, sf::Vector2f &pos);
    InfoBoxElement(std::string& info, sf::Texture& texture, sf::Vector2f& size, sf::Vector2f &pos);
    InfoBoxElement(std::string& info, sf::Vector2f& size, sf::Vector2f &pos);

    void EventHandler(sf::RenderWindow &window, sf::Event &event) override;
    void Update(sf::RenderWindow &window) override;
    void Render(sf::RenderWindow &window) override;

    void SetTitle(std::string& title);
    void SetDescription(std::string& description);
    void SetImage(sf::Texture& texture);

    std::string GetTitle() { return _titleText.getString(); }
    std::string GetDescription() { return _infoText.getString(); }

private:
    sf::Text _titleText;
    sf::Text _infoText;
    sf::Texture _infoBoxImage;
};

#endif //STARFLEET_COMMAND_INFOBOXELEMENT_HPP
