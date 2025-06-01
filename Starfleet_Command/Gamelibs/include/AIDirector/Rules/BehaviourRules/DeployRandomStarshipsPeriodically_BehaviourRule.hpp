#ifndef STARFLEET_COMMAND_DEPLOYRANDOMSTARSHIPSPERIODICALLY_BEHAVIOURRULE_HPP
#define STARFLEET_COMMAND_DEPLOYRANDOMSTARSHIPSPERIODICALLY_BEHAVIOURRULE_HPP
#include "IDirectorBehaviourRule.hpp"
#include "Sprites/Starships/StarshipFactory.hpp"
#include "Utility/RNG.hpp"

/**
 * @brief Deploys a specified starship in a random lane at fixed intervals based on the Ai Director's behaviour update rate.
 *
 * Example: If _behaviourUpdateChecksToWait is set to 3, this rule will wait until the Ai Director's behaviour update check has been performed 3 times before executing.
 */
class DeployRandomStarshipsPeriodically_BehaviourRule : public IDirectorBehaviourRule
{
public:
    DeployRandomStarshipsPeriodically_BehaviourRule(StarshipFactory::STARSHIP_TYPE starshipType, int behaviourUpdateChecksToWait, std::string ruleID, int rulePriority);
    bool IsValid(AiDirector &director) override;
    void Execute(AiDirector &director) override;

    std::string GetID() override { return _id; }
    int GetPriority() override { return _priority; }

private:
    StarshipFactory::STARSHIP_TYPE _starshipType;
    RNG _randomLane { 0, 4 };
    float _nextSpawnTime = 0.0F;
    int _behaviourUpdateChecksToWait = 1;
    int _priority = 0;
    std::string _id;
};

#endif //STARFLEET_COMMAND_DEPLOYRANDOMSTARSHIPSPERIODICALLY_BEHAVIOURRULE_HPP
