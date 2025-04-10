#ifndef STARFLEET_COMMAND_SCENE_HPP
#define STARFLEET_COMMAND_SCENE_HPP
#include <SFML/Graphics.hpp>
#include "Utility/Constants.hpp"
#include "Utility/PredefinedColours.hpp"
#include "Sprites/UI/Panel.hpp"
#include "Utility/CustomFonts.hpp"
#include "../Utility/CustomFonts.hpp"
#include <SFML/Audio.hpp>

class Scene
{
 public:
    enum class ID
    {
        MENU = 0,
        OPTIONS = 1,
        GAME = 2,
        WIN = 3,
        LOSE = 4
    };

    virtual ~Scene()  = default;

    // Pure virtual functions
    virtual bool Init() = 0;
    virtual void EventHandler(sf::RenderWindow& window, sf::Event& event)  = 0;
    virtual void Update(sf::RenderWindow &window, sf::Time deltaTime)  = 0;
    virtual void Render(sf::RenderWindow& window)  = 0;

    void SetScene(Scene::ID scene) { scene_id = scene; }
    [[nodiscard]] ID GetScene() const { return scene_id; }

    void SetPaused(bool paused) { _isPaused = paused; }
    bool IsPaused() const { return _isPaused; }

private:
    ID scene_id{};
    bool _isPaused = false;
};


#endif //STARFLEET_COMMAND_SCENE_HPP
