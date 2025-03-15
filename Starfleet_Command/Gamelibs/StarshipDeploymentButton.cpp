#include "StarshipDeploymentButton.hpp"
#include "Sprites/Starships/StarshipFactory.hpp"

StarshipDeploymentButton::StarshipDeploymentButton(StarshipFactory::STARSHIP_TYPE starshipTypeToBeDeployed, sf::Color teamColour, std::unique_ptr<ScrapMetalManager> &playerScrapMetalManager)
: _playerScrapMetalManager(playerScrapMetalManager)
{
    _starshipTemplateToBeDeployed = StarshipFactory::CreateShip(starshipTypeToBeDeployed, 0); // NOTE: Useless 2nd argument | TODO: Create an overloaded function with just the first parameter/argument
    _starshipTemplateToBeDeployed->SetColour(teamColour);
    _starshipType = starshipTypeToBeDeployed;

    _button = std::make_unique<Button>("Resources/Textures/command_button_" + std::to_string(_starshipTemplateToBeDeployed->GetStarshipIndex()) + ".png");
    _button->SetColour(DEFAULT_BTN_COLOUR);
    _button->SetScale({0.20F, 0.20F});

    _costText.setString(std::to_string(_starshipTemplateToBeDeployed->GetBuildCost()));
    _costText.setFillColor(_starshipTemplateToBeDeployed->GetColour());
    _costText.setOutlineColor(sf::Color::Black);
    _costText.setOutlineThickness(1.0F);
    _costText.setFont(Chilli::CustomFonts::GetBoldFont());
    _costText.setCharacterSize(8);

    _cost = _starshipTemplateToBeDeployed->GetBuildCost();

    _nameText.setString(static_cast<std::string>(_starshipTemplateToBeDeployed->GetStarshipName()));
    _nameText.setFillColor(_starshipTemplateToBeDeployed->GetColour());
    _nameText.setOutlineColor(sf::Color::Black);
    _nameText.setOutlineThickness(1);
    _nameText.setFont(Chilli::CustomFonts::GetBoldFont());
    _nameText.setCharacterSize(10);

   _previewStarshipSprite.LoadSprite("Resources/Textures/starfleet_ship_" + std::to_string(_starshipTemplateToBeDeployed->GetStarshipIndex()) + ".png");
   _previewStarshipSprite.GetSprite().scale({0.05F, 0.05F});
   auto starshipToBeDeployedColour = _starshipTemplateToBeDeployed->GetColour();
   _previewStarshipSprite.GetSprite().setColor({starshipToBeDeployedColour.r, starshipToBeDeployedColour.g, starshipToBeDeployedColour.b, 125});
}

void StarshipDeploymentButton::EventHandler(sf::RenderWindow &window, sf::Event &event)
{
    bool starshipIsAffordable = _playerScrapMetalManager->GetCurrentScrapMetalAmount() >= _starshipTemplateToBeDeployed->GetBuildCost();

    if (_button->IsCursorHoveredOver() && starshipIsAffordable)
    {
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            if(!_isPlacingStarship/* && _starshipTypeDeploymentQueue.size() < STARSHIP_MAX_QUEUE_SIZE*/)
            {
                _isStarshipPreviewSpriteVisible = true;
                _isPlacingStarship = true;
            }
        }
    }

    /*if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left && _isPlacingStarship)
    {
        *//*for (int i = 0; i < _spaceLanes.size(); ++i)
        {
            if(_spaceLanes[i]->IsCursorHoveredOver())
            {
                BeginStarshipDeploymentProcess(i); // TODO: Handle this in GameScene class? Instead set a bool or fire off an event?
            }
        }*//*

        _button->SetColour(DEFAULT_BTN_COLOUR);
        _previewStarshipSprite.SetPos(_button->GetPos());
        _isStarshipPreviewSpriteVisible = false;
        _isPlacingStarship = false;
    }*/
}

void StarshipDeploymentButton::Update(sf::RenderWindow &window, sf::Time deltaTime)
{
    bool starshipIsAffordable = _playerScrapMetalManager->GetCurrentScrapMetalAmount() >= _starshipTemplateToBeDeployed->GetBuildCost();
    if(_button->IsCursorHoveredOver() /*&& !gameHud->GetStarshipDeploymentBar().InProgress()*/) // TODO: Hide name if starship deployment in progress | Get a ref to GameHUD through constructor?
    {
        _isNameVisible = true;
        _nameText.setFillColor(starshipIsAffordable ? _starshipTemplateToBeDeployed->GetColour() : _predefinedColours.LIGHTRED);
    }

    if(!_button->IsCursorHoveredOver())
    {
        _isNameVisible = false;
    }

    if (_button->IsCursorHoveredOver() && starshipIsAffordable)
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

    if (!_button->IsCursorHoveredOver() && starshipIsAffordable)
    {
        _button->SetColour(DEFAULT_BTN_COLOUR);
    }

    if (!_button->IsCursorHoveredOver() && !starshipIsAffordable)
    {
        _button->SetColour(_predefinedColours.LIGHTRED);
    }

    /*bool isQueueFull = _starshipTypeDeploymentQueue.size() >= STARSHIP_MAX_QUEUE_SIZE;
    if(isQueueFull)
    {
        _button->SetColour(_predefinedColours.LIGHTORANGE);
    }*/

    auto mousePos = sf::Mouse::getPosition(window); // Mouse _position relative to the window
    auto worldPositionOfMouse = window.mapPixelToCoords(mousePos, window.getView()); // Mouse _position translated into world coordinates // TODO: Replace with _mainView?

    _button->Update(window);
    _button->SetPos(_position);

    _nameText.setPosition(_button->GetPos().x, _button->GetPos().y - 15.0F);
    _costText.setPosition({_button->GetPos().x + _button->GetBounds().width - _costText.getGlobalBounds().width - 2.5F, _button->GetPos().y + 2.0F});

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
    window.draw(_costText);
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
    _button->SetColour(DEFAULT_BTN_COLOUR);
    _previewStarshipSprite.SetPos(_button->GetPos());
    _isStarshipPreviewSpriteVisible = false;
    _isPlacingStarship = false;
}

void StarshipDeploymentButton::SetPos(sf::Vector2<float> pos)
{
    _position = pos;
}

