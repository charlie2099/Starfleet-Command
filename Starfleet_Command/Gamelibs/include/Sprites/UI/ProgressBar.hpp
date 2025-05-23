#ifndef STARFLEET_COMMAND_PROGRESSBAR_HPP
#define STARFLEET_COMMAND_PROGRESSBAR_HPP
#include "Components/SpriteComponent.hpp"
#include "Utility/CustomFonts.hpp"
#include <functional>

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

    void SetColour(sf::Color colour);
    void SetPosition(sf::Vector2<float> pos);
    void SetTimeToCompleteTask(float timeInSeconds);
    void SetProgressBarText(const std::string& text);
    void SetProgressBarWaitingText(const std::string& text);
    void SetProgressBarStatus(bool status);
    void ResetProgressBar();

    using BasicProgressBarEvent = std::pair<EventID, std::function<void()>>;
    void AddBasicObserver(BasicProgressBarEvent observer);

    bool InProgress() const { return _taskIsProgressing; }
    sf::Rect<float> GetSize() { return _outsideBarSpriteComponent.GetSprite().getGlobalBounds(); }
    sf::Vector2f GetOuterPos() { return _outerPosition; }

private:
    void InvokeSimpleEvent(EventID eventId);
    SpriteComponent _outsideBarSpriteComponent;
    SpriteComponent _insideBarSpriteComponent;
    sf::Text _text;
    std::string _progressBarText;
    sf::Text _waitingForNextTaskText;
    sf::Vector2f _innerPosition;
    sf::Vector2f _outerPosition;
    std::multimap<EventID, std::function<void()>> _basicObservers{};
    float _timeToCompleteTask = 5.0F;
    bool _taskIsProgressing = false;
    bool _taskIsComplete = false;
    float _elapsedTime = 0.0F;
};

#endif //STARFLEET_COMMAND_PROGRESSBAR_HPP
