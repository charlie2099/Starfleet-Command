#ifndef STARFLEET_COMMAND_IDIRECTORBEHAVIOURRULE_HPP
#define STARFLEET_COMMAND_IDIRECTORBEHAVIOURRULE_HPP

class AiDirector;

// Rules that determine when the director should perform certain behaviours/actions
class IDirectorBehaviourRule
{
public:
    virtual ~IDirectorBehaviourRule() = default;
    virtual bool IsValid(AiDirector& director) = 0;
    virtual void Execute(AiDirector& director) = 0;
};

#endif //STARFLEET_COMMAND_IDIRECTORBEHAVIOURRULE_HPP
