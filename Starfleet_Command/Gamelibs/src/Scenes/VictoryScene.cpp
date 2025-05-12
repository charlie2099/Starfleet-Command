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
    InitButtons();
    InitMusic();

    return true;
}

void VictoryScene::EventHandler(sf::RenderWindow &window, sf::Event &event)
{
    for (int i = 0; i < NUM_OF_BUTTONS; ++i)
    {
        _buttons[i].EventHandler(window, event);
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if(_buttons[PLAY_BUTTON].IsClicked())
        {
            SetScene(Scene::ID::GAME);
        }
        else if(_buttons[MENU_BUTTON].IsClicked())
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
        _buttons[i].Update(window);
    }

    if(_buttons[PLAY_BUTTON].IsMouseOver())
    {
        _buttons[PLAY_BUTTON].SetPanelColour(sf::Color(22, 155, 164, 65));
        _buttons[PLAY_BUTTON].SetText(_buttons[PLAY_BUTTON].GetText().getString(), sf::Color::Cyan);
        _cursor.SetCursorType(Chilli::Cursor::Type::HOVER);
    }
    else if(_buttons[MENU_BUTTON].IsMouseOver())
    {
        _buttons[MENU_BUTTON].SetPanelColour(sf::Color(22, 155, 164, 65));
        _buttons[MENU_BUTTON].SetText(_buttons[MENU_BUTTON].GetText().getString(), sf::Color::Cyan);
        _cursor.SetCursorType(Chilli::Cursor::Type::HOVER);
    }
    else
    {
        _cursor.SetCursorType(Chilli::Cursor::Type::DEFAULT);
    }

    for (int i = 0; i < NUM_OF_BUTTONS; i++)
    {
        if(!_buttons[i].IsMouseOver())
        {
            _buttons[i].SetPanelColour(sf::Color(22, 155, 164, 100));
            _buttons[i].SetText(_buttons[i].GetText().getString(), Chilli::Colour::LIGHTBLUE);
        }
    }

    _backgroundParallax->Update(window, deltaTime);
}

void VictoryScene::Render(sf::RenderWindow &window)
{
    window.setView(_worldView);
    _backgroundParallax->Render(window);
    for (auto& buttonPanel : _buttons)
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
    _backgroundParallax = std::make_unique<ParallaxBackground>(
            TEXTURES_DIR_PATH + "space_nebula_2.png",
            sf::Color::Green,
            Constants::WINDOW_WIDTH,
            Constants::WINDOW_HEIGHT,
            300,
            Chilli::Colour::LIGHTGREEN);

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

void VictoryScene::InitButtons()
{
    std::array<std::string, NUM_OF_BUTTONS> button_text
            {
                    "REMATCH",
                    "MAIN MENU"
            };

    for (int i = 0; i < NUM_OF_BUTTONS; ++i)
    {
        _buttons[i].SetText(button_text[i]);
        _buttons[i].SetTextSize(14);
        _buttons[i].SetSize(20, 15);
        _buttons[i].SetPanelColour(sf::Color(22, 155, 164, 100));
    }

    _buttons[PLAY_BUTTON].SetPosition(_winSubHeadingText.getPosition().x + 35.0F, _winSubHeadingText.getPosition().y + 50.0F);
    _buttons[MENU_BUTTON].SetPosition(_winSubHeadingText.getPosition().x + _winSubHeadingText.getGlobalBounds().width - _buttons[MENU_BUTTON].GetTextSize().width - 35.0F, _winSubHeadingText.getPosition().y + 50.0F);
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
