//
// Created by William on 02/09/2025.
//

#include "AIDirector/Rules/IntensityRules/PlayerLaneDominatedIntensityRule.hpp"
#include "AIDirector/AiDirector.hpp"

PlayerLaneDominatedIntensityRule::PlayerLaneDominatedIntensityRule(float intensityRatingPerStarship)
    : _intensityOutput(intensityRatingPerStarship)
{}

bool PlayerLaneDominatedIntensityRule::IsValid(AiDirector &director)
{
    for(int lane = 0; lane <= director.GetSpacelaneCount(); lane ++)
    {
        if (director.GetNumOfEnemyUnitsInSpacelane(lane) > 2)
        {
            return true;
        }
    }
    return false;
}

float PlayerLaneDominatedIntensityRule::CalculatePerceivedIntensity(AiDirector &director)
{
    return _intensityOutput;
}
