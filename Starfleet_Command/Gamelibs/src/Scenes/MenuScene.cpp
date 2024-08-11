#include "Scenes/MenuScene.hpp"

bool MenuScene::Init()
{
    std::mt19937 generator = GetEngine();
    InitView();
    InitBackground();
    InitButtonPanels();
    InitTitlePanel();
    InitMenuTitleIcon();
    InitBackgroundShips(generator);

    return true;
}

void MenuScene::EventHandler(sf::RenderWindow& window, sf::Event& event)
{
    for (int i = 0; i < BUTTONS; ++i)
    {
        panels[i].EventHandler(window, event);
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if(panels[PLAY_BUTTON].IsClicked())
        {
            SetScene(Scene::ID::GAME);
        }
        else if(panels[OPTIONS_BUTTON].IsClicked())
        {
            SetScene(Scene::ID::OPTIONS);
        }
        else if(panels[EXIT_BUTTON].IsClicked())
        {
            window.close();
        }
    }

    for (int i = 0; i < BUTTONS; ++i)
    {
        if(i < 2) // PLAY and OPTIONS button
            {
            if(panels[i].IsHoveredOver())
            {
                //panels[i].SetPanelColour(sf::Color(20, 210, 242, 60));
                panels[i].SetPanelColour(sf::Color(153, 210, 242, 80));
                panels[i].SetText(panels[i].GetText().getString(), sf::Color(153, 210, 242, 255));
            }
            }
        else // EXIT button
        {
            panels[i].SetPanelColour(sf::Color(242, 22, 22, 60));
            panels[i].SetText(panels[i].GetText().getString(), sf::Color::Red);
        }

        // All Buttons
        if(!panels[i].IsHoveredOver())
        {
            panels[i].SetPanelColour(sf::Color(75, 75, 75, 100));
            panels[i].SetText(panels[i].GetText().getString(), sf::Color::White);
        }
    }
}

void MenuScene::Update(sf::RenderWindow& window, sf::Time deltaTime)
{
    auto mouse_pos = sf::Mouse::getPosition(window); // Mouse _position relative to the window
    auto mousePosWorldCoords = window.mapPixelToCoords(mouse_pos, _worldView); // Mouse _position translated into world coordinates

    cursor.Update(window, deltaTime);
    cursor.SetCursorPos(window, _worldView);

    for (int i = 0; i < BUTTONS; ++i)
    {
        panels[i].Update(window);
    }
    for (auto & ship : starship)
    {
        ship->Update(window, deltaTime);
    }

    for (int i = 0; i < starship.size(); ++i)
    {
        // Ally ships
        if(i < BACKGROUND_SHIPS/2)
        {
            sf::Vector2f movement(starship[i]->GetSpeed()*2, 0.0f);
            starship[i]->GetSpriteComponent().GetSprite().move(movement * deltaTime.asSeconds());
        }
        // Enemy ships
        if(i >= BACKGROUND_SHIPS/2)
        {
            sf::Vector2f movement((starship[i]->GetSpeed()*2) * -1, 0.0f);
            starship[i]->GetSpriteComponent().GetSprite().move(movement * deltaTime.asSeconds());
        }

        if(starship[i]->GetSpriteComponent().GetPos().x >= Constants::WINDOW_WIDTH)
        {
            starship[i]->GetSpriteComponent().SetPos({0, starship[i]->GetSpriteComponent().GetPos().y});
        }
        else if(starship[i]->GetSpriteComponent().GetPos().x <= 0)
        {
            starship[i]->GetSpriteComponent().SetPos({Constants::WINDOW_WIDTH, starship[i]->GetSpriteComponent().GetPos().y});
        }
    }

    for (int i = 0; i < BACKGROUND_SHIPS/2; ++i)
    {
        if(Chilli::Vector::BoundsCheck(mousePosWorldCoords, starship[i]->GetSpriteComponent().GetSprite().getGlobalBounds()))
        {
            SELECTED_SHIP = i;
            //.snapTo(starship[SELECTED_SHIP]);
            cursor.SetCursorType(Chilli::Cursor::Type::SELECTED, sf::Color::Cyan);
            starship[i]->SetHealthBarVisibility(true);
            starship[i]->GetSpriteComponent().GetSprite().setColor(sf::Color::Cyan);
        }
        else if(!Chilli::Vector::BoundsCheck(mousePosWorldCoords,starship[SELECTED_SHIP]->GetSpriteComponent().GetSprite().getGlobalBounds()))
        {
            cursor.SetCursorType(Chilli::Cursor::DEFAULT, sf::Color::White);
            starship[i]->SetHealthBarVisibility(false);
            starship[i]->GetSpriteComponent().GetSprite().setColor(_predefinedColours.LIGHTBLUE);
        }
    }
}

