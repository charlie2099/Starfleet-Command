#include "Scenes/VictoryScene.hpp"

VictoryScene::~VictoryScene()
{
    _winMusic.stop();
}

bool VictoryScene::Init()
{
    InitView();
    InitBackground();
    InitWinText();
    InitButtonPanels();
    InitMusic();

    return true;
}

void VictoryScene::EventHandler(sf::RenderWindow &window, sf::Event &event)
{
    for (int i = 0; i < NUM_OF_BUTTONS; ++i)
    {
        _buttonPanels[i].EventHandler(window, event);
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if(_buttonPanels[PLAY_BUTTON].IsClicked())
        {
            SetScene(Scene::ID::GAME);
        }
        else if(_buttonPanels[MENU_BUTTON].IsClicked())
        {
            SetScene(Scene::ID::MENU);
        }
    }
}

void VictoryScene::Update(sf::RenderWindow &window, sf::Time deltaTime)
{
    _cursor.Update(window, deltaTime);
    _cursor.SetCursorPos(window, _worldView);

    for (int i = 0; i < NUM_OF_BUTTONS; ++i)
    {
        _buttonPanels[i].Update(window);
    }

    if(_buttonPanels[PLAY_BUTTON].IsHoveredOver())
    {
        _buttonPanels[PLAY_BUTTON].SetPanelColour(sf::Color(22, 155, 164, 65));
        _buttonPanels[PLAY_BUTTON].SetText(_buttonPanels[PLAY_BUTTON].GetText().getString(), sf::Color(22, 155, 164));
    }
    else if(_buttonPanels[MENU_BUTTON].IsHoveredOver())
    {
        _buttonPanels[MENU_BUTTON].SetPanelColour(sf::Color(22, 155, 164, 65));
        _buttonPanels[MENU_BUTTON].SetText(_buttonPanels[MENU_BUTTON].GetText().getString(), sf::Color(22, 155, 164));
    }

    for (int i = 0; i < NUM_OF_BUTTONS; i++)
    {
        if(!_buttonPanels[i].IsHoveredOver())
        {
            _buttonPanels[i].SetPanelColour(sf::Color(22, 155, 164, 100));
            _buttonPanels[i].SetText(_buttonPanels[i].GetText().getString(), sf::Color::White);
        }
    }

    _backgroundSprite.move(-25.0F * deltaTime.asSeconds(), 0);
    if(_backgroundSprite.getPosition().x + _backgroundSprite.getGlobalBounds().width/2.0F < 0)
    {
        _backgroundSprite.setPosition(0, 0);
    }

    for (auto& star : _parallaxStars)
    {
        star.position.x -= star.speed * 100.0F * deltaTime.asSeconds();
        star.circleShape.setPosition(star.position);
        if (star.position.x < 0)
        {
            star.position.x = Constants::WINDOW_WIDTH;
            star.position.y = std::rand() % (int)Constants::WINDOW_HEIGHT;
        }
    }
}

void VictoryScene::Render(sf::RenderWindow &window)
{
    window.setView(_worldView);
    window.draw(_backgroundSprite);
    for (auto& star : _parallaxStars)
    {
        window.draw(star.circleShape);
    }
    for (auto& buttonPanel : _buttonPanels)
    {
        buttonPanel.Render(window);
    }
    window.draw(_winTitleText);
    window.draw(_winSubHeadingText);
    _cursor.Render(window);
}

void VictoryScene::InitView()
{
    sf::Vector2f VIEW_SIZE = { Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT };
    sf::Vector2f WORLD_PERSPECTIVE = { Constants::WINDOW_WIDTH/2.0F, Constants::WINDOW_HEIGHT/2.0F };
    _worldView.setSize(VIEW_SIZE);
    _worldView.setCenter(WORLD_PERSPECTIVE);
}

