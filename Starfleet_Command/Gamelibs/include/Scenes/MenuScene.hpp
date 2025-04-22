#ifndef STARFLEET_COMMAND_MENUSCENE_HPP
#define STARFLEET_COMMAND_MENUSCENE_HPP
#include "Scenes/Scene.hpp"
#include "Utility/Cursor.hpp"
#include "Utility/Vector.hpp"
#include "Utility/JsonSaveSystem.hpp"
#include "Utility/JsonColourMapping.hpp"
#include "Utility/RNG.hpp"
#include "Interfaces/IStarship.hpp"
#include "../../GameSettings.hpp"
#include "Sprites/Player/Player.hpp"
#include "Sprites/Enemy/Enemy.hpp"
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
    void InitGameSettings();
    bool InitMenuMusic();
    void InitEvents();
    void HandleGameSettingsEvents(sf::RenderWindow &window, sf::Event &event);
    void HandleButtonEvents(sf::RenderWindow &window, sf::Event &event);
    void UpdateBackgroundStarshipsMovement(sf::RenderWindow &window, sf::Time &deltaTime);
    void SaveGameSettingsData_OnSettingsUpdated();

    const int PLAY_BUTTON = 0;
    const int OPTIONS_BUTTON = 1;
    const int EXIT_BUTTON = 2;
    const int BACK_BUTTON = 3;
    static const int NUM_OF_BUTTONS = 4;
    const int NUM_OF_SHIPS_PER_TEAM = 8;

    sf::View _worldView{};
    Chilli::Cursor _cursor;
    std::array<Panel, NUM_OF_BUTTONS> _buttonPanels;
    std::unique_ptr<Player> _player;
    std::unique_ptr<Enemy> _enemy;

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
    sf::Texture _backgroundEnemyPlanetTexture;
    sf::Sprite _backgroundEnemyPlanetSprite;
    sf::Texture _backgroundPlayerPlanetTexture;
    sf::Sprite _backgroundPlayerPlanetSprite;

    sf::Sprite _menuTitleImgSprite;
    sf::Texture _menuTitleImgTexture;

    /// Game Settings
    std::unique_ptr<GameSettings> _gameSettings;
    bool _isGameSettingsEnabled = false;
    const std::string SETTINGS_FILE_PATH = "Resources/Data/GameSettings.json";

    /// Game Version
    sf::Text _gameVersionText;

    /// Music
    sf::Music _menuMusic;
    bool _isMusicOn = false;
};
#endif //STARFLEET_COMMAND_MENUSCENE_HPP
