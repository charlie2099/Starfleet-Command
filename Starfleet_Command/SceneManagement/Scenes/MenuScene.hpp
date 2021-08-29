#ifndef STARFLEET_COMMAND_MENUSCENE_HPP
#define STARFLEET_COMMAND_MENUSCENE_HPP
#include "../Scene.hpp"

class MenuScene : public Scene
{
 public:
    MenuScene() = default;
    ~MenuScene() override = default;

    bool init() override;
    void eventHandler(sf::RenderWindow& window, sf::Event& event) override;
    void update(sf::RenderWindow &window, sf::Time deltaTime) override;
    void render(sf::RenderWindow& window) override;

 private:
    bool initBackground();

    sf::Texture background_texture;
    sf::Sprite background_sprite;

};
#endif //STARFLEET_COMMAND_MENUSCENE_HPP
