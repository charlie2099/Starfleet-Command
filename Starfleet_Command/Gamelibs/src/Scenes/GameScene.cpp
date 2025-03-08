#include "Scenes/GameScene.hpp"

bool GameScene::Init()
{
    InitRandomDistributions();
    backgroundParallax = std::make_unique<ParallaxBackground>("Resources/Textures/space_nebula_2.png", sf::Color::Cyan, NUM_OF_STARS, _predefinedColours.LIGHTBLUE);
    InitStarshipBuilderButtons();
    InitPlayerMothership();
    InitSpaceLanes();
    InitEnemyMothership();

    auto& playerMothership = _player.GetMothership();
    auto& enemyMothership = _enemy.GetMothership();

    _playerScrapMetalManager = std::make_unique<ScrapMetalManager>(_predefinedColours.GRAY,playerMothership->GetColour(), STARTING_SCRAP_METAL);
    _enemyScrapMetalManager = std::make_unique<ScrapMetalManager>(_predefinedColours.GRAY,enemyMothership->GetColour(), STARTING_SCRAP_METAL);

    InitMainView();

    std::string starshipCosts[5] =
    {
            std::to_string(_lightFighter->GetBuildCost()),
            std::to_string(_heavyFighter->GetBuildCost()),
            std::to_string(_supportShip->GetBuildCost()),
            std::to_string(_destroyer->GetBuildCost()),
            std::to_string(_battleship->GetBuildCost()),
    };

    gameHud = std::make_unique<GameHUD>(playerMothership, enemyMothership, starshipCosts, _mainView);

    InitMinimapView();
    InitMainViewBorder();
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

  /*  /// Whenever a STARSHIP_SPAWNED event occurs, the TestFncForObserverToCall method is called
    /// A STARSHIP_SPAWNED event is invoked in the player CreateStarship method.
    auto callbackFnc1 = std::bind(&TestClass::TestFncForObserverToCall, testClass);
    _player.AddBasicObserver({Player::EventID::STARSHIP_SPAWNED, callbackFnc1});

    auto callbackFnc2 = std::bind(&TestClass::OnEvent, testClass, std::placeholders::_1);
    _player.AddObserver2({Player::EventID::STARSHIP_SPAWNED, callbackFnc2});*/

    return true;
}

void GameScene::EventHandler(sf::RenderWindow& window, sf::Event& event)
{
    _player.EventHandler(window, event);
    HandleViewScrollingKeyboardInput(event);
    minimap->EventHandler(window, event);
    HandleStarshipBuilderButtonsInteractionMouseInput(event);
    HandleStarshipPlacementMouseInput(event);

    for (const auto & _spaceLane : _spaceLanes)
    {
        if(_spaceLane->IsCursorHoveredOver())
        {
            _spaceLane->SetColour(sf::Color(100, 100, 100, 100.0F));
        }
        else
        {
            _spaceLane->SetColour(sf::Color(100, 100, 100, 25.0F));
        }
    }

    for (int i = 0; i < _player.GetStarshipCount(); ++i)
    {
        if (_player.GetStarships()[i]->IsMouseOver())
        {
            for (int j = 0; j < _player.GetStarships()[i]->GetAttackableLanes().size(); ++j)
            {
                _spaceLanes[_player.GetStarships()[i]->GetAttackableLanes()[j]]->SetColour(sf::Color(_predefinedColours.LIGHTGREEN.r, _predefinedColours.LIGHTGREEN.g, _predefinedColours.LIGHTGREEN.b, 50.0F));
            }
        }
    }

    /*for (auto& shipInfoPanel : _shipInfoPanels)
    {
        shipInfoPanel.EventHandler(window, event);
    }*/
}

