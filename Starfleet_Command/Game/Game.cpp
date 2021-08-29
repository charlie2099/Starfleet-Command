#include "Game.hpp"

Game::Game()
{
    initWindow();
    initSceneManager();
}

void Game::run()
{
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);
    sf::Clock clock;

    while (window.isOpen())
    {
        timeSinceLastUpdate += clock.restart();
        while (timeSinceLastUpdate > timePerFrame)
        {
            timeSinceLastUpdate -= timePerFrame;
            sf::Event event{};
            processEvents(event);
            update(timePerFrame);
        }

        render();
    }
}

void Game::processEvents(sf::Event& event)
{
    while (window.pollEvent(event))
    {
        scene_manager->eventHandler(window, event);

        if(event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed &&
        event.key.code == sf::Keyboard::Escape)
        {
            window.close();
        }
    }
}

void Game::update(sf::Time deltaTime)
{
    scene_manager->update(window, deltaTime);
}

void Game::render()
{
    window.clear();
    scene_manager->render(window);
    window.display();
}

/// OTHER
void Game::initWindow()
{
    window.create(sf::VideoMode(1280, 720), "Starfleet Command");
    window.setTitle("Starfleet Command");
    window.setPosition(sf::Vector2i(300, 150));

    auto image = sf::Image{};
    if (!image.loadFromFile("images/starfleet_ship.png"))
    {
        std::cout << "Failed to load window icon image file" << std::endl;
    }
    window.setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());
}

void Game::initSceneManager()
{
    scene_manager = std::make_unique<SceneManager>();
    scene_manager->init();
}