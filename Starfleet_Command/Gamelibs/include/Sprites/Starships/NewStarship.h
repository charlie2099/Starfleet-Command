#ifndef STARFLEET_COMMAND_NEWSTARSHIP_H
#define STARFLEET_COMMAND_NEWSTARSHIP_H

class NewStarship
{
public:
    NewStarship() = default;
    NewStarship() = default;

    int GetMaxHealth() const { return _maxHealth; };
    std::string GetName() { return _name; };

private:
    StarshipClass starshipClass;
    std::string _name;
    int health
    // Command / Action / Behaviour?
    // Animation?
    // Audio?
};

#endif //STARFLEET_COMMAND_NEWSTARSHIP_H
