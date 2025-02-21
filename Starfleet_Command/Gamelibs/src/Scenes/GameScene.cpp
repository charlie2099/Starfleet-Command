#include <cstdlib>
#include "Scenes/GameScene.hpp"

bool GameScene::Init()
{
    InitRandomDistributions();
    InitBackground();
    InitStarshipBuilderButtons();
    InitPlayerScrapMetalText();
    InitStarshipNameButtonText();
    InitPlayerFlagship();
    InitSpaceLanes();
    InitEnemyFlagship();
    InitMainView();
    InitMinimapView();
    InitMainViewBorder();
    InitMinimapBorder();
    InitStarshipPreviewSprites();
    InitEvents();

    /// StarshipClass newClassType(texture, color, health, damage);
    /// Starship newShip(newClassType);
    /// starshipFighter.AddBehaviour(ChaseBehaviour());
    /// starshipFighter.AddBehaviour(FleeBehaviour());
    /// starshipFighter.AddWeapon(PlasmaCannonWeapon());
    /// starshipFighter.AddWeapon(TorpedoLauncherWeapon());
    ///
    /// for(auto& _starship : starships)
    ///     _starship.Update();
    ///     _starship.Render();

  /*  /// Whenever a SHIP_SPAWNED event occurs, the TestFncForObserverToCall method is called
    /// A SHIP_SPAWNED event is invoked in the player CreateStarship method.
    auto callbackFnc1 = std::bind(&TestClass::TestFncForObserverToCall, testClass);
    _player.AddBasicObserver({Player::EventID::SHIP_SPAWNED, callbackFnc1});

    auto callbackFnc2 = std::bind(&TestClass::OnEvent, testClass, std::placeholders::_1);
    _player.AddObserver2({Player::EventID::SHIP_SPAWNED, callbackFnc2});*/

    return true;
}

void GameScene::EventHandler(sf::RenderWindow& window, sf::Event& event)
{
    _player.EventHandler(window, event);
    HandleViewScrollingKeyboardInput(event);
    HandleMinimapInteractionsMouseInput(window, event);
    HandleStarshipBuilderButtonsInteractionMouseInput(event);
    HandleStarshipPlacementMouseInput(event);

    /*for (auto& shipInfoPanel : _shipInfoPanels)
    {
        shipInfoPanel.EventHandler(window, event);
    }*/
}

