#ifndef STARFLEET_COMMAND_TESTSCENE_HPP
#define STARFLEET_COMMAND_TESTSCENE_HPP
#include "../Scene.hpp"
#include "../../Player/Fleet.hpp"
#include "../../Ships/Starship.hpp"
#include "../../Crosshair.hpp"
#include "../../Cursor.hpp"
#include "../../Enemy.hpp"
#include "../../Player/Player1.h"

class TestScene : public Scene
{
public:
    TestScene() = default;
    ~TestScene() override = default;

    bool Init() override;
    void EventHandler(sf::RenderWindow& window, sf::Event& event) override;
    void Update(sf::RenderWindow &window, sf::Time deltaTime) override;
    void Render(sf::RenderWindow& window) override;

private:
    bool InitBackground();
    void InitView();

    Player1 _player;
    Enemy _enemy;
    Chilli::Cursor cursor;
    sf::View player_view{};
    sf::Texture background_texture;
    sf::Sprite background_sprite;
};

#endif //STARFLEET_COMMAND_TESTSCENE_HPP