void GameScene::Update(sf::RenderWindow& window, sf::Time deltaTime)
{
    auto mousePos = sf::Mouse::getPosition(window); // Mouse _position relative to the window
    auto worldPositionOfMouse = window.mapPixelToCoords(mousePos, _mainView); // Mouse _position translated into world coordinates
    UpdateMainViewMovement(window, deltaTime, mousePos);
    UpdateStarshipBuilderButtonsHoverStateAndColour();
    UpdateStarshipBuilderButtonPositions(window);
    gameHud->Update(window, deltaTime, _starshipBuilderButtons[0]->GetPos(), _starshipBuilderButtons[_starshipButtonHoveredOverIndex]->GetPos());
    _playerScrapMetalManager->Update(window, deltaTime);
    _enemyScrapMetalManager ->Update(window, deltaTime);
    _playerScrapMetalManager->SetTextPosition(gameHud->GetPlayerMothershipTextPos().x + gameHud->GetPlayerMothershipTextBounds().width/2.0F - _playerScrapMetalManager->GetTextSize().width/2.0F, gameHud->GetPlayerMothershipTextPos().y + gameHud->GetPlayerMothershipTextBounds().height + 10.0F);
    _enemyScrapMetalManager ->SetTextPosition(gameHud->GetEnemyMothershipTextPos().x + gameHud->GetEnemyMothershipTextBounds().width/2.0F - _enemyScrapMetalManager->GetTextSize().width/2.0F, gameHud->GetEnemyMothershipTextPos().y + gameHud->GetEnemyMothershipTextBounds().height + 10.0F);
    _mainViewBorder.setPosition(_mainView.getCenter().x - _mainViewBorder.getSize().x/2.0F, _mainView.getCenter().y - _mainViewBorder.getSize().y/2.0F);
    _mainViewBorderText.setPosition(_mainViewBorder.getPosition().x + 25.0F, _mainViewBorder.getPosition().y + 10.0F);
    minimap->Update(window, deltaTime);
    _cursor.Update(window, deltaTime);
    _cursor.SetCursorPos(window, _mainView);
    _player.Update(window, deltaTime);
    _enemy.Update(window, deltaTime);
    //_starship->Update(window, deltaTime);
    UpdateEnemySpawner();





    /// Enemy starship movement and shooting
    for (int i = 1; i < _enemy.GetStarshipCount(); ++i)
    {
        if(_enemy.GetStarships()[i] == nullptr) return;

        auto& enemyStarship = _enemy.GetStarships()[i];
        _enemy.MoveStarship(i, {enemyStarship->GetSpeed() * deltaTime.asSeconds() * -1, 0});

        /// Enemy starship alignment with other friendly starships
        for (int j = 1; j < _enemy.GetStarshipCount(); ++j)
        {
            auto &friendlyStarship = _enemy.GetStarships()[j];
            if (_enemy.GetStarships()[i] != friendlyStarship)
            {
                if (enemyStarship->IsInSameLaneAs(friendlyStarship) &&
                    enemyStarship->IsFriendlyStarshipAhead(friendlyStarship))
                {
                    enemyStarship->SetSpeed(friendlyStarship->GetSpeed());
                }
            }
        }

        for(const auto &playerStarship : _player.GetStarships())
        {
            /// Enemy  starship enemy engagement
            if(enemyStarship->IsEnemyInRange(playerStarship) &&
                enemyStarship->CanEngageWith(playerStarship))
            {
                enemyStarship->ShootAt(playerStarship->GetPos());

                if(enemyStarship->IsInSameLaneAs(playerStarship) &&
                   enemyStarship->IsEnemyStarshipAhead(playerStarship))
                {
                    enemyStarship->SetSpeed(0);
                }
            }

            /// Enemy projectile collision handling
            for(int k = 0; k < enemyStarship->GetProjectileCount(); k++)
            {
                auto& enemyBullet = enemyStarship->GetProjectile()[k]->GetSpriteComponent();
                if(playerStarship->CollidesWith(enemyBullet.GetSprite().getGlobalBounds()))
                {
                    int randDamage = _randomValueDistributions[STARSHIP_DAMAGE](_randomGenerator);
                    float scaledDamage = (float)randDamage * enemyStarship->GetDamageScaleFactor();
                    playerStarship->TakeDamage(scaledDamage);
                    enemyStarship->DestroyProjectile(k);
                }
            }
        }

        auto* supportShip = dynamic_cast<SupportShip*>(_enemy.GetStarships()[i].get());
        if(supportShip)
        {
            for (int j = 1; j < _enemy.GetStarshipCount(); ++j)
            {
                auto& friendlyStarship = _enemy.GetStarships()[j];
                if(_enemy.GetStarships()[i] != friendlyStarship)
                {
                    if(supportShip->IsInSameLaneAs(friendlyStarship) &&
                            supportShip->IsFriendlyStarshipAhead(friendlyStarship))
                    {
                        supportShip->ShootHealAt(friendlyStarship);
                    }

                    for(int k = 0; k < supportShip->GetProjectileCount(); k++)
                    {
                        auto& friendlyProjectile = supportShip->GetProjectile()[k]->GetSpriteComponent();
                        if(friendlyStarship->CollidesWith(friendlyProjectile.GetSprite().getGlobalBounds()))
                        {
                            int randHealAmount = _randomValueDistributions[STARSHIP_HEALING](_randomGenerator);
                            friendlyStarship->ReplenishHealth(randHealAmount);
                            supportShip->DestroyProjectile(k);
                        }
                    }
                }
            }
        }
    }





    /// Player starship movement and shooting
    for(int i = 1; i < _player.GetStarshipCount(); i++)
    {
        if(_player.GetStarships()[i] == nullptr) return;

        auto& playerStarship = _player.GetStarships()[i];
        _player.MoveStarship(i, {playerStarship->GetSpeed() * deltaTime.asSeconds(), 0});

        /// Player starship alignment with other friendly starships
        for (int j = 1; j < _player.GetStarshipCount(); ++j)
        {
            auto &friendlyStarship = _player.GetStarships()[j];
            if (_player.GetStarships()[i] != friendlyStarship)
            {
                if (playerStarship->IsInSameLaneAs(friendlyStarship) &&
                    playerStarship->IsFriendlyStarshipAhead(friendlyStarship))
                {
                    playerStarship->SetSpeed(friendlyStarship->GetSpeed());
                }
            }
        }

        for(const auto &enemyStarship : _enemy.GetStarships())
        {
            /// Player starship enemy engagement
            if(playerStarship->IsEnemyInRange(enemyStarship) &&
               playerStarship->CanEngageWith(enemyStarship))
            {
                playerStarship->ShootAt(enemyStarship->GetPos());

                if(playerStarship->IsInSameLaneAs(enemyStarship) &&
                    playerStarship->IsEnemyStarshipAhead(enemyStarship))
                {
                    playerStarship->SetSpeed(0);
                }
            }

            /// Player projectile collision handling
            for(int k = 0; k < playerStarship->GetProjectileCount(); k++)
            {
                auto& playerBulletSprite = playerStarship->GetProjectile()[k]->GetSpriteComponent().GetSprite();
                if(enemyStarship->CollidesWith(playerBulletSprite.getGlobalBounds()))
                {
                    int randDamage = _randomValueDistributions[STARSHIP_DAMAGE](_randomGenerator);
                    float scaledDamage = (float)randDamage * playerStarship->GetDamageScaleFactor();
                    enemyStarship->TakeDamage(scaledDamage);
                    playerStarship->DestroyProjectile(k);
                }
            }
        }

        auto* supportShip = dynamic_cast<SupportShip*>(_player.GetStarships()[i].get());
        if(supportShip)
        {
            for (int j = 1; j < _player.GetStarshipCount(); ++j)
            {
                auto& friendlyStarship = _player.GetStarships()[j];
                if(_player.GetStarships()[i] != friendlyStarship)
                {
                    if(supportShip->IsInSameLaneAs(friendlyStarship) &&
                        supportShip->IsFriendlyStarshipAhead(friendlyStarship))
                    {
                            supportShip->ShootHealAt(friendlyStarship);
                    }

                    for(int k = 0; k < supportShip->GetProjectileCount(); k++)
                    {
                        auto& friendlyProjectile = supportShip->GetProjectile()[k]->GetSpriteComponent();
                        if(friendlyStarship->CollidesWith(friendlyProjectile.GetSprite().getGlobalBounds()))
                        {
                            int randHealAmount = _randomValueDistributions[STARSHIP_HEALING](_randomGenerator);
                            friendlyStarship->ReplenishHealth(randHealAmount);
                            supportShip->DestroyProjectile(k);
                        }
                    }
                }
            }
        }
    }

    UpdateSpaceLanePositionsAndMouseHoverColour(window, deltaTime);
    UpdateStarshipPreviewSpritePosition(worldPositionOfMouse);
    backgroundParallax->Update(window, deltaTime);

    /*for (int i = 0; i < _shipInfoPanels.size(); ++i)
    {
        _shipInfoPanels[i].Update(window);
        _shipInfoPanels[i].SetPosition(_starshipBuilderButtons[i]->GetPos().x, _starshipBuilderButtons[i]->GetPos().y - _shipInfoPanels[i].GetPanelSize().height);
    }*/
}

