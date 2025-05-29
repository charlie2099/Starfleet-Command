#include "Scenes/MenuScene.hpp"

MenuScene::~MenuScene()
{
    StopMusic();
}

bool MenuScene::Init()
{
    InitView();
    InitBackground();
    InitButtons();
    InitTitle();
    InitBackgroundStarships();
    InitGameVersionText();
    InitGameSettings();
    InitMusic();
    InitEvents();

    return true;
}

void MenuScene::EventHandler(sf::RenderWindow& window, sf::Event& event)
{
    if(_isGameSettingsEnabled)
    {
        HandleGameSettingsEvents(window, event);
        return;
    }
    HandleButtonEvents(window, event);
}

void MenuScene::Update(sf::RenderWindow& window, sf::Time deltaTime)
{
    _backgroundParallax->Update(window, deltaTime);
    UpdateCursor(window, deltaTime);
    UpdateStarshipAnimations(window, deltaTime);

    if(_isGameSettingsEnabled)
    {
        UpdateGameSettingsButtons(window, deltaTime);
        return;
    }
    UpdateMenuButtons(window);
}

void MenuScene::Render(sf::RenderWindow& window)
{
    window.setView(_menuView);
    RenderBackground(window);
    RenderStarships(window);
    window.draw(_titleSprite);
    RenderGameSettings(window);
    RenderButtons(window);
    window.draw(_gameVersionText);
    _cursor.Render(window);
}

void MenuScene::StopMusic()
{
    if(_menuMusic.getStatus() == sf::Music::Playing)
    {
        _menuMusic.stop();
    }
}

bool MenuScene::InitMusic()
{
    _buttonClickSoundBuffer.loadFromFile("Resources/Audio/click5.ogg");
    _buttonClickSound.setBuffer(_buttonClickSoundBuffer);

    if(!_menuMusic.openFromFile(AUDIO_DIR_PATH + "MenuTheme/United_Against_Evil_175bpm_136s.wav"))
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
        return true;
    }
}

void MenuScene::InitEvents()
{
    /// Observer to game settings updated event
    auto gameSettingsUpdatedCallback = std::bind(&MenuScene::ApplyGameSettings_OnSettingsUpdated, this);
    _gameSettings->AddBasicObserver({GameSettings::SETTINGS_UPDATED, gameSettingsUpdatedCallback});

    /// Observer to game settings saved event
    auto gameSettingsSavedCallback = std::bind(&MenuScene::SaveGameSettingsData_OnSettingsSaved, this);
    _gameSettings->AddBasicObserver({GameSettings::SETTINGS_SAVED, gameSettingsSavedCallback});
}

