#ifndef STARFLEET_COMMAND_GAMESCENE_HPP
#define STARFLEET_COMMAND_GAMESCENE_HPP
#include "Scenes/Scene.hpp"
#include "Sprites/Starships/Fleet.hpp"
#include "Sprites/Starships/OLDStarship.hpp"
#include "Sprites/UI/Crosshair.hpp"
#include "Utility/Cursor.hpp"
#include "Sprites/Enemy/Enemy.hpp"
#include "Sprites/Player/Player.h"
#include "Sprites/UI/HUD/HUD.hpp"
#include "Temporary/TestClass.hpp"
#include "Interfaces/IStarship.hpp"
#include "Sprites/Starships/StarshipFactory.hpp"
#include "Sprites/GameObject.hpp"
#include "Sprites/Starships/StarshipClass.hpp"
#include "Behaviours/StarshipFighterBehaviour.hpp"
#include "Sprites/Starships/Starship.h"
#include <random>
#include <chrono>

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
    void InitDistribution();
    bool InitBackground();
    bool InitCommandButtons();
    void InitPlayerFlagship();
    void InitEnemyFlagship();
    void InitCreditsText();
    void InitView();
    void RandomiseShipSpawnPoint();
    void CreateDistribution(const std::string& name, int min, int max);
    void UpdateDistribution(const std::string& name, int min, int max);
    static std::mt19937 GetEngine();

    //Entity gameObject;
    //OldGameObject gameObject;
    //NewSpriteComponent* newSpriteComponent;
    //AiComponent* aiComponent;

    // Utility
    Chilli::Cursor _cursor;
    Chilli::Colours _predefinedColours;

    // HUD
    HUD _hud;
    sf::Text _credits_text;
    int _credits = 10000;

    // GUI
    //Crosshair crosshair;
    std::vector<std::unique_ptr<Button>> _command_buttons;
    std::vector<sf::Text> _ship_cost_text;

    // UI
    std::unique_ptr<sf::Texture> _background_texture;
    sf::Sprite _background_sprite;

    // Sprites
    Player _player;
    Enemy _enemy;

    // Other
    sf::View _worldView{};
    sf::View _minimapView{};
    std::mt19937 generator;
    std::vector<std::uniform_int_distribution<int>> uint_distrib;
    std::map<std::string, int> dist_code;
    int ship_spawned_index = 0;

    // TEST VARIABLES (TEMPORARY)
    TestClass testClass;
    //std::unique_ptr<IStarship> starship;
    //GameObject gameObject;
    //std::unique_ptr<Starship> starshipFighter;
    //std::unique_ptr<Starship> starshipScout;
};

#endif //STARFLEET_COMMAND_GAMESCENE_HPP
