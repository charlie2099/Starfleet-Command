#include "Scenes/OptionsScene.hpp"

bool OptionsScene::Init()
{
    InitBackground();
    InitView();

    return true;
}

void OptionsScene::EventHandler(sf::RenderWindow &window, sf::Event &event)
{
    auto mouse_pos = sf::Mouse::getPosition(window); // Mouse _innerPosition relative to the window
    auto mousePosWorldCoords = window.mapPixelToCoords(mouse_pos); // Mouse _innerPosition translated into world coordinates
}

void OptionsScene::Update(sf::RenderWindow &window, sf::Time deltaTime)
{
    auto mouse_pos = sf::Mouse::getPosition(window); // Mouse _innerPosition relative to the window
    auto mousePosWorldCoords = window.mapPixelToCoords(mouse_pos); // Mouse _innerPosition translated into world coordinates

    _cursor.Update(window, deltaTime);
}

void OptionsScene::Render(sf::RenderWindow &window)
{
    window.setView(_player_view);
    window.draw(_background_sprite);
    _cursor.Render(window);
}

void OptionsScene::InitView()
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

bool OptionsScene::InitBackground()
{
    if (!_background_texture.loadFromFile("Resources/Textures/space_nebula.png")) // background2
    {
        return false;
    }
    _background_texture.setRepeated(true);
    _background_sprite.setTexture(_background_texture);
    _background_sprite.scale(0.2F, 0.2F);
    auto bTexSizeX = static_cast<int>(_background_texture.getSize().x);
    auto bTexSizeY = static_cast<int>(_background_texture.getSize().y);
    _background_sprite.setTextureRect(sf::IntRect(0, 0, bTexSizeX * 2, bTexSizeY * 2));
    //_backgroundSprite.setOrigin(_backgroundSprite.getLocalBounds().width/2, _backgroundSprite.getLocalBounds().height/2);

    return true;
}