void MenuScene::InitGameSettings()
{
    _gameSettings = std::make_unique<GameSettings>();
    _gameSettings->AddSettingOption("Fullscreen Mode", std::vector<std::string>{"OFF", "ON"});
    _gameSettings->AddSettingOption("Music", std::vector<std::string>{"OFF", "ON"});
    _gameSettings->AddSettingOption("Director Debug", std::vector<std::string>{"OFF", "ON"});
    _gameSettings->AddSettingOption("Spacelanes", std::vector<std::string>{"OFF", "ON"});
    _gameSettings->AddSettingOption("Minimap", std::vector<std::string>{"OFF", "ON"});
    _gameSettings->AddSettingOption("Player Colour", std::vector<std::string>{"BLUE", "RED", "GREEN", "ORANGE", "YELLOW", "PURPLE", "PINK"});
    _gameSettings->AddSettingOption("Enemy Colour",std::vector<std::string>{"BLUE", "RED", "GREEN", "ORANGE", "YELLOW", "PURPLE", "PINK"});

    if(Chilli::JsonSaveSystem::CheckFileExists(SETTINGS_FILE_PATH))
    {
        auto gameSettingsData = Chilli::JsonSaveSystem::LoadFile(SETTINGS_FILE_PATH);

        if(gameSettingsData.contains("Fullscreen Mode"))
        {
            std::string fullscreenModeData = gameSettingsData["Fullscreen Mode"];
            _gameSettings->SetSettingOptionValueText("Fullscreen Mode", fullscreenModeData == "true");
        }

        if(gameSettingsData.contains("Music"))
        {
            std::string musicData = gameSettingsData["Music"];
            _isMusicOn = (musicData == "true");
            _gameSettings->SetSettingOptionValueText("Music", musicData == "true");
        }

        if(gameSettingsData.contains("Director Debug"))
        {
            std::string directorDebugData = gameSettingsData["Director Debug"];
            _gameSettings->SetSettingOptionValueText("Director Debug", directorDebugData == "true");
        }

        if(gameSettingsData.contains("Spacelanes"))
        {
            std::string spacelanesData = gameSettingsData["Spacelanes"];
            _gameSettings->SetSettingOptionValueText("Spacelanes", spacelanesData == "true");
        }

        if(gameSettingsData.contains("Minimap"))
        {
            std::string minimapData = gameSettingsData["Minimap"];
            _gameSettings->SetSettingOptionValueText("Minimap", minimapData == "true");
        }

        if(gameSettingsData.contains("Player Colour"))
        {
            ApplyTeamColourSettings(gameSettingsData, "Player Colour");
            _backgroundPlayerPlanetSprite.setTexture(_backgroundPlanetTextures[_gameSettings->GetSettingOptionCurrentValueIndex("Player Colour")]);
            _player->SetTeamColour(Chilli::JsonColourMapping::GetColourFromStringName(gameSettingsData["Player Colour"]));
        }

        if(gameSettingsData.contains("Enemy Colour"))
        {
            ApplyTeamColourSettings(gameSettingsData, "Enemy Colour");
            _backgroundEnemyPlanetSprite.setTexture(_backgroundPlanetTextures[_gameSettings->GetSettingOptionCurrentValueIndex("Enemy Colour")]);
            _enemy->SetTeamColour(Chilli::JsonColourMapping::GetColourFromStringName(gameSettingsData["Enemy Colour"]));
        }
    }
}

void MenuScene::InitView()
{
    sf::Vector2f VIEW_SIZE = { Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT };
    sf::Vector2f VIEW_CENTER = {Constants::WINDOW_WIDTH / 2.0F, Constants::WINDOW_HEIGHT / 2.0F };
    _menuView.setSize(VIEW_SIZE);
    _menuView.setCenter(VIEW_CENTER);
}

bool MenuScene::InitBackground()
{
    _backgroundParallax = std::make_unique<ParallaxBackground>(
            TEXTURES_DIR_PATH + "space_nebula_2.png",
            sf::Color::Cyan,
            Constants::WINDOW_WIDTH,
            Constants::WINDOW_HEIGHT,
            300,
            Chilli::Colour::LIGHTBLUE);

    _backgroundPlanetTextures[0].loadFromFile(TEXTURES_DIR_PATH + "planet_blue.png");
    _backgroundPlanetTextures[1].loadFromFile(TEXTURES_DIR_PATH + "planet_red.png");
    _backgroundPlanetTextures[2].loadFromFile(TEXTURES_DIR_PATH + "planet_green.png");
    _backgroundPlanetTextures[3].loadFromFile(TEXTURES_DIR_PATH + "planet_orange.png");
    _backgroundPlanetTextures[4].loadFromFile(TEXTURES_DIR_PATH + "planet_yellow.png");
    _backgroundPlanetTextures[5].loadFromFile(TEXTURES_DIR_PATH + "planet_blue.png");
    _backgroundPlanetTextures[6].loadFromFile(TEXTURES_DIR_PATH + "planet_red.png");

    _backgroundEnemyPlanetSprite.setTexture(_backgroundPlanetTextures[2]);
    _backgroundEnemyPlanetSprite.setPosition(Constants::WINDOW_WIDTH / 1.6F, Constants::WINDOW_HEIGHT / 2.5F);

    _backgroundPlayerPlanetSprite.setTexture(_backgroundPlanetTextures[0]);
    _backgroundPlayerPlanetSprite.setScale(0.25F, 0.25F);
    _backgroundPlayerPlanetSprite.setPosition(50.0F, 50.0F);

    return true;
}

