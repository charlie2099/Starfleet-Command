#ifndef STARFLEET_COMMAND_MOTHERSHIPHEALTHLOWRULE_HPP
#define STARFLEET_COMMAND_MOTHERSHIPHEALTHLOWRULE_HPP
#include "IDirectorIntensityRule.hpp"

class MothershipHealthLowRule : public IDirectorIntensityRule
{
public:
    MothershipHealthLowRule(int a, int b) {}

    float CalculatePerceivedIntensity(AiDirector& director) override
    {
        return 0;
    }

private:
};

#endif //STARFLEET_COMMAND_MOTHERSHIPHEALTHLOWRULE_HPP
