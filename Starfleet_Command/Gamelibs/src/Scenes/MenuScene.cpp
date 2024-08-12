#include "Scenes/MenuScene.hpp"

bool MenuScene::Init()
{
    std::mt19937 generator = GetEngine();
    InitView();
    InitBackground();
    InitButtonPanels();
    InitTitlePanel();
    InitMenuTitleIcon();
    InitBackgroundShips(generator);

    return true;
}

void MenuScene::EventHandler(sf::RenderWindow& window, sf::Event& event)
{
    for (int i = 0; i < BUTTONS; ++i)
    {
        _panels[i].EventHandler(window, event);
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if(_panels[PLAY_BUTTON].IsClicked())
        {
            SetScene(Scene::ID::GAME);
        }
        else if(_panels[OPTIONS_BUTTON].IsClicked())
        {
            SetScene(Scene::ID::OPTIONS);
        }
        else if(_panels[EXIT_BUTTON].IsClicked())
        {
            window.close();
        }
    }

    for (int i = 0; i < BUTTONS; ++i)
    {
        if(i < 2) // PLAY and OPTIONS button
            {
            if(_panels[i].IsHoveredOver())
            {
                //_panels[i].SetPanelColour(sf::Color(20, 210, 242, 60));
                _panels[i].SetPanelColour(sf::Color(153, 210, 242, 80));
                _panels[i].SetText(_panels[i].GetText().getString(), sf::Color(153, 210, 242, 255));
            }
            }
        else // EXIT button
        {
            _panels[i].SetPanelColour(sf::Color(242, 22, 22, 60));
            _panels[i].SetText(_panels[i].GetText().getString(), sf::Color::Red);
        }

        // All Buttons
        if(!_panels[i].IsHoveredOver())
        {
            _panels[i].SetPanelColour(sf::Color(75, 75, 75, 100));
            _panels[i].SetText(_panels[i].GetText().getString(), sf::Color::White);
        }
    }
}

void MenuScene::Update(sf::RenderWindow& window, sf::Time deltaTime)
{
    auto mouse_pos = sf::Mouse::getPosition(window); // Mouse _position relative to the window
    auto mousePosWorldCoords = window.mapPixelToCoords(mouse_pos, _worldView); // Mouse _position translated into world coordinates

    _cursor.Update(window, deltaTime);
    _cursor.SetCursorPos(window, _worldView);

    for (int i = 0; i < BUTTONS; ++i)
    {
        _panels[i].Update(window);
    }
    for (auto & ship : _starship)
    {
        ship->Update(window, deltaTime);
    }

    for (int i = 0; i < _starship.size(); ++i)
    {
        // Ally ships
        if(i < BACKGROUND_SHIPS/2)
        {
            sf::Vector2f movement(_starship[i]->GetSpeed() * 2, 0.0f);
            _starship[i]->GetSpriteComponent().GetSprite().move(movement * deltaTime.asSeconds());
        }
        // Enemy ships
        if(i >= BACKGROUND_SHIPS/2)
        {
            sf::Vector2f movement((_starship[i]->GetSpeed() * 2) * -1, 0.0f);
            _starship[i]->GetSpriteComponent().GetSprite().move(movement * deltaTime.asSeconds());
        }

        if(_starship[i]->GetSpriteComponent().GetPos().x >= Constants::WINDOW_WIDTH)
        {
            _starship[i]->GetSpriteComponent().SetPos({0, _starship[i]->GetSpriteComponent().GetPos().y});
        }
        else if(_starship[i]->GetSpriteComponent().GetPos().x <= 0)
        {
            _starship[i]->GetSpriteComponent().SetPos({Constants::WINDOW_WIDTH, _starship[i]->GetSpriteComponent().GetPos().y});
        }
    }
}

void MenuScene::Render(sf::RenderWindow& window)
{
    window.setView(_worldView);
    window.draw(_backgroundSprite);
    for (auto & ship : _starship)
    {
        ship->Render(window);
    }
    window.draw(_menuTitleImgSprite);
    for (auto & panel : _panels)
    {
        panel.Render(window);
    }
    _cursor.Render(window);
}

/// OTHER
std::mt19937 MenuScene::GetEngine()
{
    std::random_device eng;
    std::mt19937 generator(eng());
    unsigned long int time = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    generator.seed(time);
    return generator;
}

