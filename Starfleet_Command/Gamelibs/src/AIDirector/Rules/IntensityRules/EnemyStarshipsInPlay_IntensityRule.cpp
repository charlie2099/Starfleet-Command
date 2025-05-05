#include "AIDirector/Rules/IntensityRules/EnemyStarshipsInPlay_IntensityRule.hpp"
#include "AIDirector/AiDirector.hpp"

EnemyStarshipsInPlay_IntensityRule::EnemyStarshipsInPlay_IntensityRule(float intensityRatingPerStarship)
        : _intensityOutput(intensityRatingPerStarship)
{}

bool EnemyStarshipsInPlay_IntensityRule::IsValid(AiDirector &director)
{
    return director.GetEnemyPopulation() > 1;
}

float EnemyStarshipsInPlay_IntensityRule::CalculatePerceivedIntensity(AiDirector &director)
{
    return _intensityOutput * (director.GetEnemyPopulation()-1.0F); // NOTE: Accounting for the enemy's mothership
}