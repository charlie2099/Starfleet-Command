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
    bool initMenuTitleIcon();

    static const int BUTTONS = 3;
    static const int LEADERBOARD = 4;
    static const int TITLE_PANEL = 5;

    Constants utility;
    std::array<Panel, 5> panels;

    sf::Texture background_texture;
    sf::Sprite background_sprite;

    sf::Texture menu_title_img_texture;
    sf::Sprite menu_title_img_sprite;

    std::array<std::string, 3> button_text;
};
#endif //STARFLEET_COMMAND_MENUSCENE_HPP
