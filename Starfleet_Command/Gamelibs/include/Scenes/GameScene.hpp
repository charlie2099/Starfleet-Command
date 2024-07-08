#ifndef STARFLEET_COMMAND_GAMESCENE_HPP
#define STARFLEET_COMMAND_GAMESCENE_HPP
#include "Scenes/Scene.hpp"
#include "Sprites/Starships/Fleet.hpp"
#include "Sprites/UI/Crosshair.hpp"
#include "Utility/Cursor.hpp"
#include "Sprites/Enemy/Enemy.hpp"
#include "Sprites/Player/Player.h"
#include "Sprites/UI/HUD/Shipyard.hpp"
#include "Interfaces/IStarship.hpp"
#include "Sprites/Starships/StarshipFactory.hpp"
#include <random>
#include <chrono>

#include "Sprites/UI/HUD/Shipyard.hpp"

class GameScene : public Scene
{
public:
    GameScene() = default;
    ~GameScene() override = default;
    bool Init() override;
    void EventHandler(sf::RenderWindow& window, sf::Event& event) override;

    void SpawnShipFromShipyard();

    void Update(sf::RenderWindow &window, sf::Time deltaTime) override;
    void Render(sf::RenderWindow& window) override;

private:
    void InitDistribution();
    bool InitBackground();
    bool InitCommandButtons();
    void InitPlayerShips();
    void InitEnemyShips();
    void InitPlayerCreditsText();
    void InitWavesRemainingText();
    void InitEnemiesRemainingText();
    void InitMainView();
    void InitMinimapView();
    void InitMainViewBorder();
    void InitMinimapBorder();
    void RandomisePlayerShipSpawnPoint();
    void CreateDistribution(const std::string& name, int min, int max);
    void UpdateDistribution(const std::string& name, int min, int max);
    static std::mt19937 GetEngine();
    sf::Vector2f ConstrainViewCenter(const sf::Vector2f& proposedCenter) const;
    void ResetMinimapView();

    // Utility
    Chilli::Cursor _cursor;
    Chilli::Colours _predefinedColours;

    // HUD
    Shipyard _shipyard;
    sf::Text _playerCreditsText;
    sf::Text _wavesRemainingText;
    sf::Text _enemiesRemainingText;
    int _playerCreditsCounter = 5000;
    int _wavesRemainingCounter = 3;
    int _enemiesRemainingCounter = 100;

    // GUI
    //Crosshair crosshair;
    std::vector<std::unique_ptr<Button>> _command_buttons;
    std::vector<sf::Text> _ship_cost_text;

    // UI
    std::unique_ptr<sf::Texture> _background_texture;
    sf::Sprite _background_sprite;
    sf::RectangleShape _mainViewBorder;
    sf::RectangleShape _minimapBorder;

    // Sprites
    Player _player;
    Enemy _enemy;

    // Other
    sf::View _mainView{};
    sf::View _minimapView{};
    std::mt19937 _generator;
    std::vector<std::uniform_int_distribution<int>> _uint_distrib;
    std::map<std::string, int> _dist_code;
    int _ship_spawned_index = 0;
    float _originalZoomLevel = 1.0f;
    float _currentZoomLevel = 1.0f;
    bool _isDragging = false;
    sf::Vector2i _initialMousePosition;
    sf::Vector2f _originalMinimapViewCenter;
    //std::map<Button, IStarship> _buttonToShipDictionary;
};

#endif //STARFLEET_COMMAND_GAMESCENE_HPP
