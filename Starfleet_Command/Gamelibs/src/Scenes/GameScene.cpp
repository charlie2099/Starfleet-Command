#include "Scenes/GameScene.hpp"

bool GameScene::Init()
{
    InitRandomDistributions();
    InitBackground();
    InitShipSpawnerButtons();
    InitPlayerCreditsText();
    InitWavesRemainingText();
    InitEnemiesRemainingText();
    InitPlayerFlagship();
    InitSpaceLanes();
    InitEnemyShips();
    InitMainView();
    InitMinimapView();
    InitMainViewBorder();
    InitMinimapBorder();

    light_fighter = std::make_unique<LightFighter>();
    heavy_fighter = std::make_unique<HeavyFighter>();
    support_ship = std::make_unique<SupportShip>();
    destroyer = std::make_unique<Destroyer>();
    battleship = std::make_unique<Battleship>();

    _buttonShipDictionary[_shipSpawnerButtons[0].get()] = light_fighter.get();
    _buttonShipDictionary[_shipSpawnerButtons[1].get()] = heavy_fighter.get();
    _buttonShipDictionary[_shipSpawnerButtons[2].get()] = support_ship.get();
    _buttonShipDictionary[_shipSpawnerButtons[3].get()] = destroyer.get();
    _buttonShipDictionary[_shipSpawnerButtons[4].get()] = battleship.get();

    for(int i = 0; i < _shipSpawnerButtons.size(); i++)
    {
        std::cout << _buttonShipDictionary[_shipSpawnerButtons[i].get()]->GetTrainingSpeed() << std::endl;
    }



    _shipDragSpriteVisuals[0].LoadSprite("Resources/Textures/starfleet_ship_fighter.png");
    _shipDragSpriteVisuals[0].GetSprite().scale({0.05F, 0.05F});

    _shipDragSpriteVisuals[1].LoadSprite("Resources/Textures/starfleet_ship_repair.png");
    _shipDragSpriteVisuals[1].GetSprite().scale({0.05F, 0.05F});

    _shipDragSpriteVisuals[2].LoadSprite("Resources/Textures/starfleet_ship_scout.png");
    _shipDragSpriteVisuals[2].GetSprite().scale({0.3F, 0.3F});

    _shipDragSpriteVisuals[3].LoadSprite("Resources/Textures/starfleet_ship_destroyer.png");
    _shipDragSpriteVisuals[3].GetSprite().scale({0.05F, 0.05F});

    _shipDragSpriteVisuals[4].LoadSprite("Resources/Textures/starfleet_ship_battleship.png");
    _shipDragSpriteVisuals[4].GetSprite().scale({0.05F, 0.05F});

    for (auto& shipDragVisual : _shipDragSpriteVisuals)
    {
        auto playerShipColour = _player.GetShips()[0]->GetColour();
        shipDragVisual.GetSprite().setColor({playerShipColour.r, playerShipColour.g, playerShipColour.b, 125});
    }

    sf::Vector2f playerFlagshipPos = _player.GetFlagship()->GetPos();
    _mainView.setCenter(playerFlagshipPos.x + 350.0F, playerFlagshipPos.y);

    InitEvents();

    /// StarshipClass newClassType(texture, color, health, damage);
    /// Starship newShip(newClassType);
    /// starshipFighter.AddBehaviour(ChaseBehaviour());
    /// starshipFighter.AddBehaviour(FleeBehaviour());
    /// starshipFighter.AddWeapon(PlasmaCannonWeapon());
    /// starshipFighter.AddWeapon(TorpedoLauncherWeapon());
    ///
    /// for(auto& starship : starships)
    ///     starship.Update();
    ///     starship.Render();

  /*  /// Whenever a SHIP_SPAWNED event occurs, the TestFncForObserverToCall method is called
    /// A SHIP_SPAWNED event is invoked in the player CreateShip method.
    auto callbackFnc1 = std::bind(&TestClass::TestFncForObserverToCall, testClass);
    _player.AddBasicObserver({Player::EventID::SHIP_SPAWNED, callbackFnc1});

    auto callbackFnc2 = std::bind(&TestClass::OnEvent, testClass, std::placeholders::_1);
    _player.AddObserver2({Player::EventID::SHIP_SPAWNED, callbackFnc2});*/

    // FACTORY PATTERN
    //starship = StarshipFactory::CreateShip(StarshipFactory::LIGHTFIGHTER);

    return true;
}

