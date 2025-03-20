#ifndef STARFLEET_COMMAND_GAMESCENE_HPP
#define STARFLEET_COMMAND_GAMESCENE_HPP
#include "Scenes/Scene.hpp"
#include "Cursor.hpp"
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
    void InitRandomDistributions();
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

    /// Randomness functions
    enum DistributionsEnum { STARSHIP_DAMAGE = 0, SPACELANE = 1, ENEMY_STARSHIP_TYPE = 2, STARSHIP_HEALING =3 };
    void CreateDistribution([[maybe_unused]] [[maybe_unused]] DistributionsEnum distributionsEnum, int min, int max);
    static std::mt19937 GetEngine();

    ///Utility
    Chilli::Cursor _cursor;
    Chilli::PredefinedColours _predefinedColours;

    /// HUD
    std::unique_ptr<MothershipStatusDisplay> _mothershipStatusDisplay;

    /// GUI
    static const int NUM_OF_BUTTONS = 5;
    std::array<std::unique_ptr<StarshipDeploymentButton>, NUM_OF_BUTTONS> _starshipDeploymentButtons;

    /// Background Parallax
    std::unique_ptr<ParallaxBackground> _backgroundParallax;
    const int NUM_OF_STARS = 750;

    /// Sprites
    Player _player;
    Enemy _enemy;

    /// Views (Main view & Minimap)
    sf::View _gameplayView{};
    std::unique_ptr<Minimap> _minimap;
    bool _scrollViewLeft = false;
    bool _scrollViewRight = false;
    const float VIEW_SCROLL_SPEED = 300.0F;

    /// Random Distributions
    std::mt19937 _randomGenerator;
    std::vector<std::uniform_int_distribution<int>> _randomValueDistributions;

    /// Space Lanes
    std::vector<std::unique_ptr<SpaceLane>> _spaceLanes;
    const float LANE_ROW_SPACING = 35.0F;
    const int NUM_OF_LANES = 5;

    /// Player Spawning
    std::unique_ptr<StarshipDeploymentManager> _starshipDeploymentManager;
    const int STARSHIP_MAX_QUEUE_SIZE = 5;

    /// Enemy Spawning TODO: Enemy spawner class
    sf::Clock _enemySpawnTimerClock;
    float _enemySpawnTimer = 3.0f;
    float _enemySpawnRate = 5.0f;

    /// Scrap Metal Managers
    std::unique_ptr<ScrapMetalManager> _playerScrapMetalManager;
    std::unique_ptr<ScrapMetalManager> _enemyScrapMetalManager;
    const int STARTING_SCRAP_METAL = 5000;

    sf::Music _gameMusic;
    std::array<std::unique_ptr<Button>, 2> _musicIconButtons;
    //std::unique_ptr<Button> _nextMusicTrackButton;
    bool _isMusicOn = true;
    static const int MUSIC_ON_BUTTON = 0;
    static const int MUSIC_OFF_BUTTON = 1;
};

#endif //STARFLEET_COMMAND_GAMESCENE_HPP
