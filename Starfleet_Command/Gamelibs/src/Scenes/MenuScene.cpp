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
    _cursor.Update(window, deltaTime);
    _cursor.SetCursorPos(window, _menuView);
    _backgroundParallax->Update(window, deltaTime);
    UpdateBackgroundStarshipsMovement(window, deltaTime);

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
    _backgroundParallax->RenderBackground(window);
    window.draw(_backgroundEnemyPlanetSprite);
    window.draw(_backgroundPlayerPlanetSprite);
    _backgroundParallax->RenderStars(window);
    for (int i = 0; i < NUM_OF_SHIPS_PER_TEAM; ++i)
    {
        _player->RenderMinimapSprites(window);
        _enemy->RenderMinimapSprites(window);
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

bool MenuScene::InitMusic()
{
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
    _gameSettings->AddSettingOption("Spacelanes", std::vector<std::string>{"OFF", "ON"});
    _gameSettings->AddSettingOption("Minimap", std::vector<std::string>{"OFF", "ON"});
    _gameSettings->AddSettingOption("Player Colour", std::vector<std::string>{"BLUE", "RED", "GREEN", "ORANGE", "YELLOW"});
    _gameSettings->AddSettingOption("Enemy Colour",std::vector<std::string>{"BLUE", "RED", "GREEN", "ORANGE", "YELLOW"});
    //_gameSettings->AddSettingOption("Difficulty", std::vector<std::string>{"EASY", "MEDIUM", "HARD"});

    if(Chilli::JsonSaveSystem::CheckFileExists(SETTINGS_FILE_PATH))
    {
        auto gameSettingsData = Chilli::JsonSaveSystem::LoadFile(SETTINGS_FILE_PATH);

        if(gameSettingsData.contains("Fullscreen Mode"))
        {
            std::string fullscreenModeData = gameSettingsData["Fullscreen Mode"];
            _gameSettings->UpdateSettingOptionValueText("Fullscreen Mode", fullscreenModeData == "true");
        }

        if(gameSettingsData.contains("Music"))
        {
            std::string musicData = gameSettingsData["Music"];
            _isMusicOn = (musicData == "true");
            _gameSettings->UpdateSettingOptionValueText("Music", musicData == "true");
        }

        if(gameSettingsData.contains("Spacelanes"))
        {
            std::string spacelanesData = gameSettingsData["Spacelanes"];
            _gameSettings->UpdateSettingOptionValueText("Spacelanes", spacelanesData == "true");
        }

        if(gameSettingsData.contains("Minimap"))
        {
            std::string minimapData = gameSettingsData["Minimap"];
            _gameSettings->UpdateSettingOptionValueText("Minimap", minimapData == "true");
        }

        if(gameSettingsData.contains("Player Colour"))
        {
            std::string playerColourData = gameSettingsData["Player Colour"];

            if(playerColourData == "BLUE")
            {
                _backgroundPlayerPlanetSprite.setTexture(_backgroundPlanetTextures[0]);
                _player->SetTeamColour(Chilli::Colour::LIGHTBLUE);
                _gameSettings->UpdateSettingOptionValueText("Player Colour", 0);
            }
            else if(playerColourData == "RED")
            {
                _backgroundPlayerPlanetSprite.setTexture(_backgroundPlanetTextures[1]);
                _player->SetTeamColour(Chilli::Colour::LIGHTRED);
                _gameSettings->UpdateSettingOptionValueText("Player Colour", 1);
            }
            else if(playerColourData == "GREEN")
            {
                _backgroundPlayerPlanetSprite.setTexture(_backgroundPlanetTextures[2]);
                _player->SetTeamColour(Chilli::Colour::LIGHTGREEN);
                _gameSettings->UpdateSettingOptionValueText("Player Colour", 2);
            }
            else if(playerColourData == "ORANGE")
            {
                _backgroundPlayerPlanetSprite.setTexture(_backgroundPlanetTextures[3]);
                _player->SetTeamColour(Chilli::Colour::LIGHTORANGE);
                _gameSettings->UpdateSettingOptionValueText("Player Colour", 3);
            }
            else if(playerColourData == "YELLOW")
            {
                _backgroundPlayerPlanetSprite.setTexture(_backgroundPlanetTextures[4]);
                _player->SetTeamColour(Chilli::Colour::YELLOW);
                _gameSettings->UpdateSettingOptionValueText("Player Colour", 4);
            }
        }

        if(gameSettingsData.contains("Enemy Colour"))
        {
            std::string enemyColourData = gameSettingsData["Enemy Colour"];

            if(enemyColourData == "BLUE")
            {
                //_backgroundSprite.setColor(Chilli::Colour::LIGHTBLUE);
                _backgroundEnemyPlanetSprite.setTexture(_backgroundPlanetTextures[0]);
                _enemy->SetTeamColour(Chilli::Colour::LIGHTBLUE);
                _gameSettings->UpdateSettingOptionValueText("Enemy Colour", 0);
            }
            else if(enemyColourData == "RED")
            {
                //_backgroundSprite.setColor(Chilli::Colour::LIGHTRED);
                _backgroundEnemyPlanetSprite.setTexture(_backgroundPlanetTextures[1]);
                _enemy->SetTeamColour(Chilli::Colour::LIGHTRED);
                _gameSettings->UpdateSettingOptionValueText("Enemy Colour", 1);
            }
            else if(enemyColourData == "GREEN")
            {
                //_backgroundSprite.setColor(Chilli::Colour::LIGHTGREEN);
                _backgroundEnemyPlanetSprite.setTexture(_backgroundPlanetTextures[2]);
                _enemy->SetTeamColour(Chilli::Colour::LIGHTGREEN);
                _gameSettings->UpdateSettingOptionValueText("Enemy Colour", 2);
            }
            else if(enemyColourData == "ORANGE")
            {
                //_backgroundSprite.setColor(Chilli::Colour::LIGHTORANGE);
                _backgroundEnemyPlanetSprite.setTexture(_backgroundPlanetTextures[3]);
                _enemy->SetTeamColour(Chilli::Colour::LIGHTORANGE);
                _gameSettings->UpdateSettingOptionValueText("Enemy Colour", 3);
            }
            else if(enemyColourData == "YELLOW")
            {
                //_backgroundSprite.setColor(Chilli::Colour::YELLOW);
                _backgroundEnemyPlanetSprite.setTexture(_backgroundPlanetTextures[4]);
                _enemy->SetTeamColour(Chilli::Colour::YELLOW);
                _gameSettings->UpdateSettingOptionValueText("Enemy Colour", 4);
            }
        }
    }
}

void MenuScene::InitView()
{
    sf::Vector2f VIEW_SIZE = { Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT };
    sf::Vector2f WORLD_PERSPECTIVE = { Constants::WINDOW_WIDTH/2.0F, Constants::WINDOW_HEIGHT/2.0F };
    _menuView.setSize(VIEW_SIZE);
    _menuView.setCenter(WORLD_PERSPECTIVE);
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
        _buttonPanels[i].SetFont(Panel::TextFont::BOLD);
        _buttonPanels[i].SetText(button_text[i]);
        _buttonPanels[i].SetTextSize(14);
        _buttonPanels[i].SetSize(20, 15);
        _buttonPanels[i].SetPanelColour(sf::Color(22, 155, 164, 100));
        _buttonPanels[i].SetPosition(Constants::WINDOW_WIDTH * 0.185F,(Constants::WINDOW_HEIGHT * 0.57F) + static_cast<float>((i * (_buttonPanels[i].GetPanelSize().height + 10))));
    }
}