void GameScene::EventHandler(sf::RenderWindow& window, sf::Event& event)
{
    auto mouse_pos = sf::Mouse::getPosition(window); // Mouse position relative to the window
    auto worldPositionOfMouse = window.mapPixelToCoords(mouse_pos, _mainView); // Mouse position translated into world coordinates

    // Opening Minimap
    if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Key::M)
    {
        // If map is not open then scale it up, otherwise scale it down
        !_isMapOpen ? RescaleMinimap(1.5F, 1.5F) : RescaleMinimap(1.0F, 1.0F);
        _isMapOpen = !_isMapOpen;
    }

    if(_minimapBorder.getGlobalBounds().contains(worldPositionOfMouse))
    {
        if (event.type == sf::Event::MouseWheelScrolled)
        {
            float zoomFactor = (event.mouseWheelScroll.delta > 0) ? 0.9f : 1.1f;
            float newZoomLevel = _currentZoomLevel * zoomFactor;

            // Check if the new zoom level is within bounds
            if (newZoomLevel >= 0.15f && newZoomLevel <= 1.0f) // MAX ZOOM | MIN ZOOM
            {
                // Convert mouse position to world coordinates relative to minimap
                sf::Vector2f beforeZoom = window.mapPixelToCoords(mouse_pos, _minimapView);

                // Apply the zoom
                _minimapView.zoom(zoomFactor);

                // Update the current zoom level
                _currentZoomLevel = newZoomLevel;

                // Convert mouse position to world coordinates after zoom
                sf::Vector2f afterZoom = window.mapPixelToCoords(mouse_pos, _minimapView);

                // Calculate the difference and adjust the view center
                sf::Vector2f offset = beforeZoom - afterZoom;
                sf::Vector2f newCenter = _minimapView.getCenter() + offset;
                _minimapView.setCenter(ConstrainViewCenter(newCenter));
            }
        }

        // Allow moving focus only when zoomed in
        if (_currentZoomLevel < 1.0f)
        {
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                _isDragging = true;
                _initialMousePosition = mouse_pos;
            }

            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
            {
                _isDragging = false;
            }

            if (event.type == sf::Event::MouseMoved && _isDragging)
            {
                sf::Vector2i currentMousePosition = sf::Mouse::getPosition(window);
                sf::Vector2f delta = window.mapPixelToCoords(_initialMousePosition, _minimapView) -
                                     window.mapPixelToCoords(currentMousePosition, _minimapView);

                sf::Vector2f newCenter = _minimapView.getCenter() + delta;
                _minimapView.setCenter(ConstrainViewCenter(newCenter));
                _initialMousePosition = currentMousePosition;
            }
        }
    }
    else
    {
        ResetMinimapView();
    }




    const sf::Color DEFAULT_COLOR = {255, 255, 255, 100};
    const sf::Color HOVER_COLOR = _predefinedColours.LIGHTBLUE;
    const sf::Color SELECTED_COLOR = {153, 210, 242, 150};
    for (int i = 0; i < _shipSpawnerButtons.size(); i++)
    {
        // Check if the cursor is hovering over the button
        if (_shipSpawnerButtons[i]->IsCursorHoveredOver())
        {
            // If the button is the currently selected one and dragging, keep it in the selected color
            if (_dragging && i == _shipSelectedIndex)
            {
                _shipSpawnerButtons[i]->SetColour(SELECTED_COLOR);
            }
            else
            {
                // Highlight the button in light blue if not dragging
                _shipSpawnerButtons[i]->SetColour(HOVER_COLOR);

                // Check if the button is clicked
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && !_dragging && !_shipyard.IsTraining())
                {
                    // Set the selected button index and change its color
                    _shipSelectedIndex = i;
                    _shipSpawnerButtons[_shipSelectedIndex]->SetColour(SELECTED_COLOR);
                    _isDragVisualVisible = true;
                    _dragging = true;
                }
            }
        }
        else
        {
            // Revert the button color to default if not hovered and not the selected button
            if (!_dragging || i != _shipSelectedIndex)
            {
                _shipSpawnerButtons[i]->SetColour(DEFAULT_COLOR);
            }
        }
    }

    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left && _dragging)
    {
        for (int i = 0; i < spaceLanes.size(); ++i)
        {
            if(spaceLanes[i]->IsCursorHoveredOver())
            {
                auto& assignedShipToButton = _buttonShipDictionary[_shipSpawnerButtons[_shipSelectedIndex].get()];
                _shipyard.SetTrainingSpeed(assignedShipToButton->GetTrainingSpeed());
                _playerCreditsCounter -= static_cast<int>(assignedShipToButton->GetShipCost());
                _shipyard.SetDeployText("Deploying " + assignedShipToButton->GetShipName());
                _playerCreditsText.setString("Credits: " + std::to_string(_playerCreditsCounter));
                _shipyard.SetTrainingStatus(true);
                spaceLaneSelected = i;
                // TODO: Invoke an agnostic event here notifying subscribers that a ship is currently training?
            }
        }

        // Revert the selected button color to default
        _shipSpawnerButtons[_shipSelectedIndex]->SetColour({255, 255, 255, 100});
        _shipDragSpriteVisuals[_shipSelectedIndex].SetPos(_shipSpawnerButtons[_shipSelectedIndex]->GetPos());
        _isDragVisualVisible = false;
        _dragging = false;
    }
}

