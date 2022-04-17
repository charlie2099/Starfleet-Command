#ifndef STARFLEET_COMMAND_COMMANDMENU_HPP
#define STARFLEET_COMMAND_COMMANDMENU_HPP
#include "Panel.hpp"
#include "../Utility/Constants.hpp"
#include "../Utility/PredefinedColours.hpp"

class CommandMenu
{
 public:
    CommandMenu();
    ~CommandMenu() = default;

    enum class Command { NONE, SHOOT, ATTACK, DEFEND, FOLLOW, MOVETO, SELF_DESTRUCT };

    /// General
    void eventHandler(sf::RenderWindow& window, sf::Event& event);
    void update(sf::RenderWindow& window, sf::Time deltaTime);
    void render(sf::RenderWindow& window);

    /// Modifiers
    void setActive(bool active);

    /// Accessors
    Command &getCommand() { return command; };
    bool isActive() const;

 private:
    Command command{};
    Panel panel;
    std::array<std::unique_ptr<Button>, 1> button; // bad?
    PredefinedColours predef_colours;
    bool is_active_ = false;
};

#endif //STARFLEET_COMMAND_COMMANDMENU_HPP
