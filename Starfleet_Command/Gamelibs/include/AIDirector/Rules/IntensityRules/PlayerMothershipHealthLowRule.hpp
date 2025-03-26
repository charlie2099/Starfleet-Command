#ifndef STARFLEET_COMMAND_PLAYERMOTHERSHIPHEALTHLOWRULE_HPP
#define STARFLEET_COMMAND_PLAYERMOTHERSHIPHEALTHLOWRULE_HPP
#include "IDirectorIntensityRule.hpp"

class PlayerMothershipHealthLowRule : public IDirectorIntensityRule
{
public:
    PlayerMothershipHealthLowRule(float lowHealthThreshold, float intensityRating);
    float CalculatePerceivedIntensity(AiDirector& director) override;

private:
    float _lowHealthThreshold;
    float _intensityOutput;
};

#endif //STARFLEET_COMMAND_PLAYERMOTHERSHIPHEALTHLOWRULE_HPP
