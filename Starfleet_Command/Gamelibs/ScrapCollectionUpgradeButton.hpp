#ifndef STARFLEET_COMMAND_SCRAPCOLLECTIONUPGRADEBUTTON_HPP
#define STARFLEET_COMMAND_SCRAPCOLLECTIONUPGRADEBUTTON_HPP
#include "Sprites/UI/GUI/Button.hpp"
#include "ScrapMetalManager.hpp"
#include "Utility/Colour.hpp"
#include "Utility/CustomFonts.hpp"

class ScrapCollectionUpgradeButton
{
public:
    explicit ScrapCollectionUpgradeButton(std::unique_ptr<ScrapMetalManager>& scrapMetalManager, sf::Color hoverColour);
    ~ScrapCollectionUpgradeButton() = default;

    // TODO: Extract into IRenderable interface?
    void EventHandler(sf::RenderWindow& window, sf::Event& event);
    void Update(sf::RenderWindow &window, sf::Time deltaTime);
    void Render(sf::RenderWindow& window);

    // TODO: Extract into ISprite interface?
    void SetColour(sf::Color colour);
    void SetPos(sf::Vector2<float> pos);
    sf::Vector2<float> GetPos() { return _button->GetPos(); }
    sf::Rect<float> GetBounds() { return _button->GetBounds(); }

    void SetAffordable(bool affordable) { _isAffordable = affordable; }
    int GetUpgradeCost() { return _upgradeCost; }
    int GetUpgradeLevel(){ return _upgradeLevel; }

    bool IsCursorHoveredOver() const { return _button->IsCursorHoveredOver(); }

private:
    std::unique_ptr<ScrapMetalManager>& _scrapMetalManager;
    std::unique_ptr<Button> _button;
    sf::Text _nameText;
    int _upgradeCost = 0;
    int _upgradeLevel = 1;
    sf::Vector2<float> _position;
    bool _isNameVisible = false;
    bool _isAffordable = false;
    sf::Color _teamColour;
    const sf::Color DEFAULT_BTN_COLOUR = {255, 255, 255, 100};
    const sf::Color HOVER_BTN_COLOR = {_teamColour.r, _teamColour.g, _teamColour.b, 255};
    const sf::Color SELECTED_BTN_COLOR = {_teamColour.r, _teamColour.g, _teamColour.b, 150};
};

#endif //STARFLEET_COMMAND_SCRAPCOLLECTIONUPGRADEBUTTON_HPP
