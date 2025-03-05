#ifndef STARFLEET_COMMAND_GAMEHUD_HPP
#define STARFLEET_COMMAND_GAMEHUD_HPP
#include "Sprites/UI/ProgressBar.hpp"
#include "Sprites/UI/HealthBar.hpp"
#include "Utility/Constants.hpp"

/*
 * Responsible for managing passive (non-interactive) HUD elements such as progress bars, health bars, and text.
 */
class GameHUD
{
public:
    GameHUD(HealthComponent& playerMothershipHealthComp, HealthComponent& enemyMothershipHealthComp, sf::Color playerMothershipColour, sf::Color enemyMothershipColour, std::basic_string<char> *starshipCosts, const sf::Font& font);
    ~GameHUD() = default;

    void Update(sf::RenderWindow &window, sf::Time deltaTime, sf::Vector2<float> starshipBuilderButton1Pos, sf::Vector2<float> hoveredOverStarshipBuilderButton, sf::View mainView);
    void Render(sf::RenderWindow& window);

    sf::Text& GetPlayerMothershipText() { return _mothershipNameText[0]; }
    sf::Text& GetEnemyMothershipText() { return _mothershipNameText[1]; }
    sf::Text& GetStarshipNameButtonText() { return _starshipNameButtonText; }
    std::vector<sf::Text>& GetStarshipCostText() { return _starshipCostText; }
    ProgressBar& GetStarshipAssemblyBar() { return _starshipAssemblyBar; }

private:
    void InitStarshipNameButtonText();
    ProgressBar _starshipAssemblyBar;
    sf::Text _starshipNameButtonText;
    std::vector<sf::Text> _starshipCostText;
    std::array<sf::Text, 2> _mothershipNameText;
    std::array<std::unique_ptr<HealthBar>, 2> _mothershipHealthBar;
    sf::Color _playerMothershipColour;
    sf::Font _font;
};

#endif //STARFLEET_COMMAND_GAMEHUD_HPP
