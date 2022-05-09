#include "Scenes/GameScene.hpp"

bool GameScene::Init()
{
    InitDistribution();
    InitBackground();
    InitCommandButtons();
    InitCreditsText();
    InitView();
    InitPlayerFlagship();
    InitEnemyFlagship();




    std::unique_ptr<StarshipClass> fighterClass =
            std::make_unique<StarshipClass>("Resources/Textures/starfleet_ship_fighter.png",
                                            250,
                                            50,
                                            std::make_unique<StarshipFighterBehaviour>());

    std::unique_ptr<StarshipClass> scoutClass =
            std::make_unique<StarshipClass>("Resources/Textures/starfleet_ship_scout.png",
                                            100,
                                            10,
                                            std::make_unique<StarshipFighterBehaviour>());

    starshipFighter = std::make_unique<Starship>(fighterClass);
    starshipScout = std::make_unique<Starship>(scoutClass);
    // TODO: (FIX) Can't initialise more than 1 of the same class right now because of std::move in the starship class.

    /// StarshipClass newClassType(texture, color, health, damage, behaviour(?));
    /// Starship newShip(newClassType);
    /// starshipFighter.AddBehaviour(ChaseBehaviour());
    /// starshipFighter.AddBehaviour(FleeBehaviour());
    /// starshipFighter.AddWeapon(PlasmaCannonWeapon());
    /// starshipFighter.AddWeapon(TorpedoLauncherWeapon());
    ///
    /// for(auto& starship : starships)
    ///     starship.Update();
    ///     starship.Render();



    /// Whenever a SHIP_SPAWNED event occurs, the TestFncForObserverToCall method is called
    /// A SHIP_SPAWNED event is invoked in the player CreateShip method.
    auto callbackFnc1 = std::bind(&TestClass::TestFncForObserverToCall, testClass);
    _player.AddObserver({Player::EventID::SHIP_SPAWNED, callbackFnc1});

    auto callbackFnc2 = std::bind(&TestClass::OnEvent, testClass, std::placeholders::_1);
    _player.AddObserver2({Player::EventID::SHIP_SPAWNED, callbackFnc2});

    //auto callbackFnc3 = std::bind(&TestClass::TestFncForObserverToCall, testClass);
    //_player.GetShip()[0].GetHealthComponent().AddObserver({Player::EventID::SHIP_SPAWNED, callbackFnc3});

    // FACTORY PATTERN
    starship = StarshipFactory::CreateShip(StarshipFactory::FIGHTER);

    //auto callbackFnc4 = std::bind(&TestClass::TestFncForObserverToCall, testClass);
    //starship->GetHealthComponent().AddObserver({HealthComponent::HEALTH_DEPLETED, callbackFnc4});

    /// Remove from vector container
    /// Play explosion audio
    /// Play death animation?

    /// DILEMMA
    /// Should classes be purely generic and reusable with game logic kept in the main game source file [YES]
    /// OR
    /// can the player class for example contain logic for determining when the health bar should be updated. [NO]

    //gameObject.AddComponent(std::make_unique<TestComponent>());
    //gameObject.AddComponent<TestComponent>();
    //gameObject.GetComponent<TestComponent>()->loadSprite("");
    //gameObject.GetComponent(std::make_unique<TestComponent>())->loadSprite("Resources/Textures/starfleet_ship.png");
    //auto testcomp = dynamic_cast<TestComponent*>(gameObject.AddComponent(std::make_unique<TestComponent>()));
    //testcomp->loadSprite("Resources/Textures/starfleet_ship.png");
    //gameObject.GetComponent<TestComponent>()->loadSprite("Resources/Textures/starfleet_ship.png");

    return true;
}

