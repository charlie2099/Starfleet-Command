#include "Scenes/GameScene.hpp"

bool GameScene::Init()
{
    InitDistribution();
    InitBackground();
    InitCommandButtons();
    InitCreditsText();
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
    auto mousePosWorldCoordsOnMinimap = window.mapPixelToCoords(mouse_pos, _minimapView);

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
                _minimapView.setCenter(_minimapView.getCenter() + offset);
            }
        }

        if (_currentZoomLevel < 1.0f)
        { // Allow moving focus only when zoomed in

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                isDragging = true;
                initialMousePosition = mouse_pos;
            }

            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                isDragging = false;
            }

            if (event.type == sf::Event::MouseMoved && isDragging) {
                sf::Vector2i currentMousePosition = sf::Mouse::getPosition(window);
                sf::Vector2f delta = window.mapPixelToCoords(initialMousePosition, _minimapView) -
                                     window.mapPixelToCoords(currentMousePosition, _minimapView);

                _minimapView.setCenter(_minimapView.getCenter() + delta);
                initialMousePosition = currentMousePosition;
            }
        }
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
                        _credits -= 250;
                        //_credits_text.setPosition(_command_buttons[0]->GetSpriteComponent().GetPos().x, Constants::WINDOW_HEIGHT * 0.96F);
                        break;
                    case 1: // HEAVYFIGHTER
                        _shipyard.SetTrainingSpeed(0.5f);
                        _credits -= 200;
                        break;
                    case 2: // SUPPORT
                        _shipyard.SetTrainingSpeed(0.6f);
                        _credits -= 100;
                        break;
                    case 3: // DESTROYER
                        _shipyard.SetTrainingSpeed(0.2f);
                        _credits -= 1000;
                        break;
                    case 4: // BATTLESHIP
                        _shipyard.SetTrainingSpeed(0.3f);
                        _credits -= 750;
                        break;
                }
                _credits_text.setString("Credits: " + std::to_string(_credits));

                _shipyard.SetTrainingStatus(true);
                ship_spawned_index = i;

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
            _command_buttons[i]->GetSpriteComponent().GetSprite().setColor({178, 178, 178, 255});
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

    _minimapBorder.setPosition(_mainView.getCenter().x - _minimapBorder.getSize().x/2.0F, _mainView.getCenter().y - _mainView.getSize().y/2.0F + 7.0F);
    _mainViewBorder.setPosition(_mainView.getCenter().x - _mainViewBorder.getSize().x/2.0F, _mainView.getCenter().y - _mainViewBorder.getSize().y/2.0F);

    /*if(_player.GetShips()[0]->GetSpriteComponent().GetPos().x >= Constants::WINDOW_WIDTH/2.0F)
    {
        sf::Vector2f PLAYER_PERSPECTIVE = { _player.GetShips()[0]->GetSpriteComponent().GetPos().x,_player.GetShips()[0]->GetSpriteComponent().GetPos().y };
        _cameraViewport.setCenter(PLAYER_PERSPECTIVE);
    }*/

    // TODO: Clean up
    const float NUM_OF_BUTTONS = 5;
    for (int i = 0; i < NUM_OF_BUTTONS; ++i)
    {
        const float SPACING = 10;
        const float OFFSET = NUM_OF_BUTTONS * SPACING;
        auto button_bounds = _command_buttons[i]->GetSpriteComponent().GetSprite().getGlobalBounds();
        auto xPos = (_mainView.getCenter().x - 150.0f) + (i * (button_bounds.width+SPACING));
        auto yPos = _mainView.getCenter().y + _mainView.getSize().y/2.0f - (button_bounds.height/2.0f*3.0f);
        _command_buttons[i]->GetSpriteComponent().SetPos({xPos, yPos});
        _command_buttons[i]->Update(window);

        // Ship cost text alignment to command buttons
        auto button_sprite = _command_buttons[i]->GetSpriteComponent().GetSprite();
        auto text_xPos = button_sprite.getPosition().x + button_sprite.getGlobalBounds().width - (_ship_cost_text[i].getGlobalBounds().width+2);
        auto text_yPos = button_sprite.getPosition().y + 5;
        _ship_cost_text[i].setPosition(text_xPos, text_yPos);
    }

    _credits_text.setPosition(_command_buttons[0]->GetSpriteComponent().GetPos().x, _mainView.getCenter().y + _mainView.getSize().y/2.0F - 30.0F);
    _shipyard.SetPosition({_mainView.getCenter().x - _mainView.getSize().x/2.0F + 15.0F, _mainView.getCenter().y - _mainView.getSize().y/2.0F + 15.0F});
    _shipyard.Update(window, deltaTime);
    _cursor.Update(window, deltaTime);
    _cursor.SetCursorPos(window, _mainView);
    _player.Update(window, deltaTime);
    _enemy.Update(window, deltaTime);
    //starship->Update(window, deltaTime);

    if(_shipyard.IsTrainingComplete())
    {
        _player.CreateShip(static_cast<StarshipFactory::SHIP_TYPE>(ship_spawned_index));
        _player.GetShips()[_player.GetShips().size() - 1]->GetSpriteComponent().GetSprite().setColor(_predefinedColours.LIGHTBLUE);
        RandomisePlayerShipSpawnPoint();
        _shipyard.SetTrainingCompletedStatus(false);
    }

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

    int flagship = 0;
    if(_player.GetShips()[flagship] != nullptr)
    {
        auto& player_flagship = _player.GetShips()[flagship]->GetSpriteComponent().GetSprite();
        player_flagship.move(_player.GetShips()[flagship]->GetSpeed() * deltaTime.asSeconds(), 0);
    }

    if(_enemy.GetShips()[flagship] != nullptr)
    {
        auto& enemy_flagship = _enemy.GetShips()[flagship]->GetSpriteComponent().GetSprite();
        enemy_flagship.move(_enemy.GetShips()[flagship]->GetSpeed() * deltaTime.asSeconds() * -1, 0);
    }

    for (int i = 1; i < _enemy.GetShips().size(); ++i)
    {
        _enemy.GetShips()[i]->GetSpriteComponent().GetSprite().move(
                _enemy.GetShips()[i]->GetSpeed() * deltaTime.asSeconds() * -1, 0);
    }

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
                        int rand_damage = uint_distrib[2](generator);

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
    window.draw(_credits_text);
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
    generator = GetEngine();
    CreateDistribution("Ship xPos", 0, 0); // Initial values to be updated later
    CreateDistribution("Ship yPos", 0, 0);
    CreateDistribution("Ship damage", 100, 250);
    dist_code =
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
        button_sprite.scale({0.28f, 0.28f});
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

