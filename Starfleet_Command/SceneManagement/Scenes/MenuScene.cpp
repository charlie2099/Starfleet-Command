#include <iostream>
#include "MenuScene.hpp"

bool MenuScene::init()
{
    initBackground();

    return true;
}

void MenuScene::eventHandler(sf::RenderWindow& /*window*/, sf::Event& /*event*/)
{
    //auto mouse_pos = sf::Mouse::getPosition(window); // Mouse position relative to the window
    //auto translated_pos = window.mapPixelToCoords(mouse_pos); // Mouse position translated into world coordinates
}

void MenuScene::update(sf::RenderWindow& /*window*/, sf::Time /*deltaTime*/)
{
    //auto mouse_pos = sf::Mouse::getPosition(window); // Mouse position relative to the window
    //auto translated_pos = window.mapPixelToCoords(mouse_pos); // Mouse position translated into world coordinates
}

void MenuScene::render(sf::RenderWindow& window)
{
    window.draw(background_sprite);
}

/// OTHER
bool MenuScene::initBackground()
{
    if (!background_texture.loadFromFile("images/space_background.jpg"))
    {
        return EXIT_FAILURE;
    }

    background_sprite.setTexture(background_texture);

    return true;
}



