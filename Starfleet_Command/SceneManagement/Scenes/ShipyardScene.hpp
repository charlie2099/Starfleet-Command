#ifndef STARFLEET_COMMAND_SHIPYARDSCENE_HPP
#define STARFLEET_COMMAND_SHIPYARDSCENE_HPP
#include "../Scene.hpp"
#include "../../GameUI/ShipCard.hpp"
#include "../../Player/Player.hpp"
#include "../../Player/Fleet.hpp"

class ShipyardScene : public Scene
{
 public:
    ShipyardScene() = default;
    ~ShipyardScene() override = default;

    bool init() override;
    void eventHandler(sf::RenderWindow& window, sf::Event& event) override;
    void update(sf::RenderWindow &window, sf::Time deltaTime) override;
    void render(sf::RenderWindow& window) override;

 private:
    bool initBackground();
    void initTitleText();
    void initCreditsText();
    void initNotificationText();
    void initPanels();
    bool initMenuTitleIcon();
    void initShipCards();

    void playButtonActive(int i);
    void playButtonInactive(int i);
    void shipCardsActive(int i);
    void shipCardsInactive(int i);
    void shipCardsLeftClicked(int i);
    void shipCardsRightClicked(int i);

    static const int PLAY_BUTTON = 1;
    static const int FLEET_COLOUR = 2;
    static const int FLEET_SIZE = 3;

    int active_colour = 0;

    Constants utility;
    Player player;
    Fleet player_fleet;
    std::array<Panel, 3> panels;
    std::array<ShipCard, 4> ship_cards;

    std::array<std::string, 4> ship_names;
    std::array<std::string, 4> colours_text{};
    std::array<sf::Color, 4> colours_sf{};
    std::array<sf::Color, 4> colours_sf_light{};

    sf::Texture background_texture;
    sf::Texture ship_img_texture;

    sf::Sprite background_sprite;
    sf::Sprite ship_img_sprite;

    sf::Text shipyard_title_text;
    sf::Text credits_text;
    sf::Text notification_text;
};

#endif //STARFLEET_COMMAND_SHIPYARDSCENE_HPP
