#ifndef STARFLEET_COMMAND_PLAYERSPACELANEDOMINANCE_BEHAVIOURRULE_HPP
#define STARFLEET_COMMAND_PLAYERSPACELANEDOMINANCE_BEHAVIOURRULE_HPP
#include "IDirectorBehaviourRule.hpp"

class PlayerSpacelaneDominance_BehaviourRule : public IDirectorBehaviourRule
{
public:
    explicit PlayerSpacelaneDominance_BehaviourRule(int maxPlayerStarshipsInLane, int maxSpawnCount);
    void ApplyBehaviour(AiDirector& director) override;

private:
    int _maxPlayerStarshipsInLane;
    int _maxSpawnCount;
    //RNG _randomWeakStarship { 0, 1 };
    //RNG _randomLane { 0, 4 };
};
#endif //STARFLEET_COMMAND_PLAYERSPACELANEDOMINANCE_BEHAVIOURRULE_HPP
