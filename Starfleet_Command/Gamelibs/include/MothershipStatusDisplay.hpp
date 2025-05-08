#ifndef STARFLEET_COMMAND_MOTHERSHIPSTATUSDISPLAY_HPP
#define STARFLEET_COMMAND_MOTHERSHIPSTATUSDISPLAY_HPP
#include "Sprites/Starships/StarshipClasses/Mothership.hpp"
#include "Utility/CustomFonts.hpp"

class MothershipStatusDisplay
{
public:
    MothershipStatusDisplay(std::unique_ptr<Starship> &playerMothership, std::unique_ptr<Starship> &enemyMothership, sf::View &displayView);
    ~MothershipStatusDisplay() = default;

    void Update(sf::RenderWindow& window, sf::Time deltaTime);
    void Render(sf::RenderWindow& window);

    sf::Vector2<float> GetPlayerMothershipTextPos() { return _mothershipNameText[0].getPosition(); }
    sf::Rect<float> GetPlayerMothershipTextBounds() { return _mothershipNameText[0].getGlobalBounds(); }
    sf::Vector2<float> GetEnemyMothershipTextPos() { return _mothershipNameText[1].getPosition(); }
    sf::Rect<float> GetEnemyMothershipTextBounds() { return _mothershipNameText[1].getGlobalBounds(); }

private:
    std::array<sf::Text, 2> _mothershipNameText;
    std::array<std::unique_ptr<HealthBar>, 2> _mothershipHealthBar;
    sf::View& _displayView;
};

#endif //STARFLEET_COMMAND_MOTHERSHIPSTATUSDISPLAY_HPP
