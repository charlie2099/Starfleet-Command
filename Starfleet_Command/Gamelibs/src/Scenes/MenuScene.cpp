#include "Scenes/MenuScene.hpp"

MenuScene::~MenuScene()
{
    if(_menuMusic.getStatus() == sf::Music::Playing)
    {
        _menuMusic.stop();
    }
}

bool MenuScene::Init()
{
    std::mt19937 generator = GetEngine();
    InitView();
    InitBackground();
    InitButtonPanels();
    InitMenuTitleIcon();
    InitBackgroundShips(generator);
    InitGameVersionText();

    if(!_menuMusic.openFromFile("Resources/Audio/United_Against_Evil_175bpm_136s.wav"))
    {
        std::cout << "Failed to to load menu soundtrack (United_Against_Evil_175bpm_136s)" << std::endl;
        return false;
    }
    else
    {
        if(_isMusicOn)
        {
            _menuMusic.play();
        }
        //_menuMusic.setPlayingOffset(sf::seconds(2.0F));
        _menuMusic.setLoop(true);
    }

    _musicIconButtons[MUSIC_ON_BUTTON] = std::make_unique<Button>("Resources/Textures/musicOn.png");
    _musicIconButtons[MUSIC_OFF_BUTTON] = std::make_unique<Button>("Resources/Textures/musicOff.png");
    for (int i = 0; i < 2; ++i)
    {
        _musicIconButtons[i]->SetPos({10, 10});
        _musicIconButtons[i]->SetColour(sf::Color(22, 155, 164, 100));
    }

    return true;
}

void MenuScene::EventHandler(sf::RenderWindow& window, sf::Event& event)
{
    for (int i = 0; i < NUM_OF_BUTTONS; ++i)
    {
        _panels[i].EventHandler(window, event);
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if(_panels[PLAY_BUTTON].IsClicked())
        {
            SetScene(Scene::ID::GAME);
        }
        /*else if(_panels[OPTIONS_BUTTON].IsClicked())
        {
            SetScene(Scene::ID::OPTIONS);
        }*/
        else if(_panels[EXIT_BUTTON].IsClicked())
        {
            window.close();
        }
    }

    if(_musicIconButtons[_isMusicOn ? MUSIC_ON_BUTTON : MUSIC_OFF_BUTTON]->IsCursorHoveredOver())
    {
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            if (_isMusicOn)
            {
                _menuMusic.pause();
            }
            else
            {
                _menuMusic.play();
            }
            _isMusicOn = !_isMusicOn;
        }
    }
}