void GameScene::Update(sf::RenderWindow& window, sf::Time deltaTime)
{
    auto mousePos = sf::Mouse::getPosition(window); // Mouse _position relative to the window
    auto worldPositionOfMouse = window.mapPixelToCoords(mousePos, _mainView); // Mouse _position translated into world coordinates

    const float FLAGSHIP_FOCUS_OFFSET = 290.0F;

    // Thresholds for detecting mouse proximity to window borders
    const float EDGE_OFFSET = 200.0F;
    auto mouseProximityToLeftWindowEdge = EDGE_OFFSET;
    auto mouseProximityToRightWindowEdge = window.getSize().x - EDGE_OFFSET;

    // Current boundaries of the view in world coordinates
    auto viewportLeftBoundary = _mainView.getCenter().x - _mainView.getSize().x / 2.0F;
    auto viewportRightBoundary = _mainView.getCenter().x + _mainView.getSize().x / 2.0F;

    // Viewport movement conditions
    bool isMouseNearLeftEdge = mousePos.x <= mouseProximityToLeftWindowEdge && mousePos.x > 0;
    bool isMouseNearRightEdge = mousePos.x >= mouseProximityToRightWindowEdge && mousePos.x < window.getSize().x;
    bool isViewportLeftEdgeWithinFlagshipFocus = viewportLeftBoundary > (_player.GetFlagship()->GetPos().x - FLAGSHIP_FOCUS_OFFSET);
    bool isViewportRightEdgeWithinRightEdgeOfLevelBounds = viewportRightBoundary < Constants::LEVEL_WIDTH;
    bool isMouseYposWithinWindowBounds = mousePos.y >= 0 and mousePos.y <= window.getSize().y;

    const float VP_SCROLL_SPEED = 300.0F;
    if(isMouseNearLeftEdge and isViewportLeftEdgeWithinFlagshipFocus and isMouseYposWithinWindowBounds)
    {
        _mainView.move(-VP_SCROLL_SPEED * deltaTime.asSeconds(), 0.0F);
    }
    else if(isMouseNearRightEdge and isViewportRightEdgeWithinRightEdgeOfLevelBounds and isMouseYposWithinWindowBounds)
    {
        _mainView.move(VP_SCROLL_SPEED * deltaTime.asSeconds(), 0.0F);
    }
    // Set main view to focus on the player flagship if the flagship passes a set distance from the left view boundary
    else if(_player.GetFlagship()->GetPos().x > viewportLeftBoundary + FLAGSHIP_FOCUS_OFFSET)
    {
        _mainView.setCenter(_player.GetFlagship()->GetPos().x + 350.0F, _player.GetFlagship()->GetPos().y);
    }


    _minimapBorder.setPosition(_mainView.getCenter().x - _mainView.getSize().x/2.0F + 13.0F, _mainView.getCenter().y - _mainView.getSize().y/2.0F + 15.0F);
    //_minimapBorder.setPosition(_mainView.getCenter().x - _minimapBorder.getSize().x/2.0F, _mainView.getCenter().y - _mainView.getSize().y/2.0F + 7.0F);
    //_minimapBorder.setPosition(_mainView.getCenter().x - _mainView.getSize().x/2.0F + 13.0F, _mainView.getCenter().y + _minimapBorder.getSize().y/2.0F + 22.0F);
    _mainViewBorder.setPosition(_mainView.getCenter().x - _mainViewBorder.getSize().x/2.0F, _mainView.getCenter().y - _mainViewBorder.getSize().y/2.0F);

    // TODO: Clean up
    const float NUM_OF_BUTTONS = 5;
    for (int i = 0; i < NUM_OF_BUTTONS; ++i)
    {
        const float SPACING = 10;
        //const float OFFSET = NUM_OF_BUTTONS * SPACING;
        auto button_bounds = _shipSpawnerButtons[i]->GetBounds();
        auto xPos = 0.0F;
        auto yPos = 0.0F;

        // TODO: Clean this up
        if(i < 3) // Row 1
        {
            xPos = _minimapBorder.getPosition().x + (i * (button_bounds.width+SPACING));
            yPos = _minimapBorder.getPosition().y + _minimapBorder.getSize().y + SPACING;
        }
        else if(i >= 3) // Row 2
        {
            xPos = _minimapBorder.getPosition().x + ((i-3) * (button_bounds.width+SPACING));
            yPos = _minimapBorder.getPosition().y + _minimapBorder.getSize().y + button_bounds.height + (SPACING*2.0F);
        }
        /*else if(i >= 2 && i < 4) // Row 2
        {
            xPos = _minimapBorder.getPosition().x + ((i-2) * (button_bounds.width+SPACING));
            yPos = _minimapBorder.getPosition().y + _minimapBorder.getSize().y + button_bounds.height + (SPACING*2.0F);
        }
        else if(i >= 4) // Row 3
        {
            xPos = _minimapBorder.getPosition().x + ((i-4) * (button_bounds.width+SPACING));
            yPos = _minimapBorder.getPosition().y + _minimapBorder.getSize().y + (button_bounds.height*2.0F) + (SPACING*3.0F);
        }*/

        _shipSpawnerButtons[i]->SetPos({xPos, yPos});
        _shipSpawnerButtons[i]->Update(window);

        /*if() // TODO: If ship cost associated with button is less than player's credit ammount, lower transparency of button
        {
            _shipSpawnerButtons[i]->GetSpriteComponent().GetSprite().setColor(sf::Color(255, 255, 255, 50));
            _player.GetShips()[i]->GetShipCost()
            // Dictionary of command buttons and ship variations?
        }*/

        // Ship cost text alignment to command buttons
        auto btnPos = _shipSpawnerButtons[i]->GetPos();
        auto btnBounds = _shipSpawnerButtons[i]->GetBounds();
        auto text_xPos = btnPos.x + btnBounds.width - (_ship_cost_text[i].getGlobalBounds().width+2);
        _ship_cost_text[i].setPosition(text_xPos, btnPos.y + 5);
    }

    _playerCreditsText.setPosition(_shipSpawnerButtons[0]->GetPos().x, _shipSpawnerButtons[_shipSpawnerButtons.size() - 1]->GetPos().y + _shipSpawnerButtons[_shipSpawnerButtons.size() - 1]->GetBounds().height * 1.1F);
    _wavesRemainingText.setPosition(_mainView.getCenter().x - _wavesRemainingText.getGlobalBounds().width/2.0F, _mainView.getCenter().y - Constants::WINDOW_WIDTH/4.0F);
    _enemiesRemainingText.setPosition(_wavesRemainingText.getPosition().x + _wavesRemainingText.getGlobalBounds().width/2.0F - _enemiesRemainingText.getGlobalBounds().width/2.0F, _wavesRemainingText.getPosition().y + _wavesRemainingText.getGlobalBounds().height + 5.0F);
    //_shipyard.SetPosition({_mainView.getCenter().x - _mainView.getSize().x/2.0F + 15.0F, _mainView.getCenter().y - _mainView.getSize().y/2.0F + 15.0F});
    //_shipyard.SetPosition({_shipSpawnerButtons[0]->GetSpriteComponent().GetPos().x, _shipSpawnerButtons[0]->GetSpriteComponent().GetPos().y - _shipyard.GetSpriteComponent().GetSprite().getGlobalBounds().height*2.75F});
    _shipyard.SetPosition({_minimapBorder.getPosition().x + _minimapBorder.getSize().x + 10.0F, _minimapBorder.getPosition().y});
    _shipyard.Update(window, deltaTime);
    _cursor.Update(window, deltaTime);
    _cursor.SetCursorPos(window, _mainView);
    _player.Update(window, deltaTime);
    _enemy.Update(window, deltaTime);
    //starship->Update(window, deltaTime);

    // Check if player cursor is over their capital ship
    for(auto& playerShip : _player.GetShips())
    {
        if(playerShip != nullptr)
        {
            // Highlight player ship on mouse hover
            if(Chilli::Vector::BoundsCheck(worldPositionOfMouse, playerShip->GetSpriteComponent().GetSprite().getGlobalBounds()))
            {
                _cursor.SetCursorType(Chilli::Cursor::Type::SELECTED, sf::Color::Cyan);
                //player_ship->GetSpriteComponent().GetSprite().setColor(sf::Color::Cyan);
            }
            else
            {
                _cursor.SetCursorType(Chilli::Cursor::DEFAULT, sf::Color::White);
                //player_ship->GetSpriteComponent().GetSprite().setColor(_predefinedColours.LIGHTBLUE);
            }
        }
    }

    // Move player capital ship
    if(_player.GetFlagship() != nullptr)
    {
        auto& playerFlagship = _player.GetFlagship()->GetSpriteComponent().GetSprite();
        playerFlagship.move(_player.GetFlagship()->GetSpeed() * deltaTime.asSeconds(), 0);
    }

    // Move enemy capital ship
    if(_enemy.GetFlagship() != nullptr)
    {
        auto& enemyFlagship = _enemy.GetFlagship()->GetSpriteComponent().GetSprite();
        enemyFlagship.move(_enemy.GetFlagship()->GetSpeed() * deltaTime.asSeconds() * -1, 0);
    }

    /// Spawn enemies every x amount of time passed
    // Initialise enemySpawnTimer to the current elapsed time
    if(_enemySpawnTimer < _clock.getElapsedTime().asSeconds())
    {
        _enemySpawnTimer = _clock.getElapsedTime().asSeconds();
    }
    // If current elapsed time has reached enemySpawnTimer, spawn new enemy
    if(_clock.getElapsedTime().asSeconds() >= _enemySpawnTimer)
    {
        for (int i = 0; i < 1; ++i)
        {
            int randomShipType = _distributions[ENEMY_SHIP_TYPE](_generator);
            _enemy.CreateShip(static_cast<StarshipFactory::SHIP_TYPE>(randomShipType));
            auto& ship = _enemy.GetShips()[_enemy.GetShips().size()-1];
            int randomLane = _distributions[SPACELANE](_generator);
            auto ship_xPos = spaceLanes[randomLane]->GetPos().x + spaceLanes[randomLane]->GetSize().x;
            auto ship_yPos = spaceLanes[randomLane]->GetPos().y + spaceLanes[randomLane]->GetSize().y / 2.0F;
            _enemy.SetFleetPosition(ship, {ship_xPos, ship_yPos});
            _enemy.SetFleetRotation(ship, 180);
            _enemy.PaintShip(ship, _predefinedColours.LIGHTGREEN);
        }
        _enemySpawnTimer += _enemySpawnRate;
    }

    // Move enemy ships, and shoot at player ships when in range
    for (int i = 1; i < _enemy.GetShips().size(); ++i)
    {
        auto& enemySprite = _enemy.GetShips()[i]->GetSpriteComponent().GetSprite();
        enemySprite.move(_enemy.GetShips()[i]->GetSpeed() * deltaTime.asSeconds() * -1, 0);

        for(int j = 0; j < _player.GetShips().size(); j++)
        {
            if(_player.GetShips()[j] != nullptr)
            {
                auto& playerSprite = _player.GetShips()[j]->GetSpriteComponent().GetSprite();

                // Move towards and shoot at player ship if less than 400 pixels away from it
                if(Chilli::Vector::Distance(playerSprite.getPosition(), enemySprite.getPosition()) <= _enemy.GetShips()[i]->GetAttackRange())
                {
                    _enemy.GetShips()[i]->SetSpeed(25);
                    //_enemy.GetShips()[i]->MoveTowards(playerSprite.getPosition(), deltaTime);

                    auto& enemyShips = _enemy.GetShips()[i];
                    enemyShips->ShootAt(enemyShips->GetProjectileType(), enemyShips->GetFireRate(), playerSprite.getPosition());
                }

                for(int k = 0; k < _enemy.GetShips()[i]->GetProjectile().size(); k++)
                {
                    auto& enemyBullet = _enemy.GetShips()[i]->GetProjectile()[k]->GetSpriteComponent();

                    // Destroy projectiles if collided with enemy ship, and inflict damage to enemy ship
                    if(playerSprite.getGlobalBounds().intersects(enemyBullet.GetSprite().getGlobalBounds()))
                    {
                        //UpdateDistribution("Ship damage", 10, 80);
                        int randDamage = _distributions[SHIP_DAMAGE](_generator);

                        //_enemy.GetShips()[j]->TakeDamage(_player.GetShips()[i]->GetDamage());
                        _player.GetShips()[j]->GetHealthComponent().TakeDamage(randDamage * _enemy.GetShips()[i]->GetDamageScaleFactor(),
                                                                              _player.GetShips()[j]->GetSpriteComponent().GetPos());
                        _enemy.GetShips()[i]->GetProjectile().erase(_enemy.GetShips()[i]->GetProjectile().begin() + k);
                    }
                }
            }
        }
    }

    // Move player ships, shoot at enemy ships when in range, and destroy player projectiles when too far away
    for(int i = 1; i < _player.GetShips().size(); i++)
    {
        // If said player ship hasn't been destroyed
        if(_player.GetShips()[i] != nullptr)
        {
            auto& playerSprite = _player.GetShips()[i]->GetSpriteComponent().GetSprite();

            for(int j = 0; j < _player.GetShips()[i]->GetProjectile().size(); j++)
            {
                auto& playerBullet = _player.GetShips()[i]->GetProjectile()[j]->GetSpriteComponent();

                // Destroy player projectiles when they have travelled too far
                if(Chilli::Vector::Distance(playerSprite.getPosition(), playerBullet.GetPos()) > Constants::WINDOW_WIDTH)
                {
                    _player.GetShips()[i]->GetProjectile().erase(_player.GetShips()[i]->GetProjectile().begin() + j);
                }
            }

            for(int j = 0; j < _enemy.GetShips().size(); j++)
            {
                auto& enemySprite = _enemy.GetShips()[j]->GetSpriteComponent().GetSprite();

                // Move towards and shoot at enemy ship if less than 400 pixels away from it
                if(Chilli::Vector::Distance(playerSprite.getPosition(), enemySprite.getPosition()) <= _player.GetShips()[i]->GetAttackRange())
                {
                    _player.GetShips()[i]->SetSpeed(25);
                    //_player.GetShips()[i]->MoveTowards(enemySprite.getPosition(), deltaTime);

                    auto& playerShips = _player.GetShips()[i];
                    playerShips->ShootAt(playerShips->GetProjectileType(), playerShips->GetFireRate(), enemySprite.getPosition());
                }

                for(int k = 0; k < _player.GetShips()[i]->GetProjectile().size(); k++)
                {
                    auto& playerBullet = _player.GetShips()[i]->GetProjectile()[k]->GetSpriteComponent();

                    // Destroy projectiles if collided with enemy ship, and inflict damage to enemy ship
                    if(enemySprite.getGlobalBounds().intersects(playerBullet.GetSprite().getGlobalBounds()))
                    {
                        //UpdateDistribution("Ship damage", 10, 80);
                        int randDamage = _distributions[SHIP_DAMAGE](_generator);

                        //_enemy.GetShips()[j]->TakeDamage(_player.GetShips()[i]->GetDamage());
                        _enemy.GetShips()[j]->GetHealthComponent().TakeDamage(randDamage * _player.GetShips()[i]->GetDamageScaleFactor(),
                                                                              _enemy.GetShips()[j]->GetSpriteComponent().GetPos());
                        _player.GetShips()[i]->GetProjectile().erase(_player.GetShips()[i]->GetProjectile().begin() + k);
                    }
                }
            }

            playerSprite.move(_player.GetShips()[i]->GetSpeed() * deltaTime.asSeconds(), 0);
        }
    }

    // Space Lanes
    for (int i = 0; i < NUM_OF_LANES; ++i)
    {
        float laneHeight = spaceLanes[i]->GetSize().y;
        float totalLanesHeight = (laneHeight * NUM_OF_LANES) + (LANE_Y_SPACING * (NUM_OF_LANES-1));
        float laneXOffset = 75.0F;
        float laneYOffset = (i * (laneHeight + LANE_Y_SPACING)) - (totalLanesHeight / 2.0F);
        spaceLanes[i]->SetPos({_player.GetFlagship()->GetPos().x + laneXOffset, _player.GetFlagship()->GetPos().y + laneYOffset});
        spaceLanes[i]->Update(window, deltaTime);
    }

    // Drag visual
    if(_isDragVisualVisible)
    {
        auto xPos = worldPositionOfMouse.x - _shipDragSpriteVisuals[_shipSelectedIndex].GetSprite().getGlobalBounds().width / 2.0F;
        auto yPos = worldPositionOfMouse.y - _shipDragSpriteVisuals[_shipSelectedIndex].GetSprite().getGlobalBounds().height / 2.0F;
        _shipDragSpriteVisuals[_shipSelectedIndex].SetPos({xPos, yPos});
    }
}

