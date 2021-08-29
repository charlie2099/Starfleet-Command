#ifndef STARFLEET_COMMAND_MENUSCENE_HPP
#define STARFLEET_COMMAND_MENUSCENE_HPP
#include "../Scene.hpp"
#include "../../Utility/Constants.hpp"

class MenuScene : public Scene
{
 public:
    MenuScene() = default;
    ~MenuScene() override = default;

    bool init() override;
    void eventHandler(sf::RenderWindow& window, sf::Event& event) override;
    void update(sf::RenderWindow &window, sf::Time deltaTime) override;
    void render(sf::RenderWindow& window) override;

 private:
    bool initBackground();
    bool initMenuTitle();

    Constants utility;

    sf::Texture background_texture;
    sf::Sprite background_sprite;

    sf::Texture panel_texture;
    sf::RectangleShape panel;

    sf::Texture menu_title_img_texture;
    sf::Sprite menu_title_img_sprite;
    sf::Text menu_title;
};
#endif //STARFLEET_COMMAND_MENUSCENE_HPP
