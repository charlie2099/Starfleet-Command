#include "AIDirector/Rules/BehaviourRules/DeployRandomStarshipsPeriodically_BehaviourRule.hpp"
#include "AIDirector/AiDirector.hpp"

DeployRandomStarshipsPeriodically_BehaviourRule::DeployRandomStarshipsPeriodically_BehaviourRule(StarshipFactory::STARSHIP_TYPE starshipType, int behaviourUpdateChecksToWait, std::string ruleID, int rulePriority)
: _starshipType(starshipType), _behaviourUpdateChecksToWait(behaviourUpdateChecksToWait), _id(std::move(ruleID)), _priority(rulePriority)
{

}

bool DeployRandomStarshipsPeriodically_BehaviourRule::IsValid(AiDirector &director)
{
    return director.GetElapsedGameTime() >= _nextSpawnTime;
}

void DeployRandomStarshipsPeriodically_BehaviourRule::Execute(AiDirector &director)
{
    director.QueueEnemy(_starshipType, _randomLane.GenerateNumber());
    _nextSpawnTime += (director.GetBehaviourUpdateRate() * _behaviourUpdateChecksToWait);
}

