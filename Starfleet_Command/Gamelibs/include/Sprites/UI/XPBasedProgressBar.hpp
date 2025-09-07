#ifndef STARFLEET_COMMAND_XPBASEDPROGRESSBAR_HPP
#define STARFLEET_COMMAND_XPBASEDPROGRESSBAR_HPP
#include "Components/SpriteComponent.hpp"
#include "Utility/CustomFonts.hpp"
#include <functional>

class XPBasedProgressBar
{
public:
    enum EventID
    {
        TASK_STARTED = 1,
        TASK_COMPLETED = 2
    };

    XPBasedProgressBar();
    ~XPBasedProgressBar() =default;
    void Update(sf::RenderWindow& window, sf::Time time);
    void Render(sf::RenderWindow& window);

    void SetColour(sf::Color colour);
    void SetPosition(sf::Vector2<float> pos);
    void SetProgressBarText(const std::string& text);
    void SetProgressBarWaitingText(const std::string& text);
    void AddProgress(float amount);
    void ResetProgressBar();

    using BasicProgressBarEvent = std::pair<EventID, std::function<void()>>;
    void AddBasicObserver(BasicProgressBarEvent observer);

    float GetProgressAmountRemaining() const { return _remainingAmountToCompleteTask; }
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
    bool _taskIsComplete = false;
    float _totalAmountToCompleteTask = 1000;
    float _remainingAmountToCompleteTask = _totalAmountToCompleteTask;
    float _currentTaskProgress = 0;
    float _elapsedTime = 0.0F;
};

#endif //STARFLEET_COMMAND_XPBASEDPROGRESSBAR_HPP
