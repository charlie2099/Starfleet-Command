#include "GameScene.hpp"

bool GameScene::Init()
{
    generator = GetEngine();
    CreateDistribution("Ship xPos", 1100, 1100);
    CreateDistribution("Ship yPos", 45, 675);
    dist_code =
    {
            {"Ship yPos",1},
            {"Ship xPos",0}
    };

    InitBackground();
    InitCommandButtons();

    _credits_text.setString("Credits: 10000");
    _credits_text.setFillColor(sf::Color(153, 210, 242));
    _credits_text.setOutlineColor(sf::Color::Black);
    _credits_text.setOutlineThickness(1);
    _credits_text.setFont(GetRegularFont());
    _credits_text.setCharacterSize(20);
    _credits_text.setPosition(_command_buttons[0]->GetSpriteComponent().GetPos().x, Constants::WINDOW_HEIGHT * 0.96F);

    InitView();
    InitPlayerFlagship();
    InitEnemyFlagship();

    return true;
}

void GameScene::EventHandler(sf::RenderWindow& window, sf::Event& event)
{
    auto mouse_pos = sf::Mouse::getPosition(window); // Mouse position relative to the window
    auto mousePosWorldCoords = window.mapPixelToCoords(mouse_pos); // Mouse position translated into world coordinates

    if (event.type == sf::Event::MouseButtonPressed)
    {
        for (int i = 0; i < _player.GetShip().size(); ++i)
        {
            if(Chilli::Vector::BoundsCheck(mousePosWorldCoords, _player.GetShip()[i]->GetSpriteComponent().GetSprite().getGlobalBounds()))
            {
                std::cout << "Starship index: " << i << std::endl;
                _player.GetShip()[i]->GetHealthBar()[0].TakeDamage(50);
                //std::cout << "Starship health: " << _player.GetShip()[i]->GetHealthBar()[0].GetHealth() << std::endl;
            }
        }
    }

    for (int i = 0; i < _command_buttons.size(); i++)
    {
        if(_command_buttons[i]->IsHoveredOver())
        {
            _command_buttons[i]->GetSpriteComponent().GetSprite().setColor(_predefinedColours.LIGHTBLUE);

            if (event.type == sf::Event::MouseButtonPressed)
            {
                _command_buttons[i]->GetSpriteComponent().GetSprite().setColor({153, 210, 242, 150});

                int flagship = 0;
                _player.CreateShip(static_cast<Starship::Type>(i));
                _player.GetShip()[_player.GetShip().size() - 1]->GetSpriteComponent().GetSprite().setColor(_predefinedColours.LIGHTBLUE);

                // Randomise starship spawning locations
                auto flagship_pos = _player.GetShip()[flagship]->GetSpriteComponent().GetPos();
                UpdateDistribution("Ship xPos", flagship_pos.x, flagship_pos.x);

                int rand_x = uint_distrib[0](generator);
                int rand_y = uint_distrib[1](generator);
                _player.GetShip()[_player.GetShip().size() - 1]->GetSpriteComponent().SetPos({static_cast<float>(rand_x), static_cast<float>(rand_y)});
            }
        }
        else if(!_command_buttons[i]->IsHoveredOver())
        {
            _command_buttons[i]->GetSpriteComponent().GetSprite().setColor({178, 178, 178, 255});
        }
    }
}

