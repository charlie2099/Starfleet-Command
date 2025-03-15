#include "GameHUD.hpp"

GameHUD::GameHUD(std::unique_ptr<IStarship>& playerMothership, std::unique_ptr<IStarship>& enemyMothership, sf::View& displayView)
{
    mothershipStatusDisplay = std::make_unique<MothershipStatusDisplay>(playerMothership, enemyMothership, displayView);
}

void GameHUD::Update(sf::RenderWindow &window, sf::Time deltaTime, sf::Vector2<float> starshipBuilderButton1Pos)
{
    _starshipDeploymentBar.SetPosition({starshipBuilderButton1Pos.x, starshipBuilderButton1Pos.y - _starshipDeploymentBar.GetSize().height * 2.75F});
    _starshipDeploymentBar.Update(window, deltaTime);
    mothershipStatusDisplay->Update(window, deltaTime);
}

void GameHUD::Render(sf::RenderWindow &window)
{
    if(_isVisible)
    {
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