void MenuScene::InitButtons()
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
        _menuButtons[i].SetText(button_text[i]);
        _menuButtons[i].SetTextSize(14);
        _menuButtons[i].SetSize(20, 15);
        _menuButtons[i].SetPanelColour(sf::Color(22, 155, 164, 100));
        _menuButtons[i].SetPosition(Constants::WINDOW_WIDTH * 0.185F, (Constants::WINDOW_HEIGHT * 0.57F) + static_cast<float>((i * (_menuButtons[i].GetPanelSize().height + 10))));
    }
}

bool MenuScene::InitTitle()
{
    if (!_menuTitleImgTexture.loadFromFile(TEXTURES_DIR_PATH + "/StarfleetCommandNewLogo3.png"))
    {
        return false;
    }
    _menuTitleImgTexture.setSmooth(true);
    _titleSprite.setTexture(_menuTitleImgTexture);
    _titleSprite.setScale(0.15F, 0.15F);
    _titleSprite.setPosition(Constants::WINDOW_WIDTH / 2.0F - _titleSprite.getGlobalBounds().width / 2.0F, Constants::WINDOW_HEIGHT * 0.3F - _titleSprite.getGlobalBounds().height / 2.0F);

    return true;
}

void MenuScene::InitBackgroundStarships()
{
    RNG starshipXPosRNG {0,static_cast<int>(Constants::WINDOW_WIDTH)};
    RNG starshipYPosRNG {45, 675};
    RNG starshipTypeRNG {0,4};

    _player = std::make_unique<Player>(0, Chilli::Colour::LIGHTBLUE);
    _enemy = std::make_unique<Enemy>(0, Chilli::Colour::LIGHTGREEN);

    for (int i = 0; i < NUM_OF_SHIPS_PER_TEAM; ++i)
    {
        int rand_x = starshipXPosRNG.GenerateNumber();
        int rand_y = starshipYPosRNG.GenerateNumber();
        int rand_ship = starshipTypeRNG.GenerateNumber();
        _player->CreateStarship(static_cast<StarshipFactory::STARSHIP_TYPE>(rand_ship), 0);
        _player->SetStarshipPosition(_player->GetStarships().back(), {static_cast<float>(rand_x), static_cast<float>(rand_y)});
    }

    for (int i = 0; i < NUM_OF_SHIPS_PER_TEAM; ++i)
    {
        int rand_x = starshipXPosRNG.GenerateNumber();
        int rand_y = starshipYPosRNG.GenerateNumber();
        int rand_ship = starshipTypeRNG.GenerateNumber();
        _enemy->CreateStarship(static_cast<StarshipFactory::STARSHIP_TYPE>(rand_ship), 0);
        _enemy->SetStarshipPosition(_enemy->GetStarships().back(), {static_cast<float>(rand_x), static_cast<float>(rand_y)});
        _enemy->SetStarshipRotation(_enemy->GetStarships().back(), 180);
    }
}

void MenuScene::InitGameVersionText()
{
    _gameVersionText.setFont(Chilli::CustomFonts::GetBoldFont());
    _gameVersionText.setString(GAME_VERSION); // Early Alpha = v0.5.0, Early Beta = v0.8.0, Release = v1.0.0
    _gameVersionText.setCharacterSize(14);
    _gameVersionText.setFillColor(Chilli::Colour::LIGHTBLUE);
    _gameVersionText.setOutlineColor(sf::Color::Black);
    //_gameVersionText.setPosition(Constants::WINDOW_WIDTH - (_gameVersionText.getGlobalBounds().width + 20.0F), Constants::WINDOW_HEIGHT - (_gameVersionText.getGlobalBounds().height + 20.0F));
    _gameVersionText.setPosition(20.0F, Constants::WINDOW_HEIGHT - (_gameVersionText.getGlobalBounds().height + 20.0F));
    //_gameVersionText.setPosition(_titleSprite.getPosition().x + _titleSprite.getGlobalBounds().width/2.0F - _gameVersionText.getGlobalBounds().width/2.0F, _titleSprite.getPosition().y + _titleSprite.getGlobalBounds().height + 10.0F);
}

