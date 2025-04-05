#ifndef STARFLEET_COMMAND_ENEMYSTARSHIPSINPLAY_INTENSITYRULE_HPP
#define STARFLEET_COMMAND_ENEMYSTARSHIPSINPLAY_INTENSITYRULE_HPP
#include "AIDirector/Rules/IntensityRules/IDirectorIntensityRule.hpp"

class EnemyStarshipsInPlay_IntensityRule : public IDirectorIntensityRule
{
public:
    explicit EnemyStarshipsInPlay_IntensityRule(float intensityRatingPerStarship);
    float CalculatePerceivedIntensity(AiDirector& director) override;

private:
    float _intensityOutput;
};

#endif //STARFLEET_COMMAND_ENEMYSTARSHIPSINPLAY_INTENSITYRULE_HPP
