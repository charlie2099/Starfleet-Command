#ifndef STARFLEET_COMMAND_BUTTON_HPP
#define STARFLEET_COMMAND_BUTTON_HPP
#include <SFML/Graphics.hpp>

class Button
{
 public:
    explicit Button(const std::string& filepath);
    ~Button() = default;
    void render(sf::RenderWindow& window);

 private:
    bool initTexture(const std::string& filepath);

    sf::Texture texture;
    sf::Sprite sprite;
};

#endif //STARFLEET_COMMAND_BUTTON_HPP
