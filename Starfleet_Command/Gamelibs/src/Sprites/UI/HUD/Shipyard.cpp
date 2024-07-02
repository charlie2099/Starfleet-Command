#include "Sprites/UI/HUD/Shipyard.hpp"

Shipyard::Shipyard()
{
    spriteComponent.LoadSprite("Resources/Textures/panel_image.png");
    spriteComponent.GetSprite().setScale(1.20f,0.20f);
    spriteComponent.GetSprite().setColor(sf::Color::White);
    spriteComponent.SetPos({25, 25});

    font.loadFromFile("Resources/Fonts/Orbitron/Orbitron-Regular.ttf");
    text.setString("Ship preparing to deploy...");
    //text.setString("Preparing to deploy ship from the landing bay...");
    text.setFont(font);
    text.setCharacterSize(12);
    text.setPosition(spriteComponent.GetPos().x+6, spriteComponent.GetPos().y + spriteComponent.GetSprite().getGlobalBounds().height+5);

    spriteComponent2.LoadSprite("Resources/Textures/panel_image.png");
    spriteComponent2.GetSprite().setScale(1.175f,0.125f);
    spriteComponent2.GetSprite().setColor(sf::Color::Cyan);
    spriteComponent2.GetSprite().setOrigin(0,0);
    //auto xPos = spriteComponent.GetPos().x + spriteComponent.GetSprite().getGlobalBounds().width/2 - spriteComponent2.GetSprite().getGlobalBounds().width/2;
    auto xPos = spriteComponent.GetPos().x + 5;
    auto yPos = spriteComponent.GetPos().y + spriteComponent.GetSprite().getGlobalBounds().height/2 - spriteComponent2.GetSprite().getGlobalBounds().height/2;
    spriteComponent2.SetPos({xPos, yPos});
    _position = spriteComponent2.GetPos();

    spriteComponent2.GetSprite().setScale(0.0f,0.125f);
}

void Shipyard::Update(sf::RenderWindow& window, sf::Time time)
{
    if(_isTraining)
    {
        if(spriteComponent2.GetSprite().getScale().x <= 1.175f)
        {
            spriteComponent2.SetPos({_position.x, _position.y});
            auto scale_x = spriteComponent2.GetSprite().getScale().x + _trainingSpeed * time.asSeconds();
            auto scale_y = 0.125f;
            spriteComponent2.GetSprite().setScale(scale_x, scale_y);
        }
        else
        {
            spriteComponent2.GetSprite().setScale(0.0f, 0.125f);
            _trainingIsComplete = true;
            _isTraining = false;
        }
    }
}

void Shipyard::Render(sf::RenderWindow &window)
{
    if(_isTraining)
    {
        window.draw(spriteComponent.GetSprite());
        window.draw(spriteComponent2.GetSprite());
        window.draw(text);
    }
}

void Shipyard::SetPosition(sf::Vector2<float> pos)
{
    spriteComponent.SetPos(pos);
    text.setPosition(spriteComponent.GetPos().x+6, spriteComponent.GetPos().y + spriteComponent.GetSprite().getGlobalBounds().height+5);
    //auto xPos = spriteComponent.GetPos().x + spriteComponent.GetSprite().getGlobalBounds().width/2 - spriteComponent2.GetSprite().getGlobalBounds().width/2;
    auto xPos = spriteComponent.GetPos().x + 5;
    auto yPos = spriteComponent.GetPos().y + spriteComponent.GetSprite().getGlobalBounds().height/2 - spriteComponent2.GetSprite().getGlobalBounds().height/2;
    spriteComponent2.SetPos({xPos, yPos});
    _position = spriteComponent2.GetPos();
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

