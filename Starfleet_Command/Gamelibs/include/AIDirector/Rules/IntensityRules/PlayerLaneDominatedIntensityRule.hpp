//
// Created by William on 02/09/2025.
//

#ifndef PLAYERLANEDOMINATEDINTENSITYRULE_H
#define PLAYERLANEDOMINATEDINTENSITYRULE_H
#include "IDirectorIntensityRule.hpp"


class PlayerLaneDominatedIntensityRule : public IDirectorIntensityRule
{
public:
    explicit PlayerLaneDominatedIntensityRule(float intensityRatingPerStarship);
    bool IsValid(AiDirector& director) override;
    float CalculatePerceivedIntensity(AiDirector& director) override;
private:
    float _intensityOutput;

};



#endif //PLAYERLANEDOMINATEDINTENSITYRULE_H
