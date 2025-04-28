#ifndef STARFLEET_COMMAND_GAMESCENE_HPP
#define STARFLEET_COMMAND_GAMESCENE_HPP
#include "Scenes/Scene.hpp"
#include "Utility/Cursor.hpp"
#include "Utility/RNG.hpp"
#include "Utility/JsonSaveSystem.hpp"
#include "Utility/JsonColourMapping.hpp"
#include "Sprites/Enemy/Enemy.hpp"
#include "Sprites/Player/Player.hpp"
#include "Interfaces/IStarship.hpp"
#include "Sprites/Starships/StarshipFactory.hpp"
#include "SpaceLane.hpp"
#include "Sprites/UI/ProgressBar.hpp"
#include "Minimap.hpp"
#include "ScrapMetalManager.hpp"
#include "ParallaxBackground.hpp"
#include "StarshipDeploymentButton.hpp"
#include "StarshipDeploymentManager.hpp"
#include "MothershipStatusDisplay.hpp"
#include <random>
#include <chrono>
#include "queue"
#include "AIDirector/AiDirector.hpp"
#include "../../ScrapCollectionUpgradeButton.hpp"

class GameScene : public Scene
{
public:
    GameScene() = default;
    ~GameScene() override;
    bool Init() override;
    void EventHandler(sf::RenderWindow& window, sf::Event& event) override;
    void Update(sf::RenderWindow &window, sf::Time deltaTime) override;
    void Render(sf::RenderWindow& window) override;

private:
    /// Init functions
    void InitBackground();
    void InitPlayer();
    void InitSpacelanes();
    void InitEnemy();
    void InitGameplayView();
    void InitPauseMenu();
    void InitMinimapView();
    void InitEvents();
    void InitMusic();

    /// EventHandler functions
    void HandleViewScrollingKeyboardInput(const sf::Event &event);
    void StartNextStarshipDeployment();

    /// Update functions
    void UpdatePauseMenu(sf::RenderWindow &window);
    void UpdateGameplayViewMovement(const sf::RenderWindow &window, const sf::Time &deltaTime, const sf::Vector2i &mousePos);
    void UpdateSpaceLanePositionsAndMouseHoverColour(sf::RenderWindow &window, sf::Time &deltaTime);
    void CheckGameEndConditions();
    void UpdateMusicButtons(sf::RenderWindow &window);
    void UpdateCursorType();

    /// Render functions
    void RenderGameplayViewSprites(sf::RenderWindow &window);
    void RenderMinimapSprites(sf::RenderWindow &window);

    /// Event callback functions
    void SpawnStarshipFromShipyard_OnStarshipDeploymentComplete();
    void UpdateScrapMetal_OnEnemyStarshipDestroyed(std::any eventData);
    void UpdateScrapMetal_OnPlayerStarshipDestroyed(std::any eventData);

    /// Constants
    const std::string AUDIO_DIR_PATH = "Resources/Audio/";
    const std::string DATA_DIR_PATH = "Resources/Data/";
    const std::string FONTS_DIR_PATH = "Resources/Fonts/";
    const std::string TEXTURES_DIR_PATH = "Resources/Textures/";
    const std::string SETTINGS_FILE_PATH = (DATA_DIR_PATH + "GameSettings.json");
    const sf::Color DEFAULT_BUTTON_COLOUR = {22, 155, 164, 100};
    const sf::Color BUTTON_HIGHLIGHT_COLOUR = {22, 155, 164, 65};
    const sf::Color EXIT_BUTTON_HIGHLIGHT_COLOUR = {Chilli::Colour::LIGHTRED.r, Chilli::Colour::LIGHTRED.g, Chilli::Colour::LIGHTRED.b, 60};

    /// Utility
    Chilli::Cursor _cursor;

    /// HUD
    std::unique_ptr<MothershipStatusDisplay> _mothershipStatusDisplay;

    /// Background Parallax
    const int NUM_OF_STARS = 750;
    std::unique_ptr<ParallaxBackground> _backgroundParallax;

