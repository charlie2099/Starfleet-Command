#include "TestScene.hpp"
#include "../../Utility/Vector.hpp"

bool TestScene::Init()
{
    InitBackground();
    InitView();

    _player.CreateShip(Starship::Type::FIGHTER);
    _player.GetShip()[0]->GetSpriteComponent().setPos({50, Constants::WINDOW_HEIGHT/2.0f});
    _player.GetShip()[0]->GetSpriteComponent().getSprite().setColor(sf::Color::Cyan);

    //_enemy.Init(1);
    _enemy.CreateShip(Starship::Type::FIGHTER);
    _enemy.CreateShip(Starship::Type::REPAIR);
    _enemy.CreateShip(Starship::Type::FLAGSHIP);
    _enemy.CreateShip(Starship::Type::BATTLESHIP);
    _enemy.CreateShip(Starship::Type::DESTROYER);
    for(int i = 0; i < _enemy.GetShip().size(); i++)
    {
        _enemy.GetShip()[i]->GetSpriteComponent().setPos({Constants::WINDOW_WIDTH - 200, 100 + (i * 100.0f)});
        _enemy.GetShip()[i]->GetSpriteComponent().getSprite().setColor(sf::Color::Red);
        _enemy.GetShip()[i]->GetSpriteComponent().getSprite().setRotation(180);
    }

    return true;
}

void TestScene::EventHandler(sf::RenderWindow& window, sf::Event& event)
{
    //auto mouse_pos = sf::Mouse::getPosition(window); // Mouse position relative to the window
    //auto mousePosWorldCoords = window.mapPixelToCoords(mouse_pos); // Mouse position translated into world coordinates
}

void TestScene::Update(sf::RenderWindow& window, sf::Time deltaTime)
{
    cursor.Update(window, deltaTime);

    auto& player_sprite = _player.GetShip()[0]->GetSpriteComponent().getSprite();
    player_sprite.move(100 * deltaTime.asSeconds(), 0);

    for(int i = 0; i < _enemy.GetShip().size(); i++)
    {
        auto& enemy_sprite = _enemy.GetShip()[i]->GetSpriteComponent().getSprite();
        float distance = (abs(sqrt(((player_sprite.getPosition().x - enemy_sprite.getPosition().x) * (player_sprite.getPosition().x - enemy_sprite.getPosition().x)) + ((player_sprite.getPosition().y - enemy_sprite.getPosition().y) * (player_sprite.getPosition().y - enemy_sprite.getPosition().y)))));

        if (distance < 200)
        {
            _enemy.GetShip()[i]->MoveTowards(player_sprite.getPosition(), deltaTime);
            _enemy.GetShip()[i]->SetSpeed(30);
        }
        else
        {
            enemy_sprite.move(-_enemy.GetShip()[i]->GetSpeed() * deltaTime.asSeconds(), 0);
            enemy_sprite.setRotation(180);
            //TODO: return to original speed
        }
    }

    //TODO:
    // - Write up a learning log i.e. write-up how enemy chasing mechanic was achieved, to help properly understand it
}

void TestScene::Render(sf::RenderWindow& window)
{
    window.setView(player_view);
    window.draw(background_sprite);
    _player.Render(window);
    _enemy.Render(window);
    cursor.Render(window);
}

/// OTHER
bool TestScene::InitBackground()
{
    if (!background_texture.loadFromFile("images/space_nebula.png")) // background2
    {
    return false;
    }
    background_texture.setRepeated(true);
    background_sprite.setTexture(background_texture);
    background_sprite.scale(0.2F, 0.2F);
    auto bTexSizeX = static_cast<int>(background_texture.getSize().x);
    auto bTexSizeY = static_cast<int>(background_texture.getSize().y);
    background_sprite.setTextureRect(sf::IntRect(0, 0, bTexSizeX*2, bTexSizeY*2));
    //background_sprite.setOrigin(background_sprite.getLocalBounds().width/2, background_sprite.getLocalBounds().height/2);

    return true;
}

void TestScene::InitView()
{
    /// Reset View to default settings
    //view.setCenter(window.getDefaultView().getCenter());
    //view.setSize(window.getDefaultView().getSize());

    sf::Vector2f VIEW_SIZE = { Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT };
    sf::Vector2f WORLD_PERSPECTIVE = { Constants::WINDOW_WIDTH/2.0F, Constants::WINDOW_HEIGHT/2.0F };
    player_view.setSize(VIEW_SIZE);
    player_view.setCenter(WORLD_PERSPECTIVE);
    //player_view.zoom(0.5F);
}


