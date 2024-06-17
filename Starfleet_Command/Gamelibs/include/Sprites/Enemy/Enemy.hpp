#ifndef STARFLEET_COMMAND_ENEMY_HPP
#define STARFLEET_COMMAND_ENEMY_HPP
#include "Interfaces/IStarship.hpp"
#include "Sprites/Starships/StarshipFactory.hpp"
#include <cmath>
#include <functional>

class Enemy
{
public:
    enum EventID
    {
        SHIP_SPAWNED = 1,
        SHIP_DESTROYED = 2 // starship class?
    };

    Enemy () = default;
    ~Enemy() = default;
    void Update(sf::RenderWindow& window, sf::Time deltaTime);
    void Render(sf::RenderWindow& window);

    void CreateShip(StarshipFactory::SHIP_TYPE type);
    using BasicEnemyEvent = std::pair<EventID, std::function<void()>>;
    using AgnosticEnemyEvent = std::pair<EventID, std::function<void(std::any)>>;
    void AddBasicObserver(BasicEnemyEvent observer);
    void AddAgnosticObserver(AgnosticEnemyEvent observer);

    std::vector<std::unique_ptr<IStarship>> &GetShips();

private:
    std::vector<std::unique_ptr<IStarship>> starship{};
    std::multimap<EventID, std::function<void()>> _basicObservers{};
    std::multimap<EventID, std::function<void(std::any)>> _agnosticObservers{};
};

#endif //STARFLEET_COMMAND_ENEMY_HPP
