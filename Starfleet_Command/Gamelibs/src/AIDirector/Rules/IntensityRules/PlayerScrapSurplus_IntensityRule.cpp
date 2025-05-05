#include "AIDirector/Rules/IntensityRules/PlayerScrapSurplus_IntensityRule.hpp"
#include "AIDirector/AiDirector.hpp"

PlayerScrapSurplus_IntensityRule::PlayerScrapSurplus_IntensityRule(int scrapAmount, float intensityRating)
        : _scrapAmount(scrapAmount), _intensityOutput(intensityRating)
{}

bool PlayerScrapSurplus_IntensityRule::IsValid(AiDirector &director)
{
    return director.GetPlayerScrapAmount() >= _scrapAmount;
}

float PlayerScrapSurplus_IntensityRule::CalculatePerceivedIntensity(AiDirector &director)
{
    return _intensityOutput;
}