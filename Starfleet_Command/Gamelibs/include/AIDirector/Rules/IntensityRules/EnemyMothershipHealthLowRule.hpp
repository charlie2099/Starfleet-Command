#ifndef STARFLEET_COMMAND_ENEMYMOTHERSHIPHEALTHLOWRULE_HPP
#define STARFLEET_COMMAND_ENEMYMOTHERSHIPHEALTHLOWRULE_HPP
#include "IDirectorIntensityRule.hpp"

class EnemyMothershipHealthLowRule : public IDirectorIntensityRule
{
public:
    EnemyMothershipHealthLowRule(float lowHealthThreshold, float intensityRating);
    float CalculatePerceivedIntensity(AiDirector& director) override;

private:
    float _lowHealthThreshold;
    float _intensityOutput;
};

#endif //STARFLEET_COMMAND_ENEMYMOTHERSHIPHEALTHLOWRULE_HPP
