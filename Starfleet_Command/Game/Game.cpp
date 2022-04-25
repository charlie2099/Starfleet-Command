#include "Game.hpp"

Game::Game()
{
    InitWindow();
    InitSceneManager();
}

void Game::Run()
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
            Update(timePerFrame);
        }
        sf::Event event{};
        ProcessEvents(event);
        Render();
    }
}

void Game::ProcessEvents(sf::Event& event)
{
    while (window.pollEvent(event))
    {
        scene_manager->EventHandler(window, event);

        if(event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed &&
        event.key.code == sf::Keyboard::Escape)
        {
            window.close();
        }
    }
}

void Game::Update(sf::Time deltaTime)
{
    scene_manager->Update(window, deltaTime);
}

void Game::Render()
{
    window.clear();
    scene_manager->Render(window);
    window.display();
}

/// OTHER
void Game::InitWindow()
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
    //window.setMouseCursorVisible(false);
}

void Game::InitSceneManager()
{
    scene_manager = std::make_unique<SceneManager>();
    scene_manager->Init();
}