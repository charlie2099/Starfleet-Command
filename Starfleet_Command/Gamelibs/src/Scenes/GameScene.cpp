#include "Scenes/GameScene.hpp"

bool GameScene::Init()
{
    InitDistribution();
    InitBackground();
    InitCommandButtons();
    InitPlayerCreditsText();
    InitWavesRemainingText();
    InitEnemiesRemainingText();
    InitPlayerShips();
    InitEnemyShips();
    InitMainView();
    InitMinimapView();
    InitMainViewBorder();
    InitMinimapBorder();

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
    auto mousePosWorldCoords = window.mapPixelToCoords(mouse_pos, _mainView); // Mouse position translated into world coordinates

    if(_minimapBorder.getGlobalBounds().contains(mousePosWorldCoords))
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

    /*if (event.type == sf::Event::MouseButtonPressed)
    {
        //starship->GetHealthComponent().SetHealth(starship->GetHealthComponent().GetHealth() - 10);
    }*/

    for (int i = 0; i < _command_buttons.size(); i++)
    {
        if(_command_buttons[i]->GetSpriteComponent().GetSprite().getGlobalBounds().contains(mousePosWorldCoords))
        {
            _command_buttons[i]->GetSpriteComponent().GetSprite().setColor(_predefinedColours.LIGHTBLUE);

            if (event.type == sf::Event::MouseButtonPressed && !_shipyard.IsTraining())
            {
                _command_buttons[i]->GetSpriteComponent().GetSprite().setColor({153, 210, 242, 150});

                //_hud.SetTrainingSpeed(0.8f/*_player.GetShips()[i]->GetTrainingSpeed()*/);

                // TEMPORARY SOLUTION
                switch (i)
                {
                    case 0: // LIGHTFIGHTER
                        _shipyard.SetTrainingSpeed(0.4f);
                        _playerCreditsCounter -= 250;
                        //_credits_text.setPosition(_command_buttons[0]->GetSpriteComponent().GetPos().x, Constants::WINDOW_HEIGHT * 0.96F);
                        break;
                    case 1: // HEAVYFIGHTER
                        _shipyard.SetTrainingSpeed(0.5f);
                        _playerCreditsCounter -= 200;
                        break;
                    case 2: // SUPPORT
                        _shipyard.SetTrainingSpeed(0.6f);
                        _playerCreditsCounter -= 100;
                        break;
                    case 3: // DESTROYER
                        _shipyard.SetTrainingSpeed(0.2f);
                        _playerCreditsCounter -= 1000;
                        break;
                    case 4: // BATTLESHIP
                        _shipyard.SetTrainingSpeed(0.3f);
                        _playerCreditsCounter -= 750;
                        break;
                }
                _playerCreditsText.setString("Credits: " + std::to_string(_playerCreditsCounter));

                _shipyard.SetTrainingStatus(true);
                _ship_spawned_index = i;

                // make use of an event?

                //if(_hud.IsTrainingComplete())
                //{
                //    _player.CreateShip(static_cast<OLDStarship::Type>(i));
                //    _player.GetShips()[_player.GetShips().size() - 1]->GetSpriteComponent().GetSprite().setColor(_predefinedColours.LIGHTBLUE);
                //    RandomiseShipSpawnPoint();
                //}
            }
        }
        else if(!_command_buttons[i]->GetSpriteComponent().GetSprite().getGlobalBounds().contains(mousePosWorldCoords))
        {
            //_command_buttons[i]->GetSpriteComponent().GetSprite().setColor({178, 178, 178, 255});
            _command_buttons[i]->GetSpriteComponent().GetSprite().setColor({255, 255, 255, 100});
        }

        //if(_command_buttons[i]->IsHoveredOver())
        //{
        //    _command_buttons[i]->GetSpriteComponent().GetSprite().setColor(_predefinedColours.LIGHTBLUE);
        //
        //    if (event.type == sf::Event::MouseButtonPressed)
        //    {
        //        _command_buttons[i]->GetSpriteComponent().GetSprite().setColor({153, 210, 242, 150});
        //
        //        _player.CreateShip(static_cast<OLDStarship::Type>(i));
        //        _player.GetShips()[_player.GetShips().size() - 1]->GetSpriteComponent().GetSprite().setColor(_predefinedColours.LIGHTBLUE);
        //
        //        RandomiseShipSpawnPoint();
        //    }
        //}
        //else if(!_command_buttons[i]->IsHoveredOver())
        //{
        //    _command_buttons[i]->GetSpriteComponent().GetSprite().setColor({178, 178, 178, 255});
        //}
    }
}