bool MenuScene::InitTitle()
{
    if (!_menuTitleImgTexture.loadFromFile(TEXTURES_DIR_PATH + "/StarfleetCommandNewLogo3.png"))
    {
        return false;
    }
    _menuTitleImgTexture.setSmooth(true);
    _menuTitleImgSprite.setTexture(_menuTitleImgTexture);
    _menuTitleImgSprite.setScale(0.15F, 0.15F);
    _menuTitleImgSprite.setPosition(Constants::WINDOW_WIDTH/2.0F - _menuTitleImgSprite.getGlobalBounds().width/2.0F, Constants::WINDOW_HEIGHT * 0.3F - _menuTitleImgSprite.getGlobalBounds().height/2.0F);

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
        _player->SetStarshipPosition(_player->GetStarships().back() , {static_cast<float>(rand_x), static_cast<float>(rand_y)});
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
    //_gameVersionText.setPosition(_menuTitleImgSprite.getPosition().x + _menuTitleImgSprite.getGlobalBounds().width/2.0F - _gameVersionText.getGlobalBounds().width/2.0F, _menuTitleImgSprite.getPosition().y + _menuTitleImgSprite.getGlobalBounds().height + 10.0F);
}

void MenuScene::HandleGameSettingsEvents(sf::RenderWindow &window, sf::Event &event)
{
    _buttonPanels[BACK_BUTTON].EventHandler(window, event);
    if (event.type == sf::Event::MouseButtonPressed and event.mouseButton.button == sf::Mouse::Left)
    {
        if(_buttonPanels[BACK_BUTTON].IsClicked())
        {
            _isGameSettingsEnabled = false;
            _menuTitleImgSprite.setPosition(Constants::WINDOW_WIDTH / 2.0F - _menuTitleImgSprite.getGlobalBounds().width / 2.0F, Constants::WINDOW_HEIGHT * 0.3F - _menuTitleImgSprite.getGlobalBounds().height / 2.0F);
        }
    }

    _gameSettings->EventHandler(window, event);
}

