#ifndef STARFLEET_COMMAND_SCENE_HPP
#define STARFLEET_COMMAND_SCENE_HPP
#include <SFML/Graphics.hpp>
#include "../Utility/Constants.hpp"
#include "../GameUI/Panel.hpp"

class Scene
{
 public:
    Scene();
    virtual ~Scene() = default;

    enum class ID
    {
        MENU = 0,
        OPTIONS,
        SHIPYARD,
        GAME,
        WIN,
        LOSE
    };

    // Pure virtual functions
    virtual bool init()                                                     = 0;
    virtual void eventHandler(sf::RenderWindow& window, sf::Event& event)   = 0;
    virtual void update(sf::RenderWindow &window, sf::Time deltaTime)       = 0;
    virtual void render(sf::RenderWindow& window)                           = 0;

    void setScene(Scene::ID scene) { scene_id = scene; }
    [[nodiscard]] ID getScene() const { return scene_id; }

    sf::Font& getRegularFont() { return game_font_r; };
    sf::Font& getBoldFont() { return game_font_b; };

 private:
    bool loadFont();
    ID scene_id{};
    sf::Font game_font_r;
    sf::Font game_font_b;
};


#endif //STARFLEET_COMMAND_SCENE_HPP
