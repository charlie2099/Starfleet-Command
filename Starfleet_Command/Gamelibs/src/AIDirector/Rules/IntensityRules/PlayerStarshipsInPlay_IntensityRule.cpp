#include "AIDirector/Rules/IntensityRules/PlayerStarshipsInPlay_IntensityRule.hpp"
#include "AIDirector/AiDirector.hpp"

PlayerStarshipsInPlay_IntensityRule::PlayerStarshipsInPlay_IntensityRule(float intensityRatingPerStarship)
        : _intensityOutput(intensityRatingPerStarship)
{
    std::cout << "[PlayerStarshipsInPlay_IntensityRule]: ACTIVE" << std::endl;
}

bool PlayerStarshipsInPlay_IntensityRule::IsValid(AiDirector &director)
{
    return director.GetPlayerPopulation() > 1;
}

float PlayerStarshipsInPlay_IntensityRule::CalculatePerceivedIntensity(AiDirector &director)
{
    return _intensityOutput * (director.GetPlayerPopulation()-1.0F); // NOTE: Accounting for the player's mothership
}