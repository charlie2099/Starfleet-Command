#ifndef STARFLEET_COMMAND_DEPLOYSTARSHIPSATSTART_BEHAVIOURRULE_HPP
#define STARFLEET_COMMAND_DEPLOYSTARSHIPSATSTART_BEHAVIOURRULE_HPP
#include "IDirectorBehaviourRule.hpp"
#include "Sprites/Starships/StarshipFactory.hpp"
#include "Utility/RNG.hpp"

/**
 * @brief Deploys a random number of the specified starship into random lanes at the start of the game, upon the Ai Director's first behaviour update check.
 *
 * Example: If maxSpawnCount is set to 3, up to 3 starships may be spawned. This rule is executed only once.
 */
class DeployStarshipsAtStart_BehaviourRule : public IDirectorBehaviourRule
{
public:
    explicit DeployStarshipsAtStart_BehaviourRule(int maxSpawnCount, StarshipFactory::STARSHIP_TYPE starshipType, std::string ruleID, int rulePriority);
    bool IsValid(AiDirector& director) override;
    void Execute(AiDirector& director) override;

    std::string GetID() override { return _id; }
    int GetPriority() override { return _priority; }

private:
    bool _hasRuleBeenExecuted = false;
    int _maxSpawnCount = 2;
    StarshipFactory::STARSHIP_TYPE _starshipType;
    RNG _randomLane { 0, 4 };
    int _priority = 0;
    std::string _id;
};

#endif //STARFLEET_COMMAND_DEPLOYSTARSHIPSATSTART_BEHAVIOURRULE_HPP
