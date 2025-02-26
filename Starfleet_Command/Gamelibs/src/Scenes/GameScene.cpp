#include <cstdlib>
#include "Scenes/GameScene.hpp"

bool GameScene::Init()
{
    InitRandomDistributions();
    InitBackground();
    InitStarshipBuilderButtons();
    InitStarshipNameButtonText();
    InitPlayerFlagship();
    _playerScrapMetalManager = std::make_unique<ScrapMetalManager>(GetRegularFont(), _player.GetFlagship()->GetColour(), 2500);
    InitSpaceLanes();
    InitEnemyFlagship();
    _mothershipHealthBar[0] = std::make_unique<HealthBar>(_player.GetFlagship()->GetHealthComponent());
    _mothershipHealthBar[0]->SetMaxHealth(_player.GetFlagship()->GetHealth());
    _mothershipHealthBar[0]->SetScale(0.4F, 0.15F);

    _mothershipHealthBar[1] = std::make_unique<HealthBar>(_enemy.GetFlagship()->GetHealthComponent());
    _mothershipHealthBar[1]->SetMaxHealth(_enemy.GetFlagship()->GetHealth());
    _mothershipHealthBar[1]->SetScale(0.4F, 0.15F);

    _mothershipNameText[0].setString("Player Mothership");
    _mothershipNameText[0].setFillColor(_player.GetFlagship()->GetColour());

    _mothershipNameText[1].setString("Enemy Mothership");
    _mothershipNameText[1].setFillColor(_enemy.GetFlagship()->GetColour());
    for (int i = 0; i < 2; ++i)
    {
        _mothershipNameText[i].setOutlineColor(sf::Color::Black);
        _mothershipNameText[i].setOutlineThickness(1);
        _mothershipNameText[i].setFont(GetRegularFont());
        _mothershipNameText[i].setCharacterSize(14);
    }

    InitMainView();
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
    _playerScrapMetalManager->Update(window, deltaTime);
    UpdateMainViewMovement(window, deltaTime, mousePos);
    UpdateStarshipBuilderButtonsHoverStateAndColour();
    UpdateStarshipBuilderButtonPositions(window);
    _mainViewBorder.setPosition(_mainView.getCenter().x - _mainViewBorder.getSize().x/2.0F, _mainView.getCenter().y - _mainViewBorder.getSize().y/2.0F);
    minimap->Update(_mainView, window, deltaTime);
    _playerScrapMetalManager->SetTextPosition(_starshipBuilderButtons[0]->GetPos().x, _starshipBuilderButtons[_starshipBuilderButtons.size() - 1]->GetPos().y + _starshipBuilderButtons[_starshipBuilderButtons.size() - 1]->GetBounds().height * 1.15F);
    _starshipAssemblyBar.SetPosition({_starshipBuilderButtons[0]->GetPos().x, _starshipBuilderButtons[0]->GetPos().y - _starshipAssemblyBar.GetSize().height * 2.75F});
    _starshipAssemblyBar.Update(window, deltaTime);
    _starshipNameButtonText.setPosition(_starshipBuilderButtons[_starshipButtonHoveredOverIndex]->GetPos().x, _starshipBuilderButtons[0]->GetPos().y - 20.0F);
    _cursor.Update(window, deltaTime);
    _cursor.SetCursorPos(window, _mainView);
    _player.Update(window, deltaTime);
    _enemy.Update(window, deltaTime);

    _mothershipHealthBar[0]->SetPos({_mainView.getCenter().x - _mothershipHealthBar[0]->GetSpriteComponent().GetSprite().getGlobalBounds().width - Constants::WINDOW_WIDTH/3.0F, _mainView.getCenter().y - _mothershipHealthBar[0]->GetSpriteComponent().GetSprite().getGlobalBounds().height/2.0F + Constants::WINDOW_HEIGHT/2.265F});
    _mothershipHealthBar[1]->SetPos({_mainView.getCenter().x - _mothershipHealthBar[1]->GetSpriteComponent().GetSprite().getGlobalBounds().width + Constants::WINDOW_WIDTH/3.0F, _mainView.getCenter().y - _mothershipHealthBar[1]->GetSpriteComponent().GetSprite().getGlobalBounds().height/2.0F + Constants::WINDOW_HEIGHT/2.265F});

    _mothershipHealthBar[0]->Update(window, deltaTime);
    _mothershipHealthBar[1]->Update(window, deltaTime);

    _mothershipNameText[0].setPosition(_mothershipHealthBar[0]->GetPos().x + _mothershipHealthBar[0]->GetSpriteComponent().GetSprite().getGlobalBounds().width/2.0F, _mothershipHealthBar[0]->GetPos().y + _mothershipNameText[0].getGlobalBounds().height);
    _mothershipNameText[1].setPosition(_mothershipHealthBar[1]->GetPos().x + _mothershipHealthBar[1]->GetSpriteComponent().GetSprite().getGlobalBounds().width/2.0F, _mothershipHealthBar[1]->GetPos().y + _mothershipNameText[1].getGlobalBounds().height);

    //_starship->Update(window, deltaTime);
    UpdateEnemySpawner();

    /// Enemy starship movement and shooting
    for (int i = 1; i < _enemy.GetStarshipCount(); ++i)
    {
        if(_enemy.GetStarships()[i] == nullptr) return;

        auto& enemyStarship = _enemy.GetStarships()[i];
        _enemy.MoveStarship(i, {_enemy.GetStarships()[i]->GetSpeed() * deltaTime.asSeconds() * -1, 0});

        for(int j = 0; j < enemyStarship->GetProjectileCount(); j++)
        {
            if(enemyStarship->IsProjectileOutOfRange(j))
            {
                enemyStarship->DestroyProjectile(j);
            }
        }

        for(const auto &playerStarship : _player.GetStarships())
        {
            auto& playerSprite = playerStarship->GetSpriteComponent().GetSprite();
            if(enemyStarship->IsEnemyInRange(playerStarship) &&
               enemyStarship->CanAttackEnemy(playerStarship))
            {
                _enemy.GetStarships()[i]->SetSpeed(25);
                enemyStarship->ShootAt(enemyStarship->GetFireRate(), playerSprite.getPosition());
            }

            for(int k = 0; k < _enemy.GetStarships()[i]->GetProjectileCount(); k++)
            {
                auto& enemyBullet = _enemy.GetStarships()[i]->GetProjectile()[k]->GetSpriteComponent();
                if(playerStarship->CollidesWith(enemyBullet.GetSprite().getGlobalBounds()))
                {
                    int randDamage = _randomValueDistributions[STARSHIP_DAMAGE](_randomGenerator);
                    float scaledDamage = (float)randDamage * _enemy.GetStarships()[i]->GetDamageScaleFactor();
                    playerStarship->TakeDamage(scaledDamage);
                    _enemy.GetStarships()[i]->DestroyProjectile(k);
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

        for(int j = 0; j < playerStarship->GetProjectileCount(); j++)
        {
            if(playerStarship->IsProjectileOutOfRange(j))
            {
                playerStarship->DestroyProjectile(j);
            }
        }

        for(const auto &enemyStarship : _enemy.GetStarships())
        {
            auto& enemySprite = enemyStarship->GetSpriteComponent().GetSprite(); // QUESTION: Starship class accessor?
            if(playerStarship->IsEnemyInRange(enemyStarship) &&
               playerStarship->CanAttackEnemy(enemyStarship))
            {
                playerStarship->SetSpeed(25);
                playerStarship->ShootAt(playerStarship->GetFireRate(), enemySprite.getPosition());
            }

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
    window.draw(_starshipNameButtonText);
    _player.Render(window);
    _enemy.Render(window);
    //_starship->Render(window);
    _starshipAssemblyBar.Render(window);
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
    for (int i = 0; i < 2; ++i)
    {
        _mothershipHealthBar[i]->Render(window);
        window.draw(_mothershipNameText[i]);
    }

    /// Render the minimap
    window.setView(minimap->GetView());
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
        bool starshipAffordable =
                _playerScrapMetalManager->GetCurrentScrapMetalAmount() >= assignedStarshipToButton->GetBuildCost();

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
    _lightFighter = std::make_unique<LightFighter>(0);
    _heavyFighter = std::make_unique<HeavyFighter>(0);
    _supportShip = std::make_unique<SupportShip>(0);
    _destroyer = std::make_unique<Destroyer>(0);
    _battleship = std::make_unique<Battleship>(0);

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

        /*_shipInfoPanels[i].UpdateScrapText("Name: ");
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
    _player.CreateStarship(StarshipFactory::STARSHIP_TYPE::FLAGSHIP, 2);
    _player.PaintFlagship(_predefinedColours.LIGHTORANGE);
    _player.SetFlagshipPosition({Constants::WINDOW_WIDTH * 0.085F, Constants::LEVEL_HEIGHT/2.0f});
}

void GameScene::InitEnemyFlagship()
{
    _enemy.CreateStarship(StarshipFactory::FLAGSHIP, 2);
    _enemy.PaintFlagship(_predefinedColours.LIGHTGREEN);
    auto flagshipXpos = _spaceLanes[0]->GetPos().x + _spaceLanes[0]->GetSize().x + _enemy.GetFlagshipBounds().width/1.4F;
    _enemy.SetFlagshipPosition({flagshipXpos, Constants::LEVEL_HEIGHT / 2.0f});
    _enemy.SetFlagshipRotation(180);
}

void GameScene::InitMainView()
{
    _mainView.setSize(Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT);
    auto playerFlagshipBounds = _player.GetFlagship()->GetSpriteComponent().GetSprite().getGlobalBounds();
    _mainView.setCenter(_player.GetFlagship()->GetPos().x - playerFlagshipBounds.width + Constants::WINDOW_WIDTH/2.0F -1.0F, _player.GetFlagship()->GetPos().y);
}

void GameScene::InitMinimapView()
{
    minimap = std::make_unique<Minimap>(
            Constants::LEVEL_WIDTH,
            Constants::LEVEL_HEIGHT, // Note: Should be 3.0F?)
            Constants::Minimap::VIEWPORT_LEFT,
            Constants::Minimap::VIEWPORT_TOP,
            Constants::Minimap::VIEWPORT_WIDTH,
            Constants::Minimap::VIEWPORT_HEIGHT);
}

void GameScene::InitMainViewBorder()
{
    _mainViewBorder.setSize({Constants::WINDOW_WIDTH,Constants::WINDOW_HEIGHT});
    _mainViewBorder.setOutlineThickness(10.0f);
    _mainViewBorder.setOutlineColor(_predefinedColours.LIGHTBLUE);
    _mainViewBorder.setFillColor(sf::Color::Transparent);
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

    if(!_starshipAssemblyBar.InProgress())
    {
        StartNextStarshipDeployment();
    }
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
    auto destroyedEnemyStarshipData = std::any_cast<Enemy::StarshipDestroyedData>(eventData);
    _playerScrapMetalManager->CollectScrap(static_cast<int>(destroyedEnemyStarshipData.BuildCost));
    _playerScrapMetalManager->UpdateScrapText("Scrap Metal: " + std::to_string(_playerScrapMetalManager->GetCurrentScrapMetalAmount()));
    _playerScrapMetalManager->CreatePopup(destroyedEnemyStarshipData.BuildCost, destroyedEnemyStarshipData.DeathLocation);
}

