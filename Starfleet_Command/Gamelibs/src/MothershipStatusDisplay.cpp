#include "MothershipStatusDisplay.hpp"

MothershipStatusDisplay::MothershipStatusDisplay(std::unique_ptr<Starship> &playerMothership, std::unique_ptr<Starship> &enemyMothership, sf::View &displayView)
: _displayView(displayView)
{
    _mothershipHealthBar[0] = std::make_unique<HealthBar>(playerMothership->GetHealthComponent(), true);
    _mothershipHealthBar[0]->SetMaxHealth(playerMothership->GetHealth());
    _mothershipHealthBar[0]->SetScale(0.4F, 0.15F);

    _mothershipHealthBar[1] = std::make_unique<HealthBar>(enemyMothership->GetHealthComponent(), true);
    _mothershipHealthBar[1]->SetMaxHealth(enemyMothership->GetHealth());
    _mothershipHealthBar[1]->SetScale(0.4F, 0.15F);

    _mothershipNameText[0].setString("Player Mothership");
    _mothershipNameText[0].setFillColor(playerMothership->GetColour());

    _mothershipNameText[1].setString("Enemy Mothership");
    _mothershipNameText[1].setFillColor(enemyMothership->GetColour());
    for (int i = 0; i < 2; ++i)
    {
        _mothershipNameText[i].setOutlineColor(sf::Color::Black);
        _mothershipNameText[i].setOutlineThickness(1);
        _mothershipNameText[i].setFont(Chilli::CustomFonts::GetBoldFont());
        _mothershipNameText[i].setCharacterSize(12);
    }
}

void MothershipStatusDisplay::Update(sf::RenderWindow &window, sf::Time deltaTime)
{
    _mothershipHealthBar[0]->SetPos({_displayView.getCenter().x - Constants::WINDOW_WIDTH/2.0F + 10.0F, _displayView.getCenter().y + Constants::WINDOW_HEIGHT/2.0F - 10.0F});
    _mothershipHealthBar[1]->SetPos({_displayView.getCenter().x + Constants::WINDOW_WIDTH/2.0F - 30.0F, _displayView.getCenter().y + Constants::WINDOW_HEIGHT/2.0F - 10.0F});

    _mothershipHealthBar[0]->Update(window, deltaTime);
    _mothershipHealthBar[1]->Update(window, deltaTime);

    _mothershipNameText[0].setPosition(_mothershipHealthBar[0]->GetPos().x + _mothershipHealthBar[0]->GetSpriteComponent().GetSprite().getGlobalBounds().width*2.5F, _mothershipHealthBar[0]->GetPos().y - 135.0F);
    _mothershipNameText[1].setPosition(_mothershipHealthBar[1]->GetPos().x - _mothershipHealthBar[1]->GetSpriteComponent().GetSprite().getGlobalBounds().width - 130.0F, _mothershipHealthBar[1]->GetPos().y - 135.0F);
}

void MothershipStatusDisplay::Render(sf::RenderWindow &window)
{
    for (int i = 0; i < 2; ++i)
    {
        _mothershipHealthBar[i]->Render(window);
        window.draw(_mothershipNameText[i]);
    }
}