void MenuScene::HandleGameSettingsEvents(sf::RenderWindow &window, sf::Event &event)
{
    _menuButtons[BACK_BUTTON].EventHandler(window, event);
    if (event.type == sf::Event::MouseButtonPressed and event.mouseButton.button == sf::Mouse::Left)
    {
        if(_menuButtons[BACK_BUTTON].IsClicked())
        {
            _isGameSettingsEnabled = false;
            _titleSprite.setPosition(Constants::WINDOW_WIDTH / 2.0F - _titleSprite.getGlobalBounds().width / 2.0F, Constants::WINDOW_HEIGHT * 0.3F - _titleSprite.getGlobalBounds().height / 2.0F);
            _buttonClickSound.play();
        }
    }

    _gameSettings->EventHandler(window, event);
}

void MenuScene::HandleButtonEvents(sf::RenderWindow &window, sf::Event &event)
{
    for (int i = 0; i < NUM_OF_BUTTONS - 1; ++i)
    {
        _menuButtons[i].EventHandler(window, event);
    }

    if (event.type == sf::Event::MouseButtonPressed and event.mouseButton.button == sf::Mouse::Left)
    {
        if(_menuButtons[PLAY_BUTTON].IsClicked())
        {
            SetScene(ID::GAME);
        }
        else if(_menuButtons[OPTIONS_BUTTON].IsClicked())
        {
            _buttonClickSound.play();
            _isGameSettingsEnabled = true;
            _titleSprite.setPosition(Constants::WINDOW_WIDTH / 2.0F - _titleSprite.getGlobalBounds().width / 2.0F, Constants::WINDOW_HEIGHT * 0.2F - _titleSprite.getGlobalBounds().height / 2.0F);
            _gameSettings->RepositionPanel(Constants::WINDOW_WIDTH / 2.0F - _gameSettings->GetSettingsPanelSize().x / 2.0F, _titleSprite.getPosition().y + _titleSprite.getGlobalBounds().height + 25.0F);
        }
        else if(_menuButtons[EXIT_BUTTON].IsClicked())
        {
            window.close();
        }
    }
}

void MenuScene::UpdateCursor(sf::RenderWindow &window, sf::Time &deltaTime)
{
    _cursor.Update(window, deltaTime);
    _cursor.SetCursorPos(window, _menuView);
}

void MenuScene::UpdateStarshipAnimations(sf::RenderWindow &window, sf::Time &deltaTime)
{
    for (int i = 0; i < NUM_OF_SHIPS_PER_TEAM; ++i)
    {
        _player->Update(window, deltaTime);
        _enemy->Update(window, deltaTime);

        sf::Vector2f playerMovement(_player->GetStarships()[i]->GetSpeed() * 2 * deltaTime.asSeconds(), 0.0f);
        _player->MoveStarship(i, playerMovement);

        sf::Vector2f enemyMovement((_enemy->GetStarships()[i]->GetSpeed() * 2 * deltaTime.asSeconds()) * -1, 0.0f);
        _enemy->MoveStarship(i, enemyMovement);

        if(_player->GetStarships()[i]->GetPos().x >= Constants::WINDOW_WIDTH)
        {
            _player->GetStarships()[i]->SetPosition({0, _player->GetStarships()[i]->GetPos().y});
        }
        else if(_player->GetStarships()[i]->GetPos().x <= 0)
        {
            _player->GetStarships()[i]->SetPosition({Constants::WINDOW_WIDTH, _player->GetStarships()[i]->GetPos().y});
        }

        if(_enemy->GetStarships()[i]->GetPos().x >= Constants::WINDOW_WIDTH)
        {
            _enemy->GetStarships()[i]->SetPosition({0, _enemy->GetStarships()[i]->GetPos().y});
        }
        else if(_enemy->GetStarships()[i]->GetPos().x <= 0)
        {
            _enemy->GetStarships()[i]->SetPosition({Constants::WINDOW_WIDTH, _enemy->GetStarships()[i]->GetPos().y});
        }
    }
}

