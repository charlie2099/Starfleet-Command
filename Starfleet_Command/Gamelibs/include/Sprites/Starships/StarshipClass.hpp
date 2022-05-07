#ifndef STARFLEET_COMMAND_STARSHIPCLASS_HPP
#define STARFLEET_COMMAND_STARSHIPCLASS_HPP

class StarshipClass
{
public:
    StarshipClass() = default;
    StarshipClass() = default;

    int GetMaxHealth() const { return _maxHealth; };
    std::string GetName() { return _name; };

private:
    std::string _name;
    int _maxHealth;
    // Command / Action / Behaviour?
    // Animation?
    // Audio?
    // Attack
    // Defense
};

#endif //STARFLEET_COMMAND_STARSHIPCLASS_HPP
