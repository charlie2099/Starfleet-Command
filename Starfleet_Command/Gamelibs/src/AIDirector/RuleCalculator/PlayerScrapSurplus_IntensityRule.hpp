#ifndef STARFLEET_COMMAND_PLAYERSCRAPSURPLUS_INTENSITYRULE_HPP
#define STARFLEET_COMMAND_PLAYERSCRAPSURPLUS_INTENSITYRULE_HPP
#include "AIDirector/Rules/IntensityRules/IDirectorIntensityRule.hpp"

class PlayerScrapSurplus_IntensityRule: public IDirectorIntensityRule
{
public:
    PlayerScrapSurplus_IntensityRule(int scrapAmount, float intensityRating);
    float CalculatePerceivedIntensity(AiDirector& director) override;

private:
    int _scrapAmount;
    float _intensityOutput;
};

#endif //STARFLEET_COMMAND_PLAYERSCRAPSURPLUS_INTENSITYRULE_HPP
