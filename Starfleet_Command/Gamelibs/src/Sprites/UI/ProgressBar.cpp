#include <iostream>
#include "Sprites/UI/ProgressBar.hpp"

ProgressBar::ProgressBar()
{
    _outsideBarSpriteComponent.LoadSprite("Resources/Textures/panel_image.png");
    _outsideBarSpriteComponent.GetSprite().setScale(1.20f, 0.20f);
    _outsideBarSpriteComponent.GetSprite().setColor(sf::Color::White);
    _outsideBarSpriteComponent.SetPos({25, 25});

    _font.loadFromFile("Resources/Fonts/Orbitron/Orbitron-Regular.ttf");
    _text.setString("Task In Progress...");
    _text.setFont(_font);
    _text.setCharacterSize(12);
    _text.setPosition(_outsideBarSpriteComponent.GetPos().x + 6, _outsideBarSpriteComponent.GetPos().y + _outsideBarSpriteComponent.GetSprite().getGlobalBounds().height + 5);

    _insideBarSpriteComponent.LoadSprite("Resources/Textures/panel_image.png");
    _insideBarSpriteComponent.GetSprite().setScale(1.175f, 0.125f);
    _insideBarSpriteComponent.GetSprite().setColor(sf::Color::Cyan);
    _insideBarSpriteComponent.GetSprite().setOrigin(0, 0);
    //auto xPos = _outsideBarSpriteComponent.GetPos().x + _outsideBarSpriteComponent.GetSprite().getGlobalBounds().width/2 - spriteComponent2.GetSprite().getGlobalBounds().width/2;
    auto xPos = _outsideBarSpriteComponent.GetPos().x + 5;
    auto yPos = _outsideBarSpriteComponent.GetPos().y + _outsideBarSpriteComponent.GetSprite().getGlobalBounds().height / 2 - _insideBarSpriteComponent.GetSprite().getGlobalBounds().height / 2;
    _insideBarSpriteComponent.SetPos({xPos, yPos});
    _position = _insideBarSpriteComponent.GetPos();

    _insideBarSpriteComponent.GetSprite().setScale(0.0f, 0.125f);
}

void ProgressBar::Update(sf::RenderWindow& window, sf::Time time)
{
    if(_taskIsProgressing)
    {
        if(_insideBarSpriteComponent.GetSprite().getScale().x == 0.0F)
        {
            InvokeSimpleEvent(EventID::TASK_STARTED);
        }

        if(_insideBarSpriteComponent.GetSprite().getScale().x <= 1.175f)
        {
            _insideBarSpriteComponent.SetPos({_position.x, _position.y});
            auto scale_x = _insideBarSpriteComponent.GetSprite().getScale().x + _progressSpeed * time.asSeconds();
            auto scale_y = 0.125f;
            _insideBarSpriteComponent.GetSprite().setScale(scale_x, scale_y);
        }
        else
        {
            _insideBarSpriteComponent.GetSprite().setScale(0.0f, 0.125f);
            _taskIsComplete = true;
            _taskIsProgressing = false;
            InvokeSimpleEvent(EventID::TASK_COMPLETED);
        }
    }
}

void ProgressBar::Render(sf::RenderWindow &window)
{
    if(_taskIsProgressing)
    {
        window.draw(_outsideBarSpriteComponent.GetSprite());
        window.draw(_insideBarSpriteComponent.GetSprite());
        window.draw(_text);
    }
}

void ProgressBar::SetPosition(sf::Vector2<float> pos)
{
    _outsideBarSpriteComponent.SetPos(pos);
    _text.setPosition(_outsideBarSpriteComponent.GetPos().x + 6, _outsideBarSpriteComponent.GetPos().y + _outsideBarSpriteComponent.GetSprite().getGlobalBounds().height + 5);
    //auto xPos = _outsideBarSpriteComponent.GetPos().x + _outsideBarSpriteComponent.GetSprite().getGlobalBounds().width/2 - spriteComponent2.GetSprite().getGlobalBounds().width/2;
    auto xPos = _outsideBarSpriteComponent.GetPos().x + 5;
    auto yPos = _outsideBarSpriteComponent.GetPos().y + _outsideBarSpriteComponent.GetSprite().getGlobalBounds().height / 2 - _insideBarSpriteComponent.GetSprite().getGlobalBounds().height / 2;
    _insideBarSpriteComponent.SetPos({xPos, yPos});
    _position = _insideBarSpriteComponent.GetPos();
}

void ProgressBar::SetProgressSpeed(float speed)
{
    _progressSpeed = speed;
}

void ProgressBar::SetProgressText(const std::string& text)
{
    _text.setString(text);
}

void ProgressBar::SetProgressStatus(bool status)
{
    _taskIsProgressing = status;
}

void ProgressBar::ResetProgress()
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





