#include "AIDirector/Rules/IntensityRules/EnemyMothershipHealthLow_IntensityRule.hpp"
#include "AIDirector/AiDirector.hpp"

EnemyMothershipHealthLow_IntensityRule::EnemyMothershipHealthLow_IntensityRule(float lowHealthThreshold, float intensityRating)
: _lowHealthThreshold(lowHealthThreshold), _intensityOutput(intensityRating) {}

float EnemyMothershipHealthLow_IntensityRule::CalculatePerceivedIntensity(AiDirector &director)
{
    if(director.GetEnemyMothershipHealth() <= _lowHealthThreshold)
    {
        std::cout << "[EnemyMothershipHealthLow_IntensityRule]: ACTIVE" << std::endl;
        return _intensityOutput;
    }
    return 0;
}
