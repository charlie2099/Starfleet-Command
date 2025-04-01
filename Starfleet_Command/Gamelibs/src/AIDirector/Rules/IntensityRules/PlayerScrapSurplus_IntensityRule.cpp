#include "AIDirector/Rules/IntensityRules/PlayerScrapSurplus_IntensityRule.hpp"
#include "AIDirector/AiDirector.hpp"

PlayerScrapSurplus_IntensityRule::PlayerScrapSurplus_IntensityRule(int scrapAmount, float intensityRating)
        : _scrapAmount(scrapAmount), _intensityOutput(intensityRating) {}

float PlayerScrapSurplus_IntensityRule::CalculatePerceivedIntensity(AiDirector &director)
{
    if(director.GetPlayerScrapAmount() >= _scrapAmount)
    {
        std::cout << "[PlayerScrapSurplus_IntensityRule_IntensityRule]: ACTIVE" << std::endl;
        return _intensityOutput;
    }
    return 0;
}