void GameScene::Render(sf::RenderWindow& window)
{
    /// Render the main view
    window.setView(_mainView);
    window.draw(_background_sprite);
    for(auto& button : _shipSpawnerButtons)
    {
        button->Render(window);
    }
    for(auto& text : _ship_cost_text)
    {
        window.draw(text);
    }
    window.draw(_playerCreditsText);
    window.draw(_wavesRemainingText);
    window.draw(_enemiesRemainingText);
    _player.Render(window);
    _enemy.Render(window);
    //starship->Render(window);
    //crosshair.Render(window);
    _shipyard.Render(window);
    window.draw(_minimapBorder);
    for (const auto &lane : spaceLanes)
    {
        lane->Render(window);
    }
    if(_isDragVisualVisible)
    {
        _shipDragSpriteVisuals[_shipSelectedIndex].Render(window);
    }

    /// Render the minimap
    window.setView(_minimapView);
    window.draw(_background_sprite);
    window.draw(_mainViewBorder);
    _player.Render(window);
    _enemy.Render(window);
    for (const auto &lane : spaceLanes)
    {
        lane->Render(window);
    }

    /// Draw cursor over every view
    window.setView(_mainView);
    _cursor.Render(window);
}

void GameScene::InitRandomDistributions()
{
    _generator = GetEngine();
    CreateDistribution(SHIP_DAMAGE, 100, 250);
    CreateDistribution(SPACELANE, 0, NUM_OF_LANES-1);
    CreateDistribution(ENEMY_SHIP_TYPE, 0,  StarshipFactory::SHIP_TYPE::ENUM_COUNT-2);
}