void GameScene::Update(sf::RenderWindow& window, sf::Time deltaTime)
{
    auto mousePos = sf::Mouse::getPosition(window); // Mouse _position relative to the window
    auto worldPositionOfMouse = window.mapPixelToCoords(mousePos, _mainView); // Mouse _position translated into world coordinates
    UpdateScrapMetalPopupEffectLifeCycle(window, deltaTime);
    UpdateMainViewMovement(window, deltaTime, mousePos);
    UpdateStarshipBuilderButtonsHoverStateAndColour();
    UpdateStarshipBuilderButtonPositions(window);
    _mainViewBorder.setPosition(_mainView.getCenter().x - _mainViewBorder.getSize().x/2.0F, _mainView.getCenter().y - _mainViewBorder.getSize().y/2.0F);
    _minimapBorder.setPosition(_mainView.getCenter().x - _mainView.getSize().x/4.0F, _mainView.getCenter().y - _mainView.getSize().y/2.0F + 12.1F);
    _playerScrapText.setPosition(_starshipBuilderButtons[0]->GetPos().x, _starshipBuilderButtons[_starshipBuilderButtons.size() - 1]->GetPos().y + _starshipBuilderButtons[_starshipBuilderButtons.size() - 1]->GetBounds().height * 1.15F);
    _starshipAssemblyBar.SetPosition({_starshipBuilderButtons[0]->GetPos().x, _starshipBuilderButtons[0]->GetPos().y - _starshipAssemblyBar.GetSize().height * 2.75F});
    _starshipAssemblyBar.Update(window, deltaTime);
    _starshipNameButtonText.setPosition(_starshipBuilderButtons[_starshipButtonHoveredOverIndex]->GetPos().x, _starshipBuilderButtons[0]->GetPos().y - 20.0F);
    _cursor.Update(window, deltaTime);
    _cursor.SetCursorPos(window, _mainView);
    _player.Update(window, deltaTime);
    _enemy.Update(window, deltaTime);
    //_starship->Update(window, deltaTime);
    UpdateEnemySpawner();

    // Move enemy starships, and shoot at player starships when in range
    for (int i = 1; i < _enemy.GetStarships().size(); ++i)
    {
        auto& enemySprite = _enemy.GetStarships()[i]->GetSpriteComponent().GetSprite();
        enemySprite.move(_enemy.GetStarships()[i]->GetSpeed() * deltaTime.asSeconds() * -1, 0);

        for(const auto &playerStarship : _player.GetStarships())
        {
            if(playerStarship != nullptr)
            {
                auto& playerSprite = playerStarship->GetSpriteComponent().GetSprite();

                // Move towards and shoot at player starship if less than 400 pixels away from it
                if(Chilli::Vector::Distance(playerSprite.getPosition(), enemySprite.getPosition()) <=
                        _enemy.GetStarships()[i]->GetAttackRange())
                {
                    _enemy.GetStarships()[i]->SetSpeed(25);
                    //_enemy.GetStarships()[i]->MoveTowards(playerSprite.getPosition(), deltaTime);

                    auto& enemyStarships = _enemy.GetStarships()[i];
                    enemyStarships->ShootAt(enemyStarships->GetFireRate(), playerSprite.getPosition());
                }

                for(int k = 0; k < _enemy.GetStarships()[i]->GetProjectile().size(); k++)
                {
                    auto& enemyBullet = _enemy.GetStarships()[i]->GetProjectile()[k]->GetSpriteComponent();

                    // Destroy projectiles if collided with enemy starship, and inflict damage to enemy starship
                    if(playerSprite.getGlobalBounds().intersects(enemyBullet.GetSprite().getGlobalBounds()))
                    {
                        //UpdateDistribution("Starship damage", 10, 80);
                        int randDamage = _randomValueDistributions[STARSHIP_DAMAGE](_randomGenerator);

                        //_enemy.GetStarships()[playerStarship]->TakeDamage(_player.GetStarships()[i]->GetDamage());
                        playerStarship->GetHealthComponent().TakeDamage((float)randDamage * _enemy.GetStarships()[i]->GetDamageScaleFactor(),
                                                                        playerStarship->GetSpriteComponent().GetPos());
                        _enemy.GetStarships()[i]->GetProjectile().erase(
                                _enemy.GetStarships()[i]->GetProjectile().begin() + k);
                    }
                }
            }
        }
    }

    // Move player starships, shoot at enemy starships when in range, and destroy player projectiles when too far away
    for(int i = 1; i < _player.GetStarships().size(); i++)
    {
        // If said player starship hasn't been destroyed
        if(_player.GetStarships()[i] != nullptr)
        {
            auto& playerSprite = _player.GetStarships()[i]->GetSpriteComponent().GetSprite();

            for(int j = 0; j < _player.GetStarships()[i]->GetProjectile().size(); j++)
            {
                auto& playerBullet = _player.GetStarships()[i]->GetProjectile()[j]->GetSpriteComponent();

                // Destroy player projectiles when they have travelled too far
                if(Chilli::Vector::Distance(playerSprite.getPosition(), playerBullet.GetPos()) > Constants::WINDOW_WIDTH)
                {
                    _player.GetStarships()[i]->GetProjectile().erase(_player.GetStarships()[i]->GetProjectile().begin() + j);
                }
            }

            for(const auto &enemyStarship : _enemy.GetStarships())
            {
                auto& enemySprite = enemyStarship->GetSpriteComponent().GetSprite();

                // Move towards and shoot at enemy starship if less than 400 pixels away from it
                if(Chilli::Vector::Distance(playerSprite.getPosition(), enemySprite.getPosition()) <=
                        _player.GetStarships()[i]->GetAttackRange())
                {
                    _player.GetStarships()[i]->SetSpeed(25);
                    //_player.GetStarships()[i]->MoveTowards(enemySprite.getPosition(), deltaTime);

                    auto& playerStarships = _player.GetStarships()[i];
                    playerStarships->ShootAt(playerStarships->GetFireRate(), enemySprite.getPosition());
                }

                for(int k = 0; k < _player.GetStarships()[i]->GetProjectile().size(); k++)
                {
                    auto& playerBullet = _player.GetStarships()[i]->GetProjectile()[k]->GetSpriteComponent();

                    // Destroy projectiles if collided with enemy starship, and inflict damage to enemy starship
                    if(enemySprite.getGlobalBounds().intersects(playerBullet.GetSprite().getGlobalBounds()))
                    {
                        //UpdateDistribution("Starship damage", 10, 80);
                        int randDamage = _randomValueDistributions[STARSHIP_DAMAGE](_randomGenerator);

                        //_enemy.GetStarships()[enemyStarship]->TakeDamage(_player.GetStarships()[i]->GetDamage());
                        enemyStarship->GetHealthComponent().TakeDamage((float)randDamage * _player.GetStarships()[i]->GetDamageScaleFactor(),
                                                                       enemyStarship->GetSpriteComponent().GetPos());
                        _player.GetStarships()[i]->GetProjectile().erase(
                                _player.GetStarships()[i]->GetProjectile().begin() + k);
                    }
                }
            }

            playerSprite.move(_player.GetStarships()[i]->GetSpeed() * deltaTime.asSeconds(), 0);
        }
    }

    UpdateSpaceLanePositionsAndMouseHoverColour(window, deltaTime);
    UpdateStarshipPreviewSpritePosition(worldPositionOfMouse);
    UpdateBackgroundLayerMovementAndPosition(deltaTime);
    UpdateBackgroundStarPositions(deltaTime);

    /*for (int i = 0; i < _shipInfoPanels.size(); ++i)
    {
        _shipInfoPanels[i].Update(window);
        _shipInfoPanels[i].SetPosition(_starshipBuilderButtons[i]->GetPos().x, _starshipBuilderButtons[i]->GetPos().y - _shipInfoPanels[i].GetPanelSize().height);
    }*/
}

