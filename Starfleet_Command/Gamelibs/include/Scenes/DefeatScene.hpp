#ifndef STARFLEET_COMMAND_DEFEATSCENE_HPP
#define STARFLEET_COMMAND_DEFEATSCENE_HPP
#include "Scenes/Scene.hpp"
#include "Utility/Cursor.hpp"

class DefeatScene : public Scene
{
public:
    DefeatScene() = default;
    ~DefeatScene() override;
    bool Init() override;
    void EventHandler(sf::RenderWindow &window, sf::Event &event) override;
    void Update(sf::RenderWindow &window, sf::Time deltaTime) override;
    void Render(sf::RenderWindow &window) override;

private:
    void InitView();
    bool InitBackground();
    void InitLoseText();
    void InitButtonPanels();
    bool InitMusic();

    Chilli::Cursor _cursor;

    sf::View _worldView{};

    static const int PLAY_BUTTON = 0;
    static const int MENU_BUTTON = 1;
    static const int NUM_OF_BUTTONS = 2;
    std::array<Panel, NUM_OF_BUTTONS> _buttonPanels;

    sf::Text _loseTitleText;
    sf::Text _loseSubHeadingText;

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

    sf::Music _loseMusic;
};

#endif //STARFLEET_COMMAND_DEFEATSCENE_HPP
