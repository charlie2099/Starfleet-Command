#ifndef STARFLEET_COMMAND_PLAYER_H
#define STARFLEET_COMMAND_PLAYER_H
#include "Interfaces/IStarship.hpp"
#include "Sprites/Starships/StarshipFactory.hpp"
#include <functional>
#include <any>

class Player
{
public:
    enum EventID
    {
        SHIP_SPAWNED = 1,
        SHIP_DESTROYED = 2 // starship class?
    };

    Player() = default;
    ~Player() = default;
    void Update(sf::RenderWindow& window, sf::Time deltaTime);
    void Render(sf::RenderWindow& window);

    void CreateShip(StarshipFactory::SHIP_TYPE type);
    using BasicPlayerEvent = std::pair<EventID, std::function<void()>>;
    using AgnosticPlayerEvent = std::pair<EventID, std::function<void(std::any)>>;
    void AddBasicObserver(BasicPlayerEvent observer);
    void AddAgnosticObserver(AgnosticPlayerEvent observer);

    std::vector<std::unique_ptr<IStarship>> &GetShips();

private:
    std::vector<std::unique_ptr<IStarship>> starship{};
    std::multimap<EventID, std::function<void()>> _basicObservers{};
    std::multimap<EventID, std::function<void(std::any)>> _agnosticObservers{};
};

#endif //STARFLEET_COMMAND_PLAYER_H
