#include "Sprites/UI/GUI/ScrapCollectionUpgradeButton.hpp"

ScrapCollectionUpgradeButton::ScrapCollectionUpgradeButton(int startingCost, std::unique_ptr<ScrapMetalManager>& scrapMetalManager, sf::Color hoverColour)
: _scrapMetalManager(scrapMetalManager), _teamColour(hoverColour)
{
    _upgradeCost = startingCost;

    _button = std::make_unique<ImageButton>("Resources/Textures/scrap_drone_button.png");
    _button->SetColour(_teamColour);
    _button->SetScale({0.15F, 0.15F});

    _nameText.setString("Upgrade Scrap Collection Service? - " + std::to_string(_upgradeCost));
    _nameText.setFillColor(hoverColour);
    _nameText.setOutlineColor(sf::Color::Black);
    _nameText.setOutlineThickness(1);
    _nameText.setFont(Chilli::CustomFonts::GetBoldFont());
    _nameText.setCharacterSize(10);
}

void ScrapCollectionUpgradeButton::EventHandler(sf::RenderWindow &window, sf::Event &event)
{
    _button->EventHandler(window, event);

    if (_button->IsMouseOver() and _isAffordable)
    {
        if (event.type == sf::Event::MouseButtonPressed and event.mouseButton.button == sf::Mouse::Left)
        {
            _button->SetColour(SELECTED_BTN_COLOR);
            _scrapMetalManager->SpendScrap(_upgradeCost);
            _scrapMetalManager->SetScrapText("Scrap Metal: " + std::to_string(_scrapMetalManager->GetCurrentScrapAmount()));

            _upgradeLevel++;
            _upgradeCost *= 2;
            _nameText.setString("Upgrade Scrap Collection Service? - " + std::to_string(_upgradeCost));
            // invoke upgrade purchase valid event?
        }
    }
}

void ScrapCollectionUpgradeButton::Update(sf::RenderWindow &window, sf::Time deltaTime)
{
    if(_button->IsMouseOver())
    {
        _isNameVisible = true;
        _nameText.setFillColor(_isAffordable ? _teamColour : sf::Color {_teamColour.r, _teamColour.g, _teamColour.b, 100});
    }

    if(not _button->IsMouseOver())
    {
        _isNameVisible = false;
    }

    if (_button->IsMouseOver() and _isAffordable)
    {
        _button->SetColour(HOVER_BTN_COLOR);
    }

    if (not _button->IsMouseOver() and _isAffordable)
    {
        _button->SetColour({_teamColour.r, _teamColour.g, _teamColour.b, 125 });
    }

    if (not _button->IsMouseOver() and not _isAffordable)
    {
        _button->SetColour({_teamColour.r, _teamColour.g, _teamColour.b, 50});
    }

    _button->Update(window);
    _button->SetPos(_position);

    _nameText.setPosition(_button->GetPos().x, _button->GetPos().y - 15.0F);
}

void ScrapCollectionUpgradeButton::Render(sf::RenderWindow &window)
{
    _button->Render(window);
    if(_isNameVisible)
    {
        window.draw(_nameText);
    }
}

void ScrapCollectionUpgradeButton::SetColour(sf::Color colour)
{
    _button->SetColour(colour);
}

void ScrapCollectionUpgradeButton::SetPos(sf::Vector2<float> pos)
{
    _position = pos;
}
