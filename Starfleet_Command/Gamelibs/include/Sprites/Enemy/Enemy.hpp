#ifndef STARFLEET_COMMAND_ENEMY_HPP
#define STARFLEET_COMMAND_ENEMY_HPP
#include "Interfaces/IStarship.hpp"
#include "Sprites/Starships/StarshipFactory.hpp"
#include "Utility/PredefinedColours.hpp"
#include <cmath>
#include <functional>

class Enemy
{
public:
    enum EventID
    {
        STARSHIP_SPAWNED = 1,
        STARSHIP_DESTROYED = 2 // _starship class?
    };
    struct StarshipDestroyedData
    {
        sf::Vector2<float> DeathLocation{};
        int BuildCost{};
    };

    /// General
    Enemy () = default;
    ~Enemy() = default;
    void Update(sf::RenderWindow& window, sf::Time deltaTime);
    void Render(sf::RenderWindow& window);

    /// Behaviours
    void CreateStarship(StarshipFactory::STARSHIP_TYPE starshipType, int spacelane);
    void PaintMothership(sf::Color colour);
    void MoveStarship(int starshipIndex, sf::Vector2<float> positionOffset);

    /// Modifiers
    void SetMothershipPosition(sf::Vector2f pos);
    void SetMothershipRotation(float rot);
    void SetStarshipPosition(std::unique_ptr<IStarship>& ship, sf::Vector2f pos);
    void SetStarshipRotation(std::unique_ptr<IStarship>& ship, float rot);

    /// Accessors
    std::vector<std::unique_ptr<IStarship>> &GetStarships();
    std::unique_ptr<IStarship> &GetMothership();
    sf::FloatRect  GetMothershipBounds() const { return starship[0]->GetSpriteComponent().GetSprite().getGlobalBounds(); }
    int GetStarshipCount() { return starship.size(); }

    /// Event handling
    using BasicEnemyEvent = std::pair<EventID, std::function<void()>>;
    void AddBasicObserver(BasicEnemyEvent observer);
    using AgnosticEnemyEvent = std::pair<EventID, std::function<void(std::any)>>;
    void AddAgnosticObserver(AgnosticEnemyEvent observer);

private:
    void InvokeBasicEvent(EventID eventId);
    void InvokeAgnosticEvent(EventID eventId, const std::any& anyData);
    std::vector<std::unique_ptr<IStarship>> starship{};
    std::multimap<EventID, std::function<void()>> _basicObservers{};
    std::multimap<EventID, std::function<void(std::any)>> _agnosticObservers{};
   Chilli::PredefinedColours _predefinedColours;
   //sf::Color _teamColour;
};

#endif //STARFLEET_COMMAND_ENEMY_HPP
