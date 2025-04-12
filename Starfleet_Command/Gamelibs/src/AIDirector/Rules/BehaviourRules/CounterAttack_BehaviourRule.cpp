#include "AIDirector/Rules/BehaviourRules/CounterAttack_BehaviourRule.hpp"
#include "AIDirector/AiDirector.hpp"

CounterAttack_BehaviourRule::CounterAttack_BehaviourRule(StarshipFactory::STARSHIP_TYPE starshipTypeToCounter, const std::vector<StarshipFactory::STARSHIP_TYPE>& counterStarshipTypes)
: _starshipTypeToCounter(starshipTypeToCounter), _counterStarshipTypes(counterStarshipTypes)
{
    std::cout << "[CounterAttack_BehaviourRule]: ACTIVE" << std::endl;
}

bool CounterAttack_BehaviourRule::IsValid(AiDirector &director)
{
    if(director.IsQueueFull())
    {
        return false;
    }

    bool isCounterStarshipAlreadyQueued = director.IsEnemyStarshipTypeInQueue(_counterStarshipTypes[0]);
    if(isCounterStarshipAlreadyQueued)
    {
        return false;
    }

    for (int spacelane = 0; spacelane < director.GetSpacelaneCount(); ++spacelane)
    {
        int numOfPlayerUnitTypesInLane = director.GetNumOfPlayerUnitTypesInSpacelane(spacelane, _starshipTypeToCounter);
        int numOfEnemyUnitTypesInLane = director.GetNumOfEnemyUnitTypesInSpacelane(spacelane, _counterStarshipTypes[0]);

        bool isTargetShipsToCounter = numOfPlayerUnitTypesInLane > 0;
        if(not isTargetShipsToCounter)
        {
            continue; // Skip to next iteration in loop
        }

        bool isNumOfEnemyUnitTypesLessThanPlayersInLane = numOfEnemyUnitTypesInLane < numOfPlayerUnitTypesInLane;
        if(isNumOfEnemyUnitTypesLessThanPlayersInLane)
        {
            _targetSpacelane = spacelane;
            return true;
        }
    }

    return false;
}

void CounterAttack_BehaviourRule::Execute(AiDirector &director)
{
    for (auto & counterStarshipType : _counterStarshipTypes)
    {
        director.QueueEnemy(counterStarshipType, _targetSpacelane);
    }
}

