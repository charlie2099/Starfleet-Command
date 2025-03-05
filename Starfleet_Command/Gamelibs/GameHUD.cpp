#include "GameHUD.hpp"

GameHUD::GameHUD(HealthComponent& playerMothershipHealthComp, HealthComponent& enemyMothershipHealthComp, sf::Color playerMothershipColour, sf::Color enemyMothershipColour, std::basic_string<char> *starshipCosts, const sf::Font& font)
{
    _playerMothershipColour = playerMothershipColour;
    _font = font;

    for (int i = 0; i < 5; ++i)
    {
        _starshipCostText.emplace_back();
        _starshipCostText[i].setString(starshipCosts[i]);
        _starshipCostText[i].setFillColor(playerMothershipColour);
        _starshipCostText[i].setOutlineColor(sf::Color::Black);
        _starshipCostText[i].setOutlineThickness(1.0F);
        _starshipCostText[i].setFont(font);
        _starshipCostText[i].setCharacterSize(8);
    }

    InitStarshipNameButtonText();

    _mothershipHealthBar[0] = std::make_unique<HealthBar>(playerMothershipHealthComp);
    _mothershipHealthBar[0]->SetMaxHealth(playerMothershipHealthComp.GetHealth());
    _mothershipHealthBar[0]->SetScale(0.4F, 0.15F);

    _mothershipHealthBar[1] = std::make_unique<HealthBar>(enemyMothershipHealthComp);
    _mothershipHealthBar[1]->SetMaxHealth(enemyMothershipHealthComp.GetHealth());
    _mothershipHealthBar[1]->SetScale(0.4F, 0.15F);

    _mothershipNameText[0].setString("Player Mothership");
    _mothershipNameText[0].setFillColor(playerMothershipColour);

    _mothershipNameText[1].setString("Enemy Mothership");
    _mothershipNameText[1].setFillColor(enemyMothershipColour);
    for (int i = 0; i < 2; ++i)
    {
        _mothershipNameText[i].setOutlineColor(sf::Color::Black);
        _mothershipNameText[i].setOutlineThickness(1);
        _mothershipNameText[i].setFont(font);
        _mothershipNameText[i].setCharacterSize(14);
    }
}

void GameHUD::Update(sf::RenderWindow &window, sf::Time deltaTime, sf::Vector2<float> starshipBuilderButton1Pos, sf::Vector2<float> hoveredOverStarshipBuilderButton, sf::View mainView)
{
    _starshipAssemblyBar.SetPosition({starshipBuilderButton1Pos.x, starshipBuilderButton1Pos.y - _starshipAssemblyBar.GetSize().height * 2.75F});
    _starshipAssemblyBar.Update(window, deltaTime);
    _starshipNameButtonText.setPosition(hoveredOverStarshipBuilderButton.x, starshipBuilderButton1Pos.y - 20.0F);

    _mothershipHealthBar[0]->SetPos({mainView.getCenter().x - _mothershipHealthBar[0]->GetSpriteComponent().GetSprite().getGlobalBounds().width - Constants::WINDOW_WIDTH/3.0F, mainView.getCenter().y - _mothershipHealthBar[0]->GetSpriteComponent().GetSprite().getGlobalBounds().height/2.0F + Constants::WINDOW_HEIGHT/2.6F});
    _mothershipHealthBar[1]->SetPos({mainView.getCenter().x - _mothershipHealthBar[1]->GetSpriteComponent().GetSprite().getGlobalBounds().width + Constants::WINDOW_WIDTH/3.0F, mainView.getCenter().y - _mothershipHealthBar[1]->GetSpriteComponent().GetSprite().getGlobalBounds().height/2.0F + Constants::WINDOW_HEIGHT/2.6F});

    _mothershipHealthBar[0]->Update(window, deltaTime);
    _mothershipHealthBar[1]->Update(window, deltaTime);

    _mothershipNameText[0].setPosition(_mothershipHealthBar[0]->GetPos().x + _mothershipHealthBar[0]->GetSpriteComponent().GetSprite().getGlobalBounds().width/2.0F - 5.0F, _mothershipHealthBar[0]->GetPos().y + _mothershipNameText[0].getGlobalBounds().height + 5.0F);
    _mothershipNameText[1].setPosition(_mothershipHealthBar[1]->GetPos().x + _mothershipHealthBar[1]->GetSpriteComponent().GetSprite().getGlobalBounds().width/2.0F - 5.0F, _mothershipHealthBar[1]->GetPos().y + _mothershipNameText[1].getGlobalBounds().height + 5.0F);
}

void GameHUD::Render(sf::RenderWindow &window)
{
    for(auto& text : _starshipCostText)
    {
        window.draw(text);
    }
    /*for (auto& shipInfoPanel : _shipInfoPanels)
    {
        shipInfoPanel.Render(window);
    }*/
    window.draw(_starshipNameButtonText);
    _starshipAssemblyBar.Render(window);
    for (int i = 0; i < 2; ++i)
    {
        _mothershipHealthBar[i]->Render(window);
        window.draw(_mothershipNameText[i]);
    }
}

void GameHUD::InitStarshipNameButtonText()
{
    _starshipNameButtonText.setFillColor(_playerMothershipColour);
    _starshipNameButtonText.setOutlineColor(sf::Color::Black);
    _starshipNameButtonText.setOutlineThickness(1);
    _starshipNameButtonText.setFont(_font);
    _starshipNameButtonText.setCharacterSize(10);
}

