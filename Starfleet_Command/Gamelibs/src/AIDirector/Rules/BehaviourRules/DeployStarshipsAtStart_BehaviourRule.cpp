#include "AIDirector/Rules/BehaviourRules/DeployStarshipsAtStart_BehaviourRule.hpp"
#include "AIDirector/AiDirector.hpp"

DeployStarshipsAtStart_BehaviourRule::DeployStarshipsAtStart_BehaviourRule(int maxSpawnCount, StarshipFactory::STARSHIP_TYPE starshipType, std::string ruleID, int rulePriority)
: _maxSpawnCount(maxSpawnCount), _starshipType(starshipType), _id(std::move(ruleID)), _priority(rulePriority)
{
    RNG _randomSpawnCount {1, maxSpawnCount };
    _maxSpawnCount = _randomSpawnCount.GenerateNumber();
}

bool DeployStarshipsAtStart_BehaviourRule::IsValid(AiDirector &director)
{
    return !_hasRuleBeenExecuted;
}

void DeployStarshipsAtStart_BehaviourRule::Execute(AiDirector &director)
{
    for (int i = 0; i < _maxSpawnCount; ++i)
    {
        director.QueueEnemy(_starshipType, _randomLane.GenerateNumber());
    }
    _hasRuleBeenExecuted = true;
}