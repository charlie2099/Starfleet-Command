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

    _gameSettingsOverlayWindow.setSize({400.0F, 260.0F});
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
        _gameSettingsLeftArrowSprite[i].scale(0.25F, 0.25F);
        _gameSettingsLeftArrowSprite[i].setColor(_predefinedColours.LIGHTBLUE);

        _gameSettingsRightArrowSprite[i].setTexture(_gameSettingsRightArrowTexture);
        _gameSettingsRightArrowSprite[i].scale(0.25F, 0.25F);
        _gameSettingsRightArrowSprite[i].setColor(_predefinedColours.LIGHTBLUE);
    }

    // TODO: Create method CreateMenuElement("Music", false);
    _gameSettingsMenuElements[0].nameText.setString("Music"); // TODO: Pass in GameSettings.json data
    //_gameSettingsMenuElements[0].type = SettingsType::TOGGLE;
    //_gameSettingsMenuElements[0].subElementIndex = 1;
    _gameSettingsMenuElements[0].subElementNames.emplace_back("OFF");
    _gameSettingsMenuElements[0].subElementNames.emplace_back("ON");
    //_gameSettingsMenuElements[0].statusText.setString(_gameSettingsMenuElements[0].subElementNames[_gameSettingsMenuElements[0].subElementIndex]);

    auto path = "Resources/Data/GameSettings.json";
    if(Chilli::JsonSaveSystem::CheckFileExists(path))
    {
        std::cout << "GameSettings file found!" << std::endl;
        auto fileData = Chilli::JsonSaveSystem::LoadFile(path);

        /// Music Setting Data
        if(fileData.contains("IsMusicEnabled"))
        {
            std::string musicEnabled = fileData["IsMusicEnabled"];
            _isMusicOn = (musicEnabled == "true");
            _gameSettingsMenuElements[0].subElementIndex = _isMusicOn ? 1: 0;
            _gameSettingsMenuElements[0].statusText.setString(_gameSettingsMenuElements[0].subElementNames[_gameSettingsMenuElements[0].subElementIndex]);
        }
    }

    _gameSettingsMenuElements[1].nameText.setString("Spacelanes");
    //_gameSettingsMenuElements[1].type = SettingsType::TOGGLE;
    _gameSettingsMenuElements[1].subElementIndex = 1;
    _gameSettingsMenuElements[1].subElementNames.emplace_back("OFF");
    _gameSettingsMenuElements[1].subElementNames.emplace_back("ON");
    _gameSettingsMenuElements[1].statusText.setString(_gameSettingsMenuElements[1].subElementNames[_gameSettingsMenuElements[1].subElementIndex]);

    _gameSettingsMenuElements[2].nameText.setString("Minimap");
    //_gameSettingsMenuElements[2].type = SettingsType::TOGGLE;
    _gameSettingsMenuElements[2].subElementIndex = 1;
    _gameSettingsMenuElements[2].subElementNames.emplace_back("OFF");
    _gameSettingsMenuElements[2].subElementNames.emplace_back("ON");
    _gameSettingsMenuElements[2].statusText.setString(_gameSettingsMenuElements[2].subElementNames[_gameSettingsMenuElements[2].subElementIndex]);

    _gameSettingsMenuElements[3].nameText.setString("Player Colour");
    //_gameSettingsMenuElements[3].type = SettingsType::COLOUR_PICKER;
    _gameSettingsMenuElements[3].numOfSubElements = 5;
    _gameSettingsMenuElements[3].subElementNames.emplace_back("BLUE");
    _gameSettingsMenuElements[3].subElementNames.emplace_back("RED");
    _gameSettingsMenuElements[3].subElementNames.emplace_back("GREEN");
    _gameSettingsMenuElements[3].subElementNames.emplace_back("ORANGE");
    _gameSettingsMenuElements[3].subElementNames.emplace_back("PURPLE");
    _gameSettingsMenuElements[3].statusText.setString(_gameSettingsMenuElements[3].subElementNames[_gameSettingsMenuElements[3].subElementIndex]);

    _gameSettingsMenuElements[4].nameText.setString("Enemy Colour");
    //_gameSettingsMenuElements[4].type = SettingsType::COLOUR_PICKER;
    _gameSettingsMenuElements[4].numOfSubElements = 5;
    _gameSettingsMenuElements[4].subElementNames.emplace_back("GREEN");
    _gameSettingsMenuElements[4].subElementNames.emplace_back("RED");
    _gameSettingsMenuElements[4].subElementNames.emplace_back("BLUE");
    _gameSettingsMenuElements[4].subElementNames.emplace_back("ORANGE");
    _gameSettingsMenuElements[4].subElementNames.emplace_back("PURPLE");
    _gameSettingsMenuElements[4].statusText.setString(_gameSettingsMenuElements[4].subElementNames[_gameSettingsMenuElements[4].subElementIndex]);

    _gameSettingsMenuElements[5].nameText.setString("Director Difficulty");
    //_gameSettingsMenuElements[5].type = SettingsType::COLOUR_PICKER;
    _gameSettingsMenuElements[5].numOfSubElements = 3;
    _gameSettingsMenuElements[5].subElementNames.emplace_back("EASY");
    _gameSettingsMenuElements[5].subElementNames.emplace_back("MEDIUM");
    _gameSettingsMenuElements[5].subElementNames.emplace_back("HARD");
    _gameSettingsMenuElements[5].statusText.setString(_gameSettingsMenuElements[5].subElementNames[_gameSettingsMenuElements[5].subElementIndex]);

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

    return true;
}

