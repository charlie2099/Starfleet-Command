#ifndef STARFLEET_COMMAND_PLAYER_HPP
#define STARFLEET_COMMAND_PLAYER_HPP
#include "../Ships/Starship.hpp"
#include "../GameUI/CommandMenu.hpp"
#include <iostream>
#include <cmath>

class Player
{
 public:
    Player() = default;
    ~Player() = default;

    void eventHandler(sf::RenderWindow& window, sf::Event& event);
    void update(sf::RenderWindow& window, sf::Time deltaTime);
    void render(sf::RenderWindow& window);

    /// Modifiers
    void setCredits(int credits);

    /// Accessors
    std::vector<std::unique_ptr<Starship>> &getShip();
    int getCredits() const;

 private:
    void flagshipMovementControls(const sf::Time &deltaTime);
    bool comfortableBoundsCheck(sf::Vector2<float> mouse_vec, std::unique_ptr<Starship>& starship);

    CommandMenu command_menu;
    std::vector<std::unique_ptr<Starship>> starship{};

    // TODO: Controller Class?
    std::map<sf::Keyboard::Key, bool> key_state{};
    std::map<sf::Keyboard::Key, bool>::iterator key_idx{};

    sf::Vector2<float> clicked_pos;
    int selected = 0;
    int player_credits = 2500;
};

#endif //STARFLEET_COMMAND_PLAYER_HPP