bool VictoryScene::InitBackground()
{
    if (!_backgroundTexture.loadFromFile("Resources/Textures/space_nebula_2.png"))
    {
        return false;
    }
    _backgroundTexture.setRepeated(true);
    _backgroundSprite.setTexture(_backgroundTexture);
    _backgroundSprite.setTextureRect(sf::IntRect(0, 0, Constants::WINDOW_WIDTH * 2.0F, Constants::WINDOW_HEIGHT * 2.0F));
    _backgroundSprite.setColor(sf::Color::Green);

    // Initialize stars
    for (int i = 0; i < NUM_OF_STARS; ++i)
    {
        _parallaxStars.emplace_back();
        _parallaxStars[i].position = sf::Vector2f(std::rand() % (int)Constants::WINDOW_WIDTH, std::rand() % (int)Constants::WINDOW_HEIGHT);
        _parallaxStars[i].speed = 0.1f + static_cast<float>(std::rand() % 100) / 100.0f; // Speed between 0.1 and 1.0
        _parallaxStars[i].size = 0.5f + static_cast<float>(std::rand() % 2); // Size between 1 and 3
        _parallaxStars[i].circleShape.setRadius(_parallaxStars[i].size);
        _parallaxStars[i].circleShape.setFillColor(_predefinedColours.LIGHTGREEN);
    }

    return true;
}

void VictoryScene::InitWinText()
{
    _winTitleText.setFont(Chilli::CustomFonts::GetBoldFont());
    _winTitleText.setString("VICTORY");
    _winTitleText.setCharacterSize(42);
    _winTitleText.setFillColor(sf::Color::Green);
    _winTitleText.setOutlineColor(sf::Color::Black);
    _winTitleText.setOutlineThickness(1.0F);
    _winTitleText.setPosition(Constants::WINDOW_WIDTH / 2.0F - (_winTitleText.getGlobalBounds().width / 2.0F), Constants::WINDOW_HEIGHT / 2.0F - (_winTitleText.getGlobalBounds().height / 2.0F) - 40.0F);

    _winSubHeadingText.setFont(Chilli::CustomFonts::GetBoldFont());
    _winSubHeadingText.setString("Thank you for playing Starfleet Command.");
    _winSubHeadingText.setCharacterSize(18);
    _winSubHeadingText.setFillColor(sf::Color::White);
    _winSubHeadingText.setOutlineColor(sf::Color::Black);
    _winSubHeadingText.setOutlineThickness(1.0F);
    _winSubHeadingText.setPosition(_winTitleText.getPosition().x + _winTitleText.getGlobalBounds().width / 2.0F - _winSubHeadingText.getGlobalBounds().width / 2.0F, _winTitleText.getPosition().y + 65.0F);
}

void VictoryScene::InitButtonPanels()
{
    std::array<std::string, NUM_OF_BUTTONS> button_text
            {
                    "REMATCH",
                    "MAIN MENU"
            };

    for (int i = 0; i < NUM_OF_BUTTONS; ++i)
    {
        _buttonPanels[i].SetText(button_text[i]);
        _buttonPanels[i].SetTextSize(20);
        _buttonPanels[i].SetSize(25, 20);
        _buttonPanels[i].SetPanelColour(sf::Color(22, 155, 164, 100));
    }

    _buttonPanels[PLAY_BUTTON].SetPosition(_winSubHeadingText.getPosition().x + 35.0F, _winSubHeadingText.getPosition().y + 50.0F);
    _buttonPanels[MENU_BUTTON].SetPosition(_winSubHeadingText.getPosition().x + _winSubHeadingText.getGlobalBounds().width - _buttonPanels[MENU_BUTTON].GetTextSize().width - 35.0F, _winSubHeadingText.getPosition().y + 50.0F);
}

bool VictoryScene::InitMusic()
{
    if(!_winMusic.openFromFile("Resources/Audio/VictoryTheme/Fight_Or_Flight_30s.wav"))
    {
        std::cout << "Failed to to load lose scene soundtrack (Fight_Or_Flight_30s)" << std::endl;
        return false;
    }
    else
    {
        _winMusic.play();
        _winMusic.setLoop(true);
    }
}
