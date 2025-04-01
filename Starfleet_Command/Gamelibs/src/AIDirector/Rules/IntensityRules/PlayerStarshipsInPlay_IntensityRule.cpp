#include "AIDirector/Rules/IntensityRules/PlayerStarshipsInPlay_IntensityRule.hpp"
#include "AIDirector/AiDirector.hpp"

PlayerStarshipsInPlay_IntensityRule::PlayerStarshipsInPlay_IntensityRule(float intensityRatingPerStarship)
        : _intensityOutput(intensityRatingPerStarship) {}

float PlayerStarshipsInPlay_IntensityRule::CalculatePerceivedIntensity(AiDirector &director)
{
    if(director.GetPlayerPopulation() > 1)
    {
        std::cout << "[PlayerStarshipsInPlay_IntensityRule]: ACTIVE" << std::endl;
        return _intensityOutput * (director.GetPlayerPopulation()-1.0F); // NOTE: Accounting for the player's mothership
    }
    return 0;
}