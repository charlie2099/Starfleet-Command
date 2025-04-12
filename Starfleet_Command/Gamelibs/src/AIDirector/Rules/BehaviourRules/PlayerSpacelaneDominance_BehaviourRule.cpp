#include "AIDirector/Rules/BehaviourRules/PlayerSpacelaneDominance_BehaviourRule.hpp"
#include "AIDirector/AiDirector.hpp"

PlayerSpacelaneDominance_BehaviourRule::PlayerSpacelaneDominance_BehaviourRule(int maxPlayerStarshipsInLane, int maxSpawnCount)
: _numOfPlayerStarshipsInLaneThreshold(maxPlayerStarshipsInLane), _maxSpawnCount(maxSpawnCount)
{
    std::cout << "[PlayerSpacelaneDominance_BehaviourRule]: ACTIVE" << std::endl;
}

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
    for (int _validLane : _validLanes)
    {
        director.QueueEnemy(StarshipFactory::LIGHTFIGHTER, _validLane);
    }
    _validLanes.clear();
}
