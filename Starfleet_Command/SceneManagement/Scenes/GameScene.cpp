#include "GameScene.hpp"

bool GameScene::Init()
{
    InitBackground();
    InitCommandButtons();
    InitView();
    InitPlayerFlagship();
    InitEnemyFlagship();

    return true;
}

void GameScene::EventHandler(sf::RenderWindow& window, sf::Event& event)
{
    auto mouse_pos = sf::Mouse::getPosition(window); // Mouse position relative to the window
    auto translated_pos = window.mapPixelToCoords(mouse_pos); // Mouse position translated into world coordinates

    if(_command_button_1_sprite.getGlobalBounds().contains(translated_pos))
    {
        _command_button_1_sprite.setColor(_predefinedColours.LIGHTBLUE);
        is_hovered_over = true;
    }
    else
    {
        _command_button_1_sprite.setColor({178, 178, 178, 255});
        is_hovered_over = false;
    }

    if (event.type == sf::Event::MouseButtonPressed && is_hovered_over)
    {
        _command_button_1_sprite.setColor({153, 210, 242, 150});
        _player.CreateShip(Starship::Type::FIGHTER);
        _player.GetShip()[_player.GetShip().size()-1]->GetSpriteComponent().getSprite().setColor(_predefinedColours.LIGHTBLUE);
        _player.GetShip()[_player.GetShip().size()-1]->GetSpriteComponent().getSprite().setPosition(_player.GetShip()[0]->GetSpriteComponent().getSprite().getPosition());
    }
}

void GameScene::Update(sf::RenderWindow& window, sf::Time deltaTime)
{
    _cursor.Update(window, deltaTime);

    int flagship = 0;
    auto& player_flagship = _player.GetShip()[flagship]->GetSpriteComponent().getSprite();
    auto& enemy_flagship = _enemy.GetShip()[flagship]->GetSpriteComponent().getSprite();
    player_flagship.move(_player.GetShip()[flagship]->GetSpeed() * deltaTime.asSeconds(), 0);
    enemy_flagship.move(_enemy.GetShip()[flagship]->GetSpeed() * deltaTime.asSeconds() * -1, 0);

    for(int i = 1; i < _player.GetShip().size(); i++)
    {
        auto& player_sprite = _player.GetShip()[i]->GetSpriteComponent().getSprite();
        auto& enemy_sprite = _enemy.GetShip()[0]->GetSpriteComponent().getSprite();

        if(Chilli::Vector::Distance(player_sprite.getPosition(), enemy_sprite.getPosition()) < 200)
        {
            _player.GetShip()[i]->SetSpeed(20);
            //_player.GetShip()[i]->MoveTowards(enemy_sprite.getPosition(), deltaTime);
        }
        else
        {
            _player.GetShip()[i]->SetSpeed(80);
        }
        player_sprite.move(_player.GetShip()[i]->GetSpeed() * deltaTime.asSeconds(), 0);

//        if(distance < 300)
//        {
//            _player.GetShip()[i]->SetSpeed(20);
//
//            if(distance > 150)
//            {
//                _player.GetShip()[i]->MoveTowards(enemy_sprite.getPosition(), deltaTime);
//            }
//        }
//        else
//        {
//            _player.GetShip()[i]->SetSpeed(80);
//            player_sprite.move(_player.GetShip()[i]->GetSpeed() * deltaTime.asSeconds(), 0);
//        }
    }

//    for(int i = 1; i < _player.GetShip().size(); i++)
//    {
//        auto& player_sprite = _player.GetShip()[i]->GetSpriteComponent().getSprite();
//        //player_sprite.move(100 * deltaTime.asSeconds(), 0);
//
//        for(int i = 0; i < _enemy.GetShip().size(); i++)
//        {
//            auto& enemy_sprite = _enemy.GetShip()[i]->GetSpriteComponent().getSprite();
//            float distance = (abs(sqrt(((player_sprite.getPosition().x - enemy_sprite.getPosition().x) * (player_sprite.getPosition().x - enemy_sprite.getPosition().x)) + ((player_sprite.getPosition().y - enemy_sprite.getPosition().y) * (player_sprite.getPosition().y - enemy_sprite.getPosition().y)))));
//
//            if (distance < 200)
//            {
//                _player.GetShip()[i]->MoveTowards(enemy_sprite.getPosition(), deltaTime);
//                //_player.GetShip()[i]->SetSpeed(30);
//            }
//            else
//            {
//                player_sprite.move(100 * deltaTime.asSeconds(), 0);
//                //enemy_sprite.setRotation(180);
//                //TODO: return to original speed
//            }
//        }
//    }

//    for(int i = 0; i < _player.GetShip().size(); i++)
//    {
//        auto& player_sprite = _player.GetShip()[i]->GetSpriteComponent().getSprite();
//        //player_sprite.move(100 * deltaTime.asSeconds(), 0);
//
//        for(int i = 0; i < _enemy.GetShip().size(); i++)
//        {
//            auto& enemy_sprite = _enemy.GetShip()[i]->GetSpriteComponent().getSprite();
//            float distance = (abs(sqrt(((player_sprite.getPosition().x - enemy_sprite.getPosition().x) * (player_sprite.getPosition().x - enemy_sprite.getPosition().x)) + ((player_sprite.getPosition().y - enemy_sprite.getPosition().y) * (player_sprite.getPosition().y - enemy_sprite.getPosition().y)))));
//
//            if (distance < 200)
//            {
//                _enemy.GetShip()[i]->MoveTowards(player_sprite.getPosition(), deltaTime);
//                _enemy.GetShip()[i]->SetSpeed(30);
//            }
//            else
//            {
//                //enemy_sprite.move(100 * deltaTime.asSeconds() * -1, 0);
//                enemy_sprite.setRotation(180);
//                //TODO: return to original speed
//            }
//        }
//    }

    //TODO:
    // - Write up a learning log i.e. write-up how enemy chasing mechanic was achieved, to help properly understand it
}

