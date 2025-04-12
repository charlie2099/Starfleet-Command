#ifndef STARFLEET_COMMAND_PLAYERMOTHERSHIPHEALTHLOW_INTENSITYRULE_HPP
#define STARFLEET_COMMAND_PLAYERMOTHERSHIPHEALTHLOW_INTENSITYRULE_HPP
#include "IDirectorIntensityRule.hpp"

class PlayerMothershipHealthLow_IntensityRule : public IDirectorIntensityRule
{
public:
    PlayerMothershipHealthLow_IntensityRule(float lowHealthThreshold, float intensityRating);
    bool IsValid(AiDirector& director) override;
    float CalculatePerceivedIntensity(AiDirector& director) override;

private:
    float _lowHealthThreshold;
    float _intensityOutput;
};

#endif //STARFLEET_COMMAND_PLAYERMOTHERSHIPHEALTHLOW_INTENSITYRULE_HPP
