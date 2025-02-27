#include "ScrapMetalManager.hpp"

ScrapMetalManager::ScrapMetalManager(sf::Font& font, sf::Color scrapTextColour, sf::Color popupTextColour, int startingScrap)
{
    _scrapMetalText.setString("Scrap Metal: " + std::to_string(_scrapMetalCounter));
    _scrapMetalText.setFillColor(scrapTextColour);
    _scrapMetalText.setOutlineColor(sf::Color::Black);
    _scrapMetalText.setOutlineThickness(1);
    _scrapMetalText.setFont(font);
    _scrapMetalText.setCharacterSize(11);
    _popupTextColour = popupTextColour;

    _scrapMetalCounter = startingScrap;
}

void ScrapMetalManager::Update(sf::RenderWindow &window, sf::Time deltaTime)
{
    for(auto& popup : _scrapMetalPopupText)
    {
        popup->Update(window, deltaTime);
    }

    for (int i = 0; i < _scrapMetalPopupText.size(); ++i)
    {
        if(_scrapMetalPopupText[i]->IsFaded())
        {
            _scrapMetalPopupText.erase(_scrapMetalPopupText.begin() + i);
        }
    }
}

void ScrapMetalManager::Render(sf::RenderWindow &window)
{
    window.draw(_scrapMetalText);
    for(auto& popup : _scrapMetalPopupText)
    {
        popup->Render(window);
    }
}

void ScrapMetalManager::CollectScrap(int amount)
{
    _scrapMetalCounter += amount;
}

void ScrapMetalManager::SpendScrap(int amount)
{
    _scrapMetalCounter -= amount;
}

void ScrapMetalManager::CreatePopup(int buildCost, sf::Vector2<float> popupPosition)
{
    auto& popupText = _scrapMetalPopupText.emplace_back(std::make_unique<PopupText>(buildCost, popupPosition));
    popupText->SetColour(_popupTextColour);
    popupText->SetCharSize(15);
    popupText->SetIconImage("Resources/Textures/pixil-frame-0.png");
}

void ScrapMetalManager::UpdateScrapText(const std::string& scrapMetalText)
{
    _scrapMetalText.setString(scrapMetalText);
}

void ScrapMetalManager::SetTextPosition(float xPos, float yPos)
{
    _scrapMetalText.setPosition(xPos, yPos);
}

