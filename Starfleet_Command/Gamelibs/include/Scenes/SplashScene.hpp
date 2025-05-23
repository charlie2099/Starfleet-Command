#ifndef STARFLEET_COMMAND_SPLASHSCENE_HPP
#define STARFLEET_COMMAND_SPLASHSCENE_HPP
#include "Scenes/Scene.hpp"
#include "Utility/Cursor.hpp"

class SplashScene : public Scene
{
public:
    SplashScene() = default;
    ~SplashScene() override;

    bool Init() override;
    void EventHandler(sf::RenderWindow& window, sf::Event& event) override;
    void Update(sf::RenderWindow &window, sf::Time deltaTime) override;
    void Render(sf::RenderWindow& window) override;

private:
    void InitView();
    bool InitBackground();

    // Utility
    Chilli::Cursor _cursor;

    // Other
    sf::View _player_view{};
    sf::Texture _background_texture;
    sf::Sprite _background_sprite;
};

#endif //STARFLEET_COMMAND_SPLASHSCENE_HPP
