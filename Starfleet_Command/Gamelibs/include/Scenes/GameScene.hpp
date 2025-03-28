#ifndef STARFLEET_COMMAND_GAMESCENE_HPP
#define STARFLEET_COMMAND_GAMESCENE_HPP
#include "Scenes/Scene.hpp"
#include "Utility/Cursor.hpp"
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
#include "Utility/RNG.hpp"
#include "AIDirector/AiDirector.hpp"

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
    void InitPlayerMothership();
    void InitSpaceLanes();
    void InitEnemyMothership();
    void InitGameplayView();
    void InitMinimapView();
    void InitEvents();

    /// EventHandler functions
    void HandleViewScrollingKeyboardInput(const sf::Event &event);
    void StartNextStarshipDeployment();

    /// Update functions
    void UpdateGameplayViewMovement(const sf::RenderWindow &window, const sf::Time &deltaTime, const sf::Vector2i &mousePos);
    void UpdateEnemySpawner();
    void UpdateSpaceLanePositionsAndMouseHoverColour(sf::RenderWindow &window, sf::Time &deltaTime);

    /// Render functions
    void RenderGameplayViewSprites(sf::RenderWindow &window);
    void RenderMinimapSprites(sf::RenderWindow &window);

    /// Event callback functions
    void SpawnStarshipFromShipyard_OnStarshipDeploymentComplete();
    void UpdateScrapMetal_OnEnemyStarshipDestroyed(std::any eventData);
    void UpdateScrapMetal_OnPlayerStarshipDestroyed(std::any eventData);

    /// Utility
    Chilli::Cursor _cursor;
    Chilli::PredefinedColours _predefinedColours;

    /// HUD
    std::unique_ptr<MothershipStatusDisplay> _mothershipStatusDisplay;

    /// Background Parallax
    const int NUM_OF_STARS = 750;
    std::unique_ptr<ParallaxBackground> _backgroundParallax;

    /// Sprites
    Player _player;
    Enemy _enemy;

    /// Enemy AI
    std::unique_ptr<AiDirector> _aiDirector;

    /// Views (Main view & Minimap)
    bool _scrollViewLeft = false;
    bool _scrollViewRight = false;
    const float VIEW_SCROLL_SPEED = 300.0F;
    sf::View _gameplayView{};
    std::unique_ptr<Minimap> _minimap;

    /// Space Lanes
    const float LANE_ROW_SPACING = 35.0F;
    const int NUM_OF_LANES = 5;
    const sf::Color HIGHLIGHT_LANE_COLOUR = sf::Color(100, 100, 100, 100.0F);
    const sf::Color DEFAULT_LANE_COLOUR = sf::Color(100, 100, 100, 25.0F);
    std::vector<std::unique_ptr<SpaceLane>> _spaceLanes;

    /// Player Spawning
    const int STARSHIP_MAX_QUEUE_SIZE = 5;
    static const int NUM_OF_BUTTONS = 5;
    std::unique_ptr<StarshipDeploymentManager> _starshipDeploymentManager;
    std::array<std::unique_ptr<StarshipDeploymentButton>, NUM_OF_BUTTONS> _starshipDeploymentButtons;

    /// Enemy Spawning TODO: Enemy spawner class
    float _enemySpawnTimer = 3.0f;
    float _enemySpawnRate = 5.0f;
    sf::Clock _enemySpawnTimerClock;

    /// Scrap Metal Managers
    const int STARTING_SCRAP_METAL = 5000;
    std::unique_ptr<ScrapMetalManager> _playerScrapMetalManager;
    std::unique_ptr<ScrapMetalManager> _enemyScrapMetalManager;

    /// Music & Sound Effects
    bool _isMusicOn = false;
    static const int MUSIC_ON_BUTTON = 0;
    static const int MUSIC_OFF_BUTTON = 1;
    sf::Music _gameMusic;
    std::array<std::unique_ptr<Button>, 2> _musicIconButtons;
    //std::unique_ptr<Button> _nextMusicTrackButton;

    /// Random Distributions
    RNG _starshipDamageRNG {100, 250};
    RNG _starshipHealRNG {50, 100};
    RNG _enemyStarshipTypeRNG {0, StarshipFactory::STARSHIP_TYPE::ENUM_COUNT - 2};
    RNG _spacelaneSpawnRNG {0, NUM_OF_LANES - 1};
};

#endif //STARFLEET_COMMAND_GAMESCENE_HPP
