#ifndef STARFLEET_COMMAND_POPUPTEXT_HPP
#define STARFLEET_COMMAND_POPUPTEXT_HPP
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <random>
#include <chrono>
#include <iostream>
#include <SFML/Graphics/Sprite.hpp>

class PopupText
{
public:
    PopupText(int value, sf::Vector2f pos);
    ~PopupText() = default;
    void Update(sf::RenderWindow& window, sf::Time deltaTime);
    void Render(sf::RenderWindow& window);
    bool IsFaded() const { return _isFaded; }
    void SetColour(sf::Color color);
    void SetCharSize(int size);
    void SetIconImage(const std::string& iconImageFileName);
    void SetText(const std::string& text);

private:
    bool InitFont();
    static std::mt19937 GetEngine();
    std::mt19937 _generator;
    sf::Text _text;
    sf::Color _color;
    sf::Font _font;
    sf::Texture _iconTexture;
    sf::Sprite _iconSprite;
    int _popupValue;
    float _timePassed = 0;
    bool _isFaded = false;
    bool _isIconEnabled = false;
};

#endif //STARFLEET_COMMAND_POPUPTEXT_HPP
