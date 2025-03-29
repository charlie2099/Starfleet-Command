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
    _backgroundParallax = std::make_unique<ParallaxBackground>("Resources/Textures/space_nebula_2.png", sf::Color::Cyan, NUM_OF_STARS, _predefinedColours.LIGHTBLUE);
    InitPlayerMothership();
    InitSpaceLanes();
    InitEnemyMothership();

    auto& playerMothership = _player.GetMothership();
    auto& enemyMothership = _enemy.GetMothership();

    _playerScrapMetalManager = std::make_unique<ScrapMetalManager>(_predefinedColours.GRAY,playerMothership->GetColour(), STARTING_SCRAP_METAL);
    _enemyScrapMetalManager = std::make_unique<ScrapMetalManager>(_predefinedColours.GRAY,enemyMothership->GetColour(), STARTING_SCRAP_METAL);

    InitGameplayView();

    _aiDirector = std::make_unique<AiDirector>(_player, _enemy, _spaceLanes, _gameplayView);

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
        if (event.type == sf::Event::MouseButtonReleased and event.mouseButton.button == sf::Mouse::Left and _starshipDeploymentButtons[i]->IsPlacingStarship())
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
        _spaceLane->SetColour(_spaceLane->IsCursorHoveredOver() ? HIGHLIGHT_LANE_COLOUR : DEFAULT_LANE_COLOUR);
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
        if (event.type == sf::Event::MouseButtonPressed and event.mouseButton.button == sf::Mouse::Left)
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
        if (event.type == sf::Event::MouseButtonPressed and event.mouseButton.button == sf::Mouse::Left)
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

    _mothershipStatusDisplay->Update(window, deltaTime);

    for (int i = 0; i < NUM_OF_BUTTONS; ++i)
    {
        auto column_spacing = 5.0F;
        auto xPos = _mothershipStatusDisplay->GetPlayerMothershipTextPos().x + (i * (_starshipDeploymentButtons[0]->GetBounds().width + column_spacing));
        auto yPos = _mothershipStatusDisplay->GetPlayerMothershipTextPos().y + _mothershipStatusDisplay->GetPlayerMothershipTextBounds().height*3.75F;
        _starshipDeploymentButtons[i]->SetPos({xPos, yPos});
        _starshipDeploymentButtons[i]->SetAffordable(_playerScrapMetalManager->GetCurrentScrapMetalAmount() >= _starshipDeploymentButtons[i]->GetBuildCost()); // NOTE: Unsure about this
        _starshipDeploymentButtons[i]->Update(window, deltaTime);

        if(_starshipDeploymentManager->IsQueueFull())
        {
            _starshipDeploymentButtons[i]->SetColour(_predefinedColours.LIGHTORANGE);
        }
    }

    //_starshipDeploymentManager->SetDeploymentBarPos({_starshipDeploymentButtons[0]->GetPos().x, _starshipDeploymentButtons[0]->GetPos().y - 55.0F});
    _starshipDeploymentManager->SetDeploymentBarPos({_starshipDeploymentButtons[0]->GetPos().x, _starshipDeploymentButtons[0]->GetPos().y + 45.0F});
    _starshipDeploymentManager->Update(window, deltaTime);
    _playerScrapMetalManager->Update(window, deltaTime);
    _enemyScrapMetalManager ->Update(window, deltaTime);
    _playerScrapMetalManager->SetTextPosition(_mothershipStatusDisplay->GetPlayerMothershipTextPos().x, _mothershipStatusDisplay->GetPlayerMothershipTextPos().y + _mothershipStatusDisplay->GetPlayerMothershipTextBounds().height + 5.0F);
    _enemyScrapMetalManager ->SetTextPosition(_mothershipStatusDisplay->GetEnemyMothershipTextPos().x + 15.0F, _mothershipStatusDisplay->GetEnemyMothershipTextPos().y + _mothershipStatusDisplay->GetEnemyMothershipTextBounds().height + 5.0F);
    //_enemyScrapMetalManager ->SetTextPosition(_mothershipStatusDisplay->GetEnemyMothershipTextPos().x + _mothershipStatusDisplay->GetEnemyMothershipTextBounds().width / 2.0F - _enemyScrapMetalManager->GetTextSize().width / 2.0F, _mothershipStatusDisplay->GetEnemyMothershipTextPos().y + _mothershipStatusDisplay->GetEnemyMothershipTextBounds().height + 10.0F);

    _minimap->Update(window, deltaTime);
    _cursor.Update(window, deltaTime);
    _cursor.SetCursorPos(window, _gameplayView);
    _player.Update(window, deltaTime);
    _enemy.Update(window, deltaTime);

    //UpdateEnemySpawner();
    _aiDirector->Update(window, deltaTime);







    auto* playerMothership = dynamic_cast<Mothership*>(_player.GetMothership().get());
    if(playerMothership)
    {
        playerMothership->SetDamageLocation({
            _mothershipStatusDisplay->GetPlayerMothershipTextPos().x + _mothershipStatusDisplay->GetPlayerMothershipTextBounds().width/2.0F,
            _mothershipStatusDisplay->GetPlayerMothershipTextPos().y - _mothershipStatusDisplay->GetPlayerMothershipTextBounds().height*2.5F});
    }

    auto* enemyMothership = dynamic_cast<Mothership*>(_enemy.GetMothership().get());
    if(enemyMothership)
    {
        enemyMothership->SetDamageLocation({
            _mothershipStatusDisplay->GetEnemyMothershipTextPos().x + _mothershipStatusDisplay->GetEnemyMothershipTextBounds().width/2.0F,
            _mothershipStatusDisplay->GetEnemyMothershipTextPos().y - _mothershipStatusDisplay->GetEnemyMothershipTextBounds().height*2.5F});
    }


    /*for (int i = 1; i < _enemy.GetStarshipCount(); ++i)
    {
        if (_enemy.GetStarships()[i] == nullptr) return;

        auto &enemyStarship = _enemy.GetStarships()[i];
        auto &playerMothershipp = _player.GetMothership();


        /// Enemy  starship enemy engagement
        *//*enemyStarship->IsEnemyInRange(playerMothershipp)*//*
        if(Chilli::Vector::Distance(enemyStarship->GetPos(), playerMothershipp->GetPos()) <=(enemyStarship->GetAttackRange()*2.0F))
        {
            enemyStarship->ShootAt(playerMothershipp->GetPos());
        }

        /// Enemy projectile collision handling
        for(int k = 0; k < enemyStarship->GetProjectileCount(); k++)
        {
            auto& enemyBullet = enemyStarship->GetProjectile()[k]->GetSpriteComponent();
            if(playerMothershipp->CollidesWith(enemyBullet.GetSprite().getGlobalBounds()))
            {
                int randDamage = _starshipDamageRNG.GenerateNumber();
                float scaledDamage = (float)randDamage * enemyStarship->GetDamageScaleFactor();
                playerMothershipp->TakeDamage(scaledDamage);
                enemyStarship->DestroyProjectile(k);
            }
        }
    }*/




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
                if (enemyStarship->IsInSameLaneAs(friendlyStarship) and
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
            if(enemyStarship->IsEnemyInRange(playerStarship) and
                enemyStarship->CanEngageWith(playerStarship))
            {
                enemyStarship->ShootAt(playerStarship->GetPos());

                if(enemyStarship->IsInSameLaneAs(playerStarship) and
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
                    int randDamage = _starshipDamageRNG.GenerateNumber();
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
                    if(supportShip->IsInSameLaneAs(friendlyStarship) and
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
                            int randHealAmount = _starshipHealRNG.GenerateNumber();
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
                if (playerStarship->IsInSameLaneAs(friendlyStarship) and
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
            if(playerStarship->IsEnemyInRange(enemyStarship) and
               playerStarship->CanEngageWith(enemyStarship))
            {
                playerStarship->ShootAt(enemyStarship->GetPos());

                if(playerStarship->IsInSameLaneAs(enemyStarship) and
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
                    int randDamage = _starshipDamageRNG.GenerateNumber();
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
                    if(supportShip->IsInSameLaneAs(friendlyStarship) and
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
                            int randHealAmount = _starshipHealRNG.GenerateNumber();
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
    _aiDirector->Render(window);
    window.draw(boundaryEdgeHighlighterBox);
    //_nextMusicTrackButton->Render(window);
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
            int randomStarshipType = _enemyStarshipTypeRNG.GenerateNumber();
            int randomLane = _spacelaneSpawnRNG.GenerateNumber();
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
    /*for (int i = 0; i < _starshipDeploymentButtons.size(); ++i)
    {
        if(_starshipDeploymentButtons[i]->IsPlacingStarship())
        {
            return;
        }
    }*/

    float windowWidth = static_cast<float>(window.getSize().x);
    float windowHeight = static_cast<float>(window.getSize().y);

    // Calculate edge offsets based on window size
    float edgeOffset = windowWidth * MOUSE_WINDOW_EDGE_OFFSET_PCT;
    float topOffset = windowHeight * MOUSE_WINDOW_TOP_OFFSET_PCT;
    float bottomOffset = windowHeight * MOUSE_WINDOW_BOTTOM_OFFSET_PCT;

    // Calculate the view-to-window ratios
    float viewToWindowRatioX = _gameplayView.getSize().x / windowWidth;
    float viewToWindowRatioY = _gameplayView.getSize().y / windowHeight;

    // Convert to view coordinates
    float edgeOffsetInViewCoords = edgeOffset * viewToWindowRatioX;
    float topOffsetInViewCoords = topOffset * viewToWindowRatioY;
    float bottomOffsetInViewCoords = bottomOffset * viewToWindowRatioY;

    // Set the highlighter box size in view coordinates
    boundaryEdgeHighlighterBox.setSize({edgeOffsetInViewCoords,
                                        _gameplayView.getSize().y - topOffsetInViewCoords - bottomOffsetInViewCoords});

    // Thresholds for detecting mouse proximity to window borders (in window coordinates)
    float mouseProximityToLeftWindowEdge = edgeOffset;
    float mouseProximityToRightWindowEdge = windowWidth - edgeOffset;

    // Current boundaries of the view in world coordinates
    float viewportLeftBoundary = _gameplayView.getCenter().x - _gameplayView.getSize().x / 2.0F;
    float viewportRightBoundary = _gameplayView.getCenter().x + _gameplayView.getSize().x / 2.0F;

    // Viewport movement conditions
    bool isMouseNearLeftEdge = static_cast<float>(mousePos.x) <= mouseProximityToLeftWindowEdge and mousePos.x > 0;
    bool isMouseNearRightEdge = static_cast<float>(mousePos.x) >= mouseProximityToRightWindowEdge and mousePos.x < windowWidth;
    bool isViewportLeftEdgeWithinMothershipFocus = viewportLeftBoundary > 0;
    bool isViewportRightEdgeWithinRightSideOfEnemyMothership = viewportRightBoundary < _enemy.GetMothership()->GetPos().x + 60.0F;
    bool isMouseYposWithinWindowBounds = static_cast<float>(mousePos.y) >= topOffset and
                                         static_cast<float>(mousePos.y) <= windowHeight - bottomOffset;

    if(viewportLeftBoundary >= 0 and _scrollViewLeft)
    {
        _gameplayView.move(-VIEW_SCROLL_SPEED * deltaTime.asSeconds(), 0.0F);
    }
    else if(_scrollViewRight and isViewportRightEdgeWithinRightSideOfEnemyMothership)
    {
        _gameplayView.move(VIEW_SCROLL_SPEED * deltaTime.asSeconds(), 0.0F);
    }

    if(isMouseNearLeftEdge and isViewportLeftEdgeWithinMothershipFocus and isMouseYposWithinWindowBounds)
    {
        boundaryEdgeHighlighterBox.setPosition({viewportLeftBoundary,
                                                _gameplayView.getCenter().y - _gameplayView.getSize().y/2.0F + topOffsetInViewCoords});
        boundaryEdgeHighlighterBox.setFillColor({100, 100, 100, 25});
        _gameplayView.move(-VIEW_SCROLL_SPEED * deltaTime.asSeconds(), 0.0F);
    }
    else if(isMouseNearRightEdge and isViewportRightEdgeWithinRightSideOfEnemyMothership and isMouseYposWithinWindowBounds)
    {
        boundaryEdgeHighlighterBox.setPosition({viewportRightBoundary - boundaryEdgeHighlighterBox.getSize().x,
                                                _gameplayView.getCenter().y - _gameplayView.getSize().y/2.0F + topOffsetInViewCoords});
        boundaryEdgeHighlighterBox.setFillColor({100, 100, 100, 25});
        _gameplayView.move(VIEW_SCROLL_SPEED * deltaTime.asSeconds(), 0.0F);
    }
    else
    {
        boundaryEdgeHighlighterBox.setFillColor(sf::Color::Transparent);
    }
}

void GameScene::UpdateSpaceLanePositionsAndMouseHoverColour(sf::RenderWindow &window, sf::Time &deltaTime)
{
    for (int i = 0; i < NUM_OF_LANES; ++i)
    {
       /* float laneHeight = _spaceLanes[i]->GetSize().y;
        float totalLanesHeight = (laneHeight * (float) NUM_OF_LANES) + (LANE_ROW_SPACING * ((float) NUM_OF_LANES - 1));
        float laneXOffset = 75.0F;
        float laneYOffset = ((float)i * (laneHeight + LANE_ROW_SPACING)) - (totalLanesHeight / 2.0F);
        _spaceLanes[i]->SetPos({_player.GetMothership()->GetPos().x + laneXOffset,_player.GetMothership()->GetPos().y + laneYOffset});*/
        float laneHeight = _spaceLanes[i]->GetSize().y;
        float totalLanesHeight = (laneHeight * (float)NUM_OF_LANES) + (LANE_ROW_SPACING * ((float)NUM_OF_LANES - 1));
        sf::Vector2f playerMothershipPos = _player.GetMothership()->GetPos();
        float spacelaneXPos = playerMothershipPos.x + _player.GetMothershipBounds().width/1.8F;
        float spacelaneYPos = playerMothershipPos.y + ((float)i * (laneHeight + LANE_ROW_SPACING)) - (totalLanesHeight / 2.0F);
        _spaceLanes[i]->SetPos({spacelaneXPos, spacelaneYPos});
        _spaceLanes[i]->Update(window, deltaTime);
    }
}

void GameScene::InitPlayerMothership()
{
    _player.CreateStarship(StarshipFactory::STARSHIP_TYPE::MOTHERSHIP, 2);
    _player.PaintMothership(_predefinedColours.LIGHTBLUE);
    _player.SetMothershipPosition({60.0F, Constants::LEVEL_HEIGHT / 2.0F});
}

void GameScene::InitEnemyMothership()
{
    _enemy.CreateStarship(StarshipFactory::MOTHERSHIP, 2);
    _enemy.PaintMothership(_predefinedColours.LIGHTGREEN);
    auto mothershipXpos = _spaceLanes[0]->GetPos().x + _spaceLanes[0]->GetSize().x + _enemy.GetMothershipBounds().width/2.25F;
    auto mothershipYpos = Constants::LEVEL_HEIGHT / 2.0F;
    _enemy.SetMothershipPosition({mothershipXpos, mothershipYpos});
    _enemy.SetMothershipRotation(180);
}

void GameScene::InitGameplayView()
{
    _gameplayView.setSize(Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT);
    auto playerMothershipBounds = _player.GetMothership()->GetSpriteComponent().GetSprite().getGlobalBounds();
    _gameplayView.setCenter(_player.GetMothership()->GetPos().x + playerMothershipBounds.width - 60.0F, _player.GetMothership()->GetPos().y);
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
        sf::Vector2f playerMothershipPos = _player.GetMothership()->GetPos();
        float spacelaneXPos = playerMothershipPos.x + _player.GetMothershipBounds().width/1.5F;
        float spacelaneYPos = playerMothershipPos.y + ((float)i * (laneHeight + LANE_ROW_SPACING)) - (totalLanesHeight / 2.0F);
        float spacelaneXSize = Constants::LEVEL_WIDTH*0.8F;
        float spacelaneYSize = 50.0F;
        _spaceLanes[i]->SetPos({spacelaneXPos, spacelaneYPos});
        _spaceLanes[i]->SetSize({spacelaneXSize, spacelaneYSize});
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
    _starshipDeploymentManager->AddBasicObserver({ProgressBar::EventID::TASK_COMPLETED, starshipDeploymentBarCallback});

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
    _starshipDeploymentManager->ResetDeploymentBar();

    if(not _starshipDeploymentManager->IsQueueEmpty())
    {
        StartNextStarshipDeployment();
    }
}

void GameScene::HandleViewScrollingKeyboardInput(const sf::Event &event)
{
    if(event.type == sf::Event::KeyPressed and event.key.code == sf::Keyboard::A)
    {
        _scrollViewLeft = true;
    }
    else if(event.type == sf::Event::KeyReleased and event.key.code == sf::Keyboard::A)
    {
        _scrollViewLeft = false;
    }
    if(event.type == sf::Event::KeyPressed and event.key.code == sf::Keyboard::D)
    {
        _scrollViewRight = true;
    }
    else  if(event.type == sf::Event::KeyReleased and event.key.code == sf::Keyboard::D)
    {
        _scrollViewRight = false;
    }
}

void GameScene::StartNextStarshipDeployment()
{
    if(_starshipDeploymentManager->IsQueueEmpty())
        return;

    _starshipDeploymentManager->SetDeploymentBarText("Deploying " + _starshipDeploymentButtons[static_cast<int>(_starshipDeploymentManager->GetNextStarshipTypeInQueue())]->GetStarshipName() + "...");
    _starshipDeploymentManager->SetDeploymentTime(_starshipDeploymentButtons[_starshipDeploymentManager->GetNextStarshipTypeInQueue()]->GetStarshipDeploymentSpeed());
    _starshipDeploymentManager->SetDeploymentStatus(true);
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



