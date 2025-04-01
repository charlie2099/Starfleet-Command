#include "AIDirector/Rules/IntensityRules/EnemyStarshipsInPlay_IntensityRule.hpp"
#include "AIDirector/AiDirector.hpp"

EnemyStarshipsInPlay_IntensityRule::EnemyStarshipsInPlay_IntensityRule(float intensityRatingPerStarship)
        : _intensityOutput(intensityRatingPerStarship) {}

float EnemyStarshipsInPlay_IntensityRule::CalculatePerceivedIntensity(AiDirector &director)
{
    if(director.GetEnemyPopulation() > 1)
    {
        std::cout << "[EnemyStarshipsInPlay_IntensityRule]: ACTIVE" << std::endl;
        return _intensityOutput * (director.GetEnemyPopulation()-1.0F); // NOTE: Accounting for the enemy's mothership
    }
    return 0;
}