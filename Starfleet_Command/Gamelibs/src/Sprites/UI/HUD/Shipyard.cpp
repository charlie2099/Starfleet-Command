#include <utility>

#include "Sprites/UI/HUD/Shipyard.hpp"

Shipyard::Shipyard()
{
    _spriteComponent.LoadSprite("Resources/Textures/panel_image.png");
    _spriteComponent.GetSprite().setScale(1.20f,0.20f);
    _spriteComponent.GetSprite().setColor(sf::Color::White);
    _spriteComponent.SetPos({25, 25});

    _font.loadFromFile("Resources/Fonts/Orbitron/Orbitron-Regular.ttf");
    _deployText.setString("Ship preparing to deploy...");
    //_text.setString("Preparing to deploy ship from the landing bay...");
    _deployText.setFont(_font);
    _deployText.setCharacterSize(12);
    _deployText.setPosition(_spriteComponent.GetPos().x+6, _spriteComponent.GetPos().y + _spriteComponent.GetSprite().getGlobalBounds().height+5);

    _spriteComponent2.LoadSprite("Resources/Textures/panel_image.png");
    _spriteComponent2.GetSprite().setScale(1.175f,0.125f);
    _spriteComponent2.GetSprite().setColor(sf::Color::Cyan);
    _spriteComponent2.GetSprite().setOrigin(0,0);
    //auto xPos = _spriteComponent.GetPos().x + _spriteComponent.GetSprite().getGlobalBounds().width/2 - spriteComponent2.GetSprite().getGlobalBounds().width/2;
    auto xPos = _spriteComponent.GetPos().x + 5;
    auto yPos = _spriteComponent.GetPos().y + _spriteComponent.GetSprite().getGlobalBounds().height/2 - _spriteComponent2.GetSprite().getGlobalBounds().height/2;
    _spriteComponent2.SetPos({xPos, yPos});
    _position = _spriteComponent2.GetPos();

    _spriteComponent2.GetSprite().setScale(0.0f,0.125f);
}

void Shipyard::Update(sf::RenderWindow& window, sf::Time time)
{
    if(_isTraining)
    {
        if(_spriteComponent2.GetSprite().getScale().x <= 1.175f)
        {
            _spriteComponent2.SetPos({_position.x, _position.y});
            auto scale_x = _spriteComponent2.GetSprite().getScale().x + _trainingSpeed * time.asSeconds();
            auto scale_y = 0.125f;
            _spriteComponent2.GetSprite().setScale(scale_x, scale_y);
        }
        else
        {
            _spriteComponent2.GetSprite().setScale(0.0f, 0.125f);
            _trainingIsComplete = true;
            InvokeSimpleEvent(EventID::TRAINING_COMPLETED);
            _isTraining = false;
        }
    }
}

void Shipyard::Render(sf::RenderWindow &window)
{
    window.draw(_spriteComponent.GetSprite());
    window.draw(_spriteComponent2.GetSprite());
    if(_isTraining)
    {
        window.draw(_deployText);
    }
}

void Shipyard::SetPosition(sf::Vector2<float> pos)
{
    _spriteComponent.SetPos(pos);
    _deployText.setPosition(_spriteComponent.GetPos().x+6, _spriteComponent.GetPos().y + _spriteComponent.GetSprite().getGlobalBounds().height+5);
    //auto xPos = _spriteComponent.GetPos().x + _spriteComponent.GetSprite().getGlobalBounds().width/2 - spriteComponent2.GetSprite().getGlobalBounds().width/2;
    auto xPos = _spriteComponent.GetPos().x + 5;
    auto yPos = _spriteComponent.GetPos().y + _spriteComponent.GetSprite().getGlobalBounds().height/2 - _spriteComponent2.GetSprite().getGlobalBounds().height/2;
    _spriteComponent2.SetPos({xPos, yPos});
    _position = _spriteComponent2.GetPos();
}

void Shipyard::SetTrainingStatus(bool status)
{
    _isTraining = status;
}

void Shipyard::SetTrainingCompletedStatus(bool status)
{
    _trainingIsComplete = status;
}

void Shipyard::SetTrainingSpeed(float speed)
{
    _trainingSpeed = speed;
}

void Shipyard::SetDeployText(const std::string& text)
{
    _deployText.setString(text);
}

void Shipyard::AddBasicObserver(BasicShipyardEvent observer)
{
    _basicObservers.insert(observer);
}

void Shipyard::InvokeSimpleEvent(EventID eventId)
{
    /// Invokes the callback function assigned to the specified event id?
    auto range = _basicObservers.equal_range(eventId);
    for(auto iter = range.first; iter != range.second; ++iter)
    {
        iter->second();
    }
}