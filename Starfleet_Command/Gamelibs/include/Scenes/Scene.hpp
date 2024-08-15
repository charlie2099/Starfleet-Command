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
        TUTORIAL = 2,
        OPTIONS = 3,
        GAME = 4,
        WIN = 5,
        LOSE = 6
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