void GameScene::Render(sf::RenderWindow& window)
{
    /// Render the main view
    window.setView(_mainView);
    backgroundParallax->Render(window);
    for(auto& button : _starshipBuilderButtons)
    {
        button->Render(window);
    }
    _player.Render(window);
    _enemy.Render(window);
    //_starship->Render(window);
    minimap->Render(window);
    for (const auto &lane : _spaceLanes)
    {
        lane->Render(window);
    }
    if(_isStarshipPreviewSpriteVisible)
    {
        _starshipPreviewSprites[_starshipButtonSelectedIndex].Render(window);
    }
    _playerScrapMetalManager->Render(window);
    _enemyScrapMetalManager ->Render(window);
    gameHud->Render(window);

    /// Render the minimap
    window.setView(minimap->GetView());
    backgroundParallax->RenderBackground(window);
    window.draw(_mainViewBorder);
    window.draw(_mainViewBorderText);
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

void GameScene::UpdateEnemySpawner()
{
    // Initialise enemySpawnTimer to the current elapsed time
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
            int randomLane = _randomValueDistributions[SPACELANE](_randomGenerator);
            _enemy.CreateStarship(static_cast<StarshipFactory::STARSHIP_TYPE>(randomStarshipType), randomLane);
            auto& newestEnemyStarship = _enemy.GetStarships()[_enemy.GetStarshipCount() - 1];
            auto starshipXPos = _spaceLanes[randomLane]->GetPos().x + _spaceLanes[randomLane]->GetSize().x;
            auto starshipYPos = _spaceLanes[randomLane]->GetPos().y + _spaceLanes[randomLane]->GetSize().y / 2.0F;
            _enemy.SetStarshipPosition(newestEnemyStarship, {starshipXPos, starshipYPos});
            _enemy.SetStarshipRotation(newestEnemyStarship, 180);
            _enemyScrapMetalManager->SpendScrap(newestEnemyStarship->GetBuildCost());
            _enemyScrapMetalManager->UpdateScrapText("Scrap Metal: " + std::to_string(_enemyScrapMetalManager->GetCurrentScrapMetalAmount()));
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
    bool isViewportLeftEdgeWithinMothershipFocus = viewportLeftBoundary > _player.GetMothership()->GetPos().x - _player.GetMothership()->GetSpriteComponent().GetSprite().getGlobalBounds().width; // BUG: Main view stops moves a few pixels too far when scrolling view left
    bool isViewportRightEdgeWithinRightSideOfEnemyMothership = viewportRightBoundary < _enemy.GetMothership()->GetPos().x + _enemy.GetMothershipBounds().width;
    bool isMouseYposWithinWindowBounds = mousePos.y >= 0 and mousePos.y <= window.getSize().y;

    if(viewportLeftBoundary >= _player.GetMothership()->GetPos().x - _player.GetMothership()->GetSpriteComponent().GetSprite().getGlobalBounds().width &&
       _scrollViewLeft)
    {
        _mainView.move(-VIEW_SCROLL_SPEED * deltaTime.asSeconds(), 0.0F);
    }
    else if(_scrollViewRight && isViewportRightEdgeWithinRightSideOfEnemyMothership)
    {
        _mainView.move(VIEW_SCROLL_SPEED * deltaTime.asSeconds(), 0.0F);
    }

    if(isMouseNearLeftEdge and isViewportLeftEdgeWithinMothershipFocus and isMouseYposWithinWindowBounds)
    {
        _mainView.move(-VIEW_SCROLL_SPEED * deltaTime.asSeconds(), 0.0F);
    }
    else if(isMouseNearRightEdge and isViewportRightEdgeWithinRightSideOfEnemyMothership and isMouseYposWithinWindowBounds)
    {
        _mainView.move(VIEW_SCROLL_SPEED * deltaTime.asSeconds(), 0.0F);
    }

    // Set main view to focus on the player mothership if the mothership passes a set distance from the left view boundary
    if(viewportLeftBoundary < _player.GetMothership()->GetPos().x - _player.GetMothership()->GetSpriteComponent().GetSprite().getGlobalBounds().width)
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
            xPos = _mainView.getCenter().x - gameHud->GetStarshipDeploymentBar().GetSize().width / 2.0F + ((float)i * (button_bounds.width + SPACING));
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
        auto text_xPos = btnPos.x + btnBounds.width - (gameHud->GetStarshipCostText()[i].getGlobalBounds().width + 2);
        gameHud->GetStarshipCostText()[i].setPosition(text_xPos, btnPos.y + 5);
    }
}