void GameScene::Render(sf::RenderWindow& window)
{
    window.setView(_player_view);
    window.draw(_background_sprite);
    //_panel.Render(window);
    window.draw(_command_button_1_sprite);
    _player.Render(window);
    _enemy.Render(window);
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
    if (!_command_button_1_texture.loadFromFile("images/command_button_1.png")) // background2
    {
        return false;
    }
    _command_button_1_texture.setRepeated(true);
    _command_button_1_sprite.setTexture(_command_button_1_texture);
    _command_button_1_sprite.scale(0.3f, 0.3f);
    _command_button_1_sprite.setPosition(Constants::WINDOW_WIDTH/2.0f - _command_button_1_sprite.getGlobalBounds().width/2.0f,Constants::WINDOW_HEIGHT - (_command_button_1_sprite.getGlobalBounds().height/2.0f*4));
    _command_button_1_sprite.setColor({178, 178, 178, 255});
    //_command_button_1_sprite.setColor({153, 210, 242, 255});

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
    auto player_flagship_bounds = _player.GetShip()[flagship]->GetSpriteComponent().getSprite().getGlobalBounds();
    auto player_width = player_flagship_bounds.width/2;
    auto player_height = Constants::WINDOW_HEIGHT/2.0f;
    _player.GetShip()[flagship]->GetSpriteComponent().setPos({player_width, player_height});
    _player.GetShip()[flagship]->GetSpriteComponent().getSprite().setColor(_predefinedColours.LIGHTBLUE);
}

void GameScene::InitEnemyFlagship()
{
    _enemy.CreateShip(Starship::Type::FLAGSHIP);
    int flagship = 0;
    auto enemy_flagship_bounds = _enemy.GetShip()[flagship]->GetSpriteComponent().getSprite().getGlobalBounds();
    auto enemy_width = Constants::WINDOW_WIDTH - enemy_flagship_bounds.width/2.0f;
    auto enemy_height = Constants::WINDOW_HEIGHT/2.0f;
    _enemy.GetShip()[flagship]->GetSpriteComponent().setPos({enemy_width, enemy_height});
    _enemy.GetShip()[flagship]->GetSpriteComponent().getSprite().setColor(_predefinedColours.LIGHTGREEN);
    _enemy.GetShip()[flagship]->GetSpriteComponent().getSprite().setRotation(180);
}


