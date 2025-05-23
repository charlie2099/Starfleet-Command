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

        if(event.type == sf::Event::Closed /*or event.type == sf::Event::KeyPressed and
        event.key.code == sf::Keyboard::Escape*/)
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

void Game::InitWindow()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;


    const std::string GAME_SETTINGS_PATH = "Resources/Data/GameSettings.json";
    auto gameSettingsData = Chilli::JsonSaveSystem::LoadFile(GAME_SETTINGS_PATH);

    if(gameSettingsData.contains("Fullscreen Mode"))
    {
        std::string fullscreenModeData = gameSettingsData["Fullscreen Mode"];

        if(fullscreenModeData == "true")
        {
            sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
            window.create(desktopMode, "Starfleet Command", sf::Style::Fullscreen, settings);
        }
        else
        {
            window.create(sf::VideoMode(Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT), "Starfleet Command", sf::Style::Default, settings);
        }
    }

    //window.setPosition(sf::Vector2i(Constants::WINDOW_WIDTH/2.0F, Constants::WINDOW_HEIGHT/2.0F));

    auto image = sf::Image{};
    if (!image.loadFromFile("Resources/Textures/starfleet_ship_1.png"))
    {
        std::cout << "Failed to load window icon image file" << std::endl;
    }
    window.setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());
    window.setMouseCursorVisible(false);
    window.setMouseCursorGrabbed(true);
}

void Game::InitSceneManager()
{
    scene_manager = std::make_unique<SceneManager>();
    scene_manager->Init();
}