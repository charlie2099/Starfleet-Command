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
    InitGameSettings();
    InitMenuMusic();
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
    _cursor.SetCursorPos(window, _worldView);

    UpdateBackgroundStarshipsMovement(window, deltaTime);

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
            _buttonPanels[BACK_BUTTON].SetText(_buttonPanels[BACK_BUTTON].GetText().getString(), Chilli::PredefinedColours::LIGHTBLUE);
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
            _buttonPanels[i].SetText(_buttonPanels[i].GetText().getString(), Chilli::PredefinedColours::LIGHTBLUE);
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

bool MenuScene::InitMenuMusic()
{
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
        return true;
    }
}

void MenuScene::InitEvents()
{
    /// Observer to game settings event
    auto gameSettingsCallback = std::bind(&MenuScene::SaveGameSettingsData_OnSettingsUpdated, this);
    _gameSettings->AddBasicObserver({GameSettings::SETTINGS_UPDATED, gameSettingsCallback});
}

void MenuScene::InitGameSettings()
{
    _gameSettings = std::make_unique<GameSettings>();
    _gameSettings->AddSettingOption("Music", std::vector<std::string>{"OFF", "ON"});
    _gameSettings->AddSettingOption("Spacelanes", std::vector<std::string>{"OFF", "ON"});
    _gameSettings->AddSettingOption("Minimap", std::vector<std::string>{"OFF", "ON"});
    _gameSettings->AddSettingOption("Player Colour", std::vector<std::string>{"BLUE", "RED", "GREEN", "ORANGE", "YELLOW"});
    _gameSettings->AddSettingOption("Enemy Colour",std::vector<std::string>{"BLUE", "RED", "GREEN", "ORANGE", "YELLOW"});
    //_gameSettings->AddSettingOption("Difficulty", std::vector<std::string>{"EASY", "MEDIUM", "HARD"});

    if(Chilli::JsonSaveSystem::CheckFileExists(SETTINGS_FILE_PATH))
    {
        std::cout << "GameSettings file found!" << std::endl;
        auto fileData = Chilli::JsonSaveSystem::LoadFile(SETTINGS_FILE_PATH);

        if(fileData.contains("Music"))
        {
            std::string musicData = fileData["Music"];
            _isMusicOn = (musicData == "true");
            _gameSettings->UpdateSettingOptionValueText("Music", musicData == "true");
        }

        if(fileData.contains("Spacelanes"))
        {
            std::string spacelanesData = fileData["Spacelanes"];
            _gameSettings->UpdateSettingOptionValueText("Spacelanes", spacelanesData == "true");
        }

        if(fileData.contains("Minimap"))
        {
            std::string minimapData = fileData["Minimap"];
            _gameSettings->UpdateSettingOptionValueText("Minimap", minimapData == "true");
        }

        if(fileData.contains("Player Colour"))
        {
            std::string playerColourData = fileData["Player Colour"];

            if(playerColourData == "BLUE")
            {
                _backgroundPlayerPlanetTexture.loadFromFile("Resources/Textures/planet_blue.png");
                _backgroundPlayerPlanetSprite.setTexture(_backgroundPlayerPlanetTexture);
                _player->SetTeamColour(Chilli::PredefinedColours::LIGHTBLUE);
                _gameSettings->UpdateSettingOptionValueText("Player Colour", 0);
            }
            else if(playerColourData == "RED")
            {
                _backgroundPlayerPlanetTexture.loadFromFile("Resources/Textures/planet_red.png");
                _backgroundPlayerPlanetSprite.setTexture(_backgroundPlayerPlanetTexture);
                _player->SetTeamColour(Chilli::PredefinedColours::LIGHTRED);
                _gameSettings->UpdateSettingOptionValueText("Player Colour", 1);
            }
            else if(playerColourData == "GREEN")
            {
                _backgroundPlayerPlanetTexture.loadFromFile("Resources/Textures/planet_green.png");
                _backgroundPlayerPlanetSprite.setTexture(_backgroundPlayerPlanetTexture);
                _player->SetTeamColour(Chilli::PredefinedColours::LIGHTGREEN);
                _gameSettings->UpdateSettingOptionValueText("Player Colour", 2);
            }
            else if(playerColourData == "ORANGE")
            {
                _backgroundPlayerPlanetTexture.loadFromFile("Resources/Textures/planet_orange.png");
                _backgroundPlayerPlanetSprite.setTexture(_backgroundPlayerPlanetTexture);
                _player->SetTeamColour(Chilli::PredefinedColours::LIGHTORANGE);
                _gameSettings->UpdateSettingOptionValueText("Player Colour", 3);
            }
            else if(playerColourData == "YELLOW")
            {
                _backgroundPlayerPlanetTexture.loadFromFile("Resources/Textures/planet_yellow.png");
                _backgroundPlayerPlanetSprite.setTexture(_backgroundPlayerPlanetTexture);
                _player->SetTeamColour(Chilli::PredefinedColours::YELLOW);
                _gameSettings->UpdateSettingOptionValueText("Player Colour", 4);
            }
        }

        if(fileData.contains("Enemy Colour"))
        {
            std::string enemyColourData = fileData["Enemy Colour"];

            if(enemyColourData == "BLUE")
            {
                _backgroundEnemyPlanetTexture.loadFromFile("Resources/Textures/planet_blue.png");
                _backgroundEnemyPlanetSprite.setTexture(_backgroundEnemyPlanetTexture);
                _enemy->SetTeamColour(Chilli::PredefinedColours::LIGHTBLUE);
                _gameSettings->UpdateSettingOptionValueText("Enemy Colour", 0);
            }
            else if(enemyColourData == "RED")
            {
                _backgroundEnemyPlanetTexture.loadFromFile("Resources/Textures/planet_red.png");
                _backgroundEnemyPlanetSprite.setTexture(_backgroundEnemyPlanetTexture);
                _enemy->SetTeamColour(Chilli::PredefinedColours::LIGHTRED);
                _gameSettings->UpdateSettingOptionValueText("Enemy Colour", 1);
            }
            else if(enemyColourData == "GREEN")
            {
                _backgroundEnemyPlanetTexture.loadFromFile("Resources/Textures/planet_green.png");
                _backgroundEnemyPlanetSprite.setTexture(_backgroundEnemyPlanetTexture);
                _enemy->SetTeamColour(Chilli::PredefinedColours::LIGHTGREEN);
                _gameSettings->UpdateSettingOptionValueText("Enemy Colour", 2);
            }
            else if(enemyColourData == "ORANGE")
            {
                _backgroundEnemyPlanetTexture.loadFromFile("Resources/Textures/planet_orange.png");
                _backgroundEnemyPlanetSprite.setTexture(_backgroundEnemyPlanetTexture);
                _enemy->SetTeamColour(Chilli::PredefinedColours::LIGHTORANGE);
                _gameSettings->UpdateSettingOptionValueText("Enemy Colour", 3);
            }
            else if(enemyColourData == "YELLOW")
            {
                _backgroundEnemyPlanetTexture.loadFromFile("Resources/Textures/planet_yellow.png");
                _backgroundEnemyPlanetSprite.setTexture(_backgroundEnemyPlanetTexture);
                _enemy->SetTeamColour(Chilli::PredefinedColours::YELLOW);
                _gameSettings->UpdateSettingOptionValueText("Enemy Colour", 4);
            }
        }
    }
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
        _parallaxStars[i].circleShape.setFillColor(Chilli::PredefinedColours::LIGHTBLUE);
    }

    _backgroundEnemyPlanetTexture.loadFromFile("Resources/Textures/planet_green.png");
    _backgroundEnemyPlanetSprite.setTexture(_backgroundEnemyPlanetTexture);
    _backgroundEnemyPlanetSprite.setPosition(Constants::WINDOW_WIDTH / 1.6F, Constants::WINDOW_HEIGHT / 2.5F);

    _backgroundPlayerPlanetTexture.loadFromFile("Resources/Textures/planet_blue.png");
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

    _player = std::make_unique<Player>(0, Chilli::PredefinedColours::LIGHTBLUE);
    _enemy = std::make_unique<Enemy>(0, Chilli::PredefinedColours::LIGHTGREEN);

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
    _gameVersionText.setString("PRE-ALPHA BUILD v0.2.0"); // Early Alpha = v0.5.0, Early Beta = v0.8.0, Release = v1.0.0
    _gameVersionText.setCharacterSize(14);
    _gameVersionText.setFillColor(Chilli::PredefinedColours::LIGHTBLUE);
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

            _gameSettings->RepositionPanel(Constants::WINDOW_WIDTH / 2.0F - _gameSettings->GetSettingsPanelSize().x / 2.0F,
                                           _menuTitleImgSprite.getPosition().y + _menuTitleImgSprite.getGlobalBounds().height + 25.0F);
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