void GameScene::UpdateStarshipBuilderButtonsHoverStateAndColour()
{
    for (int i = 0; i < _starshipBuilderButtons.size(); i++)
    {
        auto &assignedStarshipToButton = _buttonStarshipDictionary[_starshipBuilderButtons[i].get()];
        bool starshipAffordable = _playerScrapMetalManager->GetCurrentScrapMetalAmount() >= assignedStarshipToButton->GetBuildCost();

        if(_starshipBuilderButtons[i]->IsCursorHoveredOver() && !gameHud->GetStarshipDeploymentBar().InProgress())
        {
            _starshipButtonHoveredOverIndex = i;
            gameHud->GetStarshipNameButtonText().setString(assignedStarshipToButton->GetStarshipName());
            gameHud->GetStarshipNameButtonText().setFillColor(starshipAffordable ? _player.GetMothership()->GetColour() : _predefinedColours.LIGHTRED);
        }

        if(!_starshipBuilderButtons[_starshipButtonHoveredOverIndex]->IsCursorHoveredOver())
        {
            gameHud->GetStarshipNameButtonText().setString("");
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

void GameScene::UpdateSpaceLanePositionsAndMouseHoverColour(sf::RenderWindow &window, sf::Time &deltaTime)
{
    for (int i = 0; i < NUM_OF_LANES; ++i)
    {
        float laneHeight = _spaceLanes[i]->GetSize().y;
        float totalLanesHeight = (laneHeight * (float) NUM_OF_LANES) + (LANE_Y_SPACING * ((float) NUM_OF_LANES - 1));
        float laneXOffset = 75.0F;
        float laneYOffset = ((float)i * (laneHeight + LANE_Y_SPACING)) - (totalLanesHeight / 2.0F);
        _spaceLanes[i]->SetPos({_player.GetMothership()->GetPos().x + laneXOffset,
                                _player.GetMothership()->GetPos().y + laneYOffset});
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

void GameScene::InitRandomDistributions()
{
    _randomGenerator = GetEngine();
    CreateDistribution(STARSHIP_DAMAGE, 100, 250);
    CreateDistribution(SPACELANE, 0, NUM_OF_LANES-1);
    CreateDistribution(ENEMY_STARSHIP_TYPE, 0, StarshipFactory::STARSHIP_TYPE::ENUM_COUNT - 2);
    CreateDistribution(STARSHIP_HEALING, 50, 100);
}

bool GameScene::InitStarshipBuilderButtons()
{
    _lightFighter = std::make_unique<LightFighter>(0);
    _heavyFighter = std::make_unique<HeavyFighter>(0);
    _supportShip = std::make_unique<SupportShip>(0);
    _destroyer = std::make_unique<Destroyer>(0);
    _battleship = std::make_unique<Battleship>(0);

    for (int i = 0; i < NUM_OF_BUTTONS; ++i)
    {
        _starshipBuilderButtons.emplace_back(std::make_unique<Button>("Resources/Textures/command_button_" + std::to_string(i) + ".png"));
        _starshipBuilderButtons[i]->SetColour(DEFAULT_BTN_COLOUR);
        _starshipBuilderButtons[i]->SetScale({0.20F, 0.20F});
    }

    _buttonStarshipDictionary[_starshipBuilderButtons[0].get()] = _lightFighter.get();
    _buttonStarshipDictionary[_starshipBuilderButtons[1].get()] = _heavyFighter.get();
    _buttonStarshipDictionary[_starshipBuilderButtons[2].get()] = _supportShip.get();
    _buttonStarshipDictionary[_starshipBuilderButtons[3].get()] = _destroyer.get();
    _buttonStarshipDictionary[_starshipBuilderButtons[4].get()] = _battleship.get();

    return true;
}

void GameScene::InitPlayerMothership()
{
    _player.CreateStarship(StarshipFactory::STARSHIP_TYPE::MOTHERSHIP, 2);
    _player.PaintMothership(_predefinedColours.LIGHTBLUE);
    _player.SetMothershipPosition({Constants::WINDOW_WIDTH * 0.085F, Constants::LEVEL_HEIGHT / 2.0f});
}

void GameScene::InitEnemyMothership()
{
    _enemy.CreateStarship(StarshipFactory::MOTHERSHIP, 2);
    _enemy.PaintMothership(_predefinedColours.LIGHTGREEN);
    auto mothershipXpos = _spaceLanes[0]->GetPos().x + _spaceLanes[0]->GetSize().x + _enemy.GetMothershipBounds().width / 1.4F;
    _enemy.SetMothershipPosition({mothershipXpos, Constants::LEVEL_HEIGHT / 2.0f});
    _enemy.SetMothershipRotation(180);
}

void GameScene::InitMainView()
{
    _mainView.setSize(Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT);
    auto playerMothershipBounds = _player.GetMothership()->GetSpriteComponent().GetSprite().getGlobalBounds();
    _mainView.setCenter(_player.GetMothership()->GetPos().x - playerMothershipBounds.width + Constants::WINDOW_WIDTH / 2.0F - 1.0F, _player.GetMothership()->GetPos().y);
}

void GameScene::InitMinimapView()
{
    minimap = std::make_unique<Minimap>(
            Constants::LEVEL_WIDTH,
            Constants::LEVEL_HEIGHT, // Note: Should be 3.0F?)
            Constants::Minimap::VIEWPORT_LEFT,
            Constants::Minimap::VIEWPORT_TOP,
            Constants::Minimap::VIEWPORT_WIDTH,
            Constants::Minimap::VIEWPORT_HEIGHT,
            _mainView);
}

void GameScene::InitMainViewBorder()
{
    _mainViewBorder.setSize({Constants::WINDOW_WIDTH,Constants::WINDOW_HEIGHT});
    _mainViewBorder.setOutlineThickness(10.0f);
    _mainViewBorder.setOutlineColor(_predefinedColours.GRAY);
    _mainViewBorder.setFillColor(sf::Color::Transparent);

    _mainViewBorderText.setFont(Chilli::CustomFonts::GetBoldFont());
    _mainViewBorderText.setString("Main View");
    _mainViewBorderText.setCharacterSize(56);
    _mainViewBorderText.setFillColor(sf::Color::White);
    _mainViewBorderText.setOutlineColor(sf::Color::Black);
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
        sf::Vector2f playerMothershipPos = _player.GetMothership()->GetSpriteComponent().GetPos();
        _spaceLanes[i]->SetPos({playerMothershipPos.x + laneXOffset, playerMothershipPos.y + laneYOffset});
        _spaceLanes[i]->SetSize({Constants::LEVEL_WIDTH*0.91F, 50.0F});
        _spaceLanes[i]->Init();
    }

    /*_spaceLanes[0]->SetColour(_predefinedColours.ORANGE);
    _spaceLanes[1]->SetColour(_predefinedColours.LIGHTBLUE);
    _spaceLanes[2]->SetColour(_predefinedColours.LIGHTGREEN);
    _spaceLanes[3]->SetColour(_predefinedColours.BLUEVIOLET);
    _spaceLanes[4]->SetColour(_predefinedColours.LIGHTRED);*/
}

void GameScene::InitEvents()
{
    /// Observer to starship deployment bar event
    auto starshipDeploymentBarCallback = std::bind(&GameScene::SpawnStarshipFromShipyard_OnStarshipDeploymentComplete, this);
    gameHud->GetStarshipDeploymentBar().AddBasicObserver({ProgressBar::EventID::TASK_COMPLETED, starshipDeploymentBarCallback});

    /// Agnostic observer to enemy starships destroyed event
    auto enemyStarshipsDestroyedCallback = std::bind(&GameScene::UpdateScrapMetal_OnEnemyStarshipDestroyed, this, std::placeholders::_1);
    _enemy.AddAgnosticObserver({Enemy::EventID::STARSHIP_DESTROYED, enemyStarshipsDestroyedCallback});

    /// Agnostic observer to player starships destroyed event
    auto playerStarshipsDestroyedCallback = std::bind(&GameScene::UpdateScrapMetal_OnPlayerStarshipDestroyed, this, std::placeholders::_1);
    _player.AddAgnosticObserver({Player::EventID::STARSHIP_DESTROYED, playerStarshipsDestroyedCallback});
}

void GameScene::SpawnStarshipFromShipyard_OnStarshipDeploymentComplete()
{
    if(_starshipTypeTrainingQueue.empty())
        return;

    _player.CreateStarship(_starshipTypeTrainingQueue.front(), _spaceLaneStarshipDeploymentQueue.front());
    auto starshipXPos = _spaceLanes[_spaceLaneStarshipDeploymentQueue.front()]->GetPos().x + 25.0F;
    auto starshipYPos = _spaceLanes[_spaceLaneStarshipDeploymentQueue.front()]->GetPos().y + _spaceLanes[_spaceLaneStarshipDeploymentQueue.front()]->GetSize().y / 2.0F;
    _player.SetStarshipPosition(_player.GetStarships().back(), {starshipXPos, starshipYPos});
    _starshipTypeTrainingQueue.pop();
    _spaceLaneStarshipDeploymentQueue.pop();
    gameHud->GetStarshipDeploymentBar().ResetProgress();

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

void GameScene::HandleStarshipBuilderButtonsInteractionMouseInput(const sf::Event &event)
{
    for (int i = 0; i < _starshipBuilderButtons.size(); i++)
    {
        auto &assignedStarshipToButton = _buttonStarshipDictionary[_starshipBuilderButtons[i].get()];
        bool starshipAffordable = _playerScrapMetalManager->GetCurrentScrapMetalAmount() >= assignedStarshipToButton->GetBuildCost();

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

void GameScene::BeginStarshipDeploymentProcess(int currentSpaceLaneSelectedIndex)
{
    auto& assignedStarshipToButton = _buttonStarshipDictionary[_starshipBuilderButtons[_starshipButtonSelectedIndex].get()];
    _playerScrapMetalManager->SpendScrap(static_cast<int>(assignedStarshipToButton->GetBuildCost()));
    _playerScrapMetalManager->UpdateScrapText("Scrap Metal: " + std::to_string(_playerScrapMetalManager->GetCurrentScrapMetalAmount()));

    _starshipTypeTrainingQueue.push(static_cast<StarshipFactory::STARSHIP_TYPE>(_starshipButtonSelectedIndex));
    _spaceLaneStarshipDeploymentQueue.push(currentSpaceLaneSelectedIndex);

    if(!gameHud->GetStarshipDeploymentBar().InProgress())
    {
        StartNextStarshipDeployment();
    }
}

void GameScene::StartNextStarshipDeployment()
{
    if(_starshipTypeTrainingQueue.empty())
        return;

    auto& assignedStarshipToButton = _buttonStarshipDictionary[_starshipBuilderButtons[_starshipTypeTrainingQueue.front()].get()];
    gameHud->GetStarshipDeploymentBar().SetProgressText("Deploying " + assignedStarshipToButton->GetStarshipName() + "...");
    gameHud->GetStarshipDeploymentBar().SetProgressSpeed(assignedStarshipToButton->GetTrainingSpeed());
    gameHud->GetStarshipDeploymentBar().SetProgressStatus(true);
}

void GameScene::UpdateScrapMetal_OnEnemyStarshipDestroyed(std::any eventData)
{
    auto destroyedEnemyStarshipData = std::any_cast<Enemy::StarshipDestroyedData>(eventData);
    _playerScrapMetalManager->CollectScrap(static_cast<int>(destroyedEnemyStarshipData.BuildCost));
    _playerScrapMetalManager->UpdateScrapText("Scrap Metal: " + std::to_string(_playerScrapMetalManager->GetCurrentScrapMetalAmount()));
    _playerScrapMetalManager->CreatePopup(destroyedEnemyStarshipData.BuildCost, destroyedEnemyStarshipData.DeathLocation);

    for (int i = 1; i < _player.GetStarshipCount(); ++i)
    {
        auto& playerStarship = _player.GetStarships()[i];
        if (playerStarship->GetSpeed() == 0)
        {
            playerStarship->SetSpeed(playerStarship->GetStartingSpeed());
        }
    }
}

void GameScene::UpdateScrapMetal_OnPlayerStarshipDestroyed(std::any eventData)
{
    auto destroyedPlayerStarshipData = std::any_cast<Player::StarshipDestroyedData>(eventData);
    _enemyScrapMetalManager->CollectScrap(static_cast<int>(destroyedPlayerStarshipData.BuildCost));
    _enemyScrapMetalManager->UpdateScrapText("Scrap Metal: " + std::to_string(_enemyScrapMetalManager->GetCurrentScrapMetalAmount()));
    _enemyScrapMetalManager->CreatePopup(destroyedPlayerStarshipData.BuildCost, destroyedPlayerStarshipData.DeathLocation);

    for (int i = 1; i < _enemy.GetStarshipCount(); ++i)
    {
        auto& enemyStarship = _enemy.GetStarships()[i];
        if (enemyStarship->GetSpeed() == 0)
        {
            enemyStarship->SetSpeed(enemyStarship->GetStartingSpeed());
        }
    }
}