void MenuScene::UpdateGameSettingsButtons(sf::RenderWindow &window, sf::Time &deltaTime)
{
    _menuButtons[BACK_BUTTON].Update(window);

    if(_menuButtons[BACK_BUTTON].IsMouseOver())
    {
        _menuButtons[BACK_BUTTON].SetPanelColour(sf::Color(22, 155, 164, 65));
        _menuButtons[BACK_BUTTON].SetText(_menuButtons[BACK_BUTTON].GetText().getString(), sf::Color::Cyan);
        _cursor.SetCursorType(Chilli::Cursor::HOVER);
    }
    else if(not _menuButtons[BACK_BUTTON].IsMouseOver())
    {
        _menuButtons[BACK_BUTTON].SetPanelColour(sf::Color(22, 155, 164, 100));
        _menuButtons[BACK_BUTTON].SetText(_menuButtons[BACK_BUTTON].GetText().getString(), Chilli::Colour::LIGHTBLUE);
        _cursor.SetCursorType(Chilli::Cursor::DEFAULT);
    }

    _gameSettings->Update(window, deltaTime);
}

void MenuScene::UpdateMenuButtons(sf::RenderWindow &window)
{
    for (int i = 0; i < NUM_OF_BUTTONS-1; ++i)
    {
        _menuButtons[i].Update(window);

        if(not _menuButtons[i].IsMouseOver())
        {
            _menuButtons[i].SetPanelColour(sf::Color(22, 155, 164, 100));
            _menuButtons[i].SetText(_menuButtons[i].GetText().getString(), Chilli::Colour::LIGHTBLUE);
        }
    }

    if(_menuButtons[PLAY_BUTTON].IsMouseOver())
    {
        _menuButtons[PLAY_BUTTON].SetPanelColour(sf::Color(22, 155, 164, 65));
        _menuButtons[PLAY_BUTTON].SetText(_menuButtons[PLAY_BUTTON].GetText().getString(), sf::Color::Cyan);
        _cursor.SetCursorType(Chilli::Cursor::HOVER);
    }
    else if(_menuButtons[OPTIONS_BUTTON].IsMouseOver())
    {
        _menuButtons[OPTIONS_BUTTON].SetPanelColour(sf::Color(22, 155, 164, 65));
        _menuButtons[OPTIONS_BUTTON].SetText(_menuButtons[OPTIONS_BUTTON].GetText().getString(), sf::Color::Cyan);
        _cursor.SetCursorType(Chilli::Cursor::HOVER);
    }
    else if(_menuButtons[EXIT_BUTTON].IsMouseOver())
    {
        _menuButtons[EXIT_BUTTON].SetPanelColour(sf::Color(242, 22, 22, 60));
        _menuButtons[EXIT_BUTTON].SetText(_menuButtons[EXIT_BUTTON].GetText().getString(), sf::Color::Red);
        _cursor.SetCursorType(Chilli::Cursor::HOVER);
    }
    else
    {
        _cursor.SetCursorType(Chilli::Cursor::DEFAULT);
    }
}

void MenuScene::RenderButtons(sf::RenderWindow &window)
{
    if(_isGameSettingsEnabled)
    {
        _menuButtons[BACK_BUTTON].Render(window);
    }
    else
    {
        for (int i = 0; i < _menuButtons.size() - 1; ++i)
        {
            _menuButtons[i].Render(window);
        }
    }
}

void MenuScene::RenderGameSettings(sf::RenderWindow &window)
{
    if(_isGameSettingsEnabled)
    {
        _gameSettings->Render(window);
    }
}

void MenuScene::RenderStarships(sf::RenderWindow &window)
{
    for (int i = 0; i < NUM_OF_SHIPS_PER_TEAM; ++i)
    {
        _player->RenderMinimapSprites(window);
        _enemy->RenderMinimapSprites(window);
    }
}