void MenuScene::Update(sf::RenderWindow& window, sf::Time deltaTime)
{
    //auto mouse_pos = sf::Mouse::getPosition(window); // Mouse _innerPosition relative to the window
    //auto mousePosWorldCoords = window.mapPixelToCoords(mouse_pos, _worldView); // Mouse _innerPosition translated into world coordinates

    _cursor.Update(window, deltaTime);
    _cursor.SetCursorPos(window, _worldView);

    for (int i = 0; i < NUM_OF_BUTTONS; ++i)
    {
        _panels[i].Update(window);
    }
    for (auto & ship : _starship)
    {
        ship->Update(window, deltaTime);
    }

    for (int i = 0; i < _starship.size(); ++i)
    {
        // Player ships movement
        if(i < BACKGROUND_SHIPS/2)
        {
            sf::Vector2f movement(_starship[i]->GetSpeed() * 2, 0.0f);
            _starship[i]->GetSpriteComponent().GetSprite().move(movement * deltaTime.asSeconds());
        }
        // Enemy ships movement
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

    // Move layers
    _backgroundSprite.move(-25.0F * deltaTime.asSeconds(), 0);

    // Wrap around logic
    if(_backgroundSprite.getPosition().x + _backgroundSprite.getGlobalBounds().width/2.0F < 0)
    {
        _backgroundSprite.setPosition(0, 0);
    }

    // Update star positions
    for (auto& star : _parallaxStars)
    {
        star.position.x -= star.speed * 100.0F * deltaTime.asSeconds();
        star.circleShape.setPosition(star.position);
        if (star.position.x < 0)
        {
            star.position.x = Constants::WINDOW_WIDTH;
            star.position.y = std::rand() % (int)Constants::WINDOW_HEIGHT;
        }
    }

    // Button highlighting
    if(_panels[PLAY_BUTTON].IsHoveredOver())
    {
        _panels[PLAY_BUTTON].SetPanelColour(sf::Color(22, 155, 164, 65));
        _panels[PLAY_BUTTON].SetText(_panels[PLAY_BUTTON].GetText().getString(), sf::Color(22, 155, 164));
    }
    /*else if(_panels[OPTIONS_BUTTON].IsHoveredOver())
    {
        _panels[OPTIONS_BUTTON].SetPanelColour(sf::Color(150, 150, 150, 60));
        _panels[OPTIONS_BUTTON].SetScrapText(_panels[OPTIONS_BUTTON].GetText().getString(), sf::Color(150, 150, 150));
    }*/
    else if(_panels[EXIT_BUTTON].IsHoveredOver())
    {
        _panels[EXIT_BUTTON].SetPanelColour(sf::Color(242, 22, 22, 60));
        _panels[EXIT_BUTTON].SetText(_panels[EXIT_BUTTON].GetText().getString(), sf::Color::Red);
    }

    for (int i = 0; i < NUM_OF_BUTTONS; i++)
    {
        if(!_panels[i].IsHoveredOver())
        {
            if(i == OPTIONS_BUTTON) // TODO: Remove this index skip code once the options menu has been implemented
            {
                _panels[OPTIONS_BUTTON].SetPanelColour(sf::Color(150, 150, 150, 50));
                _panels[OPTIONS_BUTTON].SetText(_panels[OPTIONS_BUTTON].GetText().getString(), sf::Color(150, 150, 150));
                continue;
            }

            _panels[i].SetPanelColour(sf::Color(22, 155, 164, 100));
            _panels[i].SetText(_panels[i].GetText().getString(), sf::Color::White);
        }
    }

    for (const auto & _musicIconButton : _musicIconButtons)
    {
        _musicIconButton->Update(window);
    }

    for (const auto & musicIconButton : _musicIconButtons)
    {
        if(musicIconButton->IsCursorHoveredOver())
        {
            musicIconButton->SetColour(_predefinedColours.LIGHTBLUE);
        }
        else
        {
            musicIconButton->SetColour(sf::Color(22, 155, 164, 100));
        }
    }
}

void MenuScene::Render(sf::RenderWindow& window)
{
    window.setView(_worldView);
    window.draw(_backgroundSprite);
    for (auto& star : _parallaxStars)
    {
        window.draw(star.circleShape);
    }
    for (auto & ship : _starship)
    {
        ship->Render(window);
    }
    window.draw(_menuTitleImgSprite);
    for (auto & panel : _panels)
    {
        panel.Render(window);
    }
    window.draw(_gameVersionText);
    _musicIconButtons[_isMusicOn ? MUSIC_ON_BUTTON : MUSIC_OFF_BUTTON]->Render(window);
    _cursor.Render(window);
}

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
    if (!_backgroundTexture.loadFromFile("Resources/Textures/space_nebula_2.png"))
    {
        return false;
    }
    _backgroundTexture.setRepeated(true);
    _backgroundSprite.setTexture(_backgroundTexture);
    _backgroundSprite.setTextureRect(sf::IntRect(0, 0, Constants::WINDOW_WIDTH * 2.0F, Constants::WINDOW_HEIGHT * 2.0F));
    _backgroundSprite.setColor(sf::Color::Cyan);

    // Initialize stars
    for (int i = 0; i < NUM_OF_STARS; ++i)
    {
        _parallaxStars.emplace_back();
        _parallaxStars[i].position = sf::Vector2f(std::rand() % (int)Constants::WINDOW_WIDTH, std::rand() % (int)Constants::WINDOW_HEIGHT);
        _parallaxStars[i].speed = 0.1f + static_cast<float>(std::rand() % 100) / 100.0f; // Speed between 0.1 and 1.0
        _parallaxStars[i].size = 0.5f + static_cast<float>(std::rand() % 2); // Size between 1 and 3
        _parallaxStars[i].circleShape.setRadius(_parallaxStars[i].size);
        _parallaxStars[i].circleShape.setFillColor(_predefinedColours.LIGHTBLUE);
    }

    return true;
}

