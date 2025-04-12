#include "AIDirector/Rules/IntensityRules/EnemyMothershipHealthLow_IntensityRule.hpp"
#include "AIDirector/AiDirector.hpp"

EnemyMothershipHealthLow_IntensityRule::EnemyMothershipHealthLow_IntensityRule(float lowHealthThreshold, float intensityRating)
: _lowHealthThreshold(lowHealthThreshold), _intensityOutput(intensityRating)
{
    std::cout << "[EnemyMothershipHealthLow_IntensityRule]: ACTIVE" << std::endl;
}

bool EnemyMothershipHealthLow_IntensityRule::IsValid(AiDirector &director)
{
    return director.GetEnemyMothershipHealth() <= _lowHealthThreshold;
}

float EnemyMothershipHealthLow_IntensityRule::CalculatePerceivedIntensity(AiDirector &director)
{
    return _intensityOutput;
}