void MenuScene::EventHandler(sf::RenderWindow& window, sf::Event& event)
{
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

        for (int i = 0; i < NUM_OF_SETTINGS_ELEMENTS; ++i)
        {
            if(Chilli::Vector::BoundsCheck(_cursor.GetPos(), _gameSettingsLeftArrowSprite[i].getGlobalBounds()))
            {
                if (event.type == sf::Event::MouseButtonPressed and event.mouseButton.button == sf::Mouse::Left)
                {
                    _gameSettingsMenuElements[i].subElementIndex--;
                    if(_gameSettingsMenuElements[i].subElementIndex <= 0)
                    {
                        _gameSettingsMenuElements[i].subElementIndex = 0;
                    }
                    _gameSettingsMenuElements[i].statusText.setString(_gameSettingsMenuElements[i].subElementNames[_gameSettingsMenuElements[i].subElementIndex]);
                    auto statusTextXPos = _gameSettingsOverlayWindow.getPosition().x + _gameSettingsOverlayWindow.getGlobalBounds().width*0.725F - _gameSettingsMenuElements[i].statusText.getGlobalBounds().width/2.0F;
                    _gameSettingsMenuElements[i].statusText.setPosition({statusTextXPos, _gameSettingsMenuElements[i].nameText.getPosition().y});

                    auto path = "Resources/Data/GameSettings.json";
                    json gameSettingsData;
                    gameSettingsData["IsMusicEnabled"] = _gameSettingsMenuElements[0].subElementIndex == 1 ? "true" : "false";
                    Chilli::JsonSaveSystem::SaveFile(path, gameSettingsData);
                    std::cout << "Settings saved to " << path << std::endl;
                    _isMusicOn = _gameSettingsMenuElements[0].subElementIndex;
                    if(_isMusicOn and _menuMusic.getStatus() not_eq sf::SoundSource::Playing)
                    {
                        _menuMusic.play();
                    }
                    else if(not _isMusicOn)
                    {
                        _menuMusic.stop();
                    }
                }
            }
            else if(Chilli::Vector::BoundsCheck(_cursor.GetPos(), _gameSettingsRightArrowSprite[i].getGlobalBounds()))
            {
                if (event.type == sf::Event::MouseButtonPressed and event.mouseButton.button == sf::Mouse::Left)
                {
                    _gameSettingsMenuElements[i].subElementIndex++;
                    if(_gameSettingsMenuElements[i].subElementIndex >= _gameSettingsMenuElements[i].numOfSubElements-1)
                    {
                        _gameSettingsMenuElements[i].subElementIndex = _gameSettingsMenuElements[i].numOfSubElements-1;
                    }
                    _gameSettingsMenuElements[i].statusText.setString(_gameSettingsMenuElements[i].subElementNames[_gameSettingsMenuElements[i].subElementIndex]);
                    auto statusTextXPos = _gameSettingsOverlayWindow.getPosition().x + _gameSettingsOverlayWindow.getGlobalBounds().width*0.725F - _gameSettingsMenuElements[i].statusText.getGlobalBounds().width/2.0F;
                    _gameSettingsMenuElements[i].statusText.setPosition({statusTextXPos, _gameSettingsMenuElements[i].nameText.getPosition().y});

                    auto path = "Resources/Data/GameSettings.json";
                    json gameSettingsData;
                    gameSettingsData["IsMusicEnabled"] = _gameSettingsMenuElements[0].subElementIndex == 1 ? "true" : "false";
                    Chilli::JsonSaveSystem::SaveFile(path, gameSettingsData);
                    std::cout << "Settings saved to " << path << std::endl;
                    _isMusicOn = _gameSettingsMenuElements[0].subElementIndex;
                    if(_isMusicOn and _menuMusic.getStatus() not_eq sf::SoundSource::Playing)
                    {
                        _menuMusic.play();
                    }
                    else if(not _isMusicOn)
                    {
                        _menuMusic.stop();
                    }
                }
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

                auto statusTextXPos = _gameSettingsOverlayWindow.getPosition().x + _gameSettingsOverlayWindow.getGlobalBounds().width*0.725F - _gameSettingsMenuElements[i].statusText.getGlobalBounds().width/2.0F;
                _gameSettingsMenuElements[i].statusText.setPosition({statusTextXPos, _gameSettingsMenuElements[i].nameText.getPosition().y});
                //_gameSettingsMenuElements[i].statusText.setPosition({_gameSettingsOverlayWindow.getPosition().x + _gameSettingsOverlayWindow.getSize().x/1.75F - _gameSettingsMenuElements[i].statusText.getGlobalBounds().width/2.0F, _gameSettingsMenuElements[i].nameText.getPosition().y});

                //_gameSettingsLeftArrowSprite[i].setPosition({_gameSettingsMenuElements[i].statusText.getPosition().x - _gameSettingsLeftArrowSprite[i].getGlobalBounds().width - 10.0F, _gameSettingsMenuElements[i].statusText.getPosition().y + 1.0F});
                _gameSettingsLeftArrowSprite[i].setPosition({_gameSettingsOverlayWindow.getPosition().x + _gameSettingsOverlayWindow.getSize().x/2.0F, _gameSettingsMenuElements[i].statusText.getPosition().y + 1.0F});

                _gameSettingsRightArrowSprite[i].setPosition({statusTextXPos + _gameSettingsOverlayWindow.getGlobalBounds().width*0.225F + _gameSettingsMenuElements[i].statusText.getGlobalBounds().width/2.0F - 10.0F, _gameSettingsMenuElements[i].statusText.getPosition().y + 1.0F});
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

    if(_isGameSettingsEnabled)
    {
        _buttonPanels[BACK_BUTTON].Update(window);

        if(_buttonPanels[BACK_BUTTON].IsHoveredOver())
        {
            _buttonPanels[BACK_BUTTON].SetPanelColour(sf::Color(22, 155, 164, 65));
            _buttonPanels[BACK_BUTTON].SetText(_buttonPanels[BACK_BUTTON].GetText().getString(), sf::Color::Cyan);
            _cursor.SetCursorType(Chilli::Cursor::Type::HOVER);
        }
        else if(not _buttonPanels[BACK_BUTTON].IsHoveredOver())
        {
            _buttonPanels[BACK_BUTTON].SetPanelColour(sf::Color(22, 155, 164, 100));
            _buttonPanels[BACK_BUTTON].SetText(_buttonPanels[BACK_BUTTON].GetText().getString(), _predefinedColours.LIGHTBLUE);
            _cursor.SetCursorType(Chilli::Cursor::Type::DEFAULT);
        }

        for (int i = 0; i < NUM_OF_SETTINGS_ELEMENTS; ++i)
        {
            if(Chilli::Vector::BoundsCheck(_cursor.GetPos(), _gameSettingsLeftArrowSprite[i].getGlobalBounds()))
            {
                _cursor.SetCursorType(Chilli::Cursor::Type::HOVER);
                _gameSettingsLeftArrowSprite[i].setColor(sf::Color::Cyan);
                // isHoverOver = true?
            }
            else if(Chilli::Vector::BoundsCheck(_cursor.GetPos(), _gameSettingsRightArrowSprite[i].getGlobalBounds()))
            {
                _cursor.SetCursorType(Chilli::Cursor::Type::HOVER);
                _gameSettingsRightArrowSprite[i].setColor(sf::Color::Cyan);
                // isHoverOver = true?
            }
            else
            {
                _gameSettingsLeftArrowSprite[i].setColor(_predefinedColours.LIGHTBLUE);
                _gameSettingsRightArrowSprite[i].setColor(_predefinedColours.LIGHTBLUE);
            }
        }

        return;
    }

    for (int i = 0; i < NUM_OF_BUTTONS-1; ++i)
    {
        _buttonPanels[i].Update(window);
    }

    if(_buttonPanels[PLAY_BUTTON].IsHoveredOver())
    {
        _buttonPanels[PLAY_BUTTON].SetPanelColour(sf::Color(22, 155, 164, 65));
        _buttonPanels[PLAY_BUTTON].SetText(_buttonPanels[PLAY_BUTTON].GetText().getString(), sf::Color::Cyan);
        _cursor.SetCursorType(Chilli::Cursor::Type::HOVER);
    }
    else if(_buttonPanels[OPTIONS_BUTTON].IsHoveredOver())
    {
        _buttonPanels[OPTIONS_BUTTON].SetPanelColour(sf::Color(22, 155, 164, 65));
        _buttonPanels[OPTIONS_BUTTON].SetText(_buttonPanels[OPTIONS_BUTTON].GetText().getString(), sf::Color::Cyan);
        _cursor.SetCursorType(Chilli::Cursor::Type::HOVER);
    }
    else if(_buttonPanels[EXIT_BUTTON].IsHoveredOver())
    {
        _buttonPanels[EXIT_BUTTON].SetPanelColour(sf::Color(242, 22, 22, 60));
        _buttonPanels[EXIT_BUTTON].SetText(_buttonPanels[EXIT_BUTTON].GetText().getString(), sf::Color::Red);
        _cursor.SetCursorType(Chilli::Cursor::Type::HOVER);
    }
    else
    {
        _cursor.SetCursorType(Chilli::Cursor::Type::DEFAULT);
    }

    for (int i = 0; i < NUM_OF_BUTTONS-1; ++i)
    {
        if(not _buttonPanels[i].IsHoveredOver())
        {
            _buttonPanels[i].SetPanelColour(sf::Color(22, 155, 164, 100));
            _buttonPanels[i].SetText(_buttonPanels[i].GetText().getString(), _predefinedColours.LIGHTBLUE);
        }
    }
}

void MenuScene::Render(sf::RenderWindow& window)
{
    window.setView(_worldView);
    window.draw(_backgroundSprite);
    window.draw(_backgroundEnemyPlanetSprite);
    window.draw(_backgroundPlayerPlanetSprite);
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

    _backgroundEnemyPlanetTexture.loadFromFile("Resources/Textures/spr_planet02.png"); // 4 or 7
    _backgroundEnemyPlanetSprite.setTexture(_backgroundEnemyPlanetTexture);
    /*_backgroundEnemyPlanetSprite.setScale(0.5F, 0.5F);
    _backgroundEnemyPlanetSprite.setPosition(Constants::WINDOW_WIDTH/2.0F - _backgroundEnemyPlanetSprite.getGlobalBounds().width/2.0F, 25.0F);*/
    //_backgroundEnemyPlanetSprite.setPosition(Constants::WINDOW_WIDTH/2.0F - _backgroundEnemyPlanetSprite.getGlobalBounds().width + 100.0F, 300.0F);
    _backgroundEnemyPlanetSprite.setPosition(Constants::WINDOW_WIDTH / 1.6F, Constants::WINDOW_HEIGHT / 2.5F);

    _backgroundPlayerPlanetTexture.loadFromFile("Resources/Textures/spr_planet03.png"); // 4 or 7
    _backgroundPlayerPlanetSprite.setTexture(_backgroundPlayerPlanetTexture);
    _backgroundPlayerPlanetSprite.setScale(0.25F, 0.25F);
    _backgroundPlayerPlanetSprite.setPosition(50.0F, 50.0F);

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
        _buttonPanels[i].SetFont(Panel::TextFont::BOLD);
        _buttonPanels[i].SetText(button_text[i]);
        _buttonPanels[i].SetTextSize(14);
        _buttonPanels[i].SetSize(20, 15);
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
