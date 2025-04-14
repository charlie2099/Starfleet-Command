#include "UpgradeScrapCollectionButton.hpp"

UpgradeScrapCollectionButton::UpgradeScrapCollectionButton(std::unique_ptr<ScrapMetalManager>& scrapMetalManager, sf::Color hoverColour)
: _scrapMetalManager(scrapMetalManager), _teamColour(hoverColour)
{
    _upgradeCost = 5000;

    _button = std::make_unique<Button>("Resources/Textures/scrap_drone_button.png");
    _button->SetColour(DEFAULT_BTN_COLOUR);
    _button->SetScale({0.15F, 0.15F});

    _nameText.setString("Upgrade Scrap Collection Service - " + std::to_string(_upgradeCost));
    _nameText.setFillColor(hoverColour);
    _nameText.setOutlineColor(sf::Color::Black);
    _nameText.setOutlineThickness(1);
    _nameText.setFont(Chilli::CustomFonts::GetBoldFont());
    _nameText.setCharacterSize(10);
}

void UpgradeScrapCollectionButton::EventHandler(sf::RenderWindow &window, sf::Event &event)
{
    if (_button->IsCursorHoveredOver() and _isAffordable)
    {
        if (event.type == sf::Event::MouseButtonPressed and event.mouseButton.button == sf::Mouse::Left)
        {
            _button->SetColour(SELECTED_BTN_COLOR);
            _scrapMetalManager->SpendScrap(_upgradeCost);
            _scrapMetalManager->SetScrapText("Scrap Metal: " + std::to_string(_scrapMetalManager->GetCurrentScrapAmount()));

            _upgradeLevel++;
            _upgradeCost *= 2;
            _nameText.setString("Upgrade Scrap Collection Service - " + std::to_string(_upgradeCost));
            // invoke upgrade purchase valid event?
        }
    }
}

void UpgradeScrapCollectionButton::Update(sf::RenderWindow &window, sf::Time deltaTime)
{
    if(_button->IsCursorHoveredOver())
    {
        _isNameVisible = true;
        _nameText.setFillColor(_isAffordable ? _teamColour : _predefinedColours.LIGHTRED);
    }

    if(not _button->IsCursorHoveredOver())
    {
        _isNameVisible = false;
    }

    if (_button->IsCursorHoveredOver() and _isAffordable)
    {
        _button->SetColour(HOVER_BTN_COLOR);
    }

    if (not _button->IsCursorHoveredOver() and _isAffordable)
    {
        _button->SetColour(DEFAULT_BTN_COLOUR);
    }

    if (not _button->IsCursorHoveredOver() and not _isAffordable)
    {
        _button->SetColour(_predefinedColours.LIGHTRED);
    }

    _button->Update(window);
    _button->SetPos(_position);

    _nameText.setPosition(_button->GetPos().x, _button->GetPos().y - 15.0F);
}

void UpgradeScrapCollectionButton::Render(sf::RenderWindow &window)
{
    _button->Render(window);
    if(_isNameVisible)
    {
        window.draw(_nameText);
    }
}

void UpgradeScrapCollectionButton::SetColour(sf::Color colour)
{
    _button->SetColour(colour);
}

void UpgradeScrapCollectionButton::SetPos(sf::Vector2<float> pos)
{
    _position = pos;
}
