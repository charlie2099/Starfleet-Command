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


    _gameSettings = std::make_unique<GameSettings>();
    _gameSettings->AddSettingOption("Music", std::vector<std::string>{"OFF", "ON"});
    _gameSettings->AddSettingOption("Spacelanes", std::vector<std::string>{"OFF", "ON"});
    _gameSettings->AddSettingOption("Minimap", std::vector<std::string>{"OFF", "ON"});
    _gameSettings->AddSettingOption("Player Colour",std::vector<std::string>{"BLUE", "RED", "GREEN", "ORANGE", "PURPLE"});
    //_gameSettings->AddSettingOption("Enemy Colour",std::vector<std::string>{"BLUE", "RED", "GREEN", "ORANGE", "PURPLE"});
    //_gameSettings->AddSettingOption("Difficulty", std::vector<std::string>{"EASY", "MEDIUM", "HARD"});

    auto path = "Resources/Data/GameSettings.json";
    if(Chilli::JsonSaveSystem::CheckFileExists(path))
    {
        std::cout << "GameSettings file found!" << std::endl;
        auto fileData = Chilli::JsonSaveSystem::LoadFile(path);

        if(fileData.contains("Music"))
        {
            std::cout << "[ Music ] data found!" << std::endl;

            std::string musicData = fileData["Music"];
            //_isMusicOn = (musicData == "true");
            if(musicData == "true")
            {
                _isMusicOn = true;
            }
            else if(musicData == "false")
            {
                _isMusicOn = false;
            }
            else
            {
                std::cout << "Invalid JSON data entry for Music setting" << std::endl;
            }

            _gameSettings->UpdateSettingOptionValueText("Music", musicData == "true");
        }

        if(fileData.contains("Player Colour"))
        {
            std::cout << "[ Player Colour ] data found!" << std::endl;

            std::string playerColourData = fileData["Player Colour"];

            auto playerColourSetting = _gameSettings->GetSettingOption("Player Colour");
            for (int i = 0; i < playerColourSetting.optionValues.size(); ++i)
            {
                if(playerColourData == "BLUE")
                {
                    _backgroundPlayerPlanetSprite.setColor(_predefinedColours.LIGHTBLUE);
                    for (int i = 0; i < BACKGROUND_SHIPS/2; ++i)
                    {
                        _starship[i]->SetColour(_predefinedColours.LIGHTBLUE);
                    }
                    _gameSettings->UpdateSettingOptionValueText("Player Colour", 0);
                }
                else if(playerColourData == "RED")
                {
                    _backgroundPlayerPlanetSprite.setColor(_predefinedColours.LIGHTRED);
                    for (int i = 0; i < BACKGROUND_SHIPS/2; ++i)
                    {
                        _starship[i]->SetColour(_predefinedColours.LIGHTRED);
                    }
                    _gameSettings->UpdateSettingOptionValueText("Player Colour", 1);
                }
                else if(playerColourData == "GREEN")
                {
                    _backgroundPlayerPlanetSprite.setColor(_predefinedColours.LIGHTGREEN);
                    for (int i = 0; i < BACKGROUND_SHIPS/2; ++i)
                    {
                        _starship[i]->SetColour(_predefinedColours.LIGHTGREEN);
                    }
                    _gameSettings->UpdateSettingOptionValueText("Player Colour", 2);
                }
                else if(playerColourData == "ORANGE")
                {
                    _backgroundPlayerPlanetSprite.setColor(_predefinedColours.LIGHTORANGE);
                    for (int i = 0; i < BACKGROUND_SHIPS/2; ++i)
                    {
                        _starship[i]->SetColour(_predefinedColours.LIGHTORANGE);
                    }
                    _gameSettings->UpdateSettingOptionValueText("Player Colour", 3);
                }
                else if(playerColourData == "PURPLE")
                {
                    _backgroundPlayerPlanetSprite.setColor(_predefinedColours.BLUEVIOLET);
                    for (int i = 0; i < BACKGROUND_SHIPS/2; ++i)
                    {
                        _starship[i]->SetColour(_predefinedColours.BLUEVIOLET);
                    }
                    _gameSettings->UpdateSettingOptionValueText("Player Colour", 4);
                }
            }
        }
    }

    /*auto path = "Resources/Data/GameSettings.json";
    if(Chilli::JsonSaveSystem::CheckFileExists(path))
    {
        std::cout << "GameSettings file found!" << std::endl;
        auto fileData = Chilli::JsonSaveSystem::LoadFile(path);

        for (int i = 0; i < _gameSettings->GetNumOfSettingOptions(); ++i)
        {
            std::string gameSettingOptionsLabelText = _gameSettings->GetSettingOptions()[i].labelText.getString();

            if(fileData.contains(gameSettingOptionsLabelText))
            {
                std::cout << "[ " + gameSettingOptionsLabelText + "] data found!" << std::endl;

                std::string gameSettingOptionsValueFileData = fileData[gameSettingOptionsLabelText];
                if(gameSettingOptionsValueFileData == "true")
                {
                    _gameSettingsDictionary[gameSettingOptionsLabelText] = true;
                    // TODO: Create a dictionary that maps GameSetting option names to bools i.e. std::map<SettingOption, bool> = { "Music", "_isMusicOn"}
                    _isMusicOn = true;
                }
                else if(gameSettingOptionsValueFileData == "false")
                {
                    _gameSettingsDictionary[gameSettingOptionsLabelText] = false;
                    _isMusicOn = false;
                }
                else
                {
                    std::cout << "Invalid JSON data entry for + " + gameSettingOptionsLabelText + " setting" << std::endl;
                }

                _gameSettings->UpdateSettingOptionValueText(gameSettingOptionsLabelText, gameSettingOptionsValueFileData == "true");
            }
        }
    }*/

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

    /// Observer to game settings event
    auto gameSettingsCallback = std::bind(&MenuScene::SaveGameSettingsData_OnSettingsUpdated, this);
    _gameSettings->AddBasicObserver({GameSettings::EventID::SETTINGS_UPDATED, gameSettingsCallback});

    return true;
}

