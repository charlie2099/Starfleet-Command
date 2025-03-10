#ifndef STARFLEET_COMMAND_GAMESCENE_HPP
#define STARFLEET_COMMAND_GAMESCENE_HPP
#include "Scenes/Scene.hpp"
#include "Utility/Cursor.hpp"
#include "Sprites/Enemy/Enemy.hpp"
#include "Sprites/Player/Player.hpp"
#include "Interfaces/IStarship.hpp"
#include "Sprites/Starships/StarshipFactory.hpp"
#include <random>
#include <chrono>
#include "../../SpaceLane.hpp"
#include "Sprites/UI/ProgressBar.hpp"
#include "queue"
#include "../../Minimap.hpp"
#include "../../ScrapMetalManager.hpp"
#include "../../ParallaxBackground.hpp"
#include "../../GameHUD.hpp"

class GameScene : public Scene
{
public:
    GameScene() = default;
    ~GameScene() = default;
    bool Init() override;
    void EventHandler(sf::RenderWindow& window, sf::Event& event) override;
    void Update(sf::RenderWindow &window, sf::Time deltaTime) override;
    void Render(sf::RenderWindow& window) override;

private:
    /// Init functions
    void InitRandomDistributions();
    bool InitStarshipBuilderButtons();
    void InitPlayerMothership();
    void InitSpaceLanes();
    void InitEnemyMothership();
    void InitMainView();
    void InitMinimapView();
    void InitMainViewBorder();
    void InitStarshipPreviewSprites();
    void InitEvents();

    /// EventHandler functions
    void HandleViewScrollingKeyboardInput(const sf::Event &event);
    void HandleStarshipBuilderButtonsInteractionMouseInput(const sf::Event &event);
    void HandleStarshipPlacementMouseInput(const sf::Event &event);
    void BeginStarshipDeploymentProcess(int currentSpaceLaneSelectedIndex);
    void StartNextStarshipDeployment();

    /// Update functions
    void UpdateMainViewMovement(const sf::RenderWindow &window, const sf::Time &deltaTime, const sf::Vector2i &mousePos);
    void UpdateStarshipBuilderButtonsHoverStateAndColour();
    void UpdateStarshipBuilderButtonPositions(sf::RenderWindow &window);
    void UpdateEnemySpawner();
    void UpdateSpaceLanePositionsAndMouseHoverColour(sf::RenderWindow &window, sf::Time &deltaTime);
    void UpdateStarshipPreviewSpritePosition(const sf::Vector2f &worldPositionOfMouse);

    /// Event callback functions
    void SpawnStarshipFromShipyard_OnStarshipDeploymentComplete();
    void UpdateScrapMetal_OnEnemyStarshipDestroyed(std::any eventData);
    void UpdateScrapMetal_OnPlayerStarshipDestroyed(std::any eventData);

    /// Randomness functions
    enum DistributionsEnum{ STARSHIP_DAMAGE = 0, SPACELANE = 1, ENEMY_STARSHIP_TYPE = 2, STARSHIP_HEALING =3 };
    void CreateDistribution([[maybe_unused]] [[maybe_unused]] DistributionsEnum distributionsEnum, int min, int max);
    static std::mt19937 GetEngine();

    ///Utility
    Chilli::Cursor _cursor;
    Chilli::PredefinedColours _predefinedColours;

    /// HUD
    std::unique_ptr<GameHUD> gameHud;

    /// GUI
    std::vector<std::unique_ptr<Button>> _starshipBuilderButtons;
    std::array<SpriteComponent, StarshipFactory::STARSHIP_TYPE::ENUM_COUNT - 1> _starshipPreviewSprites;
    std::map<Button*, IStarship*> _buttonStarshipDictionary;
    std::unique_ptr<LightFighter> _lightFighter;
    std::unique_ptr<HeavyFighter> _heavyFighter;
    std::unique_ptr<SupportShip> _supportShip;
    std::unique_ptr<Destroyer> _destroyer;
    std::unique_ptr<Battleship> _battleship;
    const sf::Color DEFAULT_BTN_COLOUR = {255, 255, 255, 100};
    const sf::Color HOVER_BTN_COLOR = _predefinedColours.LIGHTBLUE;
    const sf::Color SELECTED_BTN_COLOR = {153, 210, 242, 150};
    static const int NUM_OF_BUTTONS = 5;
    //std::array<Panel, NUM_OF_BUTTONS> _shipInfoPanels;
    int _starshipButtonSelectedIndex = 0;
    int _starshipButtonHoveredOverIndex = 0;
    bool _isPlacingStarship = false;
    bool _isStarshipPreviewSpriteVisible = false;

    /// Background Parallax
    std::unique_ptr<ParallaxBackground> backgroundParallax;
    const int NUM_OF_STARS = 750;

    /// Sprites
    Player _player;
    Enemy _enemy;

    /// Views (Main view & Minimap)
    std::unique_ptr<Minimap> minimap;
    sf::View _mainView{};
    sf::RectangleShape _mainViewBorder; // _minimapActiveArea // NOTE: Contain within Minimap class?
    sf::Text _mainViewBorderText;
    const float VIEW_SCROLL_SPEED = 300.0F;
    bool _scrollViewLeft = false;
    bool _scrollViewRight = false;

    /// Random Distributions
    std::mt19937 _randomGenerator;
    std::vector<std::uniform_int_distribution<int>> _randomValueDistributions;

    /// Space Lanes
    std::vector<std::unique_ptr<SpaceLane>> _spaceLanes;
    const float LANE_Y_SPACING = 35.0F;
    const int NUM_OF_LANES = 5;

    /// Player Spawning
    std::queue<StarshipFactory::STARSHIP_TYPE> _starshipTypeTrainingQueue;
    std::queue<int> _spaceLaneStarshipDeploymentQueue;
    const int STARSHIP_MAX_QUEUE_SIZE = 5;

    /// Enemy Spawning TODO: Enemy spawner class
    sf::Clock _enemySpawnTimerClock;
    float _enemySpawnTimer = 3.0f;
    float _enemySpawnRate = 5.0f;

    /// Scrap Metal Managers
    std::unique_ptr<ScrapMetalManager> _playerScrapMetalManager;
    std::unique_ptr<ScrapMetalManager> _enemyScrapMetalManager;
    const int STARTING_SCRAP_METAL = 25000;
};

#endif //STARFLEET_COMMAND_GAMESCENE_HPP
