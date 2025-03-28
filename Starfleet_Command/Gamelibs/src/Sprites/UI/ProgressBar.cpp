#include <iostream>
#include "Sprites/UI/ProgressBar.hpp"

ProgressBar::ProgressBar()
{
    _outsideBarSpriteComponent.LoadSprite("Resources/Textures/panel_image2.png"); // TODO: Replace with sf::RectangleShape
    _outsideBarSpriteComponent.GetSprite().setScale(1.20f, 0.20f);
    _outsideBarSpriteComponent.GetSprite().setColor({50,50, 50, 125});
    _outsideBarSpriteComponent.SetPos({25, 25});
    _outerPosition = _outsideBarSpriteComponent.GetPos();

    _text.setString("Task In Progress...");
    _text.setFont(Chilli::CustomFonts::GetBoldFont());
    _text.setCharacterSize(12);
    _text.setPosition(_outsideBarSpriteComponent.GetPos().x + 6, _outsideBarSpriteComponent.GetPos().y + _outsideBarSpriteComponent.GetSprite().getGlobalBounds().height + 5);
    _text.setOutlineColor(sf::Color::Black);

    _insideBarSpriteComponent.LoadSprite("Resources/Textures/panel_image2.png"); // TODO: Replace with sf::RectangleShape
    _insideBarSpriteComponent.GetSprite().setScale(1.175f, 0.125f);
    _insideBarSpriteComponent.GetSprite().setColor(sf::Color::Cyan);
    _insideBarSpriteComponent.GetSprite().setOrigin(0, 0);
    //auto xPos = _outsideBarSpriteComponent.GetPos().x + _outsideBarSpriteComponent.GetSprite().getGlobalBounds().width/2 - spriteComponent2.GetSprite().getGlobalBounds().width/2;
    auto xPos = _outsideBarSpriteComponent.GetPos().x;
    auto yPos = _outsideBarSpriteComponent.GetPos().y + _outsideBarSpriteComponent.GetSprite().getGlobalBounds().height / 2 - _insideBarSpriteComponent.GetSprite().getGlobalBounds().height / 2;
    _insideBarSpriteComponent.SetPos({xPos, yPos});
    _innerPosition = _insideBarSpriteComponent.GetPos();

    _insideBarSpriteComponent.GetSprite().setScale(0.0f, 0.125f);
}

void ProgressBar::Update(sf::RenderWindow& window, sf::Time time)
{
    if(_taskIsProgressing)
    {
        if(_elapsedTime == 0.0F)
        {
            InvokeSimpleEvent(EventID::TASK_STARTED);
        }

        _elapsedTime += time.asSeconds();

        // Calculate progress based on elapsed time and total deployment time
        float progress = std::min(1.175f, (_elapsedTime / _timeToCompleteTask) * 1.175f);

        _insideBarSpriteComponent.SetPos({_innerPosition.x, _innerPosition.y});
        _insideBarSpriteComponent.GetSprite().setScale(progress, 0.125f);

        if(_elapsedTime >= _timeToCompleteTask)
        {
            _insideBarSpriteComponent.GetSprite().setScale(1.175F, 0.125F);
            _insideBarSpriteComponent.GetSprite().setScale(0.0f, 0.125f);
            _taskIsComplete = true;
            _taskIsProgressing = false;
            _elapsedTime = 0.0F;
            InvokeSimpleEvent(EventID::TASK_COMPLETED);
        }
    }
}

void ProgressBar::Render(sf::RenderWindow &window)
{
    if(_taskIsProgressing)
    {
        window.draw(_outsideBarSpriteComponent.GetSprite()); // QUESTION: Better with or without outer bar?
        window.draw(_insideBarSpriteComponent.GetSprite());
        window.draw(_text);
    }
}

void ProgressBar::SetColour(sf::Color colour)
{
    _insideBarSpriteComponent.GetSprite().setColor(colour);
    _text.setFillColor(colour);
}

void ProgressBar::SetPosition(sf::Vector2<float> pos)
{
    _outsideBarSpriteComponent.SetPos(pos);
    _text.setPosition(_outsideBarSpriteComponent.GetPos().x + 6, _outsideBarSpriteComponent.GetPos().y + _outsideBarSpriteComponent.GetSprite().getGlobalBounds().height + 5.0F);
    //auto xPos = _outsideBarSpriteComponent.GetPos().x + _outsideBarSpriteComponent.GetSprite().getGlobalBounds().width/2 - spriteComponent2.GetSprite().getGlobalBounds().width/2;
    auto xPos = _outsideBarSpriteComponent.GetPos().x + 5;
    auto yPos = _outsideBarSpriteComponent.GetPos().y + _outsideBarSpriteComponent.GetSprite().getGlobalBounds().height / 2 - _insideBarSpriteComponent.GetSprite().getGlobalBounds().height / 2;
    _insideBarSpriteComponent.SetPos({xPos, yPos});
    _innerPosition = _insideBarSpriteComponent.GetPos();
    _outerPosition = _outsideBarSpriteComponent.GetPos();
}

void ProgressBar::SetTimeToCompleteTask(float timeInSeconds)
{
    _timeToCompleteTask = timeInSeconds;
}

void ProgressBar::SetProgressBarText(const std::string& text)
{
    _text.setString(text);
}

void ProgressBar::SetProgressBarStatus(bool status)
{
    _taskIsProgressing = status;
}

void ProgressBar::ResetProgressBar()
{
    _taskIsComplete = false;
    _taskIsProgressing = false;
}

void ProgressBar::AddBasicObserver(ProgressBar::BasicProgressBarEvent observer)
{
    _basicObservers.insert(observer);
}

void ProgressBar::InvokeSimpleEvent(EventID eventId)
{
    /// Invokes the callback function assigned to the specified event id?
    auto range = _basicObservers.equal_range(eventId);
    for(auto iter = range.first; iter != range.second; ++iter)
    {
        iter->second();
    }
}





