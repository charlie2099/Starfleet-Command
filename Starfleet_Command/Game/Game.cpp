#include "Game.hpp"

Game::Game()
{
    initWindow();
    initSceneManager();
}

void Game::run()
{
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    const sf::Time timePerFrame = sf::seconds(1.0f / 144.0f);
    sf::Clock clock;

    //window.setFramerateLimit(144);
    //window.setVerticalSyncEnabled(true);

    while (window.isOpen())
    {
        timeSinceLastUpdate += clock.restart();
        while (timeSinceLastUpdate > timePerFrame)
        {
            timeSinceLastUpdate -= timePerFrame;
            update(timePerFrame);
        }
        sf::Event event{};
        processEvents(event);
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
    window.create(sf::VideoMode(Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT), "Starfleet Command");
    window.setTitle("Starfleet Command");
    window.setPosition(sf::Vector2i(500, 200));

    auto image = sf::Image{};
    if (!image.loadFromFile("images/starfleet_ship_repairnew4.png"))
    {
        std::cout << "Failed to load window icon image file" << std::endl;
    }
    window.setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());
    window.setMouseCursorVisible(false);
}

void Game::initSceneManager()
{
    scene_manager = std::make_unique<SceneManager>();
    scene_manager->init();
}