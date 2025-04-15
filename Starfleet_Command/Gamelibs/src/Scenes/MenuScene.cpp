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
    InitView();
    InitBackground();
    InitButtonPanels();
    InitMenuTitleIcon();
    InitBackgroundShips();
    InitGameVersionText();

    _gameSettingsOverlayWindow.setSize({300.0F, 260.0F});
    _gameSettingsOverlayWindow.setFillColor(sf::Color(0, 0, 0, 125));
    _gameSettingsOverlayWindow.setOutlineColor(_predefinedColours.LIGHTBLUE);
    _gameSettingsOverlayWindow.setOutlineThickness(1.0F);

    _gameSettingsTitleText.setString("GAME SETTINGS");
    _gameSettingsTitleText.setFont(Chilli::CustomFonts::GetBoldFont());
    _gameSettingsTitleText.setCharacterSize(16);
    _gameSettingsTitleText.setFillColor(_predefinedColours.LIGHTBLUE);
    _gameSettingsTitleText.setOutlineColor(sf::Color::Black);
    _gameSettingsTitleText.setOutlineThickness(1.0F);

    _gameSettingsLeftArrowTexture.loadFromFile("Resources/Textures/left.png");
    _gameSettingsRightArrowTexture.loadFromFile("Resources/Textures/right.png");
    for (int i = 0; i < NUM_OF_SETTINGS_ELEMENTS; ++i)
    {
        _gameSettingsLeftArrowSprite[i].setTexture(_gameSettingsLeftArrowTexture);
        _gameSettingsLeftArrowSprite[i].scale(0.2F, 0.2F);
        _gameSettingsLeftArrowSprite[i].setColor(_predefinedColours.LIGHTBLUE);

        _gameSettingsRightArrowSprite[i].setTexture(_gameSettingsRightArrowTexture);
        _gameSettingsRightArrowSprite[i].scale(0.2F, 0.2F);
        _gameSettingsRightArrowSprite[i].setColor(_predefinedColours.LIGHTBLUE);
    }

    // TODO: Create method CreateMenuElement("Music", false);
    _gameSettingsMenuElements[0].nameText.setString("Music"); // TODO: Pass in GameSettings.json data
    //_gameSettingsMenuElements[0].type = SettingsType::TOGGLE;
    _gameSettingsMenuElements[0].statusText.setString("ON"); // TODO: Pass in GameSettings.json data
    _gameSettingsMenuElements[0].isEnabled = true; // TODO: Pass in GameSettings.json data

    _gameSettingsMenuElements[1].nameText.setString("Spacelanes");
    //_gameSettingsMenuElements[1].type = SettingsType::TOGGLE;
    _gameSettingsMenuElements[1].statusText.setString("ON");
    _gameSettingsMenuElements[1].isEnabled = true;

    _gameSettingsMenuElements[2].nameText.setString("Minimap");
    //_gameSettingsMenuElements[2].type = SettingsType::TOGGLE;
    _gameSettingsMenuElements[2].statusText.setString("ON");
    _gameSettingsMenuElements[2].isEnabled = true;

    _gameSettingsMenuElements[3].nameText.setString("Player Colour");
    //_gameSettingsMenuElements[3].type = SettingsType::COLOUR_PICKER;
    _gameSettingsMenuElements[3].statusText.setString("LIGHTBLUE");
    _gameSettingsMenuElements[3].isEnabled = false;

    _gameSettingsMenuElements[4].nameText.setString("Enemy Colour");
    //_gameSettingsMenuElements[4].type = SettingsType::COLOUR_PICKER;
    _gameSettingsMenuElements[4].statusText.setString("LIGHTGREEN");
    _gameSettingsMenuElements[4].isEnabled = false;

    _gameSettingsMenuElements[5].nameText.setString("Director Difficulty");
    //_gameSettingsMenuElements[5].type = SettingsType::COLOUR_PICKER;
    _gameSettingsMenuElements[5].statusText.setString("EASY");
    _gameSettingsMenuElements[5].isEnabled = false;

    for (auto & _gameSettingsMenuElement : _gameSettingsMenuElements)
    {
        _gameSettingsMenuElement.nameText.setFont(Chilli::CustomFonts::GetBoldFont());
        _gameSettingsMenuElement.nameText.setCharacterSize(12);
        _gameSettingsMenuElement.nameText.setFillColor(sf::Color::White);
        _gameSettingsMenuElement.nameText.setOutlineColor(sf::Color::Black);
        _gameSettingsMenuElement.nameText.setOutlineThickness(1.0F);

        _gameSettingsMenuElement.statusText.setFont(Chilli::CustomFonts::GetBoldFont());
        _gameSettingsMenuElement.statusText.setCharacterSize(12);
        _gameSettingsMenuElement.statusText.setFillColor(sf::Color::White);
        _gameSettingsMenuElement.statusText.setOutlineColor(sf::Color::Black);
        _gameSettingsMenuElement.statusText.setOutlineThickness(1.0F);
    }

    if(!_menuMusic.openFromFile("Resources/Audio/MenuTheme/United_Against_Evil_175bpm_136s.wav"))
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
        _musicIconButtons[i]->SetPos({20, 20});
        _musicIconButtons[i]->SetColour(sf::Color(22, 155, 164, 100));
    }

    return true;
}

