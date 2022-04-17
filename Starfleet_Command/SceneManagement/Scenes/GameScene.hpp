#ifndef STARFLEET_COMMAND_GAMESCENE_HPP
#define STARFLEET_COMMAND_GAMESCENE_HPP
#include "../Scene.hpp"
#include "../../Player/Fleet.hpp"
#include "../../Ships/Starship.hpp"
#include "../../Player/Player.hpp"
#include "../../Crosshair.hpp"
#include "../../GameUI/CommandMenu.hpp"

class GameScene : public Scene
{
 public:
    GameScene() = default;
    ~GameScene() override = default;

    bool init() override;
    void eventHandler(sf::RenderWindow& window, sf::Event& event) override;
    void update(sf::RenderWindow &window, sf::Time deltaTime) override;
    void render(sf::RenderWindow& window) override;

 private:
    bool initBackground();
    void initPlayerStarships();
    void initView();
    void initCrosshair();
    bool comfortableBoundsCheck(sf::Vector2<float> mouse_vec, std::unique_ptr<Starship>& starship);

    int selected = 0;
    bool clicked = false;
    //sf::Vector2<float> clicked_pos;
    //bool moveTo = false;

    //std::vector<std::unique_ptr<Projectile>> projectile{};

    sf::View player_view{};

    //CommandMenu command_menu;
    Player player;
    Crosshair crosshair;

    /// cursor class?
    sf::Texture cursor_texture;
    sf::Sprite cursor_sprite;

    /// background class?
    sf::Texture background_texture;
    sf::Sprite background_sprite;
};

#endif //STARFLEET_COMMAND_GAMESCENE_HPP
