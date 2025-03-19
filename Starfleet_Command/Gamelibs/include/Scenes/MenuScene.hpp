#ifndef STARFLEET_COMMAND_MENUSCENE_HPP
#define STARFLEET_COMMAND_MENUSCENE_HPP
#include "Scenes/Scene.hpp"
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
    ~MenuScene() override;

    bool Init() override;
    void EventHandler(sf::RenderWindow& window, sf::Event& event) override;
    void Update(sf::RenderWindow &window, sf::Time deltaTime) override;
    void Render(sf::RenderWindow& window) override;

 private:
    static std::mt19937 GetEngine();
    void InitView();
    bool InitBackground();
    void InitButtonPanels();
    bool InitMenuTitleIcon();
    void InitBackgroundShips(std::mt19937 &generator);
    void InitGameVersionText();
    void CreateDistribution(const std::string& name, int min, int max);

    static const int PLAY_BUTTON = 0;
    static const int OPTIONS_BUTTON = 1;
    static const int EXIT_BUTTON = 2;
    static const int NUM_OF_BUTTONS = 3;
    static const int BACKGROUND_SHIPS = 16;

    sf::View _worldView{};
    Chilli::Cursor _cursor;
    Chilli::PredefinedColours _predefinedColours;
    std::array<Panel, NUM_OF_BUTTONS> _panels;
    std::vector<std::unique_ptr<IStarship>> _starship;
    std::vector<std::uniform_int_distribution<int>> _distributions;

    sf::Sprite _backgroundSprite;
    sf::Texture _backgroundTexture;

    struct ParallaxStar
    {
        sf::CircleShape circleShape;
        sf::Vector2f position;
        float speed{};
        float size{};
    };
    std::vector<ParallaxStar> _parallaxStars;
    const int NUM_OF_STARS = 300;

    sf::Sprite _menuTitleImgSprite;
    sf::Texture _menuTitleImgTexture;

    sf::Text _gameVersionText;

    sf::Music _menuMusic;
};
#endif //STARFLEET_COMMAND_MENUSCENE_HPP
