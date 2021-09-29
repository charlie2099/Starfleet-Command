#ifndef STARFLEET_COMMAND_MENUSCENE_HPP
#define STARFLEET_COMMAND_MENUSCENE_HPP
#include "../Scene.hpp"
#include "../../Ships/Starship.hpp"
#include "../../Crosshair.hpp"
#include "../../Temporary/TestPlayer.hpp"
#include <random>

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
    static std::mt19937 getEngine();
    bool initBackground();
    void initButtonPanels();
    void initLeaderboardPanel();
    void initTitlePanel();
    bool initMenuTitleIcon();
    void initBackgroundShips(std::mt19937 &generator);
    bool comfortableBoundsCheck(sf::Vector2<float> mouse_vec, sf::FloatRect sprite_bounds);
    void createDistribution(const std::string& name, int min, int max);

    static const int PLAY_BUTTON = 0;
    static const int OPTIONS_BUTTON = 1;
    static const int EXIT_BUTTON = 2;
    static const int BUTTONS = 3;
    static const int LEADERBOARD = 4;
    static const int TITLE_PANEL = 5;
    static const int BACKGROUND_SHIPS = 16;

    int SELECTED_SHIP = 0;

    //TestPlayer test_player;
    Crosshair crosshair;
    std::array<Panel, 5> panels;
    std::vector<std::unique_ptr<Starship>> starship;
    std::vector<int> starship_speed_vec;
    std::vector<std::uniform_int_distribution<int>> uint_distrib;

    sf::Texture background_texture;
    sf::Texture menu_title_img_texture;

    sf::Sprite background_sprite;
    sf::Sprite menu_title_img_sprite;
};
#endif //STARFLEET_COMMAND_MENUSCENE_HPP