void MenuScene::SaveGameSettingsData_OnSettingsUpdated()
{
    /// Model the data and save it to file
    json gameSettingsData;
    gameSettingsData["Music"] = _gameSettings->GetSettingOption("Music").selectedValueIndex == 1 ? "true" : "false";
    gameSettingsData["Spacelanes"] = _gameSettings->GetSettingOption("Spacelanes").selectedValueIndex == 1 ? "true" : "false";
    gameSettingsData["Minimap"] = _gameSettings->GetSettingOption("Minimap").selectedValueIndex == 1 ? "true" : "false";

    if(_gameSettings->GetSettingOption("Player Colour").selectedValueIndex == 0)
    {
        gameSettingsData["Player Colour"] = "BLUE";
    }
    else if(_gameSettings->GetSettingOption("Player Colour").selectedValueIndex == 1)
    {
        gameSettingsData["Player Colour"] = "RED";
    }
    else if(_gameSettings->GetSettingOption("Player Colour").selectedValueIndex == 2)
    {
        gameSettingsData["Player Colour"] = "GREEN";
    }
    else if(_gameSettings->GetSettingOption("Player Colour").selectedValueIndex == 3)
    {
        gameSettingsData["Player Colour"] = "ORANGE";
    }
    else if(_gameSettings->GetSettingOption("Player Colour").selectedValueIndex == 4)
    {
        gameSettingsData["Player Colour"] = "PURPLE";
    }

    auto path = "Resources/Data/GameSettings.json";
    Chilli::JsonSaveSystem::SaveFile(path, gameSettingsData);
    std::cout << "Settings saved to " << path << std::endl;

    /// Update the code that is affected by the game settings being changed
    _isMusicOn = _gameSettings->GetSettingOption("Music").selectedValueIndex;
    if(_isMusicOn and _menuMusic.getStatus() not_eq sf::SoundSource::Playing)
    {
        _menuMusic.play();
    }
    else if(not _isMusicOn)
    {
        _menuMusic.stop();
    }

    auto playerColourSetting = _gameSettings->GetSettingOption("Player Colour");
    for (int i = 0; i < playerColourSetting.optionValues.size(); ++i)
    {
        if(playerColourSetting.valueText.getString() == "BLUE")
        {
            _backgroundPlayerPlanetSprite.setColor(_predefinedColours.LIGHTBLUE);
            for (int i = 0; i < BACKGROUND_SHIPS/2; ++i)
            {
                _starship[i]->SetColour(_predefinedColours.LIGHTBLUE);
            }
        }
        else if(playerColourSetting.valueText.getString() == "RED")
        {
            _backgroundPlayerPlanetSprite.setColor(_predefinedColours.LIGHTRED);
            for (int i = 0; i < BACKGROUND_SHIPS/2; ++i)
            {
                _starship[i]->SetColour(_predefinedColours.LIGHTRED);
            }
        }
        else if(playerColourSetting.valueText.getString() == "GREEN")
        {
            _backgroundPlayerPlanetSprite.setColor(_predefinedColours.LIGHTGREEN);
            for (int i = 0; i < BACKGROUND_SHIPS/2; ++i)
            {
                _starship[i]->SetColour(_predefinedColours.LIGHTGREEN);
            }
        }
        else if(playerColourSetting.valueText.getString() == "ORANGE")
        {
            _backgroundPlayerPlanetSprite.setColor(_predefinedColours.LIGHTORANGE);
            for (int i = 0; i < BACKGROUND_SHIPS/2; ++i)
            {
                _starship[i]->SetColour(_predefinedColours.LIGHTORANGE);
            }
        }
        else if(playerColourSetting.valueText.getString() == "PURPLE")
        {
            _backgroundPlayerPlanetSprite.setColor(_predefinedColours.BLUEVIOLET);
            for (int i = 0; i < BACKGROUND_SHIPS/2; ++i)
            {
                _starship[i]->SetColour(_predefinedColours.BLUEVIOLET);
            }
        }
    }
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

        _gameSettings->EventHandler(window, event);

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

            _gameSettings->RepositionPanel(
                    Constants::WINDOW_WIDTH / 2.0F - _gameSettings->GetSettingsPanelSize().x / 2.0F,
                    _menuTitleImgSprite.getPosition().y + _menuTitleImgSprite.getGlobalBounds().height + 25.0F);
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

        _gameSettings->Update(window, deltaTime);

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
        _gameSettings->Render(window);
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
