#ifndef STARFLEET_COMMAND_STARSHIPDEPLOYMENTBUTTON_HPP
#define STARFLEET_COMMAND_STARSHIPDEPLOYMENTBUTTON_HPP
#include "Sprites/UI/GUI/Button.hpp"
#include "Utility/CustomFonts.hpp"
#include "Interfaces/IStarship.hpp"
#include "ScrapMetalManager.hpp"
#include "Sprites/Starships/StarshipFactory.hpp"

class StarshipDeploymentButton // TODO: Create a higher level StarshipDeploymentConsole/Dashboard class that encapsulates this class and the starship deployment bar? // Put an array of  this in GameUI class?
{
public:
    StarshipDeploymentButton(StarshipFactory::STARSHIP_TYPE starshipTypeToBeDeployed, sf::Color teamColour, std::unique_ptr<ScrapMetalManager> &playerScrapMetalManager);
    ~StarshipDeploymentButton() = default;

    void EventHandler(sf::RenderWindow& window, sf::Event& event);
    void Update(sf::RenderWindow &window, sf::Time deltaTime);
    void Render(sf::RenderWindow& window);

    void ResetAfterStarshipPlacement();

    void SetPos(sf::Vector2<float> pos);

    std::string GetStarshipName() { return _starshipTemplateToBeDeployed->GetStarshipName(); }
    int GetBuildCost() const { return _cost; }
    float GetStarshipDeploymentSpeed() { return _starshipTemplateToBeDeployed->GetDeploymentSpeed(); }
    StarshipFactory::STARSHIP_TYPE GetStarshipType() { return _starshipType; }
    sf::Vector2<float> GetPos() { return _button->GetPos(); }
    sf::Rect<float> GetBounds() { return _button->GetBounds(); }

    bool IsPlacingStarship() const { return _isPlacingStarship; }

private:
    std::unique_ptr<Button> _button;
    sf::Text _nameText;
    sf::Text _costText;
    int _cost;
    sf::Vector2<float> _position;
    std::unique_ptr<IStarship> _starshipTemplateToBeDeployed;
    SpriteComponent _previewStarshipSprite;
    bool _isStarshipPreviewSpriteVisible = false;
    bool _isPlacingStarship = false;
    bool _isNameVisible = false;
    StarshipFactory::STARSHIP_TYPE _starshipType;
    Chilli::PredefinedColours _predefinedColours;
    std::unique_ptr<ScrapMetalManager>& _playerScrapMetalManager;
    const sf::Color DEFAULT_BTN_COLOUR = {255, 255, 255, 100};
    const sf::Color HOVER_BTN_COLOR = {153, 210, 242, 255};
    const sf::Color SELECTED_BTN_COLOR = {153, 210, 242, 150};
};

#endif //STARFLEET_COMMAND_STARSHIPDEPLOYMENTBUTTON_HPP