bool GameScene::InitBackground()
{
    _background_texture = std::make_unique<sf::Texture>();
    if (!_background_texture->loadFromFile("Resources/Textures/space_nebula.png"))
    {
        return false;
    }

    _background_texture->setRepeated(true);
    _background_sprite.setTexture(*_background_texture);
    _background_sprite.setTextureRect(sf::IntRect(0, 0, Constants::LEVEL_WIDTH, Constants::LEVEL_HEIGHT));
    //_background_sprite.scale(0.2F, 0.2F);

    return true;
}

bool GameScene::InitShipSpawnerButtons()
{
    std::string ship_costs[5] = { "50", "75", "100", "300", "400", };
    const float NUM_OF_BUTTONS = 5;
    const float SPACING = 10;
    const float OFFSET = NUM_OF_BUTTONS * SPACING;
    for (int i = 0; i < NUM_OF_BUTTONS; ++i)
    {
        _shipSpawnerButtons.emplace_back(std::make_unique<Button>("Resources/Textures/command_button_" + std::to_string(i) + ".png"));
        _shipSpawnerButtons[i]->SetColour({255, 255, 255, 100});
        _shipSpawnerButtons[i]->SetScale({0.20F, 0.20F});

        auto btnBounds = _shipSpawnerButtons[i]->GetBounds();
        auto xPos = (Constants::WINDOW_WIDTH * 0.5f - btnBounds.width * NUM_OF_BUTTONS / 2.0f - OFFSET) + (i * (btnBounds.width + SPACING));
        auto yPos = Constants::WINDOW_HEIGHT - (btnBounds.height / 2.0f * 3.0f);
        _shipSpawnerButtons[i]->SetPos({xPos, yPos});

        _ship_cost_text.emplace_back(sf::Text());
        _ship_cost_text[i].setString(ship_costs[i]);
        _ship_cost_text[i].setFillColor(sf::Color(153, 210, 242));
        //_ship_cost_text[i].setFillColor(sf::Color::Yellow);
        _ship_cost_text[i].setOutlineColor(sf::Color::Black);
        _ship_cost_text[i].setOutlineThickness(1);
        _ship_cost_text[i].setFont(GetRegularFont());
        _ship_cost_text[i].setCharacterSize(8);
        auto btnPos = _shipSpawnerButtons[i]->GetPos();
        auto text_xPos = btnPos.x + btnBounds.width - (_ship_cost_text[i].getGlobalBounds().width+2);
        _ship_cost_text[i].setPosition(text_xPos, btnPos.y + 5.0F);
    }

    return true;
}

