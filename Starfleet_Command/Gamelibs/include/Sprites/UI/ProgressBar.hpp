#ifndef STARFLEET_COMMAND_PROGRESSBAR_HPP
#define STARFLEET_COMMAND_PROGRESSBAR_HPP
#include <functional>
#include "Components/SpriteComponent.hpp"

class ProgressBar
{
public:
    enum EventID
    {
        TASK_STARTED = 1,
        TASK_COMPLETED = 2
    };

    ProgressBar();
    ~ProgressBar() =default;
    void Update(sf::RenderWindow& window, sf::Time time);
    void Render(sf::RenderWindow& window);

    void SetPosition(sf::Vector2<float> pos);
    void SetProgressSpeed(float speed);
    void SetProgressText(const std::string& text);
    void SetProgressStatus(bool status);
    void ResetProgress();

    using BasicProgressBarEvent = std::pair<EventID, std::function<void()>>;
    void AddBasicObserver(BasicProgressBarEvent observer);

    bool InProgress() const { return _taskIsProgressing; }
    sf::Rect<float> GetSize() { return _outsideBarSpriteComponent.GetSprite().getGlobalBounds(); }

private:
    void InvokeSimpleEvent(EventID eventId);
    SpriteComponent _outsideBarSpriteComponent;
    SpriteComponent _insideBarSpriteComponent;
    sf::Font _font;
    sf::Text _text;
    sf::Vector2f _position;
    std::multimap<EventID, std::function<void()>> _basicObservers{};
    float _progressSpeed = 0.2f;
    bool _taskIsProgressing = false;
    bool _taskIsComplete = false;
};

#endif //STARFLEET_COMMAND_PROGRESSBAR_HPP
