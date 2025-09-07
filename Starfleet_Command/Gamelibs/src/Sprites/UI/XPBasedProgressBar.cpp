#include "Sprites/UI/XPBasedProgressBar.hpp"

XPBasedProgressBar::XPBasedProgressBar()
{
    _outsideBarSpriteComponent.LoadSprite("Resources/Textures/panel_image2.png"); // TODO: Replace with sf::RectangleShape
    _outsideBarSpriteComponent.GetSprite().setScale(1.20f, 0.20f);
    _outsideBarSpriteComponent.GetSprite().setColor({50,50, 50, 125});
    _outsideBarSpriteComponent.SetPos({25, 25});
    _outerPosition = _outsideBarSpriteComponent.GetPos();

    SetProgressBarText("XP until next reward:");
    _text.setString(_progressBarText + " (" + std::to_string((int)(_remainingAmountToCompleteTask)) + ")");
    _text.setFont(Chilli::CustomFonts::GetBoldFont());
    _text.setCharacterSize(12);
    _text.setPosition(_outsideBarSpriteComponent.GetPos().x + 6, _outsideBarSpriteComponent.GetPos().y + _outsideBarSpriteComponent.GetSprite().getGlobalBounds().height + 5);
    _text.setOutlineColor(sf::Color::Black);

    _waitingForNextTaskText.setString("Waiting for next task");

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

void XPBasedProgressBar::Update(sf::RenderWindow& window, sf::Time time)
{
    if(_elapsedTime == 0.0F)
    {
        InvokeSimpleEvent(EventID::TASK_STARTED);
    }
}

void XPBasedProgressBar::Render(sf::RenderWindow &window)
{
    window.draw(_outsideBarSpriteComponent.GetSprite());
    window.draw(_insideBarSpriteComponent.GetSprite());
    window.draw(_text);
}

void XPBasedProgressBar::SetColour(sf::Color colour)
{
    _insideBarSpriteComponent.GetSprite().setColor(colour);
    _text.setFillColor(colour);
}

void XPBasedProgressBar::SetPosition(sf::Vector2<float> pos)
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

void XPBasedProgressBar::SetProgressBarText(const std::string& text)
{
    _progressBarText = text;
    _text.setString(_progressBarText);
}

void XPBasedProgressBar::SetProgressBarWaitingText(const std::string &text)
{
    _waitingForNextTaskText.setString(text);
}

void XPBasedProgressBar::AddProgress(float amount)
{
    _currentTaskProgress += amount;
    _remainingAmountToCompleteTask -= amount;

    _text.setString(_progressBarText + " (" + std::to_string((int)(_remainingAmountToCompleteTask)) + ")");

    float progressPercentage = _currentTaskProgress / _totalAmountToCompleteTask;
    float progress = progressPercentage * 1.175; // Scale to bar width

    _insideBarSpriteComponent.SetPos({_innerPosition.x, _innerPosition.y});
    _insideBarSpriteComponent.GetSprite().setScale(progress, 0.125f);

    if(_remainingAmountToCompleteTask <= 0)
    {
        _insideBarSpriteComponent.GetSprite().setScale(1.175F, 0.125F);
        _insideBarSpriteComponent.GetSprite().setScale(0.0f, 0.125f);
        _taskIsComplete = true;
        _currentTaskProgress = 0;
        _remainingAmountToCompleteTask = _totalAmountToCompleteTask;
        _elapsedTime = 0.0F;
        _text.setString(_waitingForNextTaskText.getString());
        InvokeSimpleEvent(EventID::TASK_COMPLETED);
    }
}

void XPBasedProgressBar::ResetProgressBar()
{
    _taskIsComplete = false;
}

void XPBasedProgressBar::AddBasicObserver(XPBasedProgressBar::BasicProgressBarEvent observer)
{
    _basicObservers.insert(observer);
}

void XPBasedProgressBar::InvokeSimpleEvent(EventID eventId)
{
    /// Invokes the callback function assigned to the specified event id?
    auto range = _basicObservers.equal_range(eventId);
    for(auto iter = range.first; iter != range.second; ++iter)
    {
        iter->second();
    }
}

