#include "Sprites/UI/Effects/UIPopUpEffect.hpp"

UIPopUpEffect::UIPopUpEffect(int value, sf::Vector2f pos)
{
    InitFont();
    text.setString(std::to_string(value));
    text.setFont(font);
    text.setCharacterSize(12.5f);

    generator = GetEngine();
    std::uniform_int_distribution<int> dist_x {static_cast<int>(pos.x-30),static_cast<int>(pos.x+30)};
    int rand_xPos = dist_x(generator);
    text.setPosition(rand_xPos, pos.y);
}

void UIPopUpEffect::Update(sf::RenderWindow& window, sf::Time deltaTime)
{
    _color = text.getFillColor();
    m_timePassed += 1.0f * deltaTime.asSeconds();
    //std::cout << "Time passed: " << m_timePassed << std::endl;

    float moveSpeed = 25.0f;
    text.setPosition(text.getPosition().x, text.getPosition().y - moveSpeed * deltaTime.asSeconds());

    if(_color.a > 0 /*&& m_timePassed > 3*/)
    {
        float disappearSpeed = 10;
        text.setFillColor(sf::Color(_color.r, _color.g, _color.b, _color.a - disappearSpeed * deltaTime.asSeconds()));
    }
    else
    {
        _isFaded = true;
    }

    if(_isIconEnabled)
    {
        _iconSprite.setPosition(text.getPosition().x - _iconSprite.getGlobalBounds().width - 3.0F, text.getPosition().y + 3.5F);
    }
}

void UIPopUpEffect::Render(sf::RenderWindow &window)
{
    window.draw(text);
    if(_isIconEnabled)
    {
        window.draw(_iconSprite);
    }
}

bool UIPopUpEffect::InitFont()
{
    if(!font.loadFromFile("Resources/Fonts/Orbitron/Orbitron-Regular.ttf"))
    {
        return false;
    }

    return true;
}

std::mt19937 UIPopUpEffect::GetEngine()
{
    std::random_device eng;
    std::mt19937 generator(eng());
    unsigned long int time = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    generator.seed(time);
    return generator;
}

void UIPopUpEffect::SetColour(sf::Color color)
{
    text.setFillColor(color);
}

void UIPopUpEffect::SetCharSize(int size)
{
    text.setCharacterSize(size);
    text.setStyle(sf::Text::Style::Bold);
}

void UIPopUpEffect::SetIconImage(const std::string& iconImageFileName)
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
