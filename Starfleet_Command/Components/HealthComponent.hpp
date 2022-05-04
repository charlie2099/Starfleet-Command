#ifndef STARFLEET_COMMAND_HEALTHCOMPONENT_HPP
#define STARFLEET_COMMAND_HEALTHCOMPONENT_HPP
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <functional>
#include <map>

class HealthComponent
{
public:
    enum EventID
    {
        HEALTH_DEPLETED = 1,
    };

    HealthComponent() = default;
    ~HealthComponent() = default;
    void Update(sf::RenderWindow& window, sf::Time time);

    // Modifiers
    void SetHealth(float health);

    // Accessors
    float GetHealth() const { return _health; }

    // Observer (for other classes to utilise to hook into and subscribe)
    using HealthEvent = std::pair<EventID, std::function<void()>>;
    void AddObserver(HealthEvent observer);

private:
    // PanelComponent _background?
    // PanelComponent _bar?
    float _health;
    std::multimap<EventID, std::function<void()>> _observers{};
};

#endif //STARFLEET_COMMAND_HEALTHCOMPONENT_HPP
