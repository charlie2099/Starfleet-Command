#ifndef STARFLEET_COMMAND_GAMESCENE_HPP
#define STARFLEET_COMMAND_GAMESCENE_HPP
#include "../Scene.hpp"
#include "../../Player/Fleet.hpp"
#include "../../SpriteComponent.hpp"

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
    bool comfortableBoundsCheck(sf::Vector2<float> mouse_vec, sf::FloatRect sprite_bounds);

    //Fleet player_fleet;
    //std::vector<Starship> ships
    //std::vector<LightFighter> light_fighter

    SpriteComponent spriteComponent;
    SpriteComponent spriteComponent2;

    sf::Texture background_texture;

    sf::Sprite background_sprite;
};

#endif //STARFLEET_COMMAND_GAMESCENE_HPP
