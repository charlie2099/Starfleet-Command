#ifndef STARFLEET_COMMAND_STARSHIPDEPLOYMENTBUTTON_HPP
#define STARFLEET_COMMAND_STARSHIPDEPLOYMENTBUTTON_HPP
#include "Sprites/UI/GUI/Button.hpp"
#include "Utility/CustomFonts.hpp"
#include "Interfaces/IStarship.hpp"
#include "ScrapMetalManager.hpp"
#include "Sprites/Starships/StarshipFactory.hpp"

class StarshipDeploymentButton // TODO: Create a higher level StarshipDeploymentConsole/Dashboard class that encapsulates this class and the starship deployment bar? // Integrate within StarshipDeploymentManager?
{
public:
    StarshipDeploymentButton(StarshipFactory::STARSHIP_TYPE starshipTypeToBeDeployed, sf::Color hoverColour);
    ~StarshipDeploymentButton() = default;

    void EventHandler(sf::RenderWindow& window, sf::Event& event);
    void Update(sf::RenderWindow &window, sf::Time deltaTime);
    void Render(sf::RenderWindow& window);

    void ResetAfterStarshipPlacement();

    void SetColour(sf::Color colour);
    void SetPos(sf::Vector2<float> pos);
    void SetAffordable(bool affordable) { _isAffordable = affordable; }

    std::string GetStarshipName() { return _starshipTemplateToBeDeployed->GetStarshipName(); }
    int GetBuildCost() const { return _starshipTemplateToBeDeployed->GetBuildCost(); }
    float GetStarshipDeploymentSpeed() { return _starshipTemplateToBeDeployed->GetDeploymentTime(); }
    StarshipFactory::STARSHIP_TYPE GetStarshipType() { return _starshipType; }
    sf::Vector2<float> GetPos() { return _button->GetPos(); }
    sf::Rect<float> GetBounds() { return _button->GetBounds(); }
    bool IsPlacingStarship() const { return _isPlacingStarship; }
    bool IsAffordable() const { return _isAffordable; }

    bool IsCursorHoveredOver() const { return _button->IsCursorHoveredOver(); }

private:
    std::unique_ptr<Button> _button;
    sf::Text _nameText;
    sf::Vector2<float> _position;
    std::unique_ptr<IStarship> _starshipTemplateToBeDeployed;
    SpriteComponent _previewStarshipSprite;
    bool _isStarshipPreviewSpriteVisible = false;
    bool _isPlacingStarship = false;
    bool _isNameVisible = false;
    bool _isAffordable = false;
    StarshipFactory::STARSHIP_TYPE _starshipType;
    Chilli::PredefinedColours _predefinedColours;
    sf::Color _teamColour;
    const sf::Color DEFAULT_BTN_COLOUR = {255, 255, 255, 100};
    const sf::Color HOVER_BTN_COLOR = {_teamColour.r, _teamColour.g, _teamColour.b, 255};
    const sf::Color SELECTED_BTN_COLOR = {_teamColour.r, _teamColour.g, _teamColour.b, 150};
};

#endif //STARFLEET_COMMAND_STARSHIPDEPLOYMENTBUTTON_HPP
