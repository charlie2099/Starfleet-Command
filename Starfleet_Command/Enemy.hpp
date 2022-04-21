#ifndef STARFLEET_COMMAND_ENEMY_HPP
#define STARFLEET_COMMAND_ENEMY_HPP
#include "Ships/Starship.hpp"
#include <cmath>

class Enemy
{
public:
    Enemy() = default;
    ~Enemy() = default;
    void Update(sf::RenderWindow& window, sf::Time deltaTime);
    void Render(sf::RenderWindow& window);

    void CreateShip(Starship::Type type);

    std::vector<std::unique_ptr<Starship>> &GetShip();

private:
    std::vector<std::unique_ptr<Starship>> starship{};
};

#endif //STARFLEET_COMMAND_ENEMY_HPP