void MenuScene::SaveGameSettingsData_OnSettingsUpdated()
{
    /// Model the data and save it to file
    json gameSettingsData;
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

    /// Apply game settings
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
            _backgroundPlayerPlanetTexture.loadFromFile("Resources/Textures/planet_blue.png");
            _backgroundPlayerPlanetSprite.setTexture(_backgroundPlayerPlanetTexture);
            _player->SetTeamColour(Chilli::PredefinedColours::LIGHTBLUE);
        }
        else if(playerColourSetting.valueText.getString() == "RED")
        {
            _backgroundPlayerPlanetTexture.loadFromFile("Resources/Textures/planet_red.png");
            _backgroundPlayerPlanetSprite.setTexture(_backgroundPlayerPlanetTexture);
            _player->SetTeamColour(Chilli::PredefinedColours::LIGHTRED);
        }
        else if(playerColourSetting.valueText.getString() == "GREEN")
        {
            _backgroundPlayerPlanetTexture.loadFromFile("Resources/Textures/planet_green.png");
            _backgroundPlayerPlanetSprite.setTexture(_backgroundPlayerPlanetTexture);
            _player->SetTeamColour(Chilli::PredefinedColours::LIGHTGREEN);
        }
        else if(playerColourSetting.valueText.getString() == "ORANGE")
        {
            _backgroundPlayerPlanetTexture.loadFromFile("Resources/Textures/planet_orange.png");
            _backgroundPlayerPlanetSprite.setTexture(_backgroundPlayerPlanetTexture);
            _player->SetTeamColour(Chilli::PredefinedColours::LIGHTORANGE);
        }
        else if(playerColourSetting.valueText.getString() == "YELLOW")
        {
            _backgroundPlayerPlanetTexture.loadFromFile("Resources/Textures/planet_yellow.png");
            _backgroundPlayerPlanetSprite.setTexture(_backgroundPlayerPlanetTexture);
            _player->SetTeamColour(Chilli::PredefinedColours::YELLOW);
        }
    }

    auto enemyColourSetting = _gameSettings->GetSettingOption("Enemy Colour");
    for (int i = 0; i < enemyColourSetting.optionValues.size(); ++i)
    {
        if(enemyColourSetting.valueText.getString() == "BLUE")
        {
            _backgroundEnemyPlanetTexture.loadFromFile("Resources/Textures/planet_blue.png");
            _backgroundEnemyPlanetSprite.setTexture(_backgroundEnemyPlanetTexture);
            _enemy->SetTeamColour(Chilli::PredefinedColours::LIGHTBLUE);
        }
        else if(enemyColourSetting.valueText.getString() == "RED")
        {
            _backgroundEnemyPlanetTexture.loadFromFile("Resources/Textures/planet_red.png");
            _backgroundEnemyPlanetSprite.setTexture(_backgroundEnemyPlanetTexture);
            _enemy->SetTeamColour(Chilli::PredefinedColours::LIGHTRED);
        }
        else if(enemyColourSetting.valueText.getString() == "GREEN")
        {
            _backgroundEnemyPlanetTexture.loadFromFile("Resources/Textures/planet_green.png");
            _backgroundEnemyPlanetSprite.setTexture(_backgroundEnemyPlanetTexture);
            _enemy->SetTeamColour(Chilli::PredefinedColours::LIGHTGREEN);
        }
        else if(enemyColourSetting.valueText.getString() == "ORANGE")
        {
            _backgroundEnemyPlanetTexture.loadFromFile("Resources/Textures/planet_orange.png");
            _backgroundEnemyPlanetSprite.setTexture(_backgroundEnemyPlanetTexture);
            _enemy->SetTeamColour(Chilli::PredefinedColours::LIGHTORANGE);
        }
        else if(enemyColourSetting.valueText.getString() == "YELLOW")
        {
            _backgroundEnemyPlanetTexture.loadFromFile("Resources/Textures/planet_yellow.png");
            _backgroundEnemyPlanetSprite.setTexture(_backgroundEnemyPlanetTexture);
            _enemy->SetTeamColour(Chilli::PredefinedColours::YELLOW);
        }
    }
}