void MenuScene::HandleButtonEvents(sf::RenderWindow &window, sf::Event &event)
{
    for (int i = 0; i < NUM_OF_BUTTONS - 1; ++i)
    {
        _buttonPanels[i].EventHandler(window, event);
    }

    if (event.type == sf::Event::MouseButtonPressed and event.mouseButton.button == sf::Mouse::Left)
    {
        if(_buttonPanels[PLAY_BUTTON].IsClicked())
        {
            SetScene(ID::GAME);
        }
        else if(_buttonPanels[OPTIONS_BUTTON].IsClicked())
        {
            _isGameSettingsEnabled = true;
            _menuTitleImgSprite.setPosition(Constants::WINDOW_WIDTH / 2.0F - _menuTitleImgSprite.getGlobalBounds().width / 2.0F, Constants::WINDOW_HEIGHT * 0.2F - _menuTitleImgSprite.getGlobalBounds().height / 2.0F);
            _gameSettings->RepositionPanel(Constants::WINDOW_WIDTH / 2.0F - _gameSettings->GetSettingsPanelSize().x / 2.0F, _menuTitleImgSprite.getPosition().y + _menuTitleImgSprite.getGlobalBounds().height + 25.0F);
        }
        else if(_buttonPanels[EXIT_BUTTON].IsClicked())
        {
            window.close();
        }
    }
}

void MenuScene::UpdateBackgroundStarshipsMovement(sf::RenderWindow &window, sf::Time &deltaTime)
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
    _buttonPanels[BACK_BUTTON].Update(window);

    if(_buttonPanels[BACK_BUTTON].IsHoveredOver())
    {
        _buttonPanels[BACK_BUTTON].SetPanelColour(sf::Color(22, 155, 164, 65));
        _buttonPanels[BACK_BUTTON].SetText(_buttonPanels[BACK_BUTTON].GetText().getString(), sf::Color::Cyan);
        _cursor.SetCursorType(Chilli::Cursor::HOVER);
    }
    else if(not _buttonPanels[BACK_BUTTON].IsHoveredOver())
    {
        _buttonPanels[BACK_BUTTON].SetPanelColour(sf::Color(22, 155, 164, 100));
        _buttonPanels[BACK_BUTTON].SetText(_buttonPanels[BACK_BUTTON].GetText().getString(), Chilli::Colour::LIGHTBLUE);
        _cursor.SetCursorType(Chilli::Cursor::DEFAULT);
    }

    _gameSettings->Update(window, deltaTime);
}