void GameScene::Update(sf::RenderWindow& window, sf::Time deltaTime)
{
    auto mouse_pos = sf::Mouse::getPosition(window); // Mouse _position relative to the window
    auto mousePosWorldCoords = window.mapPixelToCoords(mouse_pos, _mainView); // Mouse _position translated into world coordinates

    sf::Vector2f playerFlagshipPos = _player.GetShips()[0]->GetSpriteComponent().GetPos();
    _mainView.setCenter(playerFlagshipPos.x, playerFlagshipPos.y);

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
        auto button_bounds = _command_buttons[i]->GetSpriteComponent().GetSprite().getGlobalBounds();
        auto xPos = 0.0F;
        auto yPos = 0.0F;

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

        _command_buttons[i]->GetSpriteComponent().SetPos({xPos, yPos});
        _command_buttons[i]->Update(window);

        /*if() // TODO: If ship cost associated with button is less than player's credit ammount, lower transparency of button
        {
            _command_buttons[i]->GetSpriteComponent().GetSprite().setColor(sf::Color(255, 255, 255, 50));
            _player.GetShips()[i]->GetShipCost()
            // Dictionary of command buttons and ship variations?
        }*/

        // Ship cost text alignment to command buttons
        auto button_sprite = _command_buttons[i]->GetSpriteComponent().GetSprite();
        auto text_xPos = button_sprite.getPosition().x + button_sprite.getGlobalBounds().width - (_ship_cost_text[i].getGlobalBounds().width+2);
        auto text_yPos = button_sprite.getPosition().y + 5;
        _ship_cost_text[i].setPosition(text_xPos, text_yPos);
    }

    _playerCreditsText.setPosition(_command_buttons[0]->GetSpriteComponent().GetPos().x, _command_buttons[_command_buttons.size()-1]->GetSpriteComponent().GetPos().y + _command_buttons[_command_buttons.size()-1]->GetSpriteComponent().GetSprite().getGlobalBounds().height*1.1F);
    _wavesRemainingText.setPosition(_mainView.getCenter().x - _wavesRemainingText.getGlobalBounds().width/2.0F, _mainView.getCenter().y - Constants::WINDOW_WIDTH/4.0F);
    _enemiesRemainingText.setPosition(_wavesRemainingText.getPosition().x, _wavesRemainingText.getPosition().y + _wavesRemainingText.getGlobalBounds().height + 5.0F);
    //_shipyard.SetPosition({_mainView.getCenter().x - _mainView.getSize().x/2.0F + 15.0F, _mainView.getCenter().y - _mainView.getSize().y/2.0F + 15.0F});
    //_shipyard.SetPosition({_command_buttons[0]->GetSpriteComponent().GetPos().x, _command_buttons[0]->GetSpriteComponent().GetPos().y - _shipyard.GetSpriteComponent().GetSprite().getGlobalBounds().height*2.75F});
    _shipyard.SetPosition({_minimapBorder.getPosition().x + _minimapBorder.getSize().x + 10.0F, _minimapBorder.getPosition().y});
    _shipyard.Update(window, deltaTime);
    _cursor.Update(window, deltaTime);
    _cursor.SetCursorPos(window, _mainView);
    _player.Update(window, deltaTime);
    _enemy.Update(window, deltaTime);
    //starship->Update(window, deltaTime);

    if(_shipyard.IsTrainingComplete())
    {
        SpawnShipFromShipyard();
    }

    // Check if player cursor is over their capital ship
    for(auto & player_ship : _player.GetShips())
    {
        if(player_ship != nullptr)
        {
            // Highlight player ship on mouse hover
            if(Chilli::Vector::BoundsCheck(mousePosWorldCoords, player_ship->GetSpriteComponent().GetSprite().getGlobalBounds()))
            {
                _cursor.SetCursorType(Chilli::Cursor::Type::SELECTED, sf::Color::Cyan);
                player_ship->SetHealthBarVisibility(true);
                //player_ship->GetSpriteComponent().GetSprite().setColor(sf::Color::Cyan);
            }
            else
            {
                _cursor.SetCursorType(Chilli::Cursor::DEFAULT, sf::Color::White);
                player_ship->SetHealthBarVisibility(false);
                //player_ship->GetSpriteComponent().GetSprite().setColor(_predefinedColours.LIGHTBLUE);
            }
        }
    }

    // Move player capital ship
    int flagship = 0;
    if(_player.GetShips()[flagship] != nullptr)
    {
        auto& player_flagship = _player.GetShips()[flagship]->GetSpriteComponent().GetSprite();
        player_flagship.move(_player.GetShips()[flagship]->GetSpeed() * deltaTime.asSeconds(), 0);
    }

    // Move enemy capital ship
    if(_enemy.GetShips()[flagship] != nullptr)
    {
        auto& enemy_flagship = _enemy.GetShips()[flagship]->GetSpriteComponent().GetSprite();
        enemy_flagship.move(_enemy.GetShips()[flagship]->GetSpeed() * deltaTime.asSeconds() * -1, 0);
    }

    // Move enemy ships, and shoot at player ships when in range
    for (int i = 1; i < _enemy.GetShips().size(); ++i)
    {
        auto& enemy_sprite = _enemy.GetShips()[i]->GetSpriteComponent().GetSprite();
        enemy_sprite.move(_enemy.GetShips()[i]->GetSpeed() * deltaTime.asSeconds() * -1, 0);

        for(int j = 1; j < _player.GetShips().size(); j++)
        {
            if(_player.GetShips()[j] != nullptr)
            {
                auto& player_sprite = _player.GetShips()[j]->GetSpriteComponent().GetSprite();

                // Move towards and shoot at player ship if less than 400 pixels away from it
                if(Chilli::Vector::Distance(player_sprite.getPosition(), enemy_sprite.getPosition()) <= 400)
                {
                    _enemy.GetShips()[i]->SetSpeed(25);
                    _enemy.GetShips()[i]->MoveTowards(player_sprite.getPosition(), deltaTime);

                    auto& ship = _enemy.GetShips()[i];
                    ship->ShootAt(ship->GetProjectileType(), ship->GetFireRate(), player_sprite.getPosition());
                }
            }
        }
    }

    // Move player ships, shoot at enemy ships when in range, and destroy player projectiles when too far away
    for(int i = 1; i < _player.GetShips().size(); i++)
    {
        if(_player.GetShips()[i] != nullptr)
        {
            auto& player_sprite = _player.GetShips()[i]->GetSpriteComponent().GetSprite();

            for(int j = 0; j < _player.GetShips()[i]->GetProjectile().size(); j++)
            {
                auto& player_bullet = _player.GetShips()[i]->GetProjectile()[j]->GetSpriteComponent();

                // Destroy player projectiles when they have travelled too far
                if(Chilli::Vector::Distance(player_sprite.getPosition(), player_bullet.GetPos()) > Constants::WINDOW_WIDTH)
                {
                    _player.GetShips()[i]->GetProjectile().erase(_player.GetShips()[i]->GetProjectile().begin() + j);
                }
            }

            for(int j = 0; j < _enemy.GetShips().size(); j++)
            {
                auto& enemy_sprite = _enemy.GetShips()[j]->GetSpriteComponent().GetSprite();

                // Move towards and shoot at enemy ship if less than 400 pixels away from it
                if(Chilli::Vector::Distance(player_sprite.getPosition(), enemy_sprite.getPosition()) <= 400)
                {
                    _player.GetShips()[i]->SetSpeed(25);
                    _player.GetShips()[i]->MoveTowards(enemy_sprite.getPosition(), deltaTime);

                    auto& ship = _player.GetShips()[i];
                    ship->ShootAt(ship->GetProjectileType(), ship->GetFireRate(), enemy_sprite.getPosition());
                }

                for(int k = 0; k < _player.GetShips()[i]->GetProjectile().size(); k++)
                {
                    auto& player_bullet = _player.GetShips()[i]->GetProjectile()[k]->GetSpriteComponent();

                    // Destroy projectiles if collided with enemy ship
                    if(enemy_sprite.getGlobalBounds().intersects(player_bullet.GetSprite().getGlobalBounds()))
                    {
                        //UpdateDistribution("Ship damage", 10, 80);
                        int rand_damage = _uint_distrib[2](_generator);

                        //_enemy.GetShips()[j]->TakeDamage(_player.GetShips()[i]->GetDamage());
                        _enemy.GetShips()[j]->GetHealthComponent().TakeDamage(rand_damage * _player.GetShips()[i]->GetDamageScaleFactor(),
                                                                              _enemy.GetShips()[j]->GetSpriteComponent().GetPos());
                        _player.GetShips()[i]->GetProjectile().erase(_player.GetShips()[i]->GetProjectile().begin() + k);
                    }
                }
            }

            player_sprite.move(_player.GetShips()[i]->GetSpeed() * deltaTime.asSeconds(), 0);
        }
    }
}

