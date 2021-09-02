#ifndef STARFLEET_COMMAND_MENUSCENE_HPP
#define STARFLEET_COMMAND_MENUSCENE_HPP
#include "../Scene.hpp"
#include "../../Utility/Constants.hpp"
#include "../../GameUI/Panel.hpp"

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
    std::array<Panel, 4> panels;

    sf::Texture background_texture;
    sf::Sprite background_sprite;

    sf::Texture title_box_texture;
    sf::RectangleShape title_box;

    sf::Texture menu_title_img_texture;
    sf::Sprite menu_title_img_sprite;
    sf::Text menu_title;

    std::array<std::string, 3> button_text;
    static const int BUTTONS = 3;
    static const int LEADERBOARD = 4;
};
#endif //STARFLEET_COMMAND_MENUSCENE_HPP
