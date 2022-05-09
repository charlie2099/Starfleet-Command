#ifndef STARFLEET_COMMAND_ENEMY_HPP
#define STARFLEET_COMMAND_ENEMY_HPP
#include "Sprites/Starships/OLDStarship.hpp"
#include <cmath>
#include <functional>

class Enemy
{
public:
    enum EventID
    {
        SHIP_SPAWNED = 1
    };

    Enemy() = default;
    ~Enemy() = default;
    void Update(sf::RenderWindow& window, sf::Time deltaTime);
    void Render(sf::RenderWindow& window);

    void CreateShip(OLDStarship::Type type);
    void AddObserver(std::pair<EventID, std::function<void()>> observer);

    std::vector<std::unique_ptr<OLDStarship>> &GetShip();

private:
    std::vector<std::unique_ptr<OLDStarship>> starship{};
    std::multimap<EventID, std::function<void()>> _observers;
};

#endif //STARFLEET_COMMAND_ENEMY_HPP
