#ifndef STARFLEET_COMMAND_GAMESCENE_HPP
#define STARFLEET_COMMAND_GAMESCENE_HPP
#include "../Scene.hpp"
#include "../../Player/Fleet.hpp"
#include "../../Ships/Starship.hpp"
#include "../../Player/Player.hpp"
#include "../../Crosshair.hpp"

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
    bool initBackground();
    void initPlayerStarships();
    void initView();
    void initCrosshair();
    bool comfortableBoundsCheck(sf::Vector2<float> mouse_vec, std::unique_ptr<Starship>& starship);

    int selected = 0;

    std::vector<std::unique_ptr<Projectile>> projectile{};

    Player player;
    Crosshair crosshair;
    sf::View player_view{};

    sf::Texture cursor_texture;
    sf::Sprite cursor_sprite;

    sf::Texture background_texture;
    sf::Sprite background_sprite;
};

#endif //STARFLEET_COMMAND_GAMESCENE_HPP
