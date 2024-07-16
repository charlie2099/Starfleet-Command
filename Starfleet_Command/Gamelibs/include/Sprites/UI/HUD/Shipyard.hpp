#ifndef STARFLEET_COMMAND_HUD_HPP
#define STARFLEET_COMMAND_HUD_HPP
#include <functional>

#include "Components/SpriteComponent.hpp"

class Shipyard
{
public:
    enum EventID
    {
        TRAINING_STARTED = 1,
        TRAINING_COMPLETED = 2
    };

    Shipyard();
    ~Shipyard() = default;
    void Update(sf::RenderWindow& window, sf::Time time);
    void Render(sf::RenderWindow& window);

    void SetPosition(sf::Vector2<float> pos);
    void SetTrainingSpeed(float speed);
    void SetTrainingStatus(bool status);
    void SetTrainingCompletedStatus(bool status);
    void SetDeployText(const std::string& text);

    SpriteComponent& GetSpriteComponent() { return _spriteComponent; }
    float GetTrainingSpeed() const { return _trainingSpeed; }
    bool IsTraining() const { return _isTraining; }
    bool IsTrainingComplete() const { return _trainingIsComplete; }

    // Observer (for other classes to use to hook into and subscribe)
    using BasicShipyardEvent = std::pair<EventID, std::function<void()>>;
    void AddBasicObserver(BasicShipyardEvent observer);

private:
    void InvokeSimpleEvent(EventID eventId);

    SpriteComponent _spriteComponent;
    SpriteComponent _spriteComponent2;
    sf::Font _font;
    sf::Text _deployText;
    sf::Vector2f _position;
    float _trainingSpeed = 0.2f;
    bool _isTraining = false;
    bool _trainingIsComplete = false;
    std::multimap<EventID, std::function<void()>> _basicObservers{};
};

#endif //STARFLEET_COMMAND_HUD_HPP
