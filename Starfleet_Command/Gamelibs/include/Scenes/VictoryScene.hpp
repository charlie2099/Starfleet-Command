#ifndef STARFLEET_COMMAND_VICTORYSCENE_HPP
#define STARFLEET_COMMAND_VICTORYSCENE_HPP
#include "Scenes/Scene.hpp"
#include "Sprites/UI/ParallaxBackground.hpp"
#include "Utility/Cursor.hpp"

class VictoryScene : public Scene
{
public:
    VictoryScene() = default;
    ~VictoryScene() override;
    bool Init() override;
    void EventHandler(sf::RenderWindow &window, sf::Event &event) override;
    void Update(sf::RenderWindow &window, sf::Time deltaTime) override;
    void Render(sf::RenderWindow &window) override;

private:
    void InitView();
    bool InitBackground();
    void InitWinText();
    void InitButtons();
    bool InitMusic();

    Chilli::Cursor _cursor;

    sf::View _worldView{};

    static const int PLAY_BUTTON = 0;
    static const int MENU_BUTTON = 1;
    static const int NUM_OF_BUTTONS = 2;
    std::array<TextButton, NUM_OF_BUTTONS> _buttons;

    sf::Text _winTitleText;
    sf::Text _winSubHeadingText;

    std::unique_ptr<ParallaxBackground> _backgroundParallax;

    sf::Music _winMusic;

    const std::string TEXTURES_DIR_PATH = "Resources/Textures/";
};

#endif //STARFLEET_COMMAND_VICTORYSCENE_HPP