void GameScene::UpdateEnemySpawner()
{// Initialise enemySpawnTimer to the current elapsed time
    if(_enemySpawnTimer < _enemySpawnTimerClock.getElapsedTime().asSeconds())
    {
        _enemySpawnTimer = _enemySpawnTimerClock.getElapsedTime().asSeconds();
    }
    // If current elapsed time has reached enemySpawnTimer, spawn new enemy
    if(_enemySpawnTimerClock.getElapsedTime().asSeconds() >= _enemySpawnTimer)
    {
        for (int i = 0; i < 1; ++i)
        {
            int randomStarshipType = _randomValueDistributions[ENEMY_STARSHIP_TYPE](_randomGenerator);
            _enemy.CreateStarship(static_cast<StarshipFactory::STARSHIP_TYPE>(randomStarshipType));
            auto& newestEnemyStarship = _enemy.GetStarships()[_enemy.GetStarships().size() - 1];
            int randomLane = _randomValueDistributions[SPACELANE](_randomGenerator);
            auto starshipXPos = _spaceLanes[randomLane]->GetPos().x + _spaceLanes[randomLane]->GetSize().x;
            auto starshipYPos = _spaceLanes[randomLane]->GetPos().y + _spaceLanes[randomLane]->GetSize().y / 2.0F;
            _enemy.SetStarshipPosition(newestEnemyStarship, {starshipXPos, starshipYPos});
            _enemy.SetStarshipRotation(newestEnemyStarship, 180);
        }
        _enemySpawnTimer += _enemySpawnRate;
    }
}

void GameScene::UpdateMainViewMovement(const sf::RenderWindow &window, const sf::Time &deltaTime,const sf::Vector2i &mousePos)
{
    // Thresholds for detecting mouse proximity to window borders
    const float EDGE_OFFSET = 200.0F;
    auto mouseProximityToLeftWindowEdge = EDGE_OFFSET;
    auto mouseProximityToRightWindowEdge = (float)window.getSize().x - EDGE_OFFSET;

    // Current boundaries of the view in world coordinates
    auto viewportLeftBoundary = _mainView.getCenter().x - _mainView.getSize().x / 2.0F;
    auto viewportRightBoundary = _mainView.getCenter().x + _mainView.getSize().x / 2.0F;

    // Viewport movement conditions
    bool isMouseNearLeftEdge = (float)mousePos.x <= mouseProximityToLeftWindowEdge && mousePos.x > 0;
    bool isMouseNearRightEdge = (float)mousePos.x >= mouseProximityToRightWindowEdge && mousePos.x < window.getSize().x;
    bool isViewportLeftEdgeWithinFlagshipFocus = viewportLeftBoundary > _player.GetFlagship()->GetPos().x - _player.GetFlagship()->GetSpriteComponent().GetSprite().getGlobalBounds().width; // BUG: Main view stops moves a few pixels too far when scrolling view left
    bool isViewportRightEdgeWithinRightSideOfEnemyFlagship = viewportRightBoundary < _enemy.GetFlagship()->GetPos().x + _enemy.GetFlagshipBounds().width;
    bool isMouseYposWithinWindowBounds = mousePos.y >= 0 and mousePos.y <= window.getSize().y;

    if(viewportLeftBoundary >= _player.GetFlagship()->GetPos().x - _player.GetFlagship()->GetSpriteComponent().GetSprite().getGlobalBounds().width &&
       _scrollViewLeft)
    {
        _mainView.move(-VIEW_SCROLL_SPEED * deltaTime.asSeconds(), 0.0F);
    }
    else if(_scrollViewRight && isViewportRightEdgeWithinRightSideOfEnemyFlagship)
    {
        _mainView.move(VIEW_SCROLL_SPEED * deltaTime.asSeconds(), 0.0F);
    }

    if(isMouseNearLeftEdge and isViewportLeftEdgeWithinFlagshipFocus and isMouseYposWithinWindowBounds)
    {
        _mainView.move(-VIEW_SCROLL_SPEED * deltaTime.asSeconds(), 0.0F);
    }
    else if(isMouseNearRightEdge and isViewportRightEdgeWithinRightSideOfEnemyFlagship and isMouseYposWithinWindowBounds)
    {
        _mainView.move(VIEW_SCROLL_SPEED * deltaTime.asSeconds(), 0.0F);
    }

    // Set main view to focus on the player flagship if the flagship passes a set distance from the left view boundary
    if(viewportLeftBoundary < _player.GetFlagship()->GetPos().x - _player.GetFlagship()->GetSpriteComponent().GetSprite().getGlobalBounds().width)
    {
        _mainView.move(0, 0);
    }
}

void GameScene::UpdateStarshipBuilderButtonPositions(sf::RenderWindow &window)
{
    for (int i = 0; i < NUM_OF_BUTTONS; ++i)
    {
        const float ROW_LENGTH = 5;
        const float SPACING = 10;
        auto button_bounds = _starshipBuilderButtons[i]->GetBounds();
        auto xPos = 0.0F;
        auto yPos = 0.0F;

        if((float)i < ROW_LENGTH) // Row 1
        {
            xPos = _mainView.getCenter().x - _starshipAssemblyBar.GetSize().width / 2.0F + ((float)i * (button_bounds.width + SPACING));
            yPos = _mainView.getCenter().y + Constants::WINDOW_HEIGHT / 2.75F + SPACING;
        }
        /*else if(i >= ROW_LENGTH) // Row 2
        {
            xPos = _mainView.getCenter().x + ((i-ROW_LENGTH) * (button_bounds.width+SPACING));
            yPos = _mainView.getCenter().y + Constants::WINDOW_HEIGHT/3.4F + button_bounds.height + (SPACING*2.0F);
        }*/
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

        _starshipBuilderButtons[i]->SetPos({xPos, yPos});
        _starshipBuilderButtons[i]->Update(window);

        // Starship cost _text alignment to command buttons
        auto btnPos = _starshipBuilderButtons[i]->GetPos();
        auto btnBounds = _starshipBuilderButtons[i]->GetBounds();
        auto text_xPos = btnPos.x + btnBounds.width - (_starshipCostText[i].getGlobalBounds().width + 2);
        _starshipCostText[i].setPosition(text_xPos, btnPos.y + 5);
    }
}