void MenuScene::InitView()
{
    sf::Vector2f VIEW_SIZE = { Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT };
    sf::Vector2f WORLD_PERSPECTIVE = { Constants::WINDOW_WIDTH/2.0F, Constants::WINDOW_HEIGHT/2.0F };
    _worldView.setSize(VIEW_SIZE);
    _worldView.setCenter(WORLD_PERSPECTIVE);
}

bool MenuScene::InitBackground()
{
    if (!_backgroundTexture.loadFromFile("Resources/Textures/space_nebula.png"))
    {
        return false;
    }
    _backgroundTexture.setRepeated(true);
    _backgroundSprite.setTexture(_backgroundTexture);
    _backgroundSprite.scale(0.2F, 0.2F);
    auto bTexSizeX = static_cast<int>(_backgroundTexture.getSize().x);
    auto bTexSizeY = static_cast<int>(_backgroundTexture.getSize().y);
    _backgroundSprite.setTextureRect(sf::IntRect(0, 0, bTexSizeX * 2, bTexSizeY * 2));

    return true;
}

void MenuScene::InitButtonPanels()
{
    std::array<std::string, 3> button_text
    {
        "PLAY",
        "OPTIONS",
        "EXIT"
    };

    for (int i = 0; i < BUTTONS; ++i)
    {
        _panels[i].SetText(button_text[i]);
        _panels[i].SetTextSize(20);
        _panels[i].SetSize(25, 20);
        _panels[i].SetPanelColour(sf::Color(75, 75, 75, 100));
        _panels[i].SetPosition(Constants::WINDOW_WIDTH * 0.185F,
                              (Constants::WINDOW_HEIGHT * 0.57F) + static_cast<float>((i * (_panels[i].GetPanelSize().height + 10))));
    }
}

void MenuScene::InitTitlePanel()
{
    for (int i = BUTTONS; i < TITLE_PANEL; ++i)
    {
        _panels[i].SetText("Starfleet Command", sf::Color(153, 210, 242));
        _panels[i].SetTextSize(85);
        _panels[i].SetFont(Panel::TextFont::BOLD);
        _panels[i].SetPanelColour(sf::Color(0, 0, 0, 0));
        _panels[i].SetPosition(Constants::WINDOW_WIDTH * 0.5F - _panels[i].GetTextSize().width / 2,
                              Constants::WINDOW_HEIGHT * 0.22F);
    }
}

bool MenuScene::InitMenuTitleIcon()
{
    if (!_menuTitleImgTexture.loadFromFile("Resources/Textures/starfleet_ship_0.png"))
    {
        return false;
    }
    _menuTitleImgSprite.setTexture(_menuTitleImgTexture);
    _menuTitleImgSprite.setColor(sf::Color(153, 210, 242, 175));
    _menuTitleImgSprite.setScale(0.35F, 0.35F);
    _menuTitleImgSprite.setRotation(-8);
    _menuTitleImgSprite.setPosition(_panels[4].GetTextPosition().x - 44, _panels[4].GetTextPosition().y - 54);

    return true;
}

void MenuScene::InitBackgroundShips(std::mt19937 &generator)
{
    CreateDistribution("Ship xpos", 0, Constants::WINDOW_WIDTH);
    CreateDistribution("Ship ypos", 45, 675);
    CreateDistribution("Ship class", 0, 5);

    for (int i = 0; i < BACKGROUND_SHIPS; ++i)
    {
        int rand_x = _distributions[0](generator);
        int rand_y = _distributions[1](generator);
        int rand_ship = _distributions[2](generator);
        std::unique_ptr<IStarship> newStarship = StarshipFactory::CreateShip(static_cast<StarshipFactory::SHIP_TYPE>(rand_ship));
        _starship.emplace_back(std::move(newStarship));
        _starship[i]->GetSpriteComponent().GetSprite().setColor(sf::Color(153, 210, 242));
        _starship[i]->GetSpriteComponent().SetPos({static_cast<float>(rand_x), static_cast<float>(rand_y)});

        if(i >= BACKGROUND_SHIPS/2)
        {
            _starship[i]->GetSpriteComponent().GetSprite().setRotation(180);
            //_starship[i]->GetSpriteComponent().GetSpriteComponent().setColor(sf::Color(247, 85, 85));
            _starship[i]->GetSpriteComponent().GetSprite().setColor(sf::Color(91, 239, 170));
        }
    }
}

void MenuScene::CreateDistribution(const std::string& name, int min, int max)
{
    std::uniform_int_distribution<int> instance{min, max};
    _distributions.emplace_back(instance);
}