void GameScene::Update(sf::RenderWindow& window, sf::Time deltaTime)
{
    auto mouse_pos = sf::Mouse::getPosition(window); // Mouse position relative to the window
    auto mousePosWorldCoords = window.mapPixelToCoords(mouse_pos); // Mouse position translated into world coordinates

    _cursor.Update(window, deltaTime);
    for(auto& button : _command_buttons)
    {
        button->Update(window);
    }
    _player.Update(window, deltaTime);
    _enemy.Update(window, deltaTime);

    int flagship = 0;
    auto& player_flagship = _player.GetShip()[flagship]->GetSpriteComponent().GetSprite();
    auto& enemy_flagship = _enemy.GetShip()[flagship]->GetSpriteComponent().GetSprite();
    player_flagship.move(_player.GetShip()[flagship]->GetSpeed() * deltaTime.asSeconds(), 0);
    enemy_flagship.move(_enemy.GetShip()[flagship]->GetSpeed() * deltaTime.asSeconds() * -1, 0);

    if(Chilli::Vector::BoundsCheck(mousePosWorldCoords, player_flagship.getGlobalBounds()))
    {
        _selected_ship = 0;
        _cursor.SetCursorType(Chilli::Cursor::Type::SELECTED, sf::Color::Cyan);
        _player.GetShip()[flagship]->SetHealthBarVisibility(true);
        _player.GetShip()[flagship]->GetSpriteComponent().GetSprite().setColor(sf::Color::Cyan);
    }
    else if(!Chilli::Vector::BoundsCheck(mousePosWorldCoords, _player.GetShip()[_selected_ship]->GetSpriteComponent().GetSprite().getGlobalBounds()))
    {
        _cursor.SetCursorType(Chilli::Cursor::DEFAULT, sf::Color::White);
        _player.GetShip()[flagship]->SetHealthBarVisibility(false);
        _player.GetShip()[flagship]->GetSpriteComponent().GetSprite().setColor(_predefinedColours.LIGHTBLUE);
    }

    for(int i = 1; i < _player.GetShip().size(); i++)
    {
        auto& player_sprite = _player.GetShip()[i]->GetSpriteComponent().GetSprite();
        for(int j = 0; j < _enemy.GetShip().size(); j++)
        {
            auto& enemy_sprite = _enemy.GetShip()[j]->GetSpriteComponent().GetSprite();
            if(Chilli::Vector::Distance(player_sprite.getPosition(), enemy_sprite.getPosition()) < 200)
            {
                _player.GetShip()[i]->SetSpeed(20);
                _player.GetShip()[i]->MoveTowards(enemy_sprite.getPosition(), deltaTime);
            }
            else
            {
                //_player.GetShip()[i]->SetSpeed(80);
            }
        }
        player_sprite.move(_player.GetShip()[i]->GetSpeed() * deltaTime.asSeconds(), 0);



        // Select ship

        if(Chilli::Vector::BoundsCheck(mousePosWorldCoords, player_sprite.getGlobalBounds()))
        {
            _selected_ship = i;
            //crosshair.snapTo(_player.GetShip()[_selected_ship]);
            _cursor.SetCursorType(Chilli::Cursor::Type::SELECTED, sf::Color::Cyan);
            _player.GetShip()[i]->SetHealthBarVisibility(true);
            _player.GetShip()[i]->GetSpriteComponent().GetSprite().setColor(sf::Color::Cyan);
        }
        else if(!Chilli::Vector::BoundsCheck(mousePosWorldCoords, _player.GetShip()[_selected_ship]->GetSpriteComponent().GetSprite().getGlobalBounds()))
        {
            //crosshair.unSnap();
            _cursor.SetCursorType(Chilli::Cursor::DEFAULT, sf::Color::White);
            _player.GetShip()[i]->SetHealthBarVisibility(false);
            _player.GetShip()[i]->GetSpriteComponent().GetSprite().setColor(_predefinedColours.LIGHTBLUE);
        }
    }

    //TODO:
    // - Write up a learning log i.e. write-up how enemy chasing mechanic was achieved, to help properly understand concepts
}

void GameScene::Render(sf::RenderWindow& window)
{
    window.setView(_player_view);
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
    //crosshair.render(window);
    _cursor.Render(window);
}

/// OTHER
bool GameScene::InitBackground()
{
    if (!_background_texture.loadFromFile("images/space_nebula.png")) // background2
    {
        return false;
    }
    _background_texture.setRepeated(true);
    _background_sprite.setTexture(_background_texture);
    _background_sprite.scale(0.2F, 0.2F);
    auto bTexSizeX = static_cast<int>(_background_texture.getSize().x);
    auto bTexSizeY = static_cast<int>(_background_texture.getSize().y);
    _background_sprite.setTextureRect(sf::IntRect(0, 0, bTexSizeX * 2, bTexSizeY * 2));
    //_background_sprite.setOrigin(_background_sprite.getLocalBounds().width/2, _background_sprite.getLocalBounds().height/2);

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
        _command_buttons.emplace_back(std::make_unique<Button>("images/command_button_" + std::to_string(i) + ".png"));
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

void GameScene::InitView()
{
    /// Reset View to default settings
    //view.setCenter(window.getDefaultView().getCenter());
    //view.SetSize(window.getDefaultView().getSize());

    sf::Vector2f VIEW_SIZE = { Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT };
    sf::Vector2f WORLD_PERSPECTIVE = { Constants::WINDOW_WIDTH/2.0F, Constants::WINDOW_HEIGHT/2.0F };
    _player_view.setSize(VIEW_SIZE);
    _player_view.setCenter(WORLD_PERSPECTIVE);
    //_player_view.zoom(0.5F);
}

void GameScene::InitPlayerFlagship()
{
    _player.CreateShip(Starship::Type::FLAGSHIP);
    int flagship = 0;
    auto player_flagship_bounds = _player.GetShip()[flagship]->GetSpriteComponent().GetSprite().getGlobalBounds();
    auto player_width = player_flagship_bounds.width/2;
    auto player_height = Constants::WINDOW_HEIGHT/2.0f;
    _player.GetShip()[flagship]->GetSpriteComponent().SetPos({player_width, player_height});
    _player.GetShip()[flagship]->GetSpriteComponent().GetSprite().setColor(_predefinedColours.LIGHTBLUE);
}

void GameScene::InitEnemyFlagship()
{
    _enemy.CreateShip(Starship::Type::FLAGSHIP);
    int flagship = 0;
    auto enemy_flagship_bounds = _enemy.GetShip()[flagship]->GetSpriteComponent().GetSprite().getGlobalBounds();
    auto enemy_width = Constants::WINDOW_WIDTH - enemy_flagship_bounds.width/2.0f;
    auto enemy_height = Constants::WINDOW_HEIGHT/2.0f;
    _enemy.GetShip()[flagship]->GetSpriteComponent().SetPos({enemy_width, enemy_height});
    _enemy.GetShip()[flagship]->GetSpriteComponent().GetSprite().setColor(_predefinedColours.LIGHTGREEN);
    _enemy.GetShip()[flagship]->GetSpriteComponent().GetSprite().setRotation(180);
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


