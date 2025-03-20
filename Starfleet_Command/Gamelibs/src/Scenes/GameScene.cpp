#include "Scenes/GameScene.hpp"

GameScene::~GameScene()
{
    if(_gameMusic.getStatus() == sf::Music::Playing)
    {
        _gameMusic.stop();
    }
}

bool GameScene::Init()
{
    InitRandomDistributions();
    _backgroundParallax = std::make_unique<ParallaxBackground>("Resources/Textures/space_nebula_2.png", sf::Color::Cyan, NUM_OF_STARS, _predefinedColours.LIGHTBLUE);
    InitPlayerMothership();
    InitSpaceLanes();
    InitEnemyMothership();

    auto& playerMothership = _player.GetMothership();
    auto& enemyMothership = _enemy.GetMothership();

    _playerScrapMetalManager = std::make_unique<ScrapMetalManager>(_predefinedColours.GRAY,playerMothership->GetColour(), STARTING_SCRAP_METAL);
    _enemyScrapMetalManager = std::make_unique<ScrapMetalManager>(_predefinedColours.GRAY,enemyMothership->GetColour(), STARTING_SCRAP_METAL);

    InitGameplayView();

    _mothershipStatusDisplay = std::make_unique<MothershipStatusDisplay>(playerMothership, enemyMothership, _gameplayView);

    _starshipDeploymentManager = std::make_unique<StarshipDeploymentManager>(STARSHIP_MAX_QUEUE_SIZE, playerMothership->GetColour());

    for (int i = 0; i < NUM_OF_BUTTONS; ++i)
    {
        _starshipDeploymentButtons[i] = std::make_unique<StarshipDeploymentButton>(static_cast<StarshipFactory::STARSHIP_TYPE>(i), playerMothership->GetColour());;
    }

    InitMinimapView();
    InitEvents();

    if(!_gameMusic.openFromFile("Resources/Audio/Rise_Above_Darkness_225bpm_131s.wav"))
    {
        std::cout << "Failed to to load menu soundtrack (Rise_Above_Darkness_225bpm_131s)" << std::endl;
        return false;
    }
    else
    {
        if(_isMusicOn)
        {
            _gameMusic.play();
        }
        //_gameMusic.setPlayingOffset(sf::seconds(2.0F));
        _gameMusic.setLoop(true);
    }

    _musicIconButtons[MUSIC_ON_BUTTON] = std::make_unique<Button>("Resources/Textures/musicOn.png");
    _musicIconButtons[MUSIC_OFF_BUTTON] = std::make_unique<Button>("Resources/Textures/musicOff.png");
    for (int i = 0; i < 2; ++i)
    {
        _musicIconButtons[i]->SetColour(sf::Color(22, 155, 164, 100));
    }

    /*_nextMusicTrackButton = std::make_unique<Button>("Resources/Textures/next.png");
    _nextMusicTrackButton->SetColour(sf::Color(22, 155, 164, 100));
    _nextMusicTrackButton->SetScale({0.65F, 0.65F});*/

    return true;
}

void GameScene::EventHandler(sf::RenderWindow& window, sf::Event& event)
{
    _player.EventHandler(window, event);
    HandleViewScrollingKeyboardInput(event);
    _minimap->EventHandler(window, event);

    for (auto& deploymentButton : _starshipDeploymentButtons)
    {
        if(_starshipDeploymentManager->IsQueueFull())
            return;

        deploymentButton->EventHandler(window, event);
    }


    for (int i = 0; i < NUM_OF_BUTTONS; ++i)
    {
        if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left && _starshipDeploymentButtons[i]->IsPlacingStarship())
        {
            for (int j = 0; j < _spaceLanes.size(); ++j)
            {
                if(_spaceLanes[j]->IsCursorHoveredOver())
                {
                    _playerScrapMetalManager->SpendScrap(_starshipDeploymentButtons[i]->GetBuildCost());
                    _playerScrapMetalManager->SetScrapText("Scrap Metal: " + std::to_string(_playerScrapMetalManager->GetCurrentScrapMetalAmount()));

                    _starshipDeploymentManager->AddStarshipToQueue(_starshipDeploymentButtons[i]->GetStarshipType(), j);

                    if(not _starshipDeploymentManager->IsCurrentlyDeploying())
                    {
                        StartNextStarshipDeployment();
                    }
                }
            }

            _starshipDeploymentButtons[i]->ResetAfterStarshipPlacement();
        }
    }




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




    if(_musicIconButtons[_isMusicOn ? MUSIC_ON_BUTTON : MUSIC_OFF_BUTTON]->IsCursorHoveredOver())
    {
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            if (_isMusicOn)
            {
                _gameMusic.pause();
            }
            else
            {
                _gameMusic.play();
            }
            _isMusicOn = !_isMusicOn;
        }
    }

    /*if(_nextMusicTrackButton->IsCursorHoveredOver())
    {
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            if(_isMusicOn)
            {
                // increment track counter
            }
        }
    }*/
}

