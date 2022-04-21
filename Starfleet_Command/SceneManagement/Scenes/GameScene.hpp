#ifndef STARFLEET_COMMAND_GAMESCENE_HPP
#define STARFLEET_COMMAND_GAMESCENE_HPP
#include "../Scene.hpp"
#include "../../Player/Fleet.hpp"
#include "../../Ships/Starship.hpp"
#include "../../Crosshair.hpp"
#include "../../Cursor.hpp"
#include "../../Enemy.hpp"
#include "../../Player/Player.h"

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

    // Utility
    Chilli::Cursor _cursor;
    Chilli::Colours _predefinedColours;

    // Ui
    sf::Texture _command_button_1_texture;
    sf::Sprite _command_button_1_sprite;
    //Panel _panel;

    // Sprites
    Player _player;
    Enemy _enemy;

    // Other
    sf::View _player_view{};
    sf::Texture _background_texture;
    sf::Sprite _background_sprite;

    bool is_hovered_over = false;
};

#endif //STARFLEET_COMMAND_GAMESCENE_HPP
