#ifndef STARFLEET_COMMAND_SHIPYARDSCENE_HPP
#define STARFLEET_COMMAND_SHIPYARDSCENE_HPP
#include "../Scene.hpp"

class ShipyardScene : public Scene
{
 public:
    ShipyardScene() = default;
    ~ShipyardScene() override = default;

    bool init() override;
    void eventHandler(sf::RenderWindow& window, sf::Event& event) override;
    void update(sf::RenderWindow &window, sf::Time deltaTime) override;
    void render(sf::RenderWindow& window) override;

 private:
    bool initBackground();
    bool initMenuTitleIcon();
    void initTitleText();
    void initPanels();

    static const int SHIP_CARDS = 4;
    static const int PLAY_BUTTON = 5;

    Constants utility;
    std::array<Panel, 5> panels;
    std::array<std::string, 4> button_text;
    std::array<int, 4> ship_count;

    sf::Texture background_texture;
    sf::Texture ship_img_texture;

    sf::Sprite background_sprite;
    sf::Sprite ship_img_sprite;

    sf::Text shipyard_title;
};

#endif //STARFLEET_COMMAND_SHIPYARDSCENE_HPP
