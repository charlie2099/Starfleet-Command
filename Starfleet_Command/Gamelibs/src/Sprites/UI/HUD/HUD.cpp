#include "Sprites/UI/HUD/HUD.hpp"

HUD::HUD()
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
    spriteComponent2.GetSprite().setColor(sf::Color::Red);
    auto xPos = spriteComponent.GetPos().x + spriteComponent.GetSprite().getGlobalBounds().width/2 - spriteComponent2.GetSprite().getGlobalBounds().width/2;
    auto yPos = spriteComponent.GetPos().y + spriteComponent.GetSprite().getGlobalBounds().height/2 - spriteComponent2.GetSprite().getGlobalBounds().height/2;
    spriteComponent2.SetPos({xPos, yPos});
    _position = spriteComponent2.GetPos();

    spriteComponent2.GetSprite().setScale(0.0f,0.125f);
}

void HUD::Update(sf::RenderWindow& window, sf::Time time)
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

void HUD::Render(sf::RenderWindow &window)
{
    window.draw(spriteComponent.GetSprite());
    window.draw(spriteComponent2.GetSprite());
    if(_isTraining)
    {
        window.draw(text);
    }
}

void HUD::SetTrainingStatus(bool status)
{
    _isTraining = status;
}

void HUD::SetTrainingCompletedStatus(bool status)
{
    _trainingIsComplete = status;
}

void HUD::SetTrainingSpeed(float speed)
{
    _trainingSpeed = speed;
}

