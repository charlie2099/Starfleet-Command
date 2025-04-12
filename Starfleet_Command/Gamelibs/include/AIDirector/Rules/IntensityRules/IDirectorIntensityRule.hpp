#ifndef STARFLEET_COMMAND_IDIRECTORINTENSITYRULE_HPP
#define STARFLEET_COMMAND_IDIRECTORINTENSITYRULE_HPP

class AiDirector;

// Rules that determine how intense the player might be finding the game, and dictate when the director should change state
class IDirectorIntensityRule
{
public:
    virtual ~IDirectorIntensityRule() = default;
    virtual bool IsValid(AiDirector& director) = 0;
    virtual float CalculatePerceivedIntensity(AiDirector& director) = 0;
};

#endif //STARFLEET_COMMAND_IDIRECTORINTENSITYRULE_HPP