void GameScene::Update(sf::RenderWindow& window, sf::Time deltaTime)
{
    auto mousePos = sf::Mouse::getPosition(window); // Mouse _innerPosition relative to the window
    UpdateGameplayViewMovement(window, deltaTime, mousePos);

    for (int i = 0; i < NUM_OF_BUTTONS; ++i)
    {
        auto column_spacing = 10.0F;
        //auto xPos = _gameplayView.getCenter().x - _starshipDeploymentButtons[0]->GetBounds().width / 2.0F - Constants::WINDOW_WIDTH / 8.0F + (i * (_starshipDeploymentButtons[0]->GetBounds().width + column_spacing));
        auto xPos = _gameplayView.getCenter().x - (_starshipDeploymentButtons[i]->GetBounds().width/2.0F * NUM_OF_BUTTONS + (column_spacing/2.0F * NUM_OF_BUTTONS))  + (i * (_starshipDeploymentButtons[0]->GetBounds().width + column_spacing));
        auto yPos = _gameplayView.getCenter().y + Constants::WINDOW_HEIGHT * 0.4F;
        _starshipDeploymentButtons[i]->SetPos({xPos, yPos});
        _starshipDeploymentButtons[i]->SetAffordable(_playerScrapMetalManager->GetCurrentScrapMetalAmount() >= _starshipDeploymentButtons[i]->GetBuildCost()); // NOTE: Unsure about this
        _starshipDeploymentButtons[i]->Update(window, deltaTime);

        if(_starshipDeploymentManager->IsQueueFull())
        {
            _starshipDeploymentButtons[i]->SetColour(_predefinedColours.LIGHTORANGE);
        }
    }

    _mothershipStatusDisplay->Update(window, deltaTime);
    _starshipDeploymentManager->SetDeploymentBarPos({_starshipDeploymentButtons[0]->GetPos().x, _starshipDeploymentButtons[0]->GetPos().y - _starshipDeploymentManager->GetDeploymentBar().GetSize().height * 3.5F});
    _starshipDeploymentManager->Update(window, deltaTime);
    _playerScrapMetalManager->Update(window, deltaTime);
    _enemyScrapMetalManager ->Update(window, deltaTime);
    _playerScrapMetalManager->SetTextPosition(_mothershipStatusDisplay->GetPlayerMothershipTextPos().x + _mothershipStatusDisplay->GetPlayerMothershipTextBounds().width / 2.0F - _playerScrapMetalManager->GetTextSize().width / 2.0F, _mothershipStatusDisplay->GetPlayerMothershipTextPos().y + _mothershipStatusDisplay->GetPlayerMothershipTextBounds().height + 10.0F);
    _enemyScrapMetalManager ->SetTextPosition(_mothershipStatusDisplay->GetEnemyMothershipTextPos().x + _mothershipStatusDisplay->GetEnemyMothershipTextBounds().width / 2.0F - _enemyScrapMetalManager->GetTextSize().width / 2.0F, _mothershipStatusDisplay->GetEnemyMothershipTextPos().y + _mothershipStatusDisplay->GetEnemyMothershipTextBounds().height + 10.0F);
    _minimap->Update(window, deltaTime);
    _cursor.Update(window, deltaTime);
    _cursor.SetCursorPos(window, _gameplayView);
    _player.Update(window, deltaTime);
    _enemy.Update(window, deltaTime);

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
            if (enemyStarship != friendlyStarship)
            {
                if (enemyStarship->IsInSameLaneAs(friendlyStarship) &&
                    enemyStarship->IsFriendlyStarshipAhead(friendlyStarship))
                {
                    enemyStarship->SetSpeed(friendlyStarship->GetSpeed());
                }
            }
        }

        /// Enemy starship self-destruction when reaching end of it's lane
        if(enemyStarship->GetPos().x < _spaceLanes[0]->GetPos().x) // NOTE: Doesn't matter which lane as they all have the same xPos
        {
            enemyStarship->TakeDamage(enemyStarship->GetMaxHealth());
            _player.GetMothership()->TakeDamage(enemyStarship->GetMaxHealth());
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

        auto* supportShip = dynamic_cast<SupportShip*>(enemyStarship.get());
        if(supportShip)
        {
            for (int j = 1; j < _enemy.GetStarshipCount(); ++j)
            {
                auto& friendlyStarship = _enemy.GetStarships()[j];
                if(enemyStarship != friendlyStarship)
                {
                    if(supportShip->IsInSameLaneAs(friendlyStarship) &&
                            supportShip->IsFriendlyStarshipAhead(friendlyStarship))
                    {
                        if(friendlyStarship->GetHealth() >= friendlyStarship->GetMaxHealth())
                            break;

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

        /// Player starship self-destruction when reaching end of it's lane
        if(playerStarship->GetPos().x > _spaceLanes[0]->GetPos().x + _spaceLanes[0]->GetSize().x) // NOTE: Doesn't matter which lane as they all have the same xPos
        {
            playerStarship->TakeDamage(playerStarship->GetMaxHealth());
            _enemy.GetMothership()->TakeDamage(playerStarship->GetMaxHealth());
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
                        if(friendlyStarship->GetHealth() >= friendlyStarship->GetMaxHealth())
                            break;

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
    //UpdateStarshipPreviewSpritePosition(worldPositionOfMouse);
    _backgroundParallax->Update(window, deltaTime);





    for (const auto & _musicIconButton : _musicIconButtons)
    {
        _musicIconButton->Update(window);
        _musicIconButton->SetPos({_gameplayView.getCenter().x - Constants::WINDOW_WIDTH/2.0F + 10.0F, _gameplayView.getCenter().y - Constants::WINDOW_HEIGHT/2.0F + 10.0F});
    }

    for (const auto & musicIconButton : _musicIconButtons)
    {
        if(musicIconButton->IsCursorHoveredOver())
        {
            musicIconButton->SetColour(_predefinedColours.LIGHTBLUE);
        }
        else
        {
            musicIconButton->SetColour(sf::Color(22, 155, 164, 100));
        }
    }

    /*_nextMusicTrackButton->Update(window);
    _nextMusicTrackButton->SetPos({_musicIconButtons[MUSIC_ON_BUTTON]->GetPos().x +_nextMusicTrackButton->GetBounds().width + 10.0F, _musicIconButtons[MUSIC_ON_BUTTON]->GetPos().y + 10.0F});

    if(_nextMusicTrackButton->IsCursorHoveredOver())
    {
        _nextMusicTrackButton->SetColour(_predefinedColours.LIGHTBLUE);
    }
    else
    {
        _nextMusicTrackButton->SetColour(sf::Color(22, 155, 164, 100));
    }*/
}

void GameScene::Render(sf::RenderWindow& window)
{
    window.setView(_gameplayView);
    RenderGameplayViewSprites(window);

    window.setView(_minimap->GetView());
    RenderMinimapSprites(window);

    window.setView(_gameplayView);
    _cursor.Render(window);
}

void GameScene::RenderMinimapSprites(sf::RenderWindow &window)
{
    _backgroundParallax->RenderBackground(window);
    _minimap->RenderGameplayView(window);
    _player.Render(window);
    _enemy.Render(window);
    for (const auto &lane : _spaceLanes)
    {
        lane->Render(window);
    }
}

void GameScene::RenderGameplayViewSprites(sf::RenderWindow &window)
{
    _backgroundParallax->Render(window);
    _player.Render(window);
    _enemy.Render(window);
    _minimap->Render(window);
    for (const auto &lane : _spaceLanes)
    {
        lane->Render(window);
    }
    _playerScrapMetalManager->Render(window);
    _enemyScrapMetalManager->Render(window);
    _mothershipStatusDisplay->Render(window);
    _starshipDeploymentManager->Render(window);
    for (auto& deploymentButton : _starshipDeploymentButtons)
    {
        deploymentButton->Render(window);
    }
    _musicIconButtons[_isMusicOn ? MUSIC_ON_BUTTON : MUSIC_OFF_BUTTON]->Render(window);
    //_nextMusicTrackButton->Render(window);
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
            _enemyScrapMetalManager->SetScrapText(
                    "Scrap Metal: " + std::to_string(_enemyScrapMetalManager->GetCurrentScrapMetalAmount()));
        }
        _enemySpawnTimer += _enemySpawnRate;
    }
}

void GameScene::UpdateGameplayViewMovement(const sf::RenderWindow &window, const sf::Time &deltaTime, const sf::Vector2i &mousePos)
{
    // Thresholds for detecting mouse proximity to window borders
    const float EDGE_OFFSET = 200.0F;
    auto mouseProximityToLeftWindowEdge = EDGE_OFFSET;
    auto mouseProximityToRightWindowEdge = (float)window.getSize().x - EDGE_OFFSET;

    // Current boundaries of the view in world coordinates
    auto viewportLeftBoundary = _gameplayView.getCenter().x - _gameplayView.getSize().x / 2.0F;
    auto viewportRightBoundary = _gameplayView.getCenter().x + _gameplayView.getSize().x / 2.0F;

    // Viewport movement conditions
    bool isMouseNearLeftEdge = (float)mousePos.x <= mouseProximityToLeftWindowEdge && mousePos.x > 0;
    bool isMouseNearRightEdge = (float)mousePos.x >= mouseProximityToRightWindowEdge && mousePos.x < window.getSize().x;
    bool isViewportLeftEdgeWithinMothershipFocus = viewportLeftBoundary > _player.GetMothership()->GetPos().x - _player.GetMothership()->GetSpriteComponent().GetSprite().getGlobalBounds().width; // BUG: Gameplay view stops moving a few pixels too far when scrolling view left
    bool isViewportRightEdgeWithinRightSideOfEnemyMothership = viewportRightBoundary < _enemy.GetMothership()->GetPos().x + _enemy.GetMothershipBounds().width;
    bool isMouseYposWithinWindowBounds = mousePos.y >= 0 and mousePos.y <= window.getSize().y;

    if(viewportLeftBoundary >= _player.GetMothership()->GetPos().x - _player.GetMothership()->GetSpriteComponent().GetSprite().getGlobalBounds().width &&
       _scrollViewLeft)
    {
        _gameplayView.move(-VIEW_SCROLL_SPEED * deltaTime.asSeconds(), 0.0F);
    }
    else if(_scrollViewRight && isViewportRightEdgeWithinRightSideOfEnemyMothership)
    {
        _gameplayView.move(VIEW_SCROLL_SPEED * deltaTime.asSeconds(), 0.0F);
    }

    if(isMouseNearLeftEdge and isViewportLeftEdgeWithinMothershipFocus and isMouseYposWithinWindowBounds)
    {
        _gameplayView.move(-VIEW_SCROLL_SPEED * deltaTime.asSeconds(), 0.0F);
    }
    else if(isMouseNearRightEdge and isViewportRightEdgeWithinRightSideOfEnemyMothership and isMouseYposWithinWindowBounds)
    {
        _gameplayView.move(VIEW_SCROLL_SPEED * deltaTime.asSeconds(), 0.0F);
    }

    // Set gameplay view to focus on the player mothership if the mothership passes a set distance from the left view boundary
    if(viewportLeftBoundary < _player.GetMothership()->GetPos().x - _player.GetMothership()->GetSpriteComponent().GetSprite().getGlobalBounds().width)
    {
        _gameplayView.move(0, 0);
    }
}

void GameScene::UpdateSpaceLanePositionsAndMouseHoverColour(sf::RenderWindow &window, sf::Time &deltaTime)
{
    for (int i = 0; i < NUM_OF_LANES; ++i)
    {
        float laneHeight = _spaceLanes[i]->GetSize().y;
        float totalLanesHeight = (laneHeight * (float) NUM_OF_LANES) + (LANE_ROW_SPACING * ((float) NUM_OF_LANES - 1));
        float laneXOffset = 75.0F;
        float laneYOffset = ((float)i * (laneHeight + LANE_ROW_SPACING)) - (totalLanesHeight / 2.0F);
        _spaceLanes[i]->SetPos({_player.GetMothership()->GetPos().x + laneXOffset,
                                _player.GetMothership()->GetPos().y + laneYOffset});
        _spaceLanes[i]->Update(window, deltaTime);
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

void GameScene::InitGameplayView()
{
    _gameplayView.setSize(Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT);
    auto playerMothershipBounds = _player.GetMothership()->GetSpriteComponent().GetSprite().getGlobalBounds();
    _gameplayView.setCenter(_player.GetMothership()->GetPos().x - playerMothershipBounds.width + Constants::WINDOW_WIDTH / 2.0F - 1.0F, _player.GetMothership()->GetPos().y);
}

void GameScene::InitMinimapView()
{
    _minimap = std::make_unique<Minimap>(
            Constants::LEVEL_WIDTH,
            Constants::LEVEL_HEIGHT,
            Constants::Minimap::VIEWPORT_LEFT,
            Constants::Minimap::VIEWPORT_TOP,
            Constants::Minimap::VIEWPORT_WIDTH,
            Constants::Minimap::VIEWPORT_HEIGHT,
            _gameplayView);
}

void GameScene::InitSpaceLanes()
{
    for (int i = 0; i < NUM_OF_LANES; ++i)
    {
        _spaceLanes.emplace_back(std::make_unique<SpaceLane>());

        float laneHeight = _spaceLanes[i]->GetSize().y;
        float totalLanesHeight = (laneHeight * (float)NUM_OF_LANES) + (LANE_ROW_SPACING * ((float)NUM_OF_LANES - 1));
        float laneXOffset = 75.0F;
        float laneYOffset = ((float)i * (laneHeight + LANE_ROW_SPACING)) - (totalLanesHeight / 2.0F);
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
    _starshipDeploymentManager->GetDeploymentBar().AddBasicObserver({ProgressBar::EventID::TASK_COMPLETED, starshipDeploymentBarCallback});

    /// Agnostic observer to enemy starships destroyed event
    auto enemyStarshipsDestroyedCallback = std::bind(&GameScene::UpdateScrapMetal_OnEnemyStarshipDestroyed, this, std::placeholders::_1);
    _enemy.AddAgnosticObserver({Enemy::EventID::STARSHIP_DESTROYED, enemyStarshipsDestroyedCallback});

    /// Agnostic observer to player starships destroyed event
    auto playerStarshipsDestroyedCallback = std::bind(&GameScene::UpdateScrapMetal_OnPlayerStarshipDestroyed, this, std::placeholders::_1);
    _player.AddAgnosticObserver({Player::EventID::STARSHIP_DESTROYED, playerStarshipsDestroyedCallback});
}

void GameScene::SpawnStarshipFromShipyard_OnStarshipDeploymentComplete()
{
    if(_starshipDeploymentManager->IsQueueEmpty())
        return;

    int nextSpacelaneInQueue = _starshipDeploymentManager->GetNextSpacelaneInQueue();
    _player.CreateStarship(_starshipDeploymentManager->GetNextStarshipTypeInQueue(), nextSpacelaneInQueue);

    auto starshipXPos = _spaceLanes[nextSpacelaneInQueue]->GetPos().x + 25.0F;
    auto starshipYPos = _spaceLanes[nextSpacelaneInQueue]->GetPos().y + _spaceLanes[nextSpacelaneInQueue]->GetSize().y / 2.0F;
    _player.SetStarshipPosition(_player.GetStarships().back(), {starshipXPos, starshipYPos});

    _starshipDeploymentManager->RemoveFirstStarshipInQueue();
    _starshipDeploymentManager->GetDeploymentBar().ResetProgress();

    if(not _starshipDeploymentManager->IsQueueEmpty())
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

void GameScene::StartNextStarshipDeployment()
{
    if(_starshipDeploymentManager->IsQueueEmpty())
        return;

    _starshipDeploymentManager->GetDeploymentBar().SetProgressText("Deploying " + _starshipDeploymentButtons[static_cast<int>(_starshipDeploymentManager->GetNextStarshipTypeInQueue())]->GetStarshipName() + "...");
    _starshipDeploymentManager->GetDeploymentBar().SetProgressSpeed(_starshipDeploymentButtons[_starshipDeploymentManager->GetNextStarshipTypeInQueue()]->GetStarshipDeploymentSpeed());
    _starshipDeploymentManager->GetDeploymentBar().SetProgressStatus(true);
}

void GameScene::UpdateScrapMetal_OnEnemyStarshipDestroyed(std::any eventData)
{
    auto destroyedEnemyStarshipData = std::any_cast<Enemy::StarshipDestroyedData>(eventData);
    _playerScrapMetalManager->CollectScrap(static_cast<int>(destroyedEnemyStarshipData.BuildCost));
    _playerScrapMetalManager->SetScrapText("Scrap Metal: " + std::to_string(_playerScrapMetalManager->GetCurrentScrapMetalAmount()));
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
    _enemyScrapMetalManager->SetScrapText("Scrap Metal: " + std::to_string(_enemyScrapMetalManager->GetCurrentScrapMetalAmount()));
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