void MenuScene::EventHandler(sf::RenderWindow& window, sf::Event& event)
{
    if(_musicIconButtons[_isMusicOn ? MUSIC_ON_BUTTON : MUSIC_OFF_BUTTON]->IsCursorHoveredOver())
    {
        if (event.type == sf::Event::MouseButtonPressed and event.mouseButton.button == sf::Mouse::Left)
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

    if(_isGameSettingsEnabled)
    {
        _buttonPanels[BACK_BUTTON].EventHandler(window, event);
        if (event.type == sf::Event::MouseButtonPressed and event.mouseButton.button == sf::Mouse::Left)
        {
            if(_buttonPanels[BACK_BUTTON].IsClicked())
            {
                _isGameSettingsEnabled = false;
                _menuTitleImgSprite.setPosition(Constants::WINDOW_WIDTH/2.0F - _menuTitleImgSprite.getGlobalBounds().width/2.0F, Constants::WINDOW_HEIGHT * 0.3F - _menuTitleImgSprite.getGlobalBounds().height/2.0F);
            }
        }
        return;
    }

    for (int i = 0; i < NUM_OF_BUTTONS-1; ++i)
    {
        _buttonPanels[i].EventHandler(window, event);
    }

    if (event.type == sf::Event::MouseButtonPressed and event.mouseButton.button == sf::Mouse::Left)
    {
        if(_buttonPanels[PLAY_BUTTON].IsClicked())
        {
            SetScene(Scene::ID::GAME);
        }
        else if(_buttonPanels[OPTIONS_BUTTON].IsClicked())
        {
            _isGameSettingsEnabled = true;
            _menuTitleImgSprite.setPosition(Constants::WINDOW_WIDTH/2.0F - _menuTitleImgSprite.getGlobalBounds().width/2.0F, Constants::WINDOW_HEIGHT * 0.2F - _menuTitleImgSprite.getGlobalBounds().height/2.0F);
            _gameSettingsOverlayWindow.setPosition({Constants::WINDOW_WIDTH / 2.0F - _gameSettingsOverlayWindow.getSize().x / 2.0F, _menuTitleImgSprite.getPosition().y + _menuTitleImgSprite.getGlobalBounds().height + 25.0F});
            _gameSettingsTitleText.setPosition({_gameSettingsOverlayWindow.getPosition().x + _gameSettingsOverlayWindow.getSize().x / 2.0F - _gameSettingsTitleText.getGlobalBounds().width / 2.0F, _gameSettingsOverlayWindow.getPosition().y + 20.0F});

            for (int i = 0; i < NUM_OF_SETTINGS_ELEMENTS; ++i)
            {
                _gameSettingsMenuElements[i].nameText.setPosition({_gameSettingsOverlayWindow.getPosition().x + 25.0F, _gameSettingsOverlayWindow.getPosition().y + 65.0F + (i * (_gameSettingsMenuElements[0].nameText.getGlobalBounds().height + 20.0F))});
                _gameSettingsMenuElements[i].statusText.setPosition({_gameSettingsOverlayWindow.getPosition().x + _gameSettingsOverlayWindow.getGlobalBounds().width  - _gameSettingsMenuElements[i].statusText.getGlobalBounds().width -  35.0F - _gameSettingsRightArrowSprite[i].getGlobalBounds().width, _gameSettingsMenuElements[i].nameText.getPosition().y});

                _gameSettingsLeftArrowSprite[i].setPosition({_gameSettingsMenuElements[i].statusText.getPosition().x - _gameSettingsLeftArrowSprite[i].getGlobalBounds().width - 10.0F, _gameSettingsMenuElements[i].statusText.getPosition().y + 1.0F});
                _gameSettingsRightArrowSprite[i].setPosition({_gameSettingsMenuElements[i].statusText.getPosition().x + _gameSettingsMenuElements[i].statusText.getGlobalBounds().width + 10.0F, _gameSettingsMenuElements[i].statusText.getPosition().y + 1.0F});
            }
        }
        else if(_buttonPanels[EXIT_BUTTON].IsClicked())
        {
            window.close();
        }
    }
}

void MenuScene::Update(sf::RenderWindow& window, sf::Time deltaTime)
{
    _cursor.Update(window, deltaTime);
    _cursor.SetCursorPos(window, _worldView);

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


    _backgroundSprite.move(-25.0F * deltaTime.asSeconds(), 0);
    if(_backgroundSprite.getPosition().x + _backgroundSprite.getGlobalBounds().width/2.0F < 0)
    {
        _backgroundSprite.setPosition(0, 0);
    }

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

    if(_musicIconButtons[_isMusicOn]->IsCursorHoveredOver())
    {
        _cursor.SetCursorType(Chilli::Cursor::Type::HOVER);
    }
    else if(not _musicIconButtons[_isMusicOn]->IsCursorHoveredOver())
    {
        _cursor.SetCursorType(Chilli::Cursor::Type::DEFAULT);
    }


    if(_isGameSettingsEnabled)
    {
        _buttonPanels[BACK_BUTTON].Update(window);

        if(_buttonPanels[BACK_BUTTON].IsHoveredOver())
        {
            _buttonPanels[BACK_BUTTON].SetPanelColour(sf::Color(22, 155, 164, 65));
            _buttonPanels[BACK_BUTTON].SetText(_buttonPanels[BACK_BUTTON].GetText().getString(), sf::Color(22, 155, 164));
            _cursor.SetCursorType(Chilli::Cursor::Type::HOVER);
        }
        else if(not _buttonPanels[BACK_BUTTON].IsHoveredOver())
        {
            _buttonPanels[BACK_BUTTON].SetPanelColour(sf::Color(22, 155, 164, 100));
            _buttonPanels[BACK_BUTTON].SetText(_buttonPanels[BACK_BUTTON].GetText().getString(), sf::Color::White);
        }

        /*for (int i = 0; i < _gameSettingsMenuElements.size(); ++i)
        {
            if(_gameSettingsMenuElements[i].isEnabled)
            {
                //_gameSettingsMenuElements[i].statusText.setFillColor(sf::Color::Green);
                //_gameSettingsMenuElements[i].statusText.setString("ON");
            }
            else
            {
                //_gameSettingsMenuElements[i].statusText.setFillColor(sf::Color::Red);
                //_gameSettingsMenuElements[i].statusText.setString("OFF");
            }
        }*/

        return;
    }

    for (int i = 0; i < NUM_OF_BUTTONS-1; ++i)
    {
        _buttonPanels[i].Update(window);
    }

    if(_buttonPanels[PLAY_BUTTON].IsHoveredOver())
    {
        _buttonPanels[PLAY_BUTTON].SetPanelColour(sf::Color(22, 155, 164, 65));
        _buttonPanels[PLAY_BUTTON].SetText(_buttonPanels[PLAY_BUTTON].GetText().getString(), sf::Color(22, 155, 164));
        _cursor.SetCursorType(Chilli::Cursor::Type::HOVER);
    }
    else if(_buttonPanels[OPTIONS_BUTTON].IsHoveredOver())
    {
        _buttonPanels[OPTIONS_BUTTON].SetPanelColour(sf::Color(22, 155, 164, 65));
        _buttonPanels[OPTIONS_BUTTON].SetText(_buttonPanels[OPTIONS_BUTTON].GetText().getString(), sf::Color(22, 155, 164));
        _cursor.SetCursorType(Chilli::Cursor::Type::HOVER);
    }
    else if(_buttonPanels[EXIT_BUTTON].IsHoveredOver())
    {
        _buttonPanels[EXIT_BUTTON].SetPanelColour(sf::Color(242, 22, 22, 60));
        _buttonPanels[EXIT_BUTTON].SetText(_buttonPanels[EXIT_BUTTON].GetText().getString(), sf::Color::Red);
        _cursor.SetCursorType(Chilli::Cursor::Type::HOVER);
    }

    for (int i = 0; i < NUM_OF_BUTTONS-1; ++i)
    {
        if(not _buttonPanels[i].IsHoveredOver())
        {
            _buttonPanels[i].SetPanelColour(sf::Color(22, 155, 164, 100));
            _buttonPanels[i].SetText(_buttonPanels[i].GetText().getString(), sf::Color::White);
        }
    }
}

void MenuScene::Render(sf::RenderWindow& window)
{
    window.setView(_worldView);
    window.draw(_backgroundSprite);
    window.draw(_backgroundPlayerPlanetSprite);
    window.draw(_backgroundEnemyPlanetSprite);
    for (auto& star : _parallaxStars)
    {
        window.draw(star.circleShape);
    }
    for (auto & ship : _starship)
    {
        ship->Render(window);
    }
    window.draw(_menuTitleImgSprite);

    if(not _isGameSettingsEnabled)
    {
        for (int i = 0; i < _buttonPanels.size()-1; ++i)
        {
            _buttonPanels[i].Render(window);
        }
    }
    else
    {
        _buttonPanels[BACK_BUTTON].Render(window);
        window.draw(_gameSettingsOverlayWindow);
        window.draw(_gameSettingsTitleText);
        for (auto & _gameSettingsMenuElement : _gameSettingsMenuElements)
        {
            window.draw(_gameSettingsMenuElement.nameText);
            window.draw(_gameSettingsMenuElement.statusText);
        }
        for (int i = 0; i < NUM_OF_SETTINGS_ELEMENTS; ++i)
        {
            window.draw(_gameSettingsLeftArrowSprite[i]);
            window.draw(_gameSettingsRightArrowSprite[i]);
        }
    }

    window.draw(_gameVersionText);
    _musicIconButtons[_isMusicOn ? MUSIC_ON_BUTTON : MUSIC_OFF_BUTTON]->Render(window);
    _cursor.Render(window);
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

    for (int i = 0; i < NUM_OF_STARS; ++i)
    {
        _parallaxStars.emplace_back();
        _parallaxStars[i].position = sf::Vector2f(std::rand() % (int)Constants::WINDOW_WIDTH, std::rand() % (int)Constants::WINDOW_HEIGHT);
        _parallaxStars[i].speed = 0.1f + static_cast<float>(std::rand() % 100) / 100.0f; // Speed between 0.1 and 1.0
        _parallaxStars[i].size = 0.5f + static_cast<float>(std::rand() % 2); // Size between 1 and 3
        _parallaxStars[i].circleShape.setRadius(_parallaxStars[i].size);
        _parallaxStars[i].circleShape.setFillColor(_predefinedColours.LIGHTBLUE);
    }

    _backgroundPlayerPlanetTexture.loadFromFile("Resources/Textures/planet07.png"); // 4 or 7
    _backgroundPlayerPlanetSprite.setTexture(_backgroundPlayerPlanetTexture);
    /*_backgroundPlayerPlanetSprite.setScale(0.3F, 0.3F);
    _backgroundPlayerPlanetSprite.setPosition(Constants::WINDOW_WIDTH - _backgroundPlayerPlanetSprite.getGlobalBounds().width, 100.0F);*/
    //_backgroundPlayerPlanetSprite.setPosition(Constants::WINDOW_WIDTH - _backgroundPlayerPlanetSprite.getGlobalBounds().width, 300.0F);
    _backgroundPlayerPlanetSprite.setPosition(Constants::WINDOW_WIDTH / 2.0F, Constants::WINDOW_HEIGHT / 4.0F);

    _backgroundEnemyPlanetTexture.loadFromFile("Resources/Textures/planet04.png"); // 4 or 7
    _backgroundEnemyPlanetSprite.setTexture(_backgroundEnemyPlanetTexture);
    _backgroundEnemyPlanetSprite.setScale(0.2F, 0.2F);
    _backgroundEnemyPlanetSprite.setPosition(50.0F, 50.0F);

    return true;
}

void MenuScene::InitButtonPanels()
{
    std::array<std::string, NUM_OF_BUTTONS> button_text
    {
        "PLAY",
        "SETTINGS",
        "EXIT",
        "BACK"
    };

    for (int i = 0; i < NUM_OF_BUTTONS; ++i)
    {
        _buttonPanels[i].SetText(button_text[i]);
        _buttonPanels[i].SetTextSize(20);
        _buttonPanels[i].SetSize(25, 20);
        _buttonPanels[i].SetPanelColour(sf::Color(22, 155, 164, 100));
        _buttonPanels[i].SetPosition(Constants::WINDOW_WIDTH * 0.185F,(Constants::WINDOW_HEIGHT * 0.57F) + static_cast<float>((i * (_buttonPanels[i].GetPanelSize().height + 10))));
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

void MenuScene::InitBackgroundShips()
{
    RNG starshipXPosRNG {0,static_cast<int>(Constants::WINDOW_WIDTH)};
    RNG starshipYPosRNG {45, 675};
    RNG starshipTypeRNG {0,4};

    for (int i = 0; i < BACKGROUND_SHIPS; ++i)
    {
        int rand_x = starshipXPosRNG.GenerateNumber();
        int rand_y = starshipYPosRNG.GenerateNumber();
        int rand_ship = starshipTypeRNG.GenerateNumber();
        std::unique_ptr<IStarship> newStarship = StarshipFactory::CreateShip(static_cast<StarshipFactory::STARSHIP_TYPE>(rand_ship));
        _starship.emplace_back(std::move(newStarship));
        _starship[i]->SetPosition({static_cast<float>(rand_x), static_cast<float>(rand_y)});
        _starship[i]->SetColour(_predefinedColours.LIGHTBLUE);

        if(i >= BACKGROUND_SHIPS/2)
        {
            _starship[i]->SetRotation(180);
            _starship[i]->SetColour(_predefinedColours.LIGHTGREEN);
        }
    }
}

void MenuScene::InitGameVersionText()
{
    _gameVersionText.setFont(Chilli::CustomFonts::GetBoldFont());
    _gameVersionText.setString("PRE-ALPHA BUILD v0.2.0"); // Early Alpha = v0.5.0, Early Beta = v0.8.0, Release = v1.0.0
    _gameVersionText.setCharacterSize(14);
    _gameVersionText.setFillColor(_predefinedColours.LIGHTBLUE);
    _gameVersionText.setOutlineColor(sf::Color::Black);
    //_gameVersionText.setPosition(Constants::WINDOW_WIDTH - (_gameVersionText.getGlobalBounds().width + 20.0F), Constants::WINDOW_HEIGHT - (_gameVersionText.getGlobalBounds().height + 20.0F));
    _gameVersionText.setPosition(20.0F, Constants::WINDOW_HEIGHT - (_gameVersionText.getGlobalBounds().height + 20.0F));
    //_gameVersionText.setPosition(_menuTitleImgSprite.getPosition().x + _menuTitleImgSprite.getGlobalBounds().width/2.0F - _gameVersionText.getGlobalBounds().width/2.0F, _menuTitleImgSprite.getPosition().y + _menuTitleImgSprite.getGlobalBounds().height + 10.0F);
}
