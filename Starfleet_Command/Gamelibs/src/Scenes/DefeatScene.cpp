#include "Scenes/DefeatScene.hpp"

DefeatScene::~DefeatScene()
{
    _loseMusic.stop();
}

bool DefeatScene::Init()
{
    InitView();
    InitBackground();
    InitLoseText();
    InitButtons();
    InitMusic();

    return true;
}

void DefeatScene::EventHandler(sf::RenderWindow &window, sf::Event &event)
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

void DefeatScene::Update(sf::RenderWindow &window, sf::Time deltaTime)
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

void DefeatScene::Render(sf::RenderWindow &window)
{
    window.setView(_worldView);
    _backgroundParallax->Render(window);
    for (auto& buttonPanel : _buttons)
    {
        buttonPanel.Render(window);
    }
    window.draw(_loseTitleText);
    window.draw(_loseSubHeadingText);
    _cursor.Render(window);
}

void DefeatScene::InitView()
{
    sf::Vector2f VIEW_SIZE = { Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT };
    sf::Vector2f WORLD_PERSPECTIVE = { Constants::WINDOW_WIDTH/2.0F, Constants::WINDOW_HEIGHT/2.0F };
    _worldView.setSize(VIEW_SIZE);
    _worldView.setCenter(WORLD_PERSPECTIVE);
}

bool DefeatScene::InitBackground()
{
    _backgroundParallax = std::make_unique<ParallaxBackground>(
            TEXTURES_DIR_PATH + "space_nebula_2.png",
            sf::Color::Red,
            Constants::WINDOW_WIDTH,
            Constants::WINDOW_HEIGHT,
            300,
            Chilli::Colour::LIGHTRED);

    return true;
}

void DefeatScene::InitLoseText()
{
    _loseTitleText.setFont(Chilli::CustomFonts::GetBoldFont());
    _loseTitleText.setString("DEFEAT");
    _loseTitleText.setCharacterSize(42);
    _loseTitleText.setFillColor(sf::Color::Red);
    _loseTitleText.setOutlineColor(sf::Color::Black);
    _loseTitleText.setOutlineThickness(1.0F);
    _loseTitleText.setPosition(Constants::WINDOW_WIDTH/2.0F - (_loseTitleText.getGlobalBounds().width/2.0F), Constants::WINDOW_HEIGHT/2.0F - (_loseTitleText.getGlobalBounds().height/2.0F) - 40.0F);

    _loseSubHeadingText.setFont(Chilli::CustomFonts::GetBoldFont());
    _loseSubHeadingText.setString("Thank you for playing Starfleet Command.");
    _loseSubHeadingText.setCharacterSize(18);
    _loseSubHeadingText.setFillColor(sf::Color::White);
    _loseSubHeadingText.setOutlineColor(sf::Color::Black);
    _loseSubHeadingText.setOutlineThickness(1.0F);
    _loseSubHeadingText.setPosition(_loseTitleText.getPosition().x + _loseTitleText.getGlobalBounds().width/2.0F - _loseSubHeadingText.getGlobalBounds().width/2.0F, _loseTitleText.getPosition().y + 65.0F);
}

void DefeatScene::InitButtons()
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
        _buttons[i].SetPosition(Constants::WINDOW_WIDTH * 0.185F, (Constants::WINDOW_HEIGHT * 0.57F) + static_cast<float>((i * (_buttons[i].GetPanelSize().height + 10))));
    }

    _buttons[PLAY_BUTTON].SetPosition(_loseSubHeadingText.getPosition().x + 35.0F, _loseSubHeadingText.getPosition().y + 50.0F);
    _buttons[MENU_BUTTON].SetPosition(_loseSubHeadingText.getPosition().x + _loseSubHeadingText.getGlobalBounds().width - _buttons[MENU_BUTTON].GetTextSize().width - 35.0F, _loseSubHeadingText.getPosition().y + 50.0F);
}

bool DefeatScene::InitMusic()
{
    if(!_loseMusic.openFromFile("Resources/Audio/DefeatTheme/Doomsday_Clock_112bpm_30s.wav"))
    {
        std::cout << "Failed to to load lose scene soundtrack (Doomsday_Clock_112bpm_30s)" << std::endl;
        return false;
    }
    else
    {
        _loseMusic.play();
        _loseMusic.setLoop(true);
    }
}
