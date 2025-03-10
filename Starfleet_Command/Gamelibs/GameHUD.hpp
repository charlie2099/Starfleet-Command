#ifndef STARFLEET_COMMAND_GAMEHUD_HPP
#define STARFLEET_COMMAND_GAMEHUD_HPP
#include "Sprites/UI/ProgressBar.hpp"
#include "MothershipStatusDisplay.hpp"

/*
 * Responsible for managing passive (non-interactive) HUD elements such as progress bars, health bars, and text.
 */
class GameHUD
{
public:
    GameHUD(std::unique_ptr<IStarship>& playerMothership, std::unique_ptr<IStarship>& enemyMothership, std::basic_string<char> *starshipCosts, sf::View& displayView);
    ~GameHUD() = default;

    void Update(sf::RenderWindow &window, sf::Time deltaTime, sf::Vector2<float> starshipBuilderButton1Pos, sf::Vector2<float> hoveredOverStarshipBuilderButton);
    void Render(sf::RenderWindow& window);

    void Show();
    void Hide();

    sf::Vector2<float> GetPlayerMothershipTextPos() { return mothershipStatusDisplay->GetPlayerMothershipTextPos(); }
    sf::Rect<float> GetPlayerMothershipTextBounds() { return mothershipStatusDisplay->GetPlayerMothershipTextBounds(); }
    sf::Vector2<float> GetEnemyMothershipTextPos() { return mothershipStatusDisplay->GetEnemyMothershipTextPos(); }
    sf::Rect<float> GetEnemyMothershipTextBounds() { return mothershipStatusDisplay->GetEnemyMothershipTextBounds(); }

    sf::Text& GetStarshipNameButtonText() { return _starshipNameButtonText; }
    std::vector<sf::Text>& GetStarshipCostText() { return _starshipCostText; }
    ProgressBar& GetStarshipDeploymentBar() { return _starshipDeploymentBar; }

private:
    void InitStarshipNameButtonText(sf::Color playerMothershipColour);
    std::unique_ptr<MothershipStatusDisplay> mothershipStatusDisplay;
    ProgressBar _starshipDeploymentBar;
    sf::Text _starshipNameButtonText;
    std::vector<sf::Text> _starshipCostText;
    bool _isVisible = true;
};

#endif //STARFLEET_COMMAND_GAMEHUD_HPP
