#ifndef STARFLEET_COMMAND_MENUSCENE_HPP
#define STARFLEET_COMMAND_MENUSCENE_HPP
#include "Scenes/Scene.hpp"
#include "Sprites/UI/Crosshair.hpp"
#include "Utility/Cursor.hpp"
#include "Utility/Vector.hpp"
#include "Interfaces/IStarship.hpp"
#include "Sprites/Starships/StarshipFactory.hpp"
#include <random>
#include <chrono>

class MenuScene : public Scene
{
 public:
    MenuScene() = default;
    ~MenuScene() override = default;

    bool Init() override;
    void EventHandler(sf::RenderWindow& window, sf::Event& event) override;
    void Update(sf::RenderWindow &window, sf::Time deltaTime) override;
    void Render(sf::RenderWindow& window) override;

 private:
    static std::mt19937 GetEngine();
    void InitView();
    bool InitBackground();
    void InitButtonPanels();
    void InitLeaderboardPanel();
    void InitTitlePanel();
    bool InitMenuTitleIcon();
    void InitBackgroundShips(std::mt19937 &generator);
    void CreateDistribution(const std::string& name, int min, int max);

    static const int PLAY_BUTTON = 0;
    static const int OPTIONS_BUTTON = 1;
    static const int EXIT_BUTTON = 2;
    static const int BUTTONS = 3;
    static const int LEADERBOARD = 4;
    static const int TITLE_PANEL = 5;
    static const int BACKGROUND_SHIPS = 16;

    int SELECTED_SHIP = 0;

    sf::View _worldView{};
    Chilli::Cursor cursor;
    Chilli::Colours _predefinedColours;
    //Crosshair crosshair;
    std::array<Panel, 5> panels;
    std::vector<std::unique_ptr<IStarship>> starship;
    std::vector<std::uniform_int_distribution<int>> uint_distrib;

    sf::Texture background_texture;
    sf::Texture menu_title_img_texture;

    sf::Sprite background_sprite;
    sf::Sprite menu_title_img_sprite;
};
#endif //STARFLEET_COMMAND_MENUSCENE_HPP
