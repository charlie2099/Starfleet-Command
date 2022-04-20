#ifndef STARFLEET_COMMAND_PLAYER_HPP
#define STARFLEET_COMMAND_PLAYER_HPP
#include "../Ships/Starship.hpp"
#include <iostream>
#include <cmath>

class Player
{
 public:
    Player() = default;
    ~Player() = default;

    void EventHandler(sf::RenderWindow& window, sf::Event& event);
    void Update(sf::RenderWindow& window, sf::Time deltaTime);

    /// Modifiers
    void SetCredits(int credits);

    /// Accessors
    std::vector<std::unique_ptr<Starship>> &GetShip();
    int GetCredits() const;

 private:
    std::vector<std::unique_ptr<Starship>> starship{};

    // TODO: Controller Class?
    std::map<sf::Keyboard::Key, bool> key_state{};
    std::map<sf::Keyboard::Key, bool>::iterator key_idx{};
    int player_credits = 2500;
};

#endif //STARFLEET_COMMAND_PLAYER_HPP
