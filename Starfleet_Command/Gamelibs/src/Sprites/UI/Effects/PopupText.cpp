#include "Sprites/UI/Effects/PopupText.hpp"

PopupText::PopupText(int value, sf::Vector2f pos)
{
    InitFont();
    _text.setString(std::to_string(value));
    _text.setFont(_font);
    _text.setCharacterSize(12.5F);

    _generator = GetEngine();
    std::uniform_int_distribution<int> dist_x {static_cast<int>(pos.x-30.0F),static_cast<int>(pos.x+30.0F)};
    int randXPos = dist_x(_generator);
    _text.setPosition(randXPos, pos.y);
}

void PopupText::Update(sf::RenderWindow& window, sf::Time deltaTime)
{
    _color = _text.getFillColor();
    _timePassed += 1.0f * deltaTime.asSeconds();

    float moveSpeed = 25.0f;
    _text.setPosition(_text.getPosition().x, _text.getPosition().y - moveSpeed * deltaTime.asSeconds());

    if(_color.a > 0 /*&& _timePassed > 3*/)
    {
        float disappearSpeed = 10;
        _text.setFillColor(sf::Color(_color.r, _color.g, _color.b, _color.a - disappearSpeed * deltaTime.asSeconds()));
    }
    else
    {
        _isFaded = true;
    }

    if(_isIconEnabled)
    {
        _iconSprite.setPosition(_text.getPosition().x - _iconSprite.getGlobalBounds().width - 3.0F, _text.getPosition().y + 3.5F);
    }
}

void PopupText::Render(sf::RenderWindow &window)
{
    window.draw(_text);
    if(_isIconEnabled)
    {
        window.draw(_iconSprite);
    }
}

bool PopupText::InitFont()
{
    if(!_font.loadFromFile("Resources/Fonts/Orbitron/Orbitron-Regular.ttf"))
    {
        return false;
    }

    return true;
}

std::mt19937 PopupText::GetEngine()
{
    std::random_device eng;
    std::mt19937 generator(eng());
    unsigned long int time = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    generator.seed(time);
    return generator;
}

void PopupText::SetColour(sf::Color color)
{
    _text.setFillColor(color);
}

void PopupText::SetCharSize(int size)
{
    _text.setCharacterSize(size);
    _text.setStyle(sf::Text::Style::Bold);
}

void PopupText::SetIconImage(const std::string& iconImageFileName)
{
    _isIconEnabled = true;

    // NOTE: Create a private Sprite object and load the image through that? Only render sprite if _isIconEnabled = true. Set its position to be left of popup value.

    if(!_iconTexture.loadFromFile(iconImageFileName))
    {
        std::cout << "Failed to load popup effect icon image file" << std::endl;
    }
    //_iconTexture.loadFromFile(iconImageFileName);
    _iconSprite.setTexture(_iconTexture);
    _iconSprite.scale(1, 1);
}
