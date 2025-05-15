#ifndef STARFLEET_COMMAND_DIVERSION_BEHAVIOURRULE_HPP
#define STARFLEET_COMMAND_DIVERSION_BEHAVIOURRULE_HPP
#include "IDirectorBehaviourRule.hpp"
#include "Sprites/Starships/StarshipFactory.hpp"

class Diversion_BehaviourRule : public IDirectorBehaviourRule
{
public:
    Diversion_BehaviourRule(StarshipFactory::STARSHIP_TYPE starshipTypeToCounter, const std::vector<StarshipFactory::STARSHIP_TYPE>& counterStarshipTypes);
    bool IsValid(AiDirector &director) override;
    void Execute(AiDirector &director) override;

private:
    StarshipFactory::STARSHIP_TYPE _starshipTypeToCounter;
    std::vector<StarshipFactory::STARSHIP_TYPE> _counterStarshipTypes;
    int _targetSpacelane = 0;
};

#endif //STARFLEET_COMMAND_DIVERSION_BEHAVIOURRULE_HPP
