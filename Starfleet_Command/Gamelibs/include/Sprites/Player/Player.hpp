#ifndef STARFLEET_COMMAND_PLAYER_HPP
#define STARFLEET_COMMAND_PLAYER_HPP
#include "Sprites/Starships/Starship.hpp"
#include "Sprites/Starships/StarshipFactory.hpp"
#include "ScrapMetalManager.hpp"
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
    Player(int startingScrapAmount, sf::Color teamColour);
   ~Player() = default;
    void EventHandler(sf::RenderWindow &window, sf::Event &event);
    void Update(sf::RenderWindow& window, sf::Time deltaTime);
    void RenderGameplaySprites(sf::RenderWindow& window);
    void RenderMinimapSprites(sf::RenderWindow& window);

    /// Behaviours
    void MoveStarship(int starshipIndex, sf::Vector2<float> positionOffset);
    void CreateStarship(StarshipFactory::STARSHIP_TYPE starshipType, int spacelane);
    void CreateScrapPopup(int scrapAmount, sf::Vector2<float> pos);

    /// Modifiers
    void SetMothershipPosition(sf::Vector2f pos);
    void SetStarshipPosition(std::unique_ptr<Starship>& ship, sf::Vector2f pos);
    void SetTeamColour(sf::Color colour);
    void SpendScrap(int buildCost);
    void CollectScrap(int scrapAmount);
    void SetScrapText(const std::string& scrapText);
    void SetScrapTextPosition(sf::Vector2<float> pos);

    /// Accessors
    std::vector<std::unique_ptr<Starship>> &GetStarships() { return starships; }
    std::unique_ptr<Starship> &GetMothership() { return starships[0]; }
    sf::FloatRect  GetMothershipBounds() const { return starships[0]->GetSpriteComponent().GetSprite().getGlobalBounds(); }
    sf::Vector2<float> GetMothershipPos() { return starships[0]->GetPos(); }
    int GetStarshipCount() { return starships.size(); }
    std::unique_ptr<ScrapMetalManager>& GetScrapMetalManager() { return _scrapMetalManager; }
    int GetCurrentScrapAmount() { return _scrapMetalManager->GetCurrentScrapAmount(); }
    sf::Color GetTeamColour() { return _teamColour; }

    /// Event handling
    using BasicPlayerEvent = std::pair<EventID, std::function<void()>>;
    using AgnosticPlayerEvent = std::pair<EventID, std::function<void(std::any)>>;
    void AddBasicObserver(BasicPlayerEvent observer);
    void AddAgnosticObserver(AgnosticPlayerEvent observer);

private:
    void InvokeBasicEvent(EventID eventId);
    void InvokeAgnosticEvent(EventID eventId, const std::any& anyData);
    std::vector<std::unique_ptr<Starship>> starships{};
    std::unique_ptr<ScrapMetalManager> _scrapMetalManager;
    sf::Vector2<float> _scrapTextPos;
    sf::Color _teamColour;
    std::multimap<EventID, std::function<void()>> _basicObservers{};
    std::multimap<EventID, std::function<void(std::any)>> _agnosticObservers{};
};

#endif //STARFLEET_COMMAND_PLAYER_HPP