void MenuScene::UpdateMenuButtons(sf::RenderWindow &window)
{
    for (int i = 0; i < NUM_OF_BUTTONS - 1; ++i)
    {
        _buttonPanels[i].Update(window);
    }

    if(_buttonPanels[PLAY_BUTTON].IsHoveredOver())
    {
        _buttonPanels[PLAY_BUTTON].SetPanelColour(sf::Color(22, 155, 164, 65));
        _buttonPanels[PLAY_BUTTON].SetText(_buttonPanels[PLAY_BUTTON].GetText().getString(), sf::Color::Cyan);
        _cursor.SetCursorType(Chilli::Cursor::HOVER);
    }
    else if(_buttonPanels[OPTIONS_BUTTON].IsHoveredOver())
    {
        _buttonPanels[OPTIONS_BUTTON].SetPanelColour(sf::Color(22, 155, 164, 65));
        _buttonPanels[OPTIONS_BUTTON].SetText(_buttonPanels[OPTIONS_BUTTON].GetText().getString(), sf::Color::Cyan);
        _cursor.SetCursorType(Chilli::Cursor::HOVER);
    }
    else if(_buttonPanels[EXIT_BUTTON].IsHoveredOver())
    {
        _buttonPanels[EXIT_BUTTON].SetPanelColour(sf::Color(242, 22, 22, 60));
        _buttonPanels[EXIT_BUTTON].SetText(_buttonPanels[EXIT_BUTTON].GetText().getString(), sf::Color::Red);
        _cursor.SetCursorType(Chilli::Cursor::HOVER);
    }
    else
    {
        _cursor.SetCursorType(Chilli::Cursor::DEFAULT);
    }

    for (int i = 0; i < NUM_OF_BUTTONS-1; ++i)
    {
        if(not _buttonPanels[i].IsHoveredOver())
        {
            _buttonPanels[i].SetPanelColour(sf::Color(22, 155, 164, 100));
            _buttonPanels[i].SetText(_buttonPanels[i].GetText().getString(), Chilli::Colour::LIGHTBLUE);
        }
    }
}

