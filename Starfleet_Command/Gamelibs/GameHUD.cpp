#include "GameHUD.hpp"

GameHUD::GameHUD(std::unique_ptr<IStarship>& playerMothership, std::unique_ptr<IStarship>& enemyMothership, std::basic_string<char> *starshipCosts, sf::View& displayView)
{
    for (int i = 0; i < 5; ++i)
    {
        _starshipCostText.emplace_back();
        _starshipCostText[i].setString(starshipCosts[i]);
        _starshipCostText[i].setFillColor(playerMothership->GetColour());
        _starshipCostText[i].setOutlineColor(sf::Color::Black);
        _starshipCostText[i].setOutlineThickness(1.0F);
        _starshipCostText[i].setFont(Chilli::CustomFonts::GetBoldFont());
        _starshipCostText[i].setCharacterSize(8);
    }

    InitStarshipNameButtonText(playerMothership->GetColour());

    mothershipStatusDisplay = std::make_unique<MothershipStatusDisplay>(playerMothership, enemyMothership, displayView);
}

void GameHUD::Update(sf::RenderWindow &window, sf::Time deltaTime, sf::Vector2<float> starshipBuilderButton1Pos, sf::Vector2<float> hoveredOverStarshipBuilderButton)
{
    _starshipDeploymentBar.SetPosition({starshipBuilderButton1Pos.x, starshipBuilderButton1Pos.y - _starshipDeploymentBar.GetSize().height * 2.75F});
    _starshipDeploymentBar.Update(window, deltaTime);
    _starshipNameButtonText.setPosition(hoveredOverStarshipBuilderButton.x, starshipBuilderButton1Pos.y - 20.0F);

    mothershipStatusDisplay->Update(window, deltaTime);
}

void GameHUD::Render(sf::RenderWindow &window)
{
    if(_isVisible)
    {
        for(auto& text : _starshipCostText)
        {
            window.draw(text);
        }
        window.draw(_starshipNameButtonText);
        _starshipDeploymentBar.Render(window);
        mothershipStatusDisplay->Render(window);
    }
}

void GameHUD::Show()
{
    _isVisible = true;
}

void GameHUD::Hide()
{
    _isVisible = false;
}

void GameHUD::InitStarshipNameButtonText(sf::Color playerMothershipColour)
{
    _starshipNameButtonText.setFillColor(playerMothershipColour);
    _starshipNameButtonText.setOutlineColor(sf::Color::Black);
    _starshipNameButtonText.setOutlineThickness(1);
    _starshipNameButtonText.setFont(Chilli::CustomFonts::GetBoldFont());
    _starshipNameButtonText.setCharacterSize(10);
}


