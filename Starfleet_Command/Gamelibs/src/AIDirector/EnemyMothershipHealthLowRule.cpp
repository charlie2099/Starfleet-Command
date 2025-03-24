#include "AIDirector/EnemyMothershipHealthLowRule.hpp"
#include "AIDirector/AiDirector.hpp"

EnemyMothershipHealthLowRule::EnemyMothershipHealthLowRule(float lowHealthThreshold, float intensityRating)
: _lowHealthThreshold(lowHealthThreshold), _intensityOutput(intensityRating) {}

float EnemyMothershipHealthLowRule::CalculatePerceivedIntensity(AiDirector &director)
{
    if(director.GetEnemyMothershipHealth() <= _lowHealthThreshold)
    {
        std::cout << "[EnemyMothershipHealthLowRule]: LESS THAN THRESHOLD" << std::endl;
        return _intensityOutput;
    }
    return 0;
}