void GameScene::Render(sf::RenderWindow& window)
{
    // Render the main view
    window.setView(_mainView);
    window.draw(_background_sprite);
    for(auto& button : _command_buttons)
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

    // Render the minimap
    window.setView(_minimapView);
    window.draw(_background_sprite);
    window.draw(_mainViewBorder);
    _player.Render(window);
    _enemy.Render(window);

    // Draw cursor over every view
    window.setView(_mainView);
    _cursor.Render(window);
}

void GameScene::InitDistribution()
{
    _generator = GetEngine();
    CreateDistribution("Ship xPos", 0, 0); // Initial values to be updated later
    CreateDistribution("Ship yPos", 0, 0);
    CreateDistribution("Ship damage", 100, 250);
    _dist_code =
    {
            {"Ship yPos",1},
            {"Ship xPos",0},
            {"Ship damage",2}
    };
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

bool GameScene::InitCommandButtons()
{
    std::string ship_costs[5] = { "50", "75", "100", "300", "400", };
    const float NUM_OF_BUTTONS = 5;
    const float SPACING = 10;
    const float OFFSET = NUM_OF_BUTTONS * SPACING;
    for (int i = 0; i < NUM_OF_BUTTONS; ++i)
    {
        _command_buttons.emplace_back(std::make_unique<Button>("Resources/Textures/command_button_" + std::to_string(i) + ".png"));
        auto& button_sprite = _command_buttons[i]->GetSpriteComponent().GetSprite();
        button_sprite.setColor({178, 178, 178, 255});
        button_sprite.scale({0.20f, 0.20f});
        auto button_bounds = button_sprite.getGlobalBounds();
        auto xPos = (Constants::WINDOW_WIDTH * 0.5f - button_bounds.width*NUM_OF_BUTTONS/2.0f - OFFSET) + (i * (button_bounds.width+SPACING));
        auto yPos = Constants::WINDOW_HEIGHT - (button_bounds.height/2.0f*3.0f);
        _command_buttons[i]->GetSpriteComponent().SetPos({xPos, yPos});

        _ship_cost_text.emplace_back(sf::Text());
        _ship_cost_text[i].setString(ship_costs[i]);
        _ship_cost_text[i].setFillColor(sf::Color(153, 210, 242));
        //_ship_cost_text[i].setFillColor(sf::Color::Yellow);
        _ship_cost_text[i].setOutlineColor(sf::Color::Black);
        _ship_cost_text[i].setOutlineThickness(1);
        _ship_cost_text[i].setFont(GetRegularFont());
        _ship_cost_text[i].setCharacterSize(8);
        auto text_xPos = button_sprite.getPosition().x + button_sprite.getGlobalBounds().width - (_ship_cost_text[i].getGlobalBounds().width+2);
        auto text_yPos = button_sprite.getPosition().y + 5;
        _ship_cost_text[i].setPosition(text_xPos, text_yPos);
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
    _playerCreditsText.setPosition(_command_buttons[0]->GetSpriteComponent().GetPos().x, Constants::WINDOW_HEIGHT * 0.96F);
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
    _minimapView.setCenter(Constants::LEVEL_WIDTH/2.0f,Constants::LEVEL_HEIGHT/2.0f);
    _originalMinimapViewCenter = _minimapView.getCenter();

    // Position minimap at top middle of the window and set its size
    _minimapView.setViewport(sf::FloatRect(
            Constants::VIEWPORT_LEFT,
            Constants::VIEWPORT_TOP,
            Constants::VIEWPORT_WIDTH,
            Constants::VIEWPORT_HEIGHT));
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
    _minimapBorder.setSize({Constants::WINDOW_WIDTH*Constants::VIEWPORT_WIDTH,Constants::WINDOW_HEIGHT*Constants::VIEWPORT_HEIGHT});
    _minimapBorder.setOutlineThickness(2.0f); // Set the thickness of the border
    _minimapBorder.setOutlineColor(sf::Color(128,128,128)); // Set the color of the border
    _minimapBorder.setFillColor(sf::Color::Red); // Make the inside of the rectangle transparent
}

void GameScene::InitPlayerShips()
{
    _player.CreateShip(StarshipFactory::SHIP_TYPE::MOTHERSHIP);
    int flagship = 0;
    _player.GetShips()[flagship]->GetSpriteComponent().SetPos({Constants::WINDOW_WIDTH/2.0F, Constants::LEVEL_HEIGHT/2.0f});
    _player.GetShips()[flagship]->GetSpriteComponent().GetSprite().setColor(_predefinedColours.LIGHTBLUE);
}

void GameScene::InitEnemyShips()
{
    _enemy.CreateShip(StarshipFactory::MOTHERSHIP);
    int flagship = 0;
    auto enemy_flagship_bounds = _enemy.GetShips()[flagship]->GetSpriteComponent().GetSprite().getGlobalBounds();
    auto enemy_xPos = Constants::LEVEL_WIDTH - enemy_flagship_bounds.width;
    auto enemy_yPos = Constants::LEVEL_HEIGHT / 2.0f;
    _enemy.GetShips()[flagship]->GetSpriteComponent().SetPos({enemy_xPos, enemy_yPos});
    _enemy.GetShips()[flagship]->GetSpriteComponent().GetSprite().setColor(_predefinedColours.LIGHTGREEN);
    _enemy.GetShips()[flagship]->GetSpriteComponent().GetSprite().setRotation(180);

    for (int i = 0; i < 5; ++i)
    {
        _enemy.CreateShip(static_cast<StarshipFactory::SHIP_TYPE>(i));
        _enemy.GetShips()[i + 1]->GetSpriteComponent().SetPos({enemy_xPos, static_cast<float>(Constants::LEVEL_HEIGHT/2.0f + (i * 75))});
        _enemy.GetShips()[i + 1]->GetSpriteComponent().GetSprite().setRotation(180);
        _enemy.GetShips()[i + 1]->GetSpriteComponent().GetSprite().setColor(_predefinedColours.LIGHTGREEN);
    }
}

void GameScene::RandomisePlayerShipSpawnPoint()
{
    int flagship = 0;
    auto flagship_pos = _player.GetShips()[flagship]->GetSpriteComponent().GetPos();
    auto flagship_bounds = _player.GetShips()[flagship]->GetSpriteComponent().GetSprite().getGlobalBounds();
    UpdateDistribution("Ship xPos", flagship_pos.x, flagship_pos.x);
    UpdateDistribution("Ship yPos", flagship_pos.y - Constants::WINDOW_HEIGHT/2.0F + flagship_bounds.height, flagship_pos.y + Constants::WINDOW_HEIGHT/2.0F - flagship_bounds.height);
    int rand_x = _uint_distrib[0](_generator);
    int rand_y = _uint_distrib[1](_generator);

    // Regenerate y pos value if too close to the captial ship/mothership
    while(rand_y >= (flagship_pos.y - flagship_bounds.height)
       && rand_y <= (flagship_pos.y + flagship_bounds.height))
    {
        rand_y = _uint_distrib[1](_generator);
    }

    _player.GetShips()[_player.GetShips().size() - 1]->GetSpriteComponent().SetPos({static_cast<float>(rand_x), static_cast<float>(rand_y)});
}

void GameScene::CreateDistribution(const std::string& name, int min, int max)
{
    std::uniform_int_distribution<int> instance{min, max};
    _uint_distrib.emplace_back(instance);
}

void GameScene::UpdateDistribution(const std::string& name, int min, int max)
{
    std::map<std::string, int>::iterator iter;
    iter = _dist_code.find(name);

    if(iter == _dist_code.end())
        std::cout << "Key not found" << std::endl;
    else
    {
        _uint_distrib[iter->second] = std::uniform_int_distribution<>(min,max);
        std::cout << "Key found!" << std::endl;
    }
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

void GameScene::SpawnShipFromShipyard() // TODO: Rename fotr readability
{
    _player.CreateShip(static_cast<StarshipFactory::SHIP_TYPE>(_ship_spawned_index));
    _player.GetShips()[_player.GetShips().size() - 1]->GetSpriteComponent().GetSprite().setColor(_predefinedColours.LIGHTBLUE);
    RandomisePlayerShipSpawnPoint();
    _shipyard.SetTrainingCompletedStatus(false);
}

