#include "AIDirector/Rules/BehaviourRules/PlayerSpacelaneDominance_BehaviourRule.hpp"
#include "AIDirector/AiDirector.hpp"

PlayerSpacelaneDominance_BehaviourRule::PlayerSpacelaneDominance_BehaviourRule(int maxPlayerStarshipsInLane, int maxSpawnCount, std::string ruleID, int rulePriority)
: _numOfPlayerStarshipsInLaneThreshold(maxPlayerStarshipsInLane), _maxSpawnCount(maxSpawnCount), _id(std::move(ruleID)), _priority(rulePriority)
{}

bool PlayerSpacelaneDominance_BehaviourRule::IsValid(AiDirector &director)
{
    if(director.IsQueueFull())
    {
        return false;
    }

    bool isCounterStarshipAlreadyQueued = director.IsEnemyStarshipTypeInQueue(StarshipFactory::LIGHTFIGHTER);
    if(isCounterStarshipAlreadyQueued)
    {
        return false;
    }

    for (int spacelane = 0; spacelane < director.GetSpacelaneCount(); ++spacelane)
    {
        if(director.GetNumOfPlayerUnitsInSpacelane(spacelane) >= _numOfPlayerStarshipsInLaneThreshold)
        {
            if(director.GetNumOfEnemyUnitsInSpacelane(spacelane) < _numOfPlayerStarshipsInLaneThreshold)
            {
                _validLanes.push_back(spacelane);
            }
        }
    }

    return not _validLanes.empty();
}

void PlayerSpacelaneDominance_BehaviourRule::Execute(AiDirector &director)
{
    RNG spacelaneDominanceRNG;
    auto roll = spacelaneDominanceRNG.GenerateRandomRoll();

    switch (roll)
    {
        case RNG::PERFECT_ROLL:
        {
            for (int _validLane : _validLanes)
            {
                director.QueueEnemy(StarshipFactory::LIGHTFIGHTER, _validLane);
            }
        }
        break;
        case RNG::COMMON_ROLL:
        {
            for (int _validLane : _validLanes)
            {
                director.QueueEnemy(StarshipFactory::LIGHTFIGHTER, _validLane);
            }
        }
        break;
        case RNG::POOR_ROLL:
        {
            for (int _validLane : _validLanes)
            {
                director.QueueEnemy(StarshipFactory::LIGHTFIGHTER, _validLane);
            }
        }
        break;
    }
    _validLanes.clear();
}
