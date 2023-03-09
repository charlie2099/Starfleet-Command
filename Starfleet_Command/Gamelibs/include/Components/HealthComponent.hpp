#ifndef STARFLEET_COMMAND_HEALTHCOMPONENT_HPP
#define STARFLEET_COMMAND_HEALTHCOMPONENT_HPP
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <functional>
#include <map>
#include <any>
#include "Sprites/UI/Effects/DamagePopUpEffect.hpp"
#include "SpriteComponent.hpp"

class HealthComponent
{
public:
    enum EventID
    {
        HEALTH_DEPLETED = 1,
        HEALTH_UPDATED = 2,
    };
    /*struct EventParam
    {
        std::string stringData;
        float floatData;
        int intData;
        bool boolData;
    };*/

    //explicit HealthComponent(SpriteComponent& spriteComponent);
    void Update(sf::RenderWindow& window, sf::Time deltaTime);
    void Render(sf::RenderWindow& window);

    void TakeDamage(float amount, sf::Vector2f damageLocation); // TODO: Remove 2nd argument
    void ReplenishHealth(float amount);

    void SetHealth(int health);
    int GetHealth() const { return _health; }

    // Observer (for other classes to use to hook into and subscribe)
    using BasicHealthEvent = std::pair<EventID, std::function<void()>>;
    void AddBasicObserver(BasicHealthEvent observer);

    using AgnosticHealthEvent = std::pair<EventID, std::function<void(std::any)>>;
    void AddAgnosticObserver(AgnosticHealthEvent observer);

private:
    void InvokeSimpleEvent(EventID eventId);
    void InvokeAgnosticEvent(EventID eventId, const std::any& anyData);
    int _health{};
    std::vector<std::unique_ptr<DamagePopUpEffect>> _damagePopUpEffect;
    //SpriteComponent _spriteComponent;
    std::multimap<EventID, std::function<void()>> _basicObservers{};
    std::multimap<EventID, std::function<void(std::any)>> _agnosticObservers{};
};

#endif //STARFLEET_COMMAND_HEALTHCOMPONENT_HPP
