#ifndef STARFLEET_COMMAND_SCENE_HPP
#define STARFLEET_COMMAND_SCENE_HPP
#include <SFML/Graphics.hpp>
#include "Utility/Constants.hpp"
#include "Utility/PredefinedColours.hpp"
#include "Sprites/UI/Panel.hpp"

class Scene
{
 public:
    Scene();
    virtual ~Scene() = default;

    enum class ID
    {
        MENU = 0,
        OPTIONS = 1,
        GAME = 2,
        WIN = 3,
        LOSE = 4
    };

    // Pure virtual functions
    virtual bool Init() = 0;
    virtual void EventHandler(sf::RenderWindow& window, sf::Event& event)  = 0;
    virtual void Update(sf::RenderWindow &window, sf::Time deltaTime)  = 0;
    virtual void Render(sf::RenderWindow& window)  = 0;

    void SetScene(Scene::ID scene) { scene_id = scene; }
    [[nodiscard]] ID GetScene() const { return scene_id; }

    sf::Font& GetRegularFont() { return game_font_r; };
    sf::Font& GetBoldFont() { return game_font_b; };

 private:
    bool LoadFont();
    ID scene_id{};
    sf::Font game_font_r;
    sf::Font game_font_b;
};


#endif //STARFLEET_COMMAND_SCENE_HPP