void GameScene::UpdateStarshipBuilderButtonsHoverStateAndColour()
{
    for (int i = 0; i < _starshipBuilderButtons.size(); i++)
    {
        auto &assignedStarshipToButton = _buttonStarshipDictionary[_starshipBuilderButtons[i].get()];
        bool starshipAffordable = _playerScrapCounter >= assignedStarshipToButton->GetBuildCost();

        if(_starshipBuilderButtons[i]->IsCursorHoveredOver() && !_starshipAssemblyBar.InProgress())
        {
            _starshipButtonHoveredOverIndex = i;
            _starshipNameButtonText.setString(assignedStarshipToButton->GetStarshipName());
            _starshipNameButtonText.setFillColor(starshipAffordable ? _predefinedColours.LIGHTBLUE : _predefinedColours.LIGHTRED);
        }

        if(!_starshipBuilderButtons[_starshipButtonHoveredOverIndex]->IsCursorHoveredOver())
        {
            _starshipNameButtonText.setString("");
        }

        if (_starshipBuilderButtons[i]->IsCursorHoveredOver() && starshipAffordable)
        {
            if (_isPlacingStarship && i == _starshipButtonSelectedIndex)
            {
                _starshipBuilderButtons[i]->SetColour(SELECTED_BTN_COLOR);
            }
            else
            {
                _starshipBuilderButtons[i]->SetColour(HOVER_BTN_COLOR);
            }
        }

        if (!_starshipBuilderButtons[i]->IsCursorHoveredOver() && starshipAffordable)
        {
            _starshipBuilderButtons[i]->SetColour(DEFAULT_BTN_COLOUR);
        }

        if (!_starshipBuilderButtons[i]->IsCursorHoveredOver() && !starshipAffordable)
        {
            _starshipBuilderButtons[i]->SetColour(_predefinedColours.LIGHTRED);
        }

        bool isQueueFull = _starshipTypeTrainingQueue.size() >= STARSHIP_MAX_QUEUE_SIZE;
        if(isQueueFull)
        {
            _starshipBuilderButtons[i]->SetColour(_predefinedColours.LIGHTORANGE);
        }
    }
}

void GameScene::UpdateScrapMetalPopupEffectLifeCycle(sf::RenderWindow &window, sf::Time &deltaTime)
{
    for(auto& popup : _scrapMetalAcquiredPopUpEffect)
    {
        popup->Update(window, deltaTime);
    }

    for (int i = 0; i < _scrapMetalAcquiredPopUpEffect.size(); ++i)
    {
        if(_scrapMetalAcquiredPopUpEffect[i]->IsFaded())
        {
            _scrapMetalAcquiredPopUpEffect.erase(_scrapMetalAcquiredPopUpEffect.begin() + i);
        }
    }
}

void GameScene::UpdateSpaceLanePositionsAndMouseHoverColour(sf::RenderWindow &window, sf::Time &deltaTime)
{
    for (int i = 0; i < NUM_OF_LANES; ++i)
    {
        float laneHeight = _spaceLanes[i]->GetSize().y;
        float totalLanesHeight = (laneHeight * (float) NUM_OF_LANES) + (LANE_Y_SPACING * ((float) NUM_OF_LANES - 1));
        float laneXOffset = 75.0F;
        float laneYOffset = ((float)i * (laneHeight + LANE_Y_SPACING)) - (totalLanesHeight / 2.0F);
        _spaceLanes[i]->SetPos({_player.GetFlagship()->GetPos().x + laneXOffset, _player.GetFlagship()->GetPos().y + laneYOffset});
        _spaceLanes[i]->Update(window, deltaTime);
    }
}

void GameScene::UpdateStarshipPreviewSpritePosition(const sf::Vector2f &worldPositionOfMouse)
{
    if(_isStarshipPreviewSpriteVisible)
    {
        auto xPos = worldPositionOfMouse.x - _starshipPreviewSprites[_starshipButtonSelectedIndex].GetSprite().getGlobalBounds().width / 2.0F;
        auto yPos = worldPositionOfMouse.y - _starshipPreviewSprites[_starshipButtonSelectedIndex].GetSprite().getGlobalBounds().height / 2.0F;
        _starshipPreviewSprites[_starshipButtonSelectedIndex].SetPos({xPos, yPos});
    }
}

void GameScene::UpdateBackgroundLayerMovementAndPosition(const sf::Time &deltaTime)
{
    _backgroundSprite.move(-25.0F * deltaTime.asSeconds(), 0);

    if(_backgroundSprite.getPosition().x + _backgroundSprite.getGlobalBounds().width / 2.0F < 0)
    {
        _backgroundSprite.setPosition(0, Constants::LEVEL_HEIGHT / 2.0F - Constants::WINDOW_HEIGHT / 2.0F);
    }
}

void GameScene::UpdateBackgroundStarPositions(const sf::Time &deltaTime)
{
    for (auto& star : _parallaxStars)
    {
        star.position.x -= star.speed * 100.0F * deltaTime.asSeconds();
        star.circleShape.setPosition(star.position);
        if (star.position.x < 0)
        {
            star.position.x = Constants::LEVEL_WIDTH;
            star.position.y = std::rand() % (int)Constants::LEVEL_HEIGHT/2.0F + Constants::WINDOW_HEIGHT/2.0F;
        }
    }
}

