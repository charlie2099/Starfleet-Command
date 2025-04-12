#include "AIDirector/Rules/IntensityRules/PlayerMothershipHealthLow_IntensityRule.hpp"
#include "AIDirector/AiDirector.hpp"

PlayerMothershipHealthLow_IntensityRule::PlayerMothershipHealthLow_IntensityRule(float lowHealthThreshold, float intensityRating)
        : _lowHealthThreshold(lowHealthThreshold), _intensityOutput(intensityRating)
{
    std::cout << "[PlayerMothershipHealthLow_IntensityRule]: ACTIVE" << std::endl;
}

bool PlayerMothershipHealthLow_IntensityRule::IsValid(AiDirector &director)
{
    return director.GetPlayerMothershipHealth() <= _lowHealthThreshold;
}

float PlayerMothershipHealthLow_IntensityRule::CalculatePerceivedIntensity(AiDirector &director)
{
    return _intensityOutput;
}