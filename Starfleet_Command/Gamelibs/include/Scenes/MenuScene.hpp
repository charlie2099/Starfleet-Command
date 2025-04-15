#ifndef STARFLEET_COMMAND_MENUSCENE_HPP
#define STARFLEET_COMMAND_MENUSCENE_HPP
#include "Scenes/Scene.hpp"
#include "Utility/Cursor.hpp"
#include "Utility/Vector.hpp"
#include "Interfaces/IStarship.hpp"
#include "Sprites/Starships/StarshipFactory.hpp"
#include "Utility/RNG.hpp"
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
    void InitView();
    bool InitBackground();
    void InitButtonPanels();
    bool InitMenuTitleIcon();
    void InitBackgroundShips();
    void InitGameVersionText();

    static const int PLAY_BUTTON = 0;
    static const int OPTIONS_BUTTON = 1;
    static const int EXIT_BUTTON = 2;
    static const int BACK_BUTTON = 3;
    static const int NUM_OF_BUTTONS = 4;
    static const int BACKGROUND_SHIPS = 16;

    sf::View _worldView{};
    Chilli::Cursor _cursor;
    Chilli::PredefinedColours _predefinedColours;
    std::array<Panel, NUM_OF_BUTTONS> _buttonPanels;
    std::vector<std::unique_ptr<IStarship>> _starship;

    ///TODO: Replace with ParallaxBackground class
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
    sf::Texture _backgroundPlayerPlanetTexture;
    sf::Sprite _backgroundPlayerPlanetSprite;
    sf::Texture _backgroundEnemyPlanetTexture;
    sf::Sprite _backgroundEnemyPlanetSprite;

    sf::Sprite _menuTitleImgSprite;
    sf::Texture _menuTitleImgTexture;

    /// Game Settings
    bool _isGameSettingsEnabled = false;
    sf::RectangleShape _gameSettingsOverlayWindow;
    sf::Text _gameSettingsTitleText;

    const static int NUM_OF_SETTINGS_ELEMENTS = 6;
    /*enum SettingsType
    {
        TOGGLE,
        COLOUR_PICKER
    };*/
    struct SettingsElement
    {
        sf::Text nameText;
        sf::Text statusText;
        bool isEnabled{};
        //SettingsType type;
    };
    std::array<SettingsElement, NUM_OF_SETTINGS_ELEMENTS> _gameSettingsMenuElements;
    std::array<sf::Sprite, NUM_OF_SETTINGS_ELEMENTS> _gameSettingsLeftArrowSprite;
    std::array<sf::Sprite, NUM_OF_SETTINGS_ELEMENTS> _gameSettingsRightArrowSprite;
    sf::Texture _gameSettingsLeftArrowTexture;
    sf::Texture _gameSettingsRightArrowTexture;

    /// Game Version
    sf::Text _gameVersionText;

    /// Music
    sf::Music _menuMusic;
    std::array<std::unique_ptr<Button>, 2> _musicIconButtons;
    bool _isMusicOn = false;
    static const int MUSIC_ON_BUTTON = 0;
    static const int MUSIC_OFF_BUTTON = 1;
};
#endif //STARFLEET_COMMAND_MENUSCENE_HPP