void GameScene::Render(sf::RenderWindow& window)
{
    /// Render the main view
    window.setView(_mainView);
    window.draw(_backgroundSprite);
    for (auto& star : _parallaxStars)
    {
        window.draw(star.circleShape);
    }
    for(auto& button : _starshipBuilderButtons)
    {
        button->Render(window);
    }
    for(auto& text : _starshipCostText)
    {
        window.draw(text);
    }
    /*for (auto& shipInfoPanel : _shipInfoPanels)
    {
        shipInfoPanel.Render(window);
    }*/
    window.draw(_playerScrapText);
    window.draw(_starshipNameButtonText);
    _player.Render(window);
    _enemy.Render(window);
    //_starship->Render(window);
    _starshipAssemblyBar.Render(window);
    window.draw(_minimapBorder);
    for (const auto &lane : _spaceLanes)
    {
        lane->Render(window);
    }
    if(_isStarshipPreviewSpriteVisible)
    {
        _starshipPreviewSprites[_starshipButtonSelectedIndex].Render(window);
    }
    for(auto& popup : _scrapMetalAcquiredPopUpEffect)
    {
        popup->Render(window);
    }

    /// Render the minimap
    window.setView(_minimapView);
    window.draw(_backgroundSprite);
    window.draw(_mainViewBorder);
    _player.Render(window);
    _enemy.Render(window);
    for (const auto &lane : _spaceLanes)
    {
        lane->Render(window);
    }

    /// Draw cursor over every view
    window.setView(_mainView);
    _cursor.Render(window);
}

void GameScene::InitRandomDistributions()
{
    _randomGenerator = GetEngine();
    CreateDistribution(STARSHIP_DAMAGE, 100, 250);
    CreateDistribution(SPACELANE, 0, NUM_OF_LANES-1);
    CreateDistribution(ENEMY_STARSHIP_TYPE, 0, StarshipFactory::STARSHIP_TYPE::ENUM_COUNT - 2);
}

bool GameScene::InitBackground()
{
    if (!_backgroundTexture.loadFromFile("Resources/Textures/space_nebula_2.png"))
    {
        return false;
    }

    _backgroundTexture.setRepeated(true);
    _backgroundSprite.setTexture(_backgroundTexture);
    _backgroundSprite.setTextureRect(sf::IntRect(0, 0, Constants::LEVEL_WIDTH * 2.0F, Constants::WINDOW_HEIGHT));
    _backgroundSprite.setPosition(0,Constants::LEVEL_HEIGHT/2.0F - Constants::WINDOW_HEIGHT/2.0F);
    _backgroundSprite.setColor(sf::Color::Cyan);

    for (int i = 0; i < NUM_OF_STARS; ++i)
    {
        _parallaxStars.emplace_back();
        _parallaxStars[i].position = sf::Vector2f(std::rand() % (int)Constants::LEVEL_WIDTH, std::rand() % (int)Constants::LEVEL_HEIGHT/2.0F + Constants::WINDOW_HEIGHT/2.0F);
        _parallaxStars[i].speed = 0.1f + static_cast<float>(std::rand() % 100) / 100.0f; // Speed between 0.1 and 1.0
        _parallaxStars[i].size = 0.5f + static_cast<float>(std::rand() % 2); // Size between 1 and 3
        _parallaxStars[i].circleShape.setRadius(_parallaxStars[i].size);
        //_parallaxStars[i].circleShape.setFillColor(sf::Color::White);
        _parallaxStars[i].circleShape.setFillColor(_predefinedColours.LIGHTBLUE);
    }

    return true;
}

bool GameScene::InitStarshipBuilderButtons()
{
    _lightFighter = std::make_unique<LightFighter>();
    _heavyFighter = std::make_unique<HeavyFighter>();
    _supportShip = std::make_unique<SupportShip>();
    _destroyer = std::make_unique<Destroyer>();
    _battleship = std::make_unique<Battleship>();

    std::string starshipCosts[5] =
    {
            std::to_string(_lightFighter->GetBuildCost()),
            std::to_string(_heavyFighter->GetBuildCost()),
            std::to_string(_supportShip->GetBuildCost()),
            std::to_string(_destroyer->GetBuildCost()),
            std::to_string(_battleship->GetBuildCost()),
    };

    for (int i = 0; i < NUM_OF_BUTTONS; ++i)
    {
        _starshipBuilderButtons.emplace_back(std::make_unique<Button>("Resources/Textures/command_button_" + std::to_string(i) + ".png"));
        _starshipBuilderButtons[i]->SetColour(DEFAULT_BTN_COLOUR);
        _starshipBuilderButtons[i]->SetScale({0.20F, 0.20F});

        _starshipCostText.emplace_back();
        _starshipCostText[i].setString(starshipCosts[i]);
        _starshipCostText[i].setFillColor(_predefinedColours.LIGHTBLUE);
        _starshipCostText[i].setOutlineColor(sf::Color::Black);
        _starshipCostText[i].setOutlineThickness(1.0F);
        _starshipCostText[i].setFont(GetRegularFont());
        _starshipCostText[i].setCharacterSize(8);

        /*_shipInfoPanels[i].SetText("Name: ");
        _shipInfoPanels[i].SetTextOffset(Panel::TextAlign::OFFSET, 10);
        _shipInfoPanels[i].SetTextSize(10);
        _shipInfoPanels[i].SetSize(15, _starshipBuilderButtons[i]->GetBounds().height*1.0F);
        _shipInfoPanels[i].SetPanelColour(sf::Color(22, 155, 164, 100));*/
    }

    _buttonStarshipDictionary[_starshipBuilderButtons[0].get()] = _lightFighter.get();
    _buttonStarshipDictionary[_starshipBuilderButtons[1].get()] = _heavyFighter.get();
    _buttonStarshipDictionary[_starshipBuilderButtons[2].get()] = _supportShip.get();
    _buttonStarshipDictionary[_starshipBuilderButtons[3].get()] = _destroyer.get();
    _buttonStarshipDictionary[_starshipBuilderButtons[4].get()] = _battleship.get();

    return true;
}

