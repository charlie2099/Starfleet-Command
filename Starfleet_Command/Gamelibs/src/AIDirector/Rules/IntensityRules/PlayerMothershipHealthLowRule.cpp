#include "AIDirector/Rules/IntensityRules/PlayerMothershipHealthLowRule.hpp"
#include "AIDirector/AiDirector.hpp"

PlayerMothershipHealthLowRule::PlayerMothershipHealthLowRule(float lowHealthThreshold, float intensityRating)
        : _lowHealthThreshold(lowHealthThreshold), _intensityOutput(intensityRating) {}

float PlayerMothershipHealthLowRule::CalculatePerceivedIntensity(AiDirector &director)
{
    if(director.GetPlayerMothershipHealth() == 10000)
    {
        std::cout << "[PlayerMothershipHealthLowRule]: LESS THAN THRESHOLD" << std::endl;
        return _intensityOutput;
    }
    return 0;
}