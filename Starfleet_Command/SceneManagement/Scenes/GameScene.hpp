#ifndef STARFLEET_COMMAND_GAMESCENE_HPP
#define STARFLEET_COMMAND_GAMESCENE_HPP
#include "../Scene.hpp"
#include "../../Player/Fleet.hpp"
#include "../../Ships/Starship.hpp"
#include "../../Crosshair.hpp"
#include "../../Cursor.hpp"
#include "../../Enemy.hpp"
#include "../../Player/Player.h"
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
    bool InitBackground();
    bool InitCommandButtons();
    void InitPlayerFlagship();
    void InitEnemyFlagship();
    void InitView();
    void CreateDistribution(const std::string& name, int min, int max);
    void UpdateDistribution(const std::string& name, int min, int max);
    static std::mt19937 GetEngine();

    // Utility
    Chilli::Cursor _cursor;
    Chilli::Colours _predefinedColours;

    // Ui
    //Crosshair crosshair;
    std::vector<std::unique_ptr<Button>> _command_buttons;
    std::vector<sf::Text> _ship_cost_text;
    sf::Text _credits_text;

    // Sprites
    Player _player;
    Enemy _enemy;

    // Other
    sf::View _player_view{};
    sf::Texture _background_texture;
    sf::Sprite _background_sprite;
    int _selected_ship;
    std::mt19937 generator;
    std::vector<std::uniform_int_distribution<int>> uint_distrib;
    std::map<std::string, int> dist_code;

};

#endif //STARFLEET_COMMAND_GAMESCENE_HPP
