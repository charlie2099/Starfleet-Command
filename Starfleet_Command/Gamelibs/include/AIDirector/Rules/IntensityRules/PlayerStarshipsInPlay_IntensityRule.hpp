#ifndef STARFLEET_COMMAND_PLAYERSTARSHIPSINPLAY_INTENSITYRULE_HPP
#define STARFLEET_COMMAND_PLAYERSTARSHIPSINPLAY_INTENSITYRULE_HPP
#include "AIDirector/Rules/IntensityRules/IDirectorIntensityRule.hpp"

class PlayerStarshipsInPlay_IntensityRule: public IDirectorIntensityRule
{
public:
    explicit PlayerStarshipsInPlay_IntensityRule(float intensityRatingPerStarship);
    float CalculatePerceivedIntensity(AiDirector& director) override;

private:
    float _intensityOutput;
};

#endif //STARFLEET_COMMAND_PLAYERSTARSHIPSINPLAY_INTENSITYRULE_HPP