void MenuScene::Render(sf::RenderWindow& window)
{
    window.setView(_worldView);
    window.draw(background_sprite);
    for (auto & ship : starship)
    {
        ship->Render(window);
    }
    window.draw(menu_title_img_sprite);
    for (auto & panel : panels)
    {
        panel.Render(window);
    }
    cursor.Render(window);
}

/// OTHER
std::mt19937 MenuScene::GetEngine()
{
    std::random_device eng;
    std::mt19937 generator(eng());
    unsigned long int time = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    generator.seed(time);
    return generator;
}

void MenuScene::InitView()
{
    sf::Vector2f VIEW_SIZE = { Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT };
    sf::Vector2f WORLD_PERSPECTIVE = { Constants::WINDOW_WIDTH/2.0F, Constants::WINDOW_HEIGHT/2.0F };
    _worldView.setSize(VIEW_SIZE);
    _worldView.setCenter(WORLD_PERSPECTIVE);
}

bool MenuScene::InitBackground()
{
    if (!background_texture.loadFromFile("Resources/Textures/space_nebula.png"))
    {
        return false;
    }
    background_texture.setRepeated(true);
    background_sprite.setTexture(background_texture);
    background_sprite.scale(0.2F, 0.2F);
    auto bTexSizeX = static_cast<int>(background_texture.getSize().x);
    auto bTexSizeY = static_cast<int>(background_texture.getSize().y);
    background_sprite.setTextureRect(sf::IntRect(0, 0, bTexSizeX*2, bTexSizeY*2));

    return true;
}

void MenuScene::InitButtonPanels()
{
    std::array<std::string, 3> button_text
    {
        "PLAY",
        "OPTIONS",
        "EXIT"
    };

    for (int i = 0; i < BUTTONS; ++i)
    {
        panels[i].SetText(button_text[i]);
        panels[i].SetTextSize(20);
        panels[i].SetSize(25,20);
        panels[i].SetPanelColour(sf::Color(75, 75, 75, 100));
        panels[i].SetPosition(Constants::WINDOW_WIDTH * 0.185F,
                              (Constants::WINDOW_HEIGHT * 0.57F) + static_cast<float>((i * (panels[i].GetPanelSize().height + 10))));
    }
}

void MenuScene::InitTitlePanel()
{
    for (int i = BUTTONS; i < TITLE_PANEL; ++i)
    {
        panels[i].SetText("Starfleet Command", sf::Color(153, 210, 242));
        panels[i].SetTextSize(85);
        panels[i].SetFont(Panel::TextFont::BOLD);
        panels[i].SetPanelColour(sf::Color(0, 0, 0, 0));
        panels[i].SetPosition(Constants::WINDOW_WIDTH * 0.5F - panels[i].GetTextSize().width / 2,
                              Constants::WINDOW_HEIGHT * 0.22F);
    }
}

bool MenuScene::InitMenuTitleIcon()
{
    if (!menu_title_img_texture.loadFromFile("Resources/Textures/starfleet_ship_0.png"))
    {
        return false;
    }
    menu_title_img_sprite.setTexture(menu_title_img_texture);
    menu_title_img_sprite.setColor(sf::Color(153, 210, 242, 175));
    menu_title_img_sprite.setScale(0.35F, 0.35F);
    menu_title_img_sprite.setRotation(-8);
    menu_title_img_sprite.setPosition(panels[4].GetTextPosition().x - 44, panels[4].GetTextPosition().y - 54);

    return true;
}

void MenuScene::InitBackgroundShips(std::mt19937 &generator)
{
    CreateDistribution("Ship xpos", 0, Constants::WINDOW_WIDTH);
    CreateDistribution("Ship ypos", 45, 675);
    CreateDistribution("Ship class", 0, 5);

    for (int i = 0; i < BACKGROUND_SHIPS; ++i)
    {
        int rand_x = uint_distrib[0](generator);
        int rand_y = uint_distrib[1](generator);
        int rand_ship = uint_distrib[2](generator);
        std::unique_ptr<IStarship> newStarship = StarshipFactory::CreateShip(static_cast<StarshipFactory::SHIP_TYPE>(rand_ship));
        starship.emplace_back(std::move(newStarship));
        starship[i]->GetSpriteComponent().GetSprite().setColor(sf::Color(153, 210, 242));
        starship[i]->GetSpriteComponent().SetPos({static_cast<float>(rand_x), static_cast<float>(rand_y)});

        if(i >= BACKGROUND_SHIPS/2)
        {
            starship[i]->GetSpriteComponent().GetSprite().setRotation(180);
            //starship[i]->GetSpriteComponent().GetSpriteComponent().setColor(sf::Color(247, 85, 85));
            starship[i]->GetSpriteComponent().GetSprite().setColor(sf::Color(91, 239, 170));
        }
    }
}

void MenuScene::CreateDistribution(const std::string& name, int min, int max)
{
    std::uniform_int_distribution<int> instance{min, max};
    uint_distrib.emplace_back(instance);
}


