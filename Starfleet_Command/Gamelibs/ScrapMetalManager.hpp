#ifndef STARFLEET_COMMAND_SCRAPMETALMANAGER_HPP
#define STARFLEET_COMMAND_SCRAPMETALMANAGER_HPP
#include <SFML/Graphics/RenderWindow.hpp>
#include "Sprites/UI/Effects/PopupText.hpp"

class ScrapMetalManager
{
public:
    ScrapMetalManager(sf::Font& font, sf::Color scrapTextColour, sf::Color popupTextColour, int startingScrap);
    ~ScrapMetalManager() = default;

    void Update(sf::RenderWindow& window, sf::Time deltaTime);
    void Render(sf::RenderWindow& window);

    void CollectScrap(int amount);
    void SpendScrap(int amount);
    void CreatePopup(int buildCost, sf::Vector2<float> popupPosition);
    void UpdateScrapText(const std::string& scrapMetalText);
    void SetTextPosition(float xPos, float yPos);

    int GetCurrentScrapMetalAmount() const { return _scrapMetalCounter; }
    sf::Rect<float> GetTextSize() { return _scrapMetalText.getGlobalBounds(); }

private:
    std::vector<std::unique_ptr<PopupText>> _scrapMetalPopupText;
    sf::Text _scrapMetalText;
    sf::Color _popupTextColour;
    int _scrapMetalCounter = 2500;
};

#endif //STARFLEET_COMMAND_SCRAPMETALMANAGER_HPP