void GameScene::InitPlayerFlagship()
{
    _player.CreateStarhip(StarshipFactory::STARSHIP_TYPE::FLAGSHIP);
    _player.PaintFlagship(_predefinedColours.LIGHTBLUE);
    _player.SetFlagshipPosition({Constants::WINDOW_WIDTH * 0.085F, Constants::LEVEL_HEIGHT/2.0f});
}

void GameScene::InitEnemyFlagship()
{
    _enemy.CreateStarship(StarshipFactory::FLAGSHIP);
    _enemy.PaintFlagship(_predefinedColours.LIGHTGREEN);
    auto flagshipXpos = _spaceLanes[0]->GetPos().x + _spaceLanes[0]->GetSize().x + _enemy.GetFlagshipBounds().width/1.4F;
    _enemy.SetFlagshipPosition({flagshipXpos, Constants::LEVEL_HEIGHT / 2.0f});
    _enemy.SetFlagshipRotation(180);
}

void GameScene::InitPlayerScrapMetalText()
{
    _playerScrapText.setString("Scrap Metal: " + std::to_string(_playerScrapCounter));
    //_playerScrapText.setFillColor(sf::Color(153, 210, 242));
    _playerScrapText.setFillColor(_predefinedColours.LIGHTBLUE);
    _playerScrapText.setOutlineColor(sf::Color::Black);
    _playerScrapText.setOutlineThickness(1);
    _playerScrapText.setFont(GetRegularFont());
    _playerScrapText.setCharacterSize(14);
}

void GameScene::InitMainView()
{
    _mainView.setSize(Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT);
    auto playerFlagshipBounds = _player.GetFlagship()->GetSpriteComponent().GetSprite().getGlobalBounds();
    _mainView.setCenter(_player.GetFlagship()->GetPos().x - playerFlagshipBounds.width + Constants::WINDOW_WIDTH/2.0F -1.0F, _player.GetFlagship()->GetPos().y);
}

void GameScene::InitMinimapView()
{
    // Initialize the minimap view to the size of the level
    _minimapView.setSize(Constants::LEVEL_WIDTH,Constants::LEVEL_HEIGHT/3.2F); // Note: Should be 3.0F?

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
    _mainViewBorder.setOutlineThickness(10.0f);
    _mainViewBorder.setOutlineColor(_predefinedColours.LIGHTBLUE);
    _mainViewBorder.setFillColor(sf::Color::Transparent);
}

void GameScene::InitMinimapBorder()
{
    _minimapBorder.setSize({Constants::WINDOW_WIDTH * Constants::Minimap::VIEWPORT_WIDTH, Constants::WINDOW_HEIGHT * Constants::Minimap::VIEWPORT_HEIGHT});
    _minimapBorder.setOutlineThickness(1.0f);
    _minimapBorder.setOutlineColor({128, 128, 128});
    _minimapBorder.setFillColor(sf::Color::Red);
}

void GameScene::InitStarshipPreviewSprites()
{
    for (int i = 0; i < _starshipPreviewSprites.size(); ++i)
    {
        _starshipPreviewSprites[i].LoadSprite("Resources/Textures/starfleet_ship_" + std::to_string(i) + ".png");
        _starshipPreviewSprites[i].GetSprite().scale({0.05F, 0.05F});
    }

    for (auto& starshipPreviewSprite : _starshipPreviewSprites)
    {
        auto playerStarshipColour = _player.GetStarships()[0]->GetColour();
        starshipPreviewSprite.GetSprite().setColor({playerStarshipColour.r, playerStarshipColour.g, playerStarshipColour.b, 125});
        //starshipPreviewSprite.GetSprite().setColor({sf::Color::White.r, sf::Color::White.g, sf::Color::White.b, 125});
    }
}

void GameScene::InitSpaceLanes()
{
    for (int i = 0; i < NUM_OF_LANES; ++i)
    {
        _spaceLanes.emplace_back(std::make_unique<SpaceLane>());

        float laneHeight = _spaceLanes[i]->GetSize().y;
        float totalLanesHeight = (laneHeight * (float)NUM_OF_LANES) + (LANE_Y_SPACING * ((float)NUM_OF_LANES-1));
        float laneXOffset = 75.0F;
        float laneYOffset = ((float)i * (laneHeight + LANE_Y_SPACING)) - (totalLanesHeight / 2.0F);
        sf::Vector2f playerFlagshipPos = _player.GetFlagship()->GetSpriteComponent().GetPos();
        _spaceLanes[i]->SetPos({playerFlagshipPos.x + laneXOffset, playerFlagshipPos.y + laneYOffset});
        _spaceLanes[i]->SetSize({Constants::LEVEL_WIDTH*0.91F, 50.0F});
        _spaceLanes[i]->Init();
    }

    /*_spaceLanes[0]->SetColour(_predefinedColours.ORANGE);
    _spaceLanes[1]->SetColour(_predefinedColours.LIGHTBLUE);
    _spaceLanes[2]->SetColour(_predefinedColours.LIGHTGREEN);
    _spaceLanes[3]->SetColour(_predefinedColours.BLUEVIOLET);
    _spaceLanes[4]->SetColour(_predefinedColours.LIGHTRED);*/
}

