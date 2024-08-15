#ifndef STARFLEET_COMMAND_GAMESCENE_HPP
#define STARFLEET_COMMAND_GAMESCENE_HPP
#include "Scenes/Scene.hpp"
#include "Utility/Cursor.hpp"
#include "Sprites/Enemy/Enemy.hpp"
#include "Sprites/Player/Player.h"
#include "Interfaces/IStarship.hpp"
#include "Sprites/Starships/StarshipFactory.hpp"
#include <random>
#include <chrono>
#include "../../SpaceLane.hpp"
#include "../../ProgressBar.hpp"

class GameScene : public Scene
{
public:
    GameScene() = default;
    ~GameScene() override = default;
    bool Init() override;
    void EventHandler(sf::RenderWindow& window, sf::Event& event) override;
    void Update(sf::RenderWindow &window, sf::Time deltaTime) override;
    void Render(sf::RenderWindow& window) override;

private:
    void InitRandomDistributions();
    bool InitBackground();
    bool InitShipSpawnerButtons();
    void InitPlayerFlagship();
    void InitEnemyFlagship();
    void InitPlayerCreditsText();
    void InitWavesRemainingText();
    void InitEnemiesRemainingText();
    void InitMainView();
    void InitMinimapView();
    void InitMainViewBorder();
    void InitMinimapBorder();
    void InitSpaceLanes();
    void InitEvents();
    sf::Vector2f ConstrainViewCenter(const sf::Vector2f& proposedCenter) const;
    void ResetMinimapView();
    void SpawnShipFromShipyard();
    enum DistributionsEnum
    {
        SHIP_DAMAGE = 0,
        SPACELANE = 1,
        ENEMY_SHIP_TYPE = 2,
    };
    void CreateDistribution(DistributionsEnum distributionsEnum, int min, int max);
    static std::mt19937 GetEngine();

    // Utility
    Chilli::Cursor _cursor;
    Chilli::PredefinedColours _predefinedColours;

    // HUD
    ProgressBar _shipAssemblyBar;
    sf::Text _playerScrapText;
    sf::Text _wavesRemainingText;
    sf::Text _enemiesRemainingText;
    int _playerScrapCounter = 5000;
    int _wavesRemainingCounter = 3;
    int _enemiesRemainingCounter = 100;

    // GUI
    std::vector<std::unique_ptr<Button>> _shipSpawnerButtons;
    std::vector<sf::Text> _shipCostText;

    // UI
    std::unique_ptr<sf::Texture> _backgroundTexture;
    sf::Sprite _backgroundSprite;
    sf::RectangleShape _mainViewBorder;
    sf::RectangleShape _minimapBorder;

    // Sprites
    Player _player;
    Enemy _enemy;
    std::array<SpriteComponent, StarshipFactory::SHIP_TYPE::ENUM_COUNT-1> _shipDragSpriteVisuals;

    // Minimap
    sf::View _mainView{};
    sf::View _minimapView{};

    // Random Distributions
    std::mt19937 _generator;
    std::vector<std::uniform_int_distribution<int>> _distributions;

    // Other
    int _shipSelectedIndex = 0;
    float _originalZoomLevel = 1.0f;
    float _currentZoomLevel = 1.0f;
    bool _isDragging = false;
    sf::Vector2i _initialMousePosition;
    sf::Vector2f _originalMinimapViewCenter;
    std::map<Button*, IStarship*> _buttonShipDictionary;

    // For ship spawner buttons
    const int NUM_OF_BUTTONS = 5;
    std::unique_ptr<LightFighter> _lightFighter;
    std::unique_ptr<HeavyFighter> _heavyFighter;
    std::unique_ptr<SupportShip> _supportShip;
    std::unique_ptr<Destroyer> _destroyer;
    std::unique_ptr<Battleship> _battleship;

    // Space Lanes
    std::vector<std::unique_ptr<SpaceLane>> _spaceLanes;
    const float LANE_Y_SPACING = 35.0F;
    const int NUM_OF_LANES = 5;
    int _spaceLaneSelected = 0;

    // Enemy Spawning
    float _enemySpawnTimer = 3.0f;
    float _enemySpawnRate = 5.0f;
    sf::Clock _clock;

    // Drag and drop
    bool _dragging = false;
    bool _isDragVisualVisible = false;

    // Main view scroll
    const float VP_SCROLL_SPEED = 300.0F;
    bool _scrollViewLeft = false;
    bool _scrollViewRight = false;
};

#endif //STARFLEET_COMMAND_GAMESCENE_HPP
