#include "ScrapMetalManager.hpp"

ScrapMetalManager::ScrapMetalManager(sf::Color scrapTextColour, sf::Color popupTextColour, int startingScrap)
{
    _scrapMetalCounter = startingScrap;
    _popupTextColour = popupTextColour;

    _scrapMetalText.setString("Scrap Metal: " + std::to_string(_scrapMetalCounter));
    _scrapMetalText.setFillColor(scrapTextColour);
    _scrapMetalText.setOutlineColor(sf::Color::Black);
    _scrapMetalText.setOutlineThickness(1);
    _scrapMetalText.setFont(Chilli::CustomFonts::GetBoldFont());
    _scrapMetalText.setCharacterSize(11);
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
    auto& scrapPopupText = _scrapMetalPopupText.emplace_back(std::make_unique<PopupText>(buildCost, popupPosition));
    scrapPopupText->SetColour(_popupTextColour);
    scrapPopupText->SetCharSize(15);
    scrapPopupText->SetIconImage("Resources/Textures/pixil-frame-0.png");
    scrapPopupText->SetText("+");
}

void ScrapMetalManager::SetScrapText(const std::string& scrapMetalText)
{
    _scrapMetalText.setString(scrapMetalText);
}

void ScrapMetalManager::SetTextPosition(float xPos, float yPos)
{
    _scrapMetalText.setPosition(xPos, yPos);
}

