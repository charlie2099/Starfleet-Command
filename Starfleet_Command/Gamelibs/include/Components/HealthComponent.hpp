#ifndef STARFLEET_COMMAND_HEALTHCOMPONENT_HPP
#define STARFLEET_COMMAND_HEALTHCOMPONENT_HPP
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <functional>
#include <map>
#include <any>

class HealthComponent
{
public:
    enum EventID
    {
        HEALTH_DEPLETED = 1,
        HEALTH_UPDATED = 2,
    };
    struct EventParam
    {
        std::string stringData;
        float floatData;
        int intData;
        bool boolData;
    };

    void Update(sf::RenderWindow& window, sf::Time time);

    void TakeDamage(float amount);
    void ReplenishHealth(float amount);

    void SetHealth(int health);
    int GetHealth() const { return _health; }

    // Observer (for other classes to use to hook into and subscribe)
    using HealthEvent = std::pair<EventID, std::function<void()>>;
    void AddObserver(HealthEvent observer);

    using HealthEvent1Param = std::pair<EventID, std::function<void(std::any)>>;
    void AddObserver1Param(HealthEvent1Param observer);

private:
    void InvokeEvent(EventID eventId);
    void InvokeEvent(EventID eventId, const std::any& anyData);
    int _health;
    std::multimap<EventID, std::function<void()>> _observers{};
    std::multimap<EventID, std::function<void(std::any)>> _observers1Param{};
};

#endif //STARFLEET_COMMAND_HEALTHCOMPONENT_HPP