    /// Teams
    std::unique_ptr<Player> _player;
    std::unique_ptr<Enemy> _enemy;
    const int STARTING_SCRAP_METAL = 5000;

    /// Scrap Collector
    std::unique_ptr<ScrapCollectionUpgradeButton> _upgradePlayerScrapCollectionButton;
    const float PLAYER_SCRAP_ACCUMULATION_RATE = 5.0F;
    float _playerScrapAccumulationTimer = PLAYER_SCRAP_ACCUMULATION_RATE;
    sf::Clock _playerScrapAccumulationTimerClock;

    /// Ai Director
    std::unique_ptr<AiDirector> _aiDirector;

    /// Views (Main view & Minimap)
    bool _scrollViewLeft = false;
    bool _scrollViewRight = false;
    const float VIEW_SCROLL_SPEED = 600.0F;
    sf::View _gameplayView{};
    std::unique_ptr<Minimap> _minimap;
    bool _isMinimapVisible = true;
    sf::RectangleShape _scrollZoneVisualiser;
    const sf::Color SCROLL_ZONE_HIGHLIGHT_COLOUR = {100, 100, 100, 25};
    const float MOUSE_WINDOW_EDGE_OFFSET_PCT = 0.10F; // 10% of window size
    const float MOUSE_WINDOW_TOP_OFFSET_PCT = 0.20F;
    const float MOUSE_WINDOW_BOTTOM_OFFSET_PCT = 0.21F;

    /// Pause menu
    sf::Texture _pauseIconTexture;
    sf::Sprite _pauseIconSprite;
    sf::Texture _pauseOverlayTexture;
    sf::Sprite _pauseOverlaySprite;
    sf::Text _pauseText;
    std::unique_ptr<Panel> _pauseResumeGameButton;
    std::unique_ptr<Panel> _pauseMainMenuButton;
    std::unique_ptr<Panel> _pauseExitGameButton;

    /// Space Lanes
    const float LANE_ROW_SPACING = 35.0F;
    const int NUM_OF_LANES = 5;
    const sf::Color SPACELANE_HIGHLIGHT_COLOUR = sf::Color(100, 100, 100, 100.0F);
    const sf::Color SPACELANE_DEFAULT_COLOUR = sf::Color(100, 100, 100, 25.0F);
    const sf::Color ATTACKABLE_SPACELANES_HIGHLIGHT_COLOUR = {Chilli::Colour::LIGHTGREEN.r, Chilli::Colour::LIGHTGREEN.g, Chilli::Colour::LIGHTGREEN.b, 50};
    std::vector<std::unique_ptr<SpaceLane>> _spaceLanes;
    bool _isSpacelanesVisible = true;

    /// Player Spawning
    const int STARSHIP_MAX_QUEUE_SIZE = 5;
    static const int NUM_OF_BUTTONS = 5;
    std::unique_ptr<StarshipDeploymentManager> _starshipDeploymentManager;
    std::array<std::unique_ptr<StarshipDeploymentButton>, NUM_OF_BUTTONS> _starshipDeploymentButtons;

    /// Music & Sound Effects
    bool _isMusicOn = false;
    static const int MUSIC_ON_BUTTON = 0;
    static const int MUSIC_OFF_BUTTON = 1;
    std::array<sf::Music, 4> _gameMusic;
    std::array<std::unique_ptr<Button>, 2> _musicIconButtons;
    std::unique_ptr<Button> _nextMusicTrackButton;
    int _currentMusicTrackIndex = 0;

    /// Random Distributions
    RNG _starshipHealRNG {50, 100};
    RNG _enemyStarshipTypeRNG {0, StarshipFactory::STARSHIP_TYPE::ENUM_COUNT - 2};
    RNG _spacelaneSpawnRNG {0, NUM_OF_LANES - 1};
};

#endif //STARFLEET_COMMAND_GAMESCENE_HPP
