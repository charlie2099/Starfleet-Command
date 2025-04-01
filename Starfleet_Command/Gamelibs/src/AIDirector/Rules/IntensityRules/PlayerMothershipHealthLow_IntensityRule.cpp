#include "AIDirector/Rules/IntensityRules/PlayerMothershipHealthLow_IntensityRule.hpp"
#include "AIDirector/AiDirector.hpp"

PlayerMothershipHealthLow_IntensityRule::PlayerMothershipHealthLow_IntensityRule(float lowHealthThreshold, float intensityRating)
        : _lowHealthThreshold(lowHealthThreshold), _intensityOutput(intensityRating) {}

float PlayerMothershipHealthLow_IntensityRule::CalculatePerceivedIntensity(AiDirector &director)
{
    if(director.GetPlayerMothershipHealth() <= _lowHealthThreshold)
    {
        std::cout << "[PlayerMothershipHealthLow_IntensityRule]: ACTIVE" << std::endl;
        return _intensityOutput;
    }
    return 0;
}