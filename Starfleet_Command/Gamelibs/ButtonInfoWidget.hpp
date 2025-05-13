#ifndef STARFLEET_COMMAND_BUTTONINFOWIDGET_HPP
#define STARFLEET_COMMAND_BUTTONINFOWIDGET_HPP
#include "Utility/Colour.hpp"
#include "Utility/CustomFonts.hpp"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class ButtonInfoWidget
{
public:
    ButtonInfoWidget(sf::Vector2<float> widgetPanelSize, sf::Color _widgetPanelColour, const std::string& widgetTitle, std::vector<std::pair<sf::Text, sf::Text>> widgetInfoItems);
    ~ButtonInfoWidget() = default;

    void EventHandler(sf::RenderWindow& window, sf::Event& event);
    void Update(sf::RenderWindow& window, sf::Time deltaTime);
    void Render(sf::RenderWindow& window);

    void SetPos(sf::Vector2<float> pos);

    sf::Vector2f GetSize() { return _widgetPanel.getSize(); }

private:
    sf::RectangleShape _widgetPanel;
    sf::Text _widgetTitle;
    std::vector<std::pair<sf::Text, sf::Text>> _widgetTextValueItems;
};

#endif //STARFLEET_COMMAND_BUTTONINFOWIDGET_HPP
