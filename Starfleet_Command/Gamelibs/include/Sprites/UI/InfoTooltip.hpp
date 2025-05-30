#ifndef STARFLEET_COMMAND_INFOTOOLTIP_HPP
#define STARFLEET_COMMAND_INFOTOOLTIP_HPP
#include "Utility/Colour.hpp"
#include "Utility/CustomFonts.hpp"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class InfoTooltip
{
public:
    InfoTooltip(sf::Vector2<float> widgetPanelSize, sf::Color _widgetPanelColour, const std::string& widgetTitle, std::vector<std::pair<sf::Text, sf::Text>> widgetInfoItems);
    ~InfoTooltip() = default;

    void EventHandler(sf::RenderWindow& window, sf::Event& event);
    void Update(sf::RenderWindow& window, sf::Time deltaTime);
    void Render(sf::RenderWindow& window);

    void SetTitle(const std::string& title);
    void SetDescription(const std::string& description);
    void SetItems(std::vector<std::pair<sf::Text, sf::Text>> items);
    void SetPos(sf::Vector2<float> pos);
    void UpdateItem(int itemIndex, std::string label, std::string value);

    sf::Vector2f GetSize() { return _panel.getSize(); }

private:
    sf::RectangleShape _panel;
    sf::Text _title;
    sf::Text _description;
    std::vector<std::pair<sf::Text, sf::Text>> _descriptionItems;
};

#endif //STARFLEET_COMMAND_INFOTOOLTIP_HPP