void GameScene::InitPlayerCreditsText()
{
    _playerCreditsText.setString("Credits: " + std::to_string(_playerCreditsCounter));
    _playerCreditsText.setFillColor(sf::Color(153, 210, 242));
    _playerCreditsText.setOutlineColor(sf::Color::Black);
    _playerCreditsText.setOutlineThickness(1);
    _playerCreditsText.setFont(GetRegularFont());
    _playerCreditsText.setCharacterSize(14);
    _playerCreditsText.setPosition(_shipSpawnerButtons[0]->GetPos().x, Constants::WINDOW_HEIGHT * 0.96F);
}

void GameScene::InitWavesRemainingText()
{
    _wavesRemainingText.setString("Waves Remaining: " + std::to_string(_wavesRemainingCounter));
    _wavesRemainingText.setFillColor(sf::Color(153, 210, 242));
    _wavesRemainingText.setOutlineColor(sf::Color::Black);
    _wavesRemainingText.setOutlineThickness(1);
    _wavesRemainingText.setFont(GetRegularFont());
    _wavesRemainingText.setCharacterSize(24);
    _wavesRemainingText.setPosition(Constants::WINDOW_WIDTH * 0.5F - _wavesRemainingText.getGlobalBounds().width/2.0F, Constants::WINDOW_HEIGHT * 0.1F);
}