void MenuScene::InitButtonPanels()
{
    std::array<std::string, NUM_OF_BUTTONS> button_text
    {
        "PLAY",
        "OPTIONS",
        "EXIT"
    };

    for (int i = 0; i < NUM_OF_BUTTONS; ++i)
    {
        _panels[i].SetText(button_text[i]);
        _panels[i].SetTextSize(20);
        _panels[i].SetSize(25, 20);
        _panels[i].SetPanelColour(sf::Color(22, 155, 164, 100));
        _panels[i].SetPosition(Constants::WINDOW_WIDTH * 0.185F,
                              (Constants::WINDOW_HEIGHT * 0.57F) + static_cast<float>((i * (_panels[i].GetPanelSize().height + 10))));
    }
}

bool MenuScene::InitMenuTitleIcon()
{
    if (!_menuTitleImgTexture.loadFromFile("Resources/Textures/StarfleetCommandNewLogo3.png"))
    {
        return false;
    }
    _menuTitleImgTexture.setSmooth(true);
    _menuTitleImgSprite.setTexture(_menuTitleImgTexture);
    _menuTitleImgSprite.setScale(0.15F, 0.15F);
    _menuTitleImgSprite.setPosition(Constants::WINDOW_WIDTH/2.0F - _menuTitleImgSprite.getGlobalBounds().width/2.0F, Constants::WINDOW_HEIGHT * 0.3F - _menuTitleImgSprite.getGlobalBounds().height/2.0F);

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
        std::unique_ptr<IStarship> newStarship = StarshipFactory::CreateShip(static_cast<StarshipFactory::STARSHIP_TYPE>(rand_ship), 0);
        _starship.emplace_back(std::move(newStarship));
        _starship[i]->GetSpriteComponent().SetPos({static_cast<float>(rand_x), static_cast<float>(rand_y)});
        _starship[i]->GetSpriteComponent().GetSprite().setColor(_predefinedColours.LIGHTBLUE);

        /*if(i < 2)
        {
            _starship[i]->GetSpriteComponent().GetSprite().setColor(_predefinedColours.LIGHTGREEN);
        }
        else if (i >= 2 && i < 4)
        {
            _starship[i]->GetSpriteComponent().GetSprite().setColor(_predefinedColours.LIGHTBLUE);
        }
        else if (i >= 4 && i < 6)
        {
            _starship[i]->GetSpriteComponent().GetSprite().setColor(_predefinedColours.LIGHTRED);
        }
        else
        {
            _starship[i]->GetSpriteComponent().GetSprite().setColor(_predefinedColours.ORANGE);
        }*/


        if(i >= BACKGROUND_SHIPS/2)
        {
            _starship[i]->GetSpriteComponent().GetSprite().setRotation(180);
            _starship[i]->GetSpriteComponent().GetSprite().setColor(_predefinedColours.LIGHTGREEN);

            /*if(i < 10)
            {
                _starship[i]->GetSpriteComponent().GetSprite().setColor(_predefinedColours.YELLOW);
            }
            else if (i >= 10 && i < 12)
            {
                _starship[i]->GetSpriteComponent().GetSprite().setColor(_predefinedColours.BLUEVIOLET);
            }
            else if (i >= 12 && i < 14)
            {
                _starship[i]->GetSpriteComponent().GetSprite().setColor(sf::Color::White);
            }
            else
            {
                _starship[i]->GetSpriteComponent().GetSprite().setColor(sf::Color::Magenta);
            }*/
        }
    }
}

void MenuScene::InitGameVersionText()
{
    _gameVersionText.setFont(Chilli::CustomFonts::GetRegularFont());
    _gameVersionText.setString("PRE-ALPHA BUILD v0.0.1");
    _gameVersionText.setCharacterSize(12);
    _gameVersionText.setFillColor(sf::Color::White);
    _gameVersionText.setOutlineColor(sf::Color::Black);
    _gameVersionText.setPosition(Constants::WINDOW_WIDTH - (_gameVersionText.getGlobalBounds().width + 20.0F), Constants::WINDOW_HEIGHT - (_gameVersionText.getGlobalBounds().height + 20.0F));
}

void MenuScene::CreateDistribution(const std::string& name, int min, int max)
{
    std::uniform_int_distribution<int> instance{min, max};
    _distributions.emplace_back(instance);
}





