#ifndef STARFLEET_COMMAND_DIVERSION_BEHAVIOURRULE_HPP
#define STARFLEET_COMMAND_DIVERSION_BEHAVIOURRULE_HPP
#include "IDirectorBehaviourRule.hpp"
#include "Sprites/Starships/StarshipFactory.hpp"

/**
 * @brief Deploys starships into the lanes directly above and/or below that of the specified player starship type.
 *
 * Example: If starshipTypeToCounter is set to DREADNOUGHT, and the counterStarshipTypes contains LIGHTFIGHTER and HEAVYFIGHTER, the rule will deploy the latter mentioned starships into the lanes above and/or below lanes containing player dreadnoughts.
 */
class Diversion_BehaviourRule : public IDirectorBehaviourRule
{
public:
    Diversion_BehaviourRule(StarshipFactory::STARSHIP_TYPE starshipTypeToCounter, const std::vector<StarshipFactory::STARSHIP_TYPE>& counterStarshipTypes, std::string ruleID, int rulePriority);
    bool IsValid(AiDirector &director) override;
    void Execute(AiDirector &director) override;

    std::string GetID() override { return _id; }
    int GetPriority() override { return _priority; }

private:
    StarshipFactory::STARSHIP_TYPE _starshipTypeToCounter;
    std::vector<StarshipFactory::STARSHIP_TYPE> _counterStarshipTypes;
    int _targetSpacelane = 0;
    int _priority = 0;
    std::string _id;
};

#endif //STARFLEET_COMMAND_DIVERSION_BEHAVIOURRULE_HPP