void GameScene::InitCreditsText()
{
    _credits_text.setString("Credits: " + std::to_string(_credits));
    _credits_text.setFillColor(sf::Color(153, 210, 242));
    _credits_text.setOutlineColor(sf::Color::Black);
    _credits_text.setOutlineThickness(1);
    _credits_text.setFont(GetRegularFont());
    _credits_text.setCharacterSize(20);
    _credits_text.setPosition(_command_buttons[0]->GetSpriteComponent().GetPos().x, Constants::WINDOW_HEIGHT * 0.96F);
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
    _mainViewBorder.setOutlineColor(sf::Color::White); // Set the color of the border
    _mainViewBorder.setFillColor(sf::Color::Transparent); // Make the inside of the rectangle transparent
}

void GameScene::InitMinimapBorder()
{
    _minimapBorder.setSize({Constants::WINDOW_WIDTH*Constants::VIEWPORT_WIDTH,Constants::WINDOW_HEIGHT*Constants::VIEWPORT_HEIGHT});
    _minimapBorder.setOutlineThickness(2.0f); // Set the thickness of the border
    _minimapBorder.setOutlineColor(sf::Color(128,128,128)); // Set the color of the border
    _minimapBorder.setFillColor(sf::Color::Transparent); // Make the inside of the rectangle transparent
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
    UpdateDistribution("Ship xPos", flagship_pos.x, flagship_pos.x);
    UpdateDistribution("Ship yPos", flagship_pos.y - 200.0f, flagship_pos.y + 200.0f);
    int rand_x = uint_distrib[0](generator);
    int rand_y = uint_distrib[1](generator);
    _player.GetShips()[_player.GetShips().size() - 1]->GetSpriteComponent().SetPos({static_cast<float>(rand_x), static_cast<float>(rand_y)});
}

void GameScene::CreateDistribution(const std::string& name, int min, int max)
{
    std::uniform_int_distribution<int> instance{min, max};
    uint_distrib.emplace_back(instance);
}

void GameScene::UpdateDistribution(const std::string& name, int min, int max)
{
    std::map<std::string, int>::iterator iter;
    iter = dist_code.find(name);

    if(iter == dist_code.end())
        std::cout << "Key not found" << std::endl;
    else
    {
        uint_distrib[iter->second] = std::uniform_int_distribution<>(min,max);
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