void GameScene::InitEnemiesRemainingText()
{
    _enemiesRemainingText.setString("Hostiles Remaining: " + std::to_string(_enemiesRemainingCounter));
    _enemiesRemainingText.setFillColor(sf::Color::Red);
    _enemiesRemainingText.setOutlineColor(sf::Color::Black);
    _enemiesRemainingText.setOutlineThickness(1);
    _enemiesRemainingText.setFont(GetRegularFont());
    _enemiesRemainingText.setCharacterSize(14);
    _enemiesRemainingText.setPosition(_wavesRemainingText.getPosition().x, _wavesRemainingText.getPosition().y);
}

void GameScene::InitMainView()
{
    // Initialise the main view to the size of the window
    _mainView.setSize(Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT);
}

void GameScene::InitMinimapView()
{
    // Initialize the minimap view to the size of the level
    _minimapView.setSize(Constants::LEVEL_WIDTH,Constants::LEVEL_HEIGHT);

    // Focus the view/camera on the centre point of the level
    _minimapView.setCenter(Constants::LEVEL_WIDTH/2.0F,Constants::LEVEL_HEIGHT/2.0F);
    _originalMinimapViewCenter = _minimapView.getCenter();

    // Position minimap at top middle of the window and set its size
    _minimapView.setViewport(sf::FloatRect(
            Constants::Minimap::VIEWPORT_LEFT,
            Constants::Minimap::VIEWPORT_TOP,
            Constants::Minimap::VIEWPORT_WIDTH,
            Constants::Minimap::VIEWPORT_HEIGHT));
}

void GameScene::InitMainViewBorder()
{
    _mainViewBorder.setSize({Constants::WINDOW_WIDTH,Constants::WINDOW_HEIGHT});
    _mainViewBorder.setOutlineThickness(20.0f); // Set the thickness of the border
    _mainViewBorder.setOutlineColor(sf::Color(128,128,128)); // Set the color of the border
    _mainViewBorder.setFillColor(sf::Color::Transparent); // Make the inside of the rectangle transparent
}

void GameScene::InitMinimapBorder()
{
    _minimapBorder.setSize({Constants::WINDOW_WIDTH*Constants::Minimap::VIEWPORT_WIDTH,Constants::WINDOW_HEIGHT*Constants::Minimap::VIEWPORT_HEIGHT});
    _minimapBorder.setOutlineThickness(2.0f); // Set the thickness of the border
    _minimapBorder.setOutlineColor(sf::Color(128,128,128)); // Set the color of the border
    _minimapBorder.setFillColor(sf::Color::Red); // Make the inside of the rectangle transparent
}

void GameScene::InitSpaceLanes()
{
    for (int i = 0; i < NUM_OF_LANES; ++i)
    {
        spaceLanes.emplace_back(std::make_unique<SpaceLane>());

        float laneHeight = spaceLanes[i]->GetSize().y;
        float totalLanesHeight = (laneHeight * NUM_OF_LANES) + (LANE_Y_SPACING * (NUM_OF_LANES-1));
        float laneXOffset = 75.0F;
        float laneYOffset = (i * (laneHeight + LANE_Y_SPACING)) - (totalLanesHeight / 2.0F);
        sf::Vector2f playerFlagshipPos = _player.GetFlagship()->GetSpriteComponent().GetPos();
        spaceLanes[i]->SetPos({playerFlagshipPos.x + laneXOffset, playerFlagshipPos.y + laneYOffset});
    }

    for (const auto &lane : spaceLanes)
    {
        lane->Init();
    }

    /*spaceLanes[0]->SetColour(_predefinedColours.ORANGE);
    spaceLanes[1]->SetColour(_predefinedColours.LIGHTBLUE);
    spaceLanes[2]->SetColour(_predefinedColours.LIGHTGREEN);
    spaceLanes[3]->SetColour(_predefinedColours.BLUEVIOLET);
    spaceLanes[4]->SetColour(_predefinedColours.LIGHTRED);*/
}