void GameScene::EventHandler(sf::RenderWindow& window, sf::Event& event)
{
    auto mouse_pos = sf::Mouse::getPosition(window); // Mouse _position relative to the window
    auto mousePosWorldCoords = window.mapPixelToCoords(mouse_pos, _worldView); // Mouse _position translated into world coordinates

    if (event.type == sf::Event::MouseButtonPressed)
    {
        starship->GetHealthComponent().SetHealth(starship->GetHealthComponent().GetHealth() - 10);
    }

    for (int i = 0; i < _command_buttons.size(); i++)
    {
        if(_command_buttons[i]->GetSpriteComponent().GetSprite().getGlobalBounds().contains(mousePosWorldCoords))
        {
            _command_buttons[i]->GetSpriteComponent().GetSprite().setColor(_predefinedColours.LIGHTBLUE);

            if (event.type == sf::Event::MouseButtonPressed && !_hud.IsTraining())
            {
                _command_buttons[i]->GetSpriteComponent().GetSprite().setColor({153, 210, 242, 150});

                //_hud.SetTrainingSpeed(0.8f/*_player.GetShip()[i]->GetTrainingSpeed()*/);

                // TEMPORARY SOLUTION
                switch (i)
                {
                    case 0: // FIGHTER
                        _hud.SetTrainingSpeed(0.4f);
                        _credits -= 250;
                        //_credits_text.setPosition(_command_buttons[0]->GetSpriteComponent().GetPos().x, Constants::WINDOW_HEIGHT * 0.96F);
                        break;
                    case 1: // REPAIR
                        _hud.SetTrainingSpeed(0.5f);
                        _credits -= 200;
                        break;
                    case 2: // SCOUT
                        _hud.SetTrainingSpeed(0.6f);
                        _credits -= 100;
                        break;
                    case 3: // DESTROYER
                        _hud.SetTrainingSpeed(0.2f);
                        _credits -= 1000;
                        break;
                    case 4: // BATTLESHIP
                        _hud.SetTrainingSpeed(0.3f);
                        _credits -= 750;
                        break;
                }
                _credits_text.setString("Credits: " + std::to_string(_credits));

                _hud.SetTrainingStatus(true);
                ship_spawned_index = i;

                // make use of an event?

                //if(_hud.IsTrainingComplete())
                //{
                //    _player.CreateShip(static_cast<OLDStarship::Type>(i));
                //    _player.GetShip()[_player.GetShip().size() - 1]->GetSpriteComponent().GetSprite().setColor(_predefinedColours.LIGHTBLUE);
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
        //        _player.GetShip()[_player.GetShip().size() - 1]->GetSpriteComponent().GetSprite().setColor(_predefinedColours.LIGHTBLUE);
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
    auto mousePosWorldCoords = window.mapPixelToCoords(mouse_pos, _worldView); // Mouse _position translated into world coordinates

    for(auto& button : _command_buttons)
    {
        button->Update(window);
    }
     _hud.Update(window, deltaTime);
    _cursor.Update(window, deltaTime);
    _cursor.SetCursorPos(window, _worldView);
    _player.Update(window, deltaTime);
    _enemy.Update(window, deltaTime);
    starship->Update(window, deltaTime);

    if(_hud.IsTrainingComplete())
    {
        _player.CreateShip(static_cast<OLDStarship::Type>(ship_spawned_index));
        _player.GetShip()[_player.GetShip().size() - 1]->GetSpriteComponent().GetSprite().setColor(_predefinedColours.LIGHTBLUE);
        RandomiseShipSpawnPoint();
        _hud.SetTrainingCompletedStatus(false);
    }

    for(auto & player_ship : _player.GetShip())
    {
        if(player_ship != nullptr)
        {
            // Highlight player ship on mouse hover
            if(Chilli::Vector::BoundsCheck(mousePosWorldCoords, player_ship->GetSpriteComponent().GetSprite().getGlobalBounds()))
            {
                _cursor.SetCursorType(Chilli::Cursor::Type::SELECTED, sf::Color::Cyan);
                player_ship->SetHealthBarVisibility(true);
                player_ship->GetSpriteComponent().GetSprite().setColor(sf::Color::Cyan);
            }
            else
            {
                _cursor.SetCursorType(Chilli::Cursor::DEFAULT, sf::Color::White);
                player_ship->SetHealthBarVisibility(false);
                player_ship->GetSpriteComponent().GetSprite().setColor(_predefinedColours.LIGHTBLUE);
            }
        }
    }

    int flagship = 0;
    if(_player.GetShip()[flagship] != nullptr)
    {
        auto& player_flagship = _player.GetShip()[flagship]->GetSpriteComponent().GetSprite();
        player_flagship.move(_player.GetShip()[flagship]->GetSpeed() * deltaTime.asSeconds(), 0);
    }

    if(_enemy.GetShip()[flagship] != nullptr)
    {
        auto& enemy_flagship = _enemy.GetShip()[flagship]->GetSpriteComponent().GetSprite();
        enemy_flagship.move(_enemy.GetShip()[flagship]->GetSpeed() * deltaTime.asSeconds() * -1, 0);
    }

    for (int i = 1; i < _enemy.GetShip().size(); ++i)
    {
        _enemy.GetShip()[i]->GetSpriteComponent().GetSprite().move(_enemy.GetShip()[i]->GetSpeed() * deltaTime.asSeconds() * -1, 0);
    }

    for(int i = 1; i < _player.GetShip().size(); i++)
    {
        if(_player.GetShip()[i] != nullptr)
        {
            auto& player_sprite = _player.GetShip()[i]->GetSpriteComponent().GetSprite();

            for(int j = 0; j < _player.GetShip()[i]->GetProjectile().size(); j++)
            {
                auto& player_bullet = _player.GetShip()[i]->GetProjectile()[j]->GetSpriteComponent();

                // Destroy player projectiles when they have travelled too far
                if(Chilli::Vector::Distance(player_sprite.getPosition(), player_bullet.GetPos()) > Constants::WINDOW_WIDTH)
                {
                    _player.GetShip()[i]->GetProjectile().erase(_player.GetShip()[i]->GetProjectile().begin() + j);
                }
            }

            for(int j = 0; j < _enemy.GetShip().size(); j++)
            {
                auto& enemy_sprite = _enemy.GetShip()[j]->GetSpriteComponent().GetSprite();

                // Move towards and shoot at enemy ship if less than 400 pixels away from it
                if(Chilli::Vector::Distance(player_sprite.getPosition(), enemy_sprite.getPosition()) <= 400)
                {
                    _player.GetShip()[i]->SetSpeed(25);
                    _player.GetShip()[i]->MoveTowards(enemy_sprite.getPosition(), deltaTime);

                    auto& ship = _player.GetShip()[i];
                    ship->ShootAt(ship->GetProjectileType(), ship->GetFireRate(), enemy_sprite.getPosition());
                }

                for(int k = 0; k < _player.GetShip()[i]->GetProjectile().size(); k++)
                {
                    auto& player_bullet = _player.GetShip()[i]->GetProjectile()[k]->GetSpriteComponent();

                    // Destroy projectiles if collided with enemy ship
                    if(enemy_sprite.getGlobalBounds().intersects(player_bullet.GetSprite().getGlobalBounds()))
                    {
                        //UpdateDistribution("Ship damage", 10, 80);
                        int rand_damage = uint_distrib[2](generator);

                        //_enemy.GetShip()[j]->TakeDamage(_player.GetShip()[i]->GetDamage());
                        _enemy.GetShip()[j]->GetHealthComponent().TakeDamage(rand_damage * _player.GetShip()[i]->GetDamageScaleFactor());
                        _player.GetShip()[i]->GetProjectile().erase(_player.GetShip()[i]->GetProjectile().begin() + k);
                    }
                }
            }

            player_sprite.move(_player.GetShip()[i]->GetSpeed() * deltaTime.asSeconds(), 0);
        }
    }

    //aiComponent->MoveTowards(newSpriteComponent->GetSprite(), _enemy.GetShip()[0]->GetSpriteComponent().GetPos(), 100, deltaTime);
}

void GameScene::Render(sf::RenderWindow& window)
{
    window.setView(_worldView);
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

    //gameObject.Render(window);
    starship->Render(window);
    starshipFighter->Render(window);
    starshipScout->Render(window);

    //crosshair.Render(window);
    _hud.Render(window);
    _cursor.Render(window);


    //window.setView(_minimapView);
    //window.draw(_background_sprite2);
    //_cursor.Render(window);
}

void GameScene::InitDistribution()
{
    generator = GetEngine();
    CreateDistribution("Ship xPos", 1100, 1100);
    CreateDistribution("Ship yPos", 100, 600);
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
    if (!_background_texture->loadFromFile("Resources/Textures/space_nebula.png")) // background2
    {
        return false;
    }

    _background_texture->setRepeated(true);
    _background_sprite.setTexture(*_background_texture);
    _background_sprite.scale(0.2F, 0.2F);
    auto bTexSizeX = static_cast<int>(_background_texture->getSize().x);
    auto bTexSizeY = static_cast<int>(_background_texture->getSize().y);
    _background_sprite.setTextureRect(sf::IntRect(0, 0, bTexSizeX * 2, bTexSizeY * 2));
    //_background_sprite.setOrigin(_background_sprite.getLocalBounds().width/2, _background_sprite.getLocalBounds().height/2);

//    if (!_background_texture2.loadFromFile("Resources/Textures/space_background.jpg"))
//    {
//        return false;
//    }
//    _background_sprite2.setTexture(_background_texture2);
//    _background_sprite2.scale(1.0F, 1.25F);

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

void GameScene::InitView()
{
    /// Reset View to default settings
    //view.setCenter(window.getDefaultView().getCenter());
    //view.SetSize(window.getDefaultView().getSize());

    sf::Vector2f VIEW_SIZE = { Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT };
    sf::Vector2f WORLD_PERSPECTIVE = { Constants::WINDOW_WIDTH/2.0F, Constants::WINDOW_HEIGHT/2.0F };
    _worldView.setSize(VIEW_SIZE);
    _worldView.setCenter(WORLD_PERSPECTIVE);
    //_player_view.zoom(0.5F);

    //_minimapView.setViewport(sf::FloatRect(0.70f, 0.70f, 0.25f, 0.25f));


      // LEFT 75%, RIGHT 25%
//    const sf::Vector2f leftSize(1440.0f, 1080.0f);
//    const sf::Vector2f rightSize(480.0f, 1080.0f);
//    const sf::Vector2f origin(0.0f, 0.0f);
//
//    _worldView = sf::View(sf::FloatRect(origin, leftSize));
//    _worldView.setViewport(sf::FloatRect(0.0f, 0.0f, 0.75f, 1.0f));
//
//    _minimapView = sf::View(sf::FloatRect(origin, rightSize));
//    _minimapView.setViewport(sf::FloatRect(0.75f, 0, 0.25f, 1.0f));


      // TOP 75%, BOTTOM 25%
//    const sf::Vector2f leftSize(1440.0f, 720.0f);
//    const sf::Vector2f rightSize(1440.0f, 270.0f);
//    const sf::Vector2f origin(0.0f, 0.0f);
//
//    _worldView = sf::View(sf::FloatRect(origin, leftSize));
//    _worldView.setViewport(sf::FloatRect(0.0f, 0.0f, 1.0f, 0.75f));
//
//    _minimapView = sf::View(sf::FloatRect(origin, rightSize));
//    _minimapView.setViewport(sf::FloatRect(0.0f, 0.0f, 1.0f, 0.25f));
}

void GameScene::InitPlayerFlagship()
{
    _player.CreateShip(OLDStarship::Type::FLAGSHIP);
    int flagship = 0;
    auto player_flagship_bounds = _player.GetShip()[flagship]->GetSpriteComponent().GetSprite().getGlobalBounds();
    auto player_width = player_flagship_bounds.width/2;
    auto player_height = Constants::WINDOW_HEIGHT/2.0f;
    _player.GetShip()[flagship]->GetSpriteComponent().SetPos({player_width, player_height});
    _player.GetShip()[flagship]->GetSpriteComponent().GetSprite().setColor(_predefinedColours.LIGHTBLUE);
}

void GameScene::InitEnemyFlagship()
{
    _enemy.CreateShip(OLDStarship::Type::FLAGSHIP);
    int flagship = 0;
    auto enemy_flagship_bounds = _enemy.GetShip()[flagship]->GetSpriteComponent().GetSprite().getGlobalBounds();
    auto enemy_xPos = Constants::WINDOW_WIDTH - enemy_flagship_bounds.width / 2.0f;
    auto enemy_yPos = Constants::WINDOW_HEIGHT / 2.0f;
    _enemy.GetShip()[flagship]->GetSpriteComponent().SetPos({enemy_xPos, enemy_yPos});
    _enemy.GetShip()[flagship]->GetSpriteComponent().GetSprite().setColor(_predefinedColours.LIGHTGREEN);
    _enemy.GetShip()[flagship]->GetSpriteComponent().GetSprite().setRotation(180);

    for (int i = 0; i < 5; ++i)
    {
        _enemy.CreateShip(static_cast<OLDStarship::Type>(i));
        _enemy.GetShip()[i+1]->GetSpriteComponent().GetSprite().setColor(_predefinedColours.LIGHTGREEN);
        _enemy.GetShip()[i+1]->GetSpriteComponent().SetPos({enemy_xPos, static_cast<float>(200 + (i * 75))});
        _enemy.GetShip()[i+1]->GetSpriteComponent().GetSprite().setRotation(180);
    }
}

void GameScene::RandomiseShipSpawnPoint()
{
    int flagship = 0;
    auto flagship_pos = _player.GetShip()[flagship]->GetSpriteComponent().GetPos();
    UpdateDistribution("Ship xPos", flagship_pos.x, flagship_pos.x);
    int rand_x = uint_distrib[0](generator);
    int rand_y = uint_distrib[1](generator);
    _player.GetShip()[_player.GetShip().size() - 1]->GetSpriteComponent().SetPos({static_cast<float>(rand_x), static_cast<float>(rand_y)});
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