void GameScene::InitStarshipNameButtonText()
{
    _starshipNameButtonText.setFillColor(_predefinedColours.LIGHTBLUE);
    _starshipNameButtonText.setOutlineColor(sf::Color::Black);
    _starshipNameButtonText.setOutlineThickness(1);
    _starshipNameButtonText.setFont(GetRegularFont());
    _starshipNameButtonText.setCharacterSize(10);
}

void GameScene::InitEvents()
{
    /// Observer to starship assembly bar event
    auto starshipAssemblyBarCallback = std::bind(&GameScene::SpawnStarshipFromShipyard_OnStarshipDeploymentComplete, this);
    _starshipAssemblyBar.AddBasicObserver({ProgressBar::EventID::TASK_COMPLETED, starshipAssemblyBarCallback});

    /// Agnostic observer to enemy starships destroyed event
    auto enemyStarshipsDestroyedCallback = std::bind(&GameScene::UpdateScrapMetal_OnEnemyStarshipDestroyed, this, std::placeholders::_1);
    _enemy.AddAgnosticObserver({Enemy::EventID::STARSHIP_DESTROYED, enemyStarshipsDestroyedCallback});
}

sf::Vector2f GameScene::ClampViewCentreBounds(const sf::Vector2f& proposedCenter) const
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
    float zoomAdjustment = _originalZoomLevel / _currentZoomLevel;
    _minimapView.setSize(_minimapView.getSize() * zoomAdjustment);
    _currentZoomLevel = _originalZoomLevel;
}

void GameScene::SpawnStarshipFromShipyard_OnStarshipDeploymentComplete()
{
    if(_starshipTypeTrainingQueue.empty())
        return;

    //_player.CreateStarship(static_cast<StarshipFactory::STARSHIP_TYPE>(_starshipButtonSelectedIndex));
    _player.CreateStarhip(_starshipTypeTrainingQueue.front());
    auto starshipXPos = _spaceLanes[_spaceLaneStarshipDeploymentQueue.front()]->GetPos().x + 25.0F;
    auto starshipYPos = _spaceLanes[_spaceLaneStarshipDeploymentQueue.front()]->GetPos().y +
                     _spaceLanes[_spaceLaneStarshipDeploymentQueue.front()]->GetSize().y / 2.0F;
    _player.SetStarshipPosition(_player.GetStarships().back(), {starshipXPos, starshipYPos});

    _starshipTypeTrainingQueue.pop();
    _spaceLaneStarshipDeploymentQueue.pop();

    _starshipAssemblyBar.ResetProgress();

    if(!_starshipTypeTrainingQueue.empty())
    {
        StartNextStarshipDeployment();
    }
}

/// \param distributionsEnum - no use in the method, purely for readability
void GameScene::CreateDistribution([[maybe_unused]] DistributionsEnum distributionsEnum, int min, int max)
{
    std::uniform_int_distribution<int> instance{min, max};
    _randomValueDistributions.emplace_back(instance);
}

std::mt19937 GameScene::GetEngine()
{
    std::random_device eng;
    std::mt19937 generator(eng());
    unsigned long int time = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    generator.seed(time);
    return generator;
}

void GameScene::HandleViewScrollingKeyboardInput(const sf::Event &event)
{
    if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::A)
    {
        _scrollViewLeft = true;
    }
    else if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::A)
    {
        _scrollViewLeft = false;
    }
    if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::D)
    {
        _scrollViewRight = true;
    }
    else  if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::D)
    {
        _scrollViewRight = false;
    }
}

void GameScene::HandleStarshipPlacementMouseInput(const sf::Event &event)
{
    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left && _isPlacingStarship)
    {
        for (int i = 0; i < _spaceLanes.size(); ++i)
        {
            if(_spaceLanes[i]->IsCursorHoveredOver())
            {
                BeginStarshipDeploymentProcess(i);
            }
        }

        _starshipBuilderButtons[_starshipButtonSelectedIndex]->SetColour(DEFAULT_BTN_COLOUR);
        _starshipPreviewSprites[_starshipButtonSelectedIndex].SetPos(_starshipBuilderButtons[_starshipButtonSelectedIndex]->GetPos());
        _isStarshipPreviewSpriteVisible = false;
        _isPlacingStarship = false;
    }
}

void GameScene::HandleMinimapInteractionsMouseInput(const sf::RenderWindow &window, const sf::Event &event)
{
    auto mouse_pos = sf::Mouse::getPosition(window); // Mouse position relative to the window
    auto worldPositionOfMouse = window.mapPixelToCoords(mouse_pos, _mainView); // Mouse position translated into world coordinates
    bool isMouseCursorOnMinimap = _minimapBorder.getGlobalBounds().contains(worldPositionOfMouse);

    if(isMouseCursorOnMinimap)
    {
        if (event.type == sf::Event::MouseWheelScrolled)
        {
            HandleMinimapZooming(window, event, mouse_pos);
        }
        if (_currentZoomLevel < 1.0f)
        {
            HandleMinimapPanning(window, event, mouse_pos);
        }
    }
    else
    {
        ResetMinimapView();
    }
}

