#ifndef STARFLEET_COMMAND_PLAYER_HPP
#define STARFLEET_COMMAND_PLAYER_HPP
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
        SHIP_DESTROYED = 2 // _starship class?
    };

    Player() = default;
    ~Player() = default;
    void EventHandler(sf::RenderWindow &window, sf::Event &event);
    void Update(sf::RenderWindow& window, sf::Time deltaTime);
    void Render(sf::RenderWindow& window);

    void CreateShip(StarshipFactory::SHIP_TYPE type);
    void PaintFlagship(sf::Color colour);
    void SetFlagshipPosition(sf::Vector2f pos);
    void SetShipPosition(std::unique_ptr<IStarship>& ship, sf::Vector2f pos);
    using BasicPlayerEvent = std::pair<EventID, std::function<void()>>;
    using AgnosticPlayerEvent = std::pair<EventID, std::function<void(std::any)>>;
    void AddBasicObserver(BasicPlayerEvent observer);
    void AddAgnosticObserver(AgnosticPlayerEvent observer);

    std::vector<std::unique_ptr<IStarship>> &GetShips();
    std::unique_ptr<IStarship> &GetFlagship();

private:
    void InvokeBasicEvent(EventID eventId);
    void InvokeAgnosticEvent(EventID eventId, const std::any& anyData);
    std::vector<std::unique_ptr<IStarship>> starship{};
    std::multimap<EventID, std::function<void()>> _basicObservers{};
    std::multimap<EventID, std::function<void(std::any)>> _agnosticObservers{};
};

#endif //STARFLEET_COMMAND_PLAYER_HPP
