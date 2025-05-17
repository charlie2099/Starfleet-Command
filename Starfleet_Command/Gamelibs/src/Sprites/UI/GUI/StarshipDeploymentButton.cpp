#include "Sprites/UI/GUI/StarshipDeploymentButton.hpp"
#include "Sprites/Starships/StarshipFactory.hpp"

StarshipDeploymentButton::StarshipDeploymentButton(StarshipFactory::STARSHIP_TYPE starshipTypeToBeDeployed, sf::Color hoverColour)
: _teamColour(hoverColour)
{
    _starshipTemplateToBeDeployed = StarshipFactory::CreateShip(starshipTypeToBeDeployed);
    _starshipTemplateToBeDeployed->SetColour(hoverColour);
    _starshipType = starshipTypeToBeDeployed;

    _button = std::make_unique<ImageButton>("Resources/Textures/command_button_" + std::to_string(_starshipTemplateToBeDeployed->GetStarshipIndex()) + ".png");
    _button->SetColour(_teamColour);
    _button->SetScale({0.15F, 0.15F});

    _nameText.setString(static_cast<std::string>(_starshipTemplateToBeDeployed->GetStarshipName() + " - " + std::to_string(_starshipTemplateToBeDeployed->GetBuildCost())));
    _nameText.setFillColor(hoverColour);
    _nameText.setOutlineColor(sf::Color::Black);
    _nameText.setOutlineThickness(1);
    _nameText.setFont(Chilli::CustomFonts::GetBoldFont());
    _nameText.setCharacterSize(10);

   _previewStarshipSprite.LoadSprite("Resources/Textures/starfleet_ship_" + std::to_string(_starshipTemplateToBeDeployed->GetStarshipIndex()) + ".png");
   _previewStarshipSprite.GetSprite().scale({0.05F, 0.05F});
   _previewStarshipSprite.GetSprite().setColor({hoverColour.r, hoverColour.g, hoverColour.b, 125});
}

void StarshipDeploymentButton::EventHandler(sf::RenderWindow& window, sf::Event& event)
{
    if (_button->IsMouseOver() and _isAffordable)
    {
        if (event.type == sf::Event::MouseButtonPressed and event.mouseButton.button == sf::Mouse::Left)
        {
            if(not _isPlacingStarship)
            {
                _isStarshipPreviewSpriteVisible = true;
                _isPlacingStarship = true;
            }
        }
    }
}

void StarshipDeploymentButton::Update(sf::RenderWindow &window, sf::Time deltaTime)
{
    if(_button->IsMouseOver())
    {
        if(_mouseOverTimer < _mouseOverCheckRate)
        {
            _isNameVisible = true;
        }
        _nameText.setFillColor(_isAffordable ? _teamColour : sf::Color {_teamColour.r, _teamColour.g, _teamColour.b, 100});

        _mouseOverTimer = _mouseOverClock.getElapsedTime().asSeconds();
        if(_mouseOverTimer >= _mouseOverCheckRate)
        {
            _isNameVisible = false;
        }
    }

    if(not _button->IsMouseOver())
    {
        _mouseOverClock.restart();
        _isNameVisible = false;
    }

    if (_button->IsMouseOver() and _isAffordable)
    {
        if (_isPlacingStarship)
        {
            _button->SetColour(SELECTED_BTN_COLOR);
        }
        else
        {
            _button->SetColour(HOVER_BTN_COLOR);
        }
    }

    if (not _button->IsMouseOver() and _isAffordable)
    {
        _button->SetColour({_teamColour.r, _teamColour.g, _teamColour.b, 160 });
    }

    if (not _button->IsMouseOver() and not _isAffordable)
    {
        _button->SetColour({_teamColour.r, _teamColour.g, _teamColour.b, 50});
    }

    auto mousePos = sf::Mouse::getPosition(window); // Mouse _innerPosition relative to the window
    auto worldPositionOfMouse = window.mapPixelToCoords(mousePos, window.getView()); // Mouse _innerPosition translated into world coordinates // TODO: Replace with _gameplayView?

    _button->Update(window);
    _button->SetPos(_position);

    _nameText.setPosition(_button->GetPos().x, _button->GetPos().y - 15.0F);

    if(_isStarshipPreviewSpriteVisible)
    {
        auto xPos = worldPositionOfMouse.x - _previewStarshipSprite.GetSprite().getGlobalBounds().width / 2.0F;
        auto yPos = worldPositionOfMouse.y - _previewStarshipSprite.GetSprite().getGlobalBounds().height / 2.0F;
        _previewStarshipSprite.SetPos({xPos, yPos});
    }
}

void StarshipDeploymentButton::Render(sf::RenderWindow &window)
{
    _button->Render(window);
    if(_isNameVisible)
    {
        window.draw(_nameText);
    }
    if(_isStarshipPreviewSpriteVisible)
    {
        _previewStarshipSprite.Render(window);
    }
}

void StarshipDeploymentButton::ResetAfterStarshipPlacement()
{
    _button->SetColour(_teamColour);
    _previewStarshipSprite.SetPos(_button->GetPos());
    _isStarshipPreviewSpriteVisible = false;
    _isPlacingStarship = false;
}

void StarshipDeploymentButton::SetColour(sf::Color colour)
{
    _button->SetColour(colour);
}

void StarshipDeploymentButton::SetPos(sf::Vector2<float> pos)
{
    _position = pos;
}