void MenuScene::ApplyGameSettings_OnSettingsUpdated()
{
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
            _backgroundPlayerPlanetSprite.setTexture(_backgroundPlanetTextures[0]);
            _player->SetTeamColour(Chilli::Colour::LIGHTBLUE);
        }
        else if(playerColourSetting.valueText.getString() == "RED")
        {
            _backgroundPlayerPlanetSprite.setTexture(_backgroundPlanetTextures[1]);
            _player->SetTeamColour(Chilli::Colour::LIGHTRED);
        }
        else if(playerColourSetting.valueText.getString() == "GREEN")
        {
            _backgroundPlayerPlanetSprite.setTexture(_backgroundPlanetTextures[2]);
            _player->SetTeamColour(Chilli::Colour::LIGHTGREEN);
        }
        else if(playerColourSetting.valueText.getString() == "ORANGE")
        {
            _backgroundPlayerPlanetSprite.setTexture(_backgroundPlanetTextures[3]);
            _player->SetTeamColour(Chilli::Colour::LIGHTORANGE);
        }
        else if(playerColourSetting.valueText.getString() == "YELLOW")
        {
            _backgroundPlayerPlanetSprite.setTexture(_backgroundPlanetTextures[4]);
            _player->SetTeamColour(Chilli::Colour::YELLOW);
        }
    }

    auto enemyColourSetting = _gameSettings->GetSettingOption("Enemy Colour");
    for (int i = 0; i < enemyColourSetting.optionValues.size(); ++i)
    {
        if(enemyColourSetting.valueText.getString() == "BLUE")
        {
            //_backgroundSprite.setColor(Chilli::Colour::LIGHTBLUE);
            _backgroundEnemyPlanetSprite.setTexture(_backgroundPlanetTextures[0]);
            _enemy->SetTeamColour(Chilli::Colour::LIGHTBLUE);
        }
        else if(enemyColourSetting.valueText.getString() == "RED")
        {
            //_backgroundSprite.setColor(Chilli::Colour::LIGHTRED);
            _backgroundEnemyPlanetSprite.setTexture(_backgroundPlanetTextures[1]);
            _enemy->SetTeamColour(Chilli::Colour::LIGHTRED);
        }
        else if(enemyColourSetting.valueText.getString() == "GREEN")
        {
            //_backgroundSprite.setColor(Chilli::Colour::LIGHTGREEN);
            _backgroundEnemyPlanetSprite.setTexture(_backgroundPlanetTextures[2]);
            _enemy->SetTeamColour(Chilli::Colour::LIGHTGREEN);
        }
        else if(enemyColourSetting.valueText.getString() == "ORANGE")
        {
            /*for (int j = 0; j < _parallaxStars.size(); ++j)
            {
                _parallaxStars[j].circleShape.setFillColor(Chilli::Colour::ORANGE);
            }*/
            //_backgroundSprite.setColor(Chilli::Colour::LIGHTORANGE);
            _backgroundEnemyPlanetSprite.setTexture(_backgroundPlanetTextures[3]);
            _enemy->SetTeamColour(Chilli::Colour::LIGHTORANGE);
        }
        else if(enemyColourSetting.valueText.getString() == "YELLOW")
        {
            //_backgroundSprite.setColor(Chilli::Colour::YELLOW);
            _backgroundEnemyPlanetSprite.setTexture(_backgroundPlanetTextures[4]);
            _enemy->SetTeamColour(Chilli::Colour::YELLOW);
        }
    }
}

void MenuScene::SaveGameSettingsData_OnSettingsSaved()
{
    /// Model the data and write it to file
    json gameSettingsData;
    gameSettingsData["Fullscreen Mode"] = _gameSettings->GetSettingOption("Fullscreen Mode").selectedValueIndex == 1 ? "true" : "false";
    gameSettingsData["Music"] = _gameSettings->GetSettingOption("Music").selectedValueIndex == 1 ? "true" : "false";
    gameSettingsData["Spacelanes"] = _gameSettings->GetSettingOption("Spacelanes").selectedValueIndex == 1 ? "true" : "false";
    gameSettingsData["Minimap"] = _gameSettings->GetSettingOption("Minimap").selectedValueIndex == 1 ? "true" : "false";

    /// Player Colour
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
        gameSettingsData["Player Colour"] = "YELLOW";
    }

    /// Enemy Colour
    if(_gameSettings->GetSettingOption("Enemy Colour").selectedValueIndex == 0)
    {
        gameSettingsData["Enemy Colour"] = "BLUE";
    }
    else if(_gameSettings->GetSettingOption("Enemy Colour").selectedValueIndex == 1)
    {
        gameSettingsData["Enemy Colour"] = "RED";
    }
    else if(_gameSettings->GetSettingOption("Enemy Colour").selectedValueIndex == 2)
    {
        gameSettingsData["Enemy Colour"] = "GREEN";
    }
    else if(_gameSettings->GetSettingOption("Enemy Colour").selectedValueIndex == 3)
    {
        gameSettingsData["Enemy Colour"] = "ORANGE";
    }
    else if(_gameSettings->GetSettingOption("Enemy Colour").selectedValueIndex == 4)
    {
        gameSettingsData["Enemy Colour"] = "YELLOW";
    }

    Chilli::JsonSaveSystem::SaveFile(SETTINGS_FILE_PATH, gameSettingsData);
    std::cout << "Settings saved to " << SETTINGS_FILE_PATH << std::endl;
}