void GameScene::HandleStarshipBuilderButtonsInteractionMouseInput(const sf::Event &event)
{
    for (int i = 0; i < _starshipBuilderButtons.size(); i++)
    {
        auto &assignedStarshipToButton = _buttonStarshipDictionary[_starshipBuilderButtons[i].get()];
        bool starshipAffordable = _playerScrapCounter >= assignedStarshipToButton->GetBuildCost();

        if (_starshipBuilderButtons[i]->IsCursorHoveredOver() && starshipAffordable)
        {
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                if(!_isPlacingStarship && _starshipTypeTrainingQueue.size() < STARSHIP_MAX_QUEUE_SIZE)
                {
                    _starshipButtonSelectedIndex = i;
                    _isStarshipPreviewSpriteVisible = true;
                    _isPlacingStarship = true;
                }
            }
        }
    }
}

void GameScene::HandleMinimapPanning(const sf::RenderWindow &window, const sf::Event &event, const sf::Vector2i &mouse_pos)
{
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    {
        _canMinimapViewPan = true;
        _initialMousePosition = mouse_pos;
    }

    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
    {
        _canMinimapViewPan = false;
    }

    if (event.type == sf::Event::MouseMoved && _canMinimapViewPan)
    {
        UpdateMinimapPanPosition(window);
    }
}

void GameScene::UpdateMinimapPanPosition(const sf::RenderWindow &window)
{
    sf::Vector2i currentMousePosition = sf::Mouse::getPosition(window);
    sf::Vector2f delta = window.mapPixelToCoords(_initialMousePosition, _minimapView) -
                         window.mapPixelToCoords(currentMousePosition, _minimapView);

    sf::Vector2f newCenter = _minimapView.getCenter() + delta;
    _minimapView.setCenter(ClampViewCentreBounds(newCenter));
    _initialMousePosition = currentMousePosition;
}

void GameScene::HandleMinimapZooming(const sf::RenderWindow &window, const sf::Event &event, const sf::Vector2i &mouse_pos)
{
    float zoomFactor = (event.mouseWheelScroll.delta > 0) ? 0.9f : 1.1f;
    float newZoomLevel = _currentZoomLevel * zoomFactor;
    bool isZoomLevelWithinConstraints = newZoomLevel >= 0.15f && newZoomLevel <= 1.0f; // MAX ZOOM | MIN ZOOM

    if (isZoomLevelWithinConstraints)
    {
        sf::Vector2f beforeZoom = window.mapPixelToCoords(mouse_pos, _minimapView);
        _minimapView.zoom(zoomFactor);
        _currentZoomLevel = newZoomLevel;
        sf::Vector2f afterZoom = window.mapPixelToCoords(mouse_pos, _minimapView);
        sf::Vector2f offset = beforeZoom - afterZoom;
        sf::Vector2f newCenter = _minimapView.getCenter() + offset;
        _minimapView.setCenter(ClampViewCentreBounds(newCenter));
    }
}

void GameScene::BeginStarshipDeploymentProcess(int currentSpaceLaneSelectedIndex)
{
    auto& assignedStarshipToButton = _buttonStarshipDictionary[_starshipBuilderButtons[_starshipButtonSelectedIndex].get()];
    _playerScrapCounter -= static_cast<int>(assignedStarshipToButton->GetBuildCost());
    _playerScrapText.setString("Scrap Metal: " + std::to_string(_playerScrapCounter));

    _starshipTypeTrainingQueue.push(static_cast<StarshipFactory::STARSHIP_TYPE>(_starshipButtonSelectedIndex));
    _spaceLaneStarshipDeploymentQueue.push(currentSpaceLaneSelectedIndex);

    if(!_starshipAssemblyBar.InProgress())
    {
        StartNextStarshipDeployment();
    }

    // TODO: Invoke an agnostic event here notifying subscribers that a starship is currently training?
}

void GameScene::StartNextStarshipDeployment()
{
    if(_starshipTypeTrainingQueue.empty())
        return;

    auto& assignedStarshipToButton = _buttonStarshipDictionary[_starshipBuilderButtons[_starshipTypeTrainingQueue.front()].get()];
    _starshipAssemblyBar.SetProgressText("Deploying " + assignedStarshipToButton->GetStarshipName() + "...");
    _starshipAssemblyBar.SetProgressSpeed(assignedStarshipToButton->GetTrainingSpeed());
    _starshipAssemblyBar.SetProgressStatus(true);
}

void GameScene::UpdateScrapMetal_OnEnemyStarshipDestroyed(std::any eventData)
{
    auto destroyedEnemyStarshipData = std::any_cast<Enemy::StarshipDataToSend>(eventData); // NOTE: Don't know if this is a good way of handling this problem? (making a public struct within enemy class to encapsulate required data)
    _playerScrapCounter += static_cast<int>(destroyedEnemyStarshipData.BuildCost);
    _playerScrapText.setString("Scrap Metal: " + std::to_string(_playerScrapCounter));

    auto& scrapMetalPopup = _scrapMetalAcquiredPopUpEffect.emplace_back(std::make_unique<UIPopUpEffect>(destroyedEnemyStarshipData.BuildCost, destroyedEnemyStarshipData.DeathLocation));
    scrapMetalPopup->SetColour(_predefinedColours.LIGHTBLUE);
    scrapMetalPopup->SetCharSize(15);
    scrapMetalPopup->SetIconImage("Resources/Textures/pixil-frame-0.png");
}

