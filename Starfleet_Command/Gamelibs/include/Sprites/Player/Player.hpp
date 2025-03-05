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
        STARSHIP_SPAWNED = 1,
        STARSHIP_DESTROYED = 2
    };
    struct StarshipDestroyedData
    {
        sf::Vector2<float> DeathLocation{};
        int BuildCost{};
    };

    /// General
    ~Player() = default;
    Player() = default;
    void EventHandler(sf::RenderWindow &window, sf::Event &event);
    void Update(sf::RenderWindow& window, sf::Time deltaTime);
    void Render(sf::RenderWindow& window);

    /// Behaviours
    void MoveStarship(int starshipIndex, sf::Vector2<float> positionOffset);
    void CreateStarship(StarshipFactory::STARSHIP_TYPE starshipType, int spacelane);

    /// Modifiers
    void PaintMothership(sf::Color colour);
    void SetMothershipPosition(sf::Vector2f pos);
    void SetStarshipPosition(std::unique_ptr<IStarship>& ship, sf::Vector2f pos);

    /// Accessors
    std::vector<std::unique_ptr<IStarship>> &GetStarships() { return starship; }
    std::unique_ptr<IStarship> &GetMothership() { return starship[0]; }
    int GetStarshipCount() { return starship.size(); }

    /// Event handling
    using BasicPlayerEvent = std::pair<EventID, std::function<void()>>;
    using AgnosticPlayerEvent = std::pair<EventID, std::function<void(std::any)>>;
    void AddBasicObserver(BasicPlayerEvent observer);
    void AddAgnosticObserver(AgnosticPlayerEvent observer);

private:
    void InvokeBasicEvent(EventID eventId);
    void InvokeAgnosticEvent(EventID eventId, const std::any& anyData);
    std::vector<std::unique_ptr<IStarship>> starship{};
    std::multimap<EventID, std::function<void()>> _basicObservers{};
    std::multimap<EventID, std::function<void(std::any)>> _agnosticObservers{};
};

#endif //STARFLEET_COMMAND_PLAYER_HPP
