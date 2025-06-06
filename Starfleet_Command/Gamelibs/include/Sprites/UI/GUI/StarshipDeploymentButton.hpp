#ifndef STARFLEET_COMMAND_STARSHIPDEPLOYMENTBUTTON_HPP
#define STARFLEET_COMMAND_STARSHIPDEPLOYMENTBUTTON_HPP
#include "Sprites/UI/GUI/ImageButton.hpp"
#include "Utility/CustomFonts.hpp"
#include "Sprites/Starships/Starship.hpp"
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

    bool IsMouseOver() const { return _button->IsMouseOver(); }

private:
    std::unique_ptr<ImageButton> _button;
    sf::Text _nameText;
    sf::Vector2<float> _position;
    std::unique_ptr<Starship> _starshipTemplateToBeDeployed;
    SpriteComponent _previewStarshipSprite;
    bool _isStarshipPreviewSpriteVisible = false;
    bool _isPlacingStarship = false;
    bool _isNameVisible = false;
    bool _isAffordable = false;
    StarshipFactory::STARSHIP_TYPE _starshipType;
    sf::Color _teamColour;

    sf::Clock _mouseOverClock;
    float _mouseOverTimer = 0.0F;
    float _mouseOverCheckRate = 1.0F;

    const sf::Color HOVER_BTN_COLOUR = {_teamColour.r, _teamColour.g, _teamColour.b, 255};
    const sf::Color DEFAULT_BTN_COLOUR = {_teamColour.r, _teamColour.g, _teamColour.b, 160};
    const sf::Color INACTIVE_BTN_COLOUR = {_teamColour.r, _teamColour.g, _teamColour.b, 50};
    const sf::Color INACTIVE_TEXT_COLOUR = {_teamColour.r, _teamColour.g, _teamColour.b, 100};
};

#endif //STARFLEET_COMMAND_STARSHIPDEPLOYMENTBUTTON_HPP
