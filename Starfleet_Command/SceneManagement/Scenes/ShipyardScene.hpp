#ifndef STARFLEET_COMMAND_SHIPYARDSCENE_HPP
#define STARFLEET_COMMAND_SHIPYARDSCENE_HPP
#include "../Scene.hpp"
#include "../../GameUI/ShipCard.hpp"

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
    void initPanels();
    bool initMenuTitleIcon();
    void initShipCards();
    void playButtonActive(int i);
    void playButtonInactive(int i);
    void shipCardsActive(int i);
    void shipCardsInactive(int i);
    void shipCardsLeftClicked(int i);
    void shipCardsRightClicked(int i);

    Constants utility;

    std::array<Panel, 1> panels;
    std::array<ShipCard, 4> ship_cards;
    std::array<std::string, 4> button_text;
    std::array<int, 4> ship_count{};

    sf::Texture background_texture;
    sf::Texture ship_img_texture;

    sf::Sprite background_sprite;
    sf::Sprite ship_img_sprite;

    sf::Text shipyard_title;
};

#endif //STARFLEET_COMMAND_SHIPYARDSCENE_HPP