void MenuScene::RenderBackground(sf::RenderWindow &window)
{
    _backgroundParallax->RenderBackground(window);
    window.draw(_backgroundEnemyPlanetSprite);
    window.draw(_backgroundPlayerPlanetSprite);
    _backgroundParallax->RenderStars(window);
}

void MenuScene::ApplyGameSettings_OnSettingsUpdated()
{
    _isMusicOn = _gameSettings->GetSettingOptionCurrentValueIndex("Music");
    if(_isMusicOn and _menuMusic.getStatus() not_eq sf::SoundSource::Playing)
    {
        _menuMusic.play();
    }
    else if(not _isMusicOn)
    {
        _menuMusic.stop();
    }

    auto playerColourSetting = _gameSettings->GetSettingOption("Player Colour");
    _backgroundPlayerPlanetSprite.setTexture(_backgroundPlanetTextures[playerColourSetting.selectedOptionIndex]);
    _player->SetTeamColour(Chilli::JsonColourMapping::GetColourFromStringName(playerColourSetting.currentValueText.getString()));
    _gameSettings->SetSettingOptionValueColour("Player Colour", Chilli::JsonColourMapping::GetColourFromStringName(playerColourSetting.currentValueText.getString()));

    auto enemyColourSetting = _gameSettings->GetSettingOption("Enemy Colour");
    _backgroundEnemyPlanetSprite.setTexture(_backgroundPlanetTextures[enemyColourSetting.selectedOptionIndex]);
    _enemy->SetTeamColour(Chilli::JsonColourMapping::GetColourFromStringName(enemyColourSetting.currentValueText.getString()));
    _gameSettings->SetSettingOptionValueColour("Enemy Colour", Chilli::JsonColourMapping::GetColourFromStringName(enemyColourSetting.currentValueText.getString()));
}

void MenuScene::SaveGameSettingsData_OnSettingsSaved()
{
    /// Model the data and write it to file
    json gameSettingsData;
    gameSettingsData["Fullscreen Mode"] = _gameSettings->GetSettingOptionCurrentValueIndex("Fullscreen Mode") == 1 ? "true" : "false";
    gameSettingsData["Music"] = _gameSettings->GetSettingOptionCurrentValueIndex("Music") == 1 ? "true" : "false";
    gameSettingsData["Director Debug"] = _gameSettings->GetSettingOptionCurrentValueIndex("Director Debug") == 1 ? "true" : "false";
    gameSettingsData["Spacelanes"] = _gameSettings->GetSettingOptionCurrentValueIndex("Spacelanes") == 1 ? "true" : "false";
    gameSettingsData["Minimap"] = _gameSettings->GetSettingOptionCurrentValueIndex("Minimap") == 1 ? "true" : "false";
    gameSettingsData["Player Colour"] = _gameSettings->GetSettingOptionCurrentValue("Player Colour");
    gameSettingsData["Enemy Colour"] =_gameSettings->GetSettingOptionCurrentValue("Enemy Colour");

    Chilli::JsonSaveSystem::SaveFile(SETTINGS_FILE_PATH, gameSettingsData);
    std::cout << "Settings saved to " << SETTINGS_FILE_PATH << std::endl;
}

void MenuScene::ApplyTeamColourSettings(const json &gameSettingsData, const std::string& teamColourSettingName)
{
    std::string teamColourSettings = gameSettingsData[teamColourSettingName];
    auto teamColourSettingOptionValues = _gameSettings->GetSettingOption(teamColourSettingName).availableValues;

    for (int i = 0; i < teamColourSettingOptionValues.size(); ++i)
    {
        if (teamColourSettings == teamColourSettingOptionValues[i])
        {
            _gameSettings->GetSettingOption(teamColourSettingName).selectedOptionIndex = i;
            break;
        }
    }

    _gameSettings->SetSettingOptionValueText(teamColourSettingName, _gameSettings->GetSettingOptionCurrentValueIndex(teamColourSettingName));
    _gameSettings->SetSettingOptionValueColour(teamColourSettingName, Chilli::JsonColourMapping::GetColourFromStringName(teamColourSettings));
}
