#ifndef STARFLEET_COMMAND_MENUSCENE_HPP
#define STARFLEET_COMMAND_MENUSCENE_HPP
#include "Scenes/Scene.hpp"
#include "Utility/Cursor.hpp"
#include "Utility/Vector.hpp"
#include "Utility/JsonSaveSystem.hpp"
#include "Utility/JsonColourMapping.hpp"
#include "Utility/RNG.hpp"
#include "Sprites/Starships/Starship.hpp"
#include "GameSettings.hpp"
#include "Sprites/Player/Player.hpp"
#include "Sprites/Enemy/Enemy.hpp"
#include "Sprites/UI/ParallaxBackground.hpp"
#include <random>
#include <chrono>

class MenuScene : public Scene
{
 public:
    MenuScene() = default;
    ~MenuScene() override;

    bool Init() override;
    void EventHandler(sf::RenderWindow& window, sf::Event& event) override;
    void Update(sf::RenderWindow &window, sf::Time deltaTime) override;
    void Render(sf::RenderWindow& window) override;

 private:
    /// Destructor functions
    void StopMusic();

    /// Init functions
    void InitView();
    bool InitBackground();
    void InitButtons();
    bool InitTitle();
    void InitBackgroundStarships();
    void InitGameVersionText();
    void InitGameSettings();
    bool InitMusic();
    void InitEvents();

    /// EventHandler functions
    void HandleGameSettingsEvents(sf::RenderWindow &window, sf::Event &event);
    void HandleButtonEvents(sf::RenderWindow &window, sf::Event &event);

    /// Update functions
    void UpdateCursor(sf::RenderWindow &window, sf::Time &deltaTime);
    void UpdateStarshipAnimations(sf::RenderWindow &window, sf::Time &deltaTime);
    void UpdateGameSettingsButtons(sf::RenderWindow &window, sf::Time &deltaTime);
    void UpdateMenuButtons(sf::RenderWindow &window);

    /// Render functions
    void RenderBackground(sf::RenderWindow &window);
    void RenderStarships(sf::RenderWindow &window);
    void RenderGameSettings(sf::RenderWindow &window);
    void RenderButtons(sf::RenderWindow &window);

    /// Event functions
    void ApplyGameSettings_OnSettingsUpdated();
    void SaveGameSettingsData_OnSettingsSaved();

    /// Other functions
    void ApplyTeamColourSettings(const json &gameSettingsData, const std::string& teamColourSettingName);

    /// Constants
    const std::string GAME_VERSION = "PRE-ALPHA BUILD v0.3.0"; // Early Alpha = v0.5.0, Early Beta = v0.8.0, Release = v1.0.0
    const std::string AUDIO_DIR_PATH = "Resources/Audio/";
    const std::string DATA_DIR_PATH = "Resources/Data/";
    const std::string FONTS_DIR_PATH = "Resources/Fonts/";
    const std::string TEXTURES_DIR_PATH = "Resources/Textures/";
    const std::string SETTINGS_FILE_PATH = (DATA_DIR_PATH + "GameSettings.json");
    const int PLAY_BUTTON = 0;
    const int OPTIONS_BUTTON = 1;
    const int EXIT_BUTTON = 2;
    const int BACK_BUTTON = 3;
    static const int NUM_OF_BUTTONS = 4;
    const int NUM_OF_SHIPS_PER_TEAM = 8;

    /// Utility
    Chilli::Cursor _cursor;

    /// View
    sf::View _menuView{};

    /// Buttons
    std::array<TextButton, NUM_OF_BUTTONS> _menuButtons;

    /// Teams
    std::unique_ptr<Player> _player;
    std::unique_ptr<Enemy> _enemy;

    /// Background
    std::unique_ptr<ParallaxBackground> _backgroundParallax;
    std::array<sf::Texture, 7> _backgroundPlanetTextures;
    sf::Sprite _backgroundEnemyPlanetSprite;
    sf::Sprite _backgroundPlayerPlanetSprite;

    /// Menu Title
    sf::Sprite _titleSprite;
    sf::Texture _menuTitleImgTexture;

    /// Game Settings
    std::unique_ptr<GameSettings> _gameSettings;
    bool _isGameSettingsEnabled = false;

    /// Game Version
    sf::Text _gameVersionText;

    /// Audio
    sf::Music _menuMusic;
    bool _isMusicOn = false;
    sf::SoundBuffer _buttonClickSoundBuffer;
    sf::Sound _buttonClickSound;
};
#endif //STARFLEET_COMMAND_MENUSCENE_HPP
