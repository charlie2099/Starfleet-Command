#ifndef STARFLEET_COMMAND_PLAYER_H
#define STARFLEET_COMMAND_PLAYER_H
#include "../Ships/Starship.hpp"
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

    void CreateShip(Starship::Type type);

    using PlayerEvent = std::pair<EventID, std::function<void()>>;
    using PlayerAgnosticEvent = std::pair<EventID, std::function<void(std::any)>>;
    void AddObserver(PlayerEvent observer);
    void AddObserver2(PlayerAgnosticEvent observer);

    std::vector<std::unique_ptr<Starship>> &GetShip();

private:
    std::vector<std::unique_ptr<Starship>> starship{};
    std::multimap<EventID, std::function<void()>> _observers{};
    std::multimap<EventID, std::function<void(std::any)>> _observers_agnostic{};
};

#endif //STARFLEET_COMMAND_PLAYER_H
