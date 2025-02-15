#ifndef STARFLEET_COMMAND_UIPOPUPEFFECT_HPP
#define STARFLEET_COMMAND_UIPOPUPEFFECT_HPP
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <random>
#include <chrono>
#include <iostream>
#include <SFML/Graphics/Sprite.hpp>

class UIPopUpEffect
{
public:
    UIPopUpEffect(int value, sf::Vector2f pos);
    ~UIPopUpEffect() = default;
    void Update(sf::RenderWindow& window, sf::Time deltaTime);
    void Render(sf::RenderWindow& window);
    bool IsFaded() const { return _isFaded; };
    void SetColour(sf::Color color);
    void SetCharSize(int size);
    void SetIconImage(const std::string& iconImageFileName);

private:
    bool InitFont();
    static std::mt19937 GetEngine();
    std::mt19937 generator;
    sf::Text text;
    sf::Color _color;
    sf::Font font;
    sf::Texture _iconTexture;
    sf::Sprite _iconSprite;
    float m_timePassed = 0;
    bool _isFaded = false;
    bool _isIconEnabled = false;
};

#endif //STARFLEET_COMMAND_UIPOPUPEFFECT_HPP
