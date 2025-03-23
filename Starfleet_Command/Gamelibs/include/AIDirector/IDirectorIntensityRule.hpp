#ifndef STARFLEET_COMMAND_IDIRECTORINTENSITYRULE_HPP
#define STARFLEET_COMMAND_IDIRECTORINTENSITYRULE_HPP

// Forward declaration to avoid circular dependency issue
class AiDirector;

class IDirectorIntensityRule
{
public:
    virtual ~IDirectorIntensityRule() = default;
    virtual float CalculatePerceivedIntensity(AiDirector& director) = 0;
};

#endif //STARFLEET_COMMAND_IDIRECTORINTENSITYRULE_HPP
