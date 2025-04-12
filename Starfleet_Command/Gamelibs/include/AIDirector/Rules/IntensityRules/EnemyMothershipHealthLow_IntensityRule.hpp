#ifndef STARFLEET_COMMAND_ENEMYMOTHERSHIPHEALTHLOW_INTENSITYRULE_HPP
#define STARFLEET_COMMAND_ENEMYMOTHERSHIPHEALTHLOW_INTENSITYRULE_HPP
#include "IDirectorIntensityRule.hpp"

class EnemyMothershipHealthLow_IntensityRule : public IDirectorIntensityRule
{
public:
    EnemyMothershipHealthLow_IntensityRule(float lowHealthThreshold, float intensityRating);
    bool IsValid(AiDirector& director) override;
    float CalculatePerceivedIntensity(AiDirector& director) override;

private:
    float _lowHealthThreshold;
    float _intensityOutput;
};

#endif //STARFLEET_COMMAND_ENEMYMOTHERSHIPHEALTHLOW_INTENSITYRULE_HPP