void GameScene::InitEvents()
{
    /// Observer to shipyard event
    auto shipyardCallback = std::bind(&GameScene::SpawnShipFromShipyard, this);
    _shipyard.AddBasicObserver({Shipyard::TRAINING_COMPLETED, shipyardCallback});
}

void GameScene::InitPlayerFlagship()
{
    _player.CreateShip(StarshipFactory::SHIP_TYPE::MOTHERSHIP);
    _player.PaintShip(_player.GetFlagship(), _predefinedColours.LIGHTBLUE);
    _player.SetFlagshipPosition({Constants::WINDOW_WIDTH/2.0F, Constants::LEVEL_HEIGHT/2.0f});
}

void GameScene::InitEnemyShips()
{
    _enemy.CreateShip(StarshipFactory::MOTHERSHIP);
    auto flagship_xPos = Constants::LEVEL_WIDTH -  _enemy.GetFlagshipBounds().width;
    _enemy.SetFlagshipPosition({flagship_xPos, Constants::LEVEL_HEIGHT / 2.0f});
    _enemy.SetFlagshipRotation(180);
    _enemy.PaintShip(_enemy.GetShips()[0], _predefinedColours.LIGHTGREEN);
}

// TODO: Reuse for enemy ship distribution.
void GameScene::RandomisePlayerShipSpawnPoint()
{
    int randomLane = _distributions[SPACELANE](_generator);
    auto ship_xPos = spaceLanes[randomLane]->GetPos().x + 25.0F;
    auto ship_yPos = spaceLanes[randomLane]->GetPos().y + spaceLanes[randomLane]->GetSize().y / 2.0F;
    _player.SetFleetPosition(_player.GetShips()[_player.GetShips().size()-1], {ship_xPos, ship_yPos});
}

/// \param distributionsEnum - no use in the method, purely for readability
void GameScene::CreateDistribution(DistributionsEnum distributionsEnum, int min, int max)
{
    std::uniform_int_distribution<int> instance{min, max};
    _distributions.emplace_back(instance);
}

std::mt19937 GameScene::GetEngine()
{
    std::random_device eng;
    std::mt19937 generator(eng());
    unsigned long int time = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    generator.seed(time);
    return generator;
}

sf::Vector2f GameScene::ConstrainViewCenter(const sf::Vector2f& proposedCenter) const
{
    sf::FloatRect levelBounds(0, 0, Constants::LEVEL_WIDTH, Constants::LEVEL_HEIGHT); // Example level bounds
    sf::Vector2f viewSize = _minimapView.getSize();
    sf::Vector2f halfViewSize = viewSize / 2.0f;

    // Calculate the permissible bounds for the view center
    float minX = levelBounds.left + halfViewSize.x;
    float maxX = levelBounds.left + levelBounds.width - halfViewSize.x;
    float minY = levelBounds.top + halfViewSize.y;
    float maxY = levelBounds.top + levelBounds.height - halfViewSize.y;

    // Constrain the center within the permissible bounds
    float constrainedX = std::max(minX, std::min(proposedCenter.x, maxX));
    float constrainedY = std::max(minY, std::min(proposedCenter.y, maxY));

    return {constrainedX, constrainedY};
}

void GameScene::ResetMinimapView()
{
    _minimapView.setCenter(_originalMinimapViewCenter);

    // Calculate the size adjustment needed to return to original zoom level
    float zoomAdjustment = _originalZoomLevel / _currentZoomLevel;

    // Reset the size of the view to its original size before zooming
    _minimapView.setSize(_minimapView.getSize() * zoomAdjustment);

    _currentZoomLevel = _originalZoomLevel;
}

void GameScene::SpawnShipFromShipyard()
{
    _player.CreateShip(static_cast<StarshipFactory::SHIP_TYPE>(_shipSelectedIndex));
    _player.PaintShip(_player.GetShips()[_player.GetShips().size()-1], _predefinedColours.LIGHTBLUE);
    auto ship_xPos = spaceLanes[spaceLaneSelected]->GetPos().x + 25.0F;
    auto ship_yPos = spaceLanes[spaceLaneSelected]->GetPos().y + spaceLanes[spaceLaneSelected]->GetSize().y / 2.0F;
    _player.SetFleetPosition(_player.GetShips()[_player.GetShips().size()-1], {ship_xPos, ship_yPos});
    //RandomisePlayerShipSpawnPoint();
    _shipyard.SetTrainingCompletedStatus(false);
}

void GameScene::RescaleMinimap(float scaleFactorX, float scaleFactorY)
{
    _minimapView.setViewport(sf::FloatRect(
        Constants::Minimap::VIEWPORT_LEFT,
        Constants::Minimap::VIEWPORT_TOP,
        Constants::Minimap::VIEWPORT_WIDTH * scaleFactorX,
        Constants::Minimap::VIEWPORT_HEIGHT * scaleFactorY));

    _minimapBorder.setSize({Constants::WINDOW_WIDTH*Constants::Minimap::VIEWPORT_WIDTH * scaleFactorX,Constants::WINDOW_HEIGHT*Constants::Minimap::VIEWPORT_HEIGHT * scaleFactorY});
}