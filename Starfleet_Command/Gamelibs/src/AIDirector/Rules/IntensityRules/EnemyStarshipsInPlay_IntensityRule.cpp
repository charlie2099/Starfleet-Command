#include "AIDirector/Rules/IntensityRules/EnemyStarshipsInPlay_IntensityRule.hpp"
#include "AIDirector/AiDirector.hpp"

EnemyStarshipsInPlay_IntensityRule::EnemyStarshipsInPlay_IntensityRule(float intensityRatingPerStarship)
        : _intensityOutput(intensityRatingPerStarship)
{
    std::cout << "[EnemyStarshipsInPlay_IntensityRule]: ACTIVE" << std::endl;
}

float EnemyStarshipsInPlay_IntensityRule::CalculatePerceivedIntensity(AiDirector &director)
{
    if(director.GetEnemyPopulation() > 1)
    {
        return _intensityOutput * (director.GetEnemyPopulation()-1.0F); // NOTE: Accounting for the enemy's mothership
    }
    return 0;
}