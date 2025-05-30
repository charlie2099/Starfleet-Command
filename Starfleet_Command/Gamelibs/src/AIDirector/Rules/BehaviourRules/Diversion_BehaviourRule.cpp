#include "AIDirector/Rules/BehaviourRules/Diversion_BehaviourRule.hpp"
#include "AIDirector/AiDirector.hpp"

Diversion_BehaviourRule::Diversion_BehaviourRule(StarshipFactory::STARSHIP_TYPE starshipTypeToCounter, const std::vector<StarshipFactory::STARSHIP_TYPE> &counterStarshipTypes, std::string ruleID, int rulePriority)
: _starshipTypeToCounter(starshipTypeToCounter), _counterStarshipTypes(counterStarshipTypes), _id(std::move(ruleID)), _priority(rulePriority)
{}

bool Diversion_BehaviourRule::IsValid(AiDirector &director)
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

    for (int spacelane = 1; spacelane < director.GetSpacelaneCount()-1; ++spacelane) /// Only checking the 3 middle lanes
    {
        int numOfPlayerUnitTypesInLane = director.GetNumOfPlayerUnitTypesInSpacelane(spacelane, _starshipTypeToCounter);

        bool isTargetShipsToCounter = numOfPlayerUnitTypesInLane > 0;
        if(! isTargetShipsToCounter)
        {
            continue; // Skip to next iteration in loop
        }

        _targetSpacelane = spacelane;
        return true;


        /*int numOfPlayerUnitTypesInLane = director.GetNumOfPlayerUnitTypesInSpacelane(spacelane, _starshipTypeToCounter);
        int numOfEnemyUnitTypesInLane = director.GetNumOfEnemyUnitTypesInSpacelane(spacelane, _counterStarshipTypes[0]);

        bool isTargetShipsToCounter = numOfPlayerUnitTypesInLane > 0;
        if(! isTargetShipsToCounter)
        {
            continue; // Skip to next iteration in loop
        }

        bool isNumOfEnemyUnitTypesLessThanPlayersInLane = numOfEnemyUnitTypesInLane < numOfPlayerUnitTypesInLane;
        if(isNumOfEnemyUnitTypesLessThanPlayersInLane)
        {
            _targetSpacelane = spacelane;
            return true;
        }*/
    }

    return false;
}

void Diversion_BehaviourRule::Execute(AiDirector &director)
{
    RNG counterAttackRNG;
    auto roll = counterAttackRNG.GenerateRandomRoll();

    switch (roll)
    {
        case RNG::PERFECT_ROLL:
        {
            director.QueueEnemy(_counterStarshipTypes[0], _targetSpacelane-1);
            director.QueueEnemy(_counterStarshipTypes[1], _targetSpacelane+1);
        }
        break;
        case RNG::COMMON_ROLL:
        {
            RNG topOrBottomLaneChance { 0, 1 };
            auto roll2 = topOrBottomLaneChance.GenerateNumber();

            if(roll2 == 0)
            {
                director.QueueEnemy(_counterStarshipTypes[0], _targetSpacelane-1);
            }
            else
            {
                director.QueueEnemy(_counterStarshipTypes[1], _targetSpacelane+1);
            }
        }
        break;
        case RNG::POOR_ROLL:
        {
            // Do nothing
        }
        break;
    }
}